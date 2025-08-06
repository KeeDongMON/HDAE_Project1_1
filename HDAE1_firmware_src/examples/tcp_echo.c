#include <examples/tcp_echo.h>
#include <string.h>
#include "lwip/opt.h"
#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"
#include "my_stdio.h"

#define STORAGE_SIZE_BYTES 256          /* Size in bytes of the space in memory allocated for storing incoming data */

enum TcpEchoStates                      /* States of the session with the remote user                               */
{
    ES_NONE = 0,                        /* Session not completely initialized                                       */
    ES_ACCEPTED,                        /* Session assigned to a remote client and resources are being allocated    */
    ES_RECEIVING,                       /* Session is receiving data sent from remote client                        */
    ES_CLOSING                          /* Session is being closed and assigned resources will be deallocated       */
};

typedef struct tcp_pcb tcpPcb;          /* Define a more convenient type                                            */
typedef struct pbuf pBuf;               /* Define a more convenient type                                            */

typedef struct                          /* Session data structure used for communicating with a single remote client*/
{
    u8_t state;                         /* The current state for the session                                        */
    tcpPcb *pcb;                        /* Pointer to the TCP protocol control block used for this session          */
    pBuf *p;                            /* Pointer to the packet buffers used to store received packets             */
    char storage[STORAGE_SIZE_BYTES];   /* Storage for the received strings                                         */
    uint16 nextFreeStoragePos;          /* Position of the next free position in the storage array                  */
} TcpEchoSession;


tcpPcb *g_tcpEchoPcb;                   /* Pointer to the TCP protocol control block    */

err_t echoAccept (void *arg, tcpPcb *newPcb, err_t err);            /* Accept callback is called every time a client establishes a new connection                   */
err_t echoRecv (void *arg, tcpPcb *tpcb, pBuf *p, err_t err);       /* Recv callback is called every time data is received through the TCP connection               */
void echoError (void *arg, err_t err);                              /* Error callback is called if a fatal error has already occurred on the connection             */
err_t echoPoll (void *arg, tcpPcb *tpcb);                           /* Poll function is called periodically by the TCP stack                                        */
err_t echoSent (void *arg, tcpPcb *tpcb, u16_t len);                /* Sent callback is called when TCP data has successfully been delivered to the remote host     */
void echoSend (tcpPcb *tPcb, TcpEchoSession *es);                   /* Send function enqueues TCP data to be delivered to the remote client                         */
void echoUnpack (tcpPcb *tPcb, TcpEchoSession *es);                 /* Unpack function dequeues data from the package buffer and copies it in the session storage   */
void echoClose (tcpPcb *tPcb, TcpEchoSession *es);                  /* Close function closes a TCP connection and deallocates session resources                     */

void TcpEchoInit(void)
{
    g_tcpEchoPcb = tcp_new(); /* Create a new TCP protocol control block */
    if (g_tcpEchoPcb != NULL) /* If the creation was successful... */
    {
        err_t err = tcp_bind(g_tcpEchoPcb, IP_ADDR_ANY, 80); /* ...bind the TCP procotol control block to any local address and local port 80. */
        if (err == ERR_OK) /* If the binding was successful... */
        {
            g_tcpEchoPcb = tcp_listen(g_tcpEchoPcb); /* ...set the TCP control block able to accept incoming connections. */
            tcp_accept(g_tcpEchoPcb, echoAccept); /* Configure the callback function to be called when a new connection is established. */
        }
        else
        {
            LWIP_DEBUGF(ECHO_DEBUG | LWIP_DBG_STATE, ("Echo: unable to bind to any address on port 80.\n"));
        }
    }
    else
    {
        LWIP_DEBUGF(ECHO_DEBUG | LWIP_DBG_STATE, ("Echo: unable to create a TCP control block.\n"));
    }
}

/* Accept callback: it is called every time a client establish a new connection */
err_t echoAccept(void *arg, tcpPcb *newPcb, err_t err)
{
    LWIP_UNUSED_ARG(arg);                                               /* Eliminate compiler warning about unused arguments                                        */
    LWIP_UNUSED_ARG(err);                                               /* Eliminate compiler warning about unused arguments                                        */

    err_t retErr;                                                       /* Allocate memory for function return value                                                */
    TcpEchoSession *es = (TcpEchoSession*) mem_malloc(sizeof(TcpEchoSession));   /* Allocate memory for the session data                                                     */
    if (es != NULL)                                                     /* If memory allocation was successful the session can be initialized                       */
    {
        es->state = ES_ACCEPTED;                                        /* The new session has been accepted                                                        */
        es->pcb = newPcb;                                               /* A pointer to the TCP control block to use for this session is saved in the session       */
        es->p = NULL;                                                   /* The packet buffer for received data is initially empty                                   */
        memset(es->storage, 0, STORAGE_SIZE_BYTES);                     /* Allocate memory for storing processed received data                                      */
        es->nextFreeStoragePos = 0;                                     /* The first free position in the received data array is the beginning of the array         */

        tcp_arg(newPcb, es);                                            /* Specify that the session shall be passed as argument to every callback function          */
        tcp_recv(newPcb, echoRecv);                                     /* Configure the callback function to be called when new data is received                   */
        tcp_sent(newPcb, echoSent);                                     /* Configure the callback function to be called when new data is sent                       */
        tcp_err(newPcb, echoError);                                     /* Configure the callback function to be called when a fatal connection error occurs        */
        tcp_poll(newPcb, echoPoll, 0);                                  /* Configure the callback function to be periodically called by TCP
                                                                         * The time interval is specified as multiple of the TCP coarse timer interval, which is
                                                                         * called twice a second                                                                    */
        retErr = ERR_OK;                                                /* Set the return value when no error occured                                               */

        my_printf("New TCP connection accepted!\n");
    }
    else                                                                /* If it was not possible to allocate the necessary memory for the session...               */
    {
        retErr = ERR_MEM;                                               /* ... set the return value to "Out of memory".                                             */
    }
    return retErr;                                                      /* Return result                                                                            */
}

/* Recv callback: it is called every time data is received through the TCP connection */
err_t echoRecv (void *arg, tcpPcb *tpcb, pBuf *p, err_t err)
{
    err_t retErr;                                                       /* Allocate memory for function return value                                                */
    TcpEchoSession *es = (TcpEchoSession*) arg;                               /* Get a pointer to the current session                                                     */

    if (p == NULL)                                                      /* If there is no enqueued received data after the RECV callback was called, it means the   */
    {                                                                   /* remote client closed the connection in the meanwhile                                     */
        es->state = ES_CLOSING;                                         /* Set the state of this session to CLOSING in order to free its resources                  */
        if (es->p == NULL)                                              /* If the session does not have any leftover unprocessed data...                            */
        {
            echoClose(tpcb, es);                                        /* ... close the session and free its resources.                                            */
        }
        else                                                            /* If the session does have leftover unprocessed data...                                    */
        {
            echoUnpack(tpcb, es);                                       /* ... process unprocessed data ...                                                         */
            echoSend(tpcb, es);                                         /* ... and send processed data.                                                             */
        }
        retErr = ERR_OK;                                                /* Signal a successful outcome                                                              */
    }
    else if (err != ERR_OK)                                             /* If there was an error while receiving data...                                            */
    {
        /* Cleanup, for unkown reason */
        if (p != NULL)                                                  /* ... if some data was received and stored...                                              */
        {
            es->p = NULL;                                               /* ... invalidate the unprocessed data contained in the session.                            */
            pbuf_free(p);                                               /* Dereference and deallocate last received data which is probably corrupted                */
        }
        retErr = err;                                                   /* Propagate the error                                                                      */
    }
    else if (es->state == ES_ACCEPTED)                                  /* If the current session is in state ACCEPTED...                                           */
    {
        es->state = ES_RECEIVING;                                       /* ... change its state to RECEIVING.                                                       */
        es->p = p;                                                      /* Set the unprocessed data buffer of the session to the received one                       */
        echoUnpack(tpcb, es);                                           /* Perform a first incoming data processing                                                 */
        echoSend(tpcb, es);                                             /* Send the first echo to remote client                                                     */
        retErr = ERR_OK;                                                /* Signal a successful outcome                                                              */
    }
    else if (es->state == ES_RECEIVING)                                 /* If the current session was already receiving data...                                     */
    {
        if (es->p == NULL)                                              /* ... and no unprocessed data is contained in the session...                               */
        {
            es->p = p;                                                  /* ... set the unprocessed data buffer of the session to the received one                   */
            echoUnpack(tpcb, es);                                       /* Process the incoming data                                                                */
            echoSend(tpcb, es);                                         /* Send an echo to the remote client                                                        */
        }
        else                                                            /* If the session still contains some unprocessed received data...                          */
        {
            pBuf *ptr = es->p;                                          /* ... create a local reference for the received data                                       */
            pbuf_chain(ptr, p);                                         /* Chain the old unprocessed data contained in the session with the new one                 */
        }
        retErr = ERR_OK;                                                /* Signal a successful outcome                                                              */
    }
    else                                                                /* If we got new incoming data in an unknown state, discard the data                        */
    {
        tcp_recved(tpcb, p->tot_len);                                   /* Mark the incoming data as received                                                       */
        es->p = NULL;                                                   /* Invalidate the unprocessed data contained in the session                                 */
        pbuf_free(p);                                                   /* Dereference and deallocate last received data                                            */
        retErr = ERR_OK;                                                /* Signal a successful outcome                                                              */
    }
    return retErr;                                                      /* Return result                                                                            */
}

/* Error callback: it is called if a fatal error has already occurred on the connection */
void echoError(void *arg, err_t err)
{
    LWIP_UNUSED_ARG(err);                                               /* Eliminate compiler warning about unused arguments                                        */

    TcpEchoSession *es = (TcpEchoSession*) arg;                               /* Get a pointer to the current session                                                     */

    if (es != NULL)                                                     /* If a session exists we cannot do anything with it anymore, since the fatal error         */
    {                                                                   /* occurred ...                                                                             */
        mem_free(es);                                                   /* ... free memory assigned to the session                                                  */
    }
}

/* Poll function: it is called periodically by the TCP stack */
err_t echoPoll(void *arg, tcpPcb *tpcb)
{
    err_t retErr;                                                       /* Allocate memory for function return value                                                */
    TcpEchoSession *es = (TcpEchoSession*) arg;                               /* Get a pointer to the current session                                                     */

    if (es != NULL)                                                     /* If a session exists ...                                                                  */
    {
        if (es->p != NULL ||                                            /* ... and if the session has any leftover unprocessed data...                              */
            es->nextFreeStoragePos != 0)                                /* ... or there is still data in the session storage to send back...                        */
        {
            echoUnpack(tpcb, es);                                       /* ... process unprocessed data ...                                                         */
            echoSend(tpcb, es);                                         /* ... and send processed data.                                                             */
        }
        else                                                            /* If the session has no leftover unprocessed data...                                       */
        {
            if (es->state == ES_CLOSING)                                /* ... and the session was marked for being closed...                                       */
            {
                echoClose(tpcb, es);                                    /* ... close the session and free its resources.                                            */
            }
        }
        retErr = ERR_OK;                                                /* Signal a successful outcome                                                              */
    }
    else                                                                /* If no session exists something went wrong, the TCP connection has to be aborted          */
    {
        tcp_abort(tpcb);                                                /* Abort the TCP connection                                                                 */
        retErr = ERR_ABRT;                                              /* Propagate the abort error                                                                */
    }
    return retErr;                                                      /* Return result                                                                            */
}

/* Sent callback: it is called when TCP data has successfully been delivered to the remote host */
err_t echoSent(void *arg, tcpPcb *tpcb, u16_t len)
{
    LWIP_UNUSED_ARG(len);                                               /* Eliminates compiler warning about unused arguments                                       */

    TcpEchoSession *es = (TcpEchoSession*) arg;                               /* Get a pointer to the current session                                                     */

    if (es->p != NULL )                                                 /* If the session has any leftover unprocessed data...                                      */
    {
        echoUnpack(tpcb, es);                                           /* ... process unprocessed data ...                                                         */
        echoSend(tpcb, es);                                             /* ... and send processed data.                                                             */
    }
    else                                                                /* If the session has no leftover unprocessed data...                                       */
    {
        if (es->state == ES_CLOSING)                                    /* ... and the session was marked for being closed...                                       */
        {
            echoClose(tpcb, es);                                        /* ... close the session and free its resources.                                            */
        }
    }
    return ERR_OK;                                                      /* Return successful result                                                                 */
}

/* Send function: enqueues TCP data to be delivered to the remote client */
void echoSend(tcpPcb *tpcb, TcpEchoSession *es)
{
    if(es->nextFreeStoragePos == 0)                                     /* If the next free position in the storage array is the beginning of the array, there is   */
    {                                                                   /* nothing to send                                                                          */
        return;
    }

    err_t wrErr = tcp_write(tpcb, es->storage, es->nextFreeStoragePos, 1);                     /* Enqueue an echo preamble to be sent to the remote client          */
    if(wrErr == ERR_OK)                                                 /* If data was correctly enqueued for TCP transmission ...                                  */
    {
        es->nextFreeStoragePos = 0;                                     /* ... remove sent data from the session storage.                                           */
    }
}

/* Unpack function: dequeues data from the package buffer and copies it in the session storage */
void echoUnpack(tcpPcb *tpcb, TcpEchoSession *es)
{
    pBuf *ptr;                                                          /* Local reference to a packet buffer                                                       */

    while ((es->p != NULL))                                             /* Process data while there still are packets to process                                    */
    {
        ptr = es->p;                                                    /* Local reference of the packet to process                                                 */

        if (es->nextFreeStoragePos + ptr->len <= STORAGE_SIZE_BYTES)    /* If there is enough space in the session storage for the new data ...                     */
        {
            memcpy(&es->storage[es->nextFreeStoragePos],                /* ... copy data in the session storage                                                     */
                    ptr->payload,
                    ptr->len);
            es->nextFreeStoragePos += ptr->len;                         /* Increase the index of the new free position in the session storage array                 */

            u16_t plen = ptr->len;                                      /* Number of bytes successfully received and stored                                         */

            es->p = ptr->next;                                          /* Get the next packet in the chain (if any)                                                */
            if (es->p != NULL)                                          /* If there is another packet to be processed...                                            */
            {
                pbuf_ref(es->p);                                        /* Inform the LwIP framework that the packet to be processed is linked to the session,      */
            }                                                           /* and shall not be disposed                                                                */

            u8_t freed;                                                 /* Number of bytes successfully freed from memory                                           */
            do
            {
                freed = pbuf_free(ptr);                                 /* Free memory used by the packet that was just processed                                   */
            } while (freed == 0);

            tcp_recved(tpcb, plen);                                     /* Signal the remote host that more data can be received                                    */
        }
    }
}

/* Close function: closes a TCP connection and deallocates session resources */
void echoClose(tcpPcb *tpcb, TcpEchoSession *es)
{
    tcp_arg(tpcb, NULL);                                                /* Set the argument passed to every callback to NULL                                        */
    tcp_sent(tpcb, NULL);                                               /* Set the data sent callback to NULL                                                       */
    tcp_recv(tpcb, NULL);                                               /* Set the data received callback to NULL                                                   */
    tcp_err(tpcb, NULL);                                                /* Set the data error callback to NULL                                                      */
    tcp_poll(tpcb, NULL, 0);                                            /* Set the periodical callback to NULL                                                      */

    if (es != NULL)                                                     /* If a session still exists...                                                             */
    {
        mem_free(es);                                                   /* ...free memory assigned to the session.                                                  */
    }
    tcp_close(tpcb);                                                    /* Close the TCP connection                                                                 */
}
