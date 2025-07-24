#include "lwip/opt.h"
#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"
#include "string.h"
#include "DoIP.h"
#include "Ultrasonic.h"
#include "evadc.h"

#if LWIP_TCP

static struct tcp_pcb *doip_pcb;

enum doip_states
{
	ES_NONE = 0,
	ES_ACCEPTED,
	ES_RECEIVED,
	ES_CLOSING
};

struct doip_state
{
	u8_t state;
	u8_t retries;
	struct tcp_pcb *pcb;
	/* pbuf (chain) to recycle */
	struct pbuf *p;
};

err_t doip_accept(void *arg, struct tcp_pcb *newpcb, err_t err);
err_t doip_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
void doip_error(void *arg, err_t err);
err_t doip_poll(void *arg, struct tcp_pcb *tpcb);
err_t doip_sent(void *arg, struct tcp_pcb *tpcb, u16_t len);
void doip_send(struct tcp_pcb *tpcb, struct doip_state *es);
void doip_close(struct tcp_pcb *tpcb, struct doip_state *es);

#define UDS_PORT 13400

void DoIP_Init(void)
{
	doip_pcb = tcp_new();
	if (doip_pcb != NULL) {
		err_t err;

		err = tcp_bind(doip_pcb, IP_ADDR_ANY, UDS_PORT);
		if (err == ERR_OK) {
			doip_pcb = tcp_listen(doip_pcb);
			tcp_accept(doip_pcb, doip_accept);
		} else {
			/* abort? output diagnostic? */
		}
	} else {
		/* abort? output diagnostic? */
	}
}

err_t doip_accept(void *arg, struct tcp_pcb *newpcb, err_t err)
{
	err_t ret_err;
	struct doip_state *es;

	LWIP_UNUSED_ARG(arg);
	LWIP_UNUSED_ARG(err);
//	LWIP_DEBUGF(ECHO_DEBUG, ("doip_accept\n"));

	/* Unless this pcb should have NORMAL priority, set its priority now.
	 When running out of pcbs, low priority pcbs can be aborted to create
	 new pcbs of higher priority. */
	tcp_setprio(newpcb, TCP_PRIO_MIN);

	es = (struct doip_state*) mem_malloc(sizeof(struct doip_state));
	if (es != NULL) {
		es->state = ES_ACCEPTED;
		es->pcb = newpcb;
		es->retries = 0;
		es->p = NULL;
		/* pass newly allocated es to our callbacks */
		tcp_arg(newpcb, es);
		tcp_recv(newpcb, doip_recv);
		tcp_err(newpcb, doip_error);
		tcp_poll(newpcb, doip_poll, 0);
		ret_err = ERR_OK;
		es->state = ES_RECEIVED;
	} else {
		ret_err = ERR_MEM;
	}
	return ret_err;
}

err_t doip_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
	struct doip_state *es;
	err_t ret_err;

	LWIP_ASSERT("arg != NULL", arg != NULL);
//	LWIP_DEBUGF(ECHO_DEBUG, ("doip_recv\n"));
	es = (struct doip_state*) arg;
	if (p == NULL) {
		/* remote host closed connection */
		es->state = ES_CLOSING;
		if (es->p == NULL) {
			/* we're done sending, close it */
			doip_close(tpcb, es);
		} else {
			/* we're not done yet */
			tcp_sent(tpcb, doip_sent);
			doip_send(tpcb, es);
		}
		ret_err = ERR_OK;
	} else if (err != ERR_OK) {
		/* cleanup, for unkown reason */
		if (p != NULL) {
			es->p = NULL;
			pbuf_free(p);
		}
		ret_err = err;
	} else if (es->state == ES_ACCEPTED) {
		/* first data chunk in p->payload */
		es->state = ES_RECEIVED;
		/* store reference to incoming pbuf (chain) */
		es->p = p;
		/* install send completion notifier */
		tcp_sent(tpcb, doip_sent);
		doip_send(tpcb, es);
		ret_err = ERR_OK;
	} else if (es->state == ES_RECEIVED) {
		/* read some more data */
		if (es->p == NULL) {
			es->p = p;

			volatile uint8 service_id = *(((uint8*)p->payload) + 12);
			volatile uint16 data_id = *(((uint8*)p->payload) + 13) << 8 | *(((uint8*)p->payload) + 14);
//			volatile uint8 service_id = *((uint8*)(p->payload + 12));
//			volatile uint16 data_id = *(uint8*)(p->payload + 13) << 8 | *(uint8*)(p->payload + 14);

			uint8 respMsg[] =
			{
					0x03, /* Protocol Version */
					0xFC, /* Inverse Protocol Version */
					0x80, 0x01, /* DoIP Payload Type */
					0x00, 0x00, 0x00, 0x09, /* DoIP Payload Length */
					/* DoIP Payload */
					0x02, 0x01, /* DoIP Src Addr */
					0x02, 0x00, /* DoIP Target Addr */
					0x62, 0x00, /* UDS */
					0x00, 0x00, 0x00 /* Sensor Values */
			};

			uint16 US_val, ADC_val;
			if (service_id == 0x22) {
				if (data_id == 0x2) {
					US_val = (uint16)Ultrasonic_ReadSensor_noFilt();
					respMsg[14] = 0x02;
					respMsg[15] = US_val >> 8;
					respMsg[16] = (uint8)US_val;
				} else if (data_id == 0x3) {
//					ADC_val = (uint16)IO_ADC_getValueIR();
					ADC_val = (uint16)Evadc_readVR();
					respMsg[14] = 0x03;
					respMsg[15] = ADC_val >> 8;
					respMsg[16] = (uint8)ADC_val;
				}
			}

			es->p->len = 17;
			memcpy(es->p->payload, respMsg, sizeof(respMsg));

			tcp_sent(tpcb, doip_sent);
			doip_send(tpcb, es);
		} else {
			struct pbuf *ptr;

			/* chain pbufs to the end of what we recv'ed previously  */
			ptr = es->p;
			pbuf_chain(ptr, p);
		}
		ret_err = ERR_OK;
	} else if (es->state == ES_CLOSING) {
		/* odd case, remote side closing twice, trash data */
		tcp_recved(tpcb, p->tot_len);
		es->p = NULL;
		pbuf_free(p);
		ret_err = ERR_OK;
	} else {
		/* unkown es->state, trash data  */
		tcp_recved(tpcb, p->tot_len);
		es->p = NULL;
		pbuf_free(p);
		ret_err = ERR_OK;
	}
	return ret_err;
}

void doip_error(void *arg, err_t err)
{
	struct doip_state *es;
//	LWIP_DEBUGF(ECHO_DEBUG, ("doip_error\n"));

	LWIP_UNUSED_ARG(err);

	es = (struct doip_state*) arg;
	if (es != NULL) {
		mem_free(es);
	}
}

err_t doip_poll(void *arg, struct tcp_pcb *tpcb)
{
	err_t ret_err;
	struct doip_state *es;
//	LWIP_DEBUGF(ECHO_DEBUG, ("doip_poll\n"));

	es = (struct doip_state*) arg;
	if (es != NULL) {
		if (es->p != NULL) {
			/* there is a remaining pbuf (chain)  */
			tcp_sent(tpcb, doip_sent);
			doip_send(tpcb, es);
		} else {
			/* no remaining pbuf (chain)  */
			if (es->state == ES_CLOSING) {
				doip_close(tpcb, es);
			}
		}
		ret_err = ERR_OK;
	} else {
		/* nothing to be done */
		tcp_abort(tpcb);
		ret_err = ERR_ABRT;
	}
	return ret_err;
}

err_t doip_sent(void *arg, struct tcp_pcb *tpcb, u16_t len)
{
	struct doip_state *es;

	LWIP_UNUSED_ARG(len);
//	LWIP_DEBUGF(ECHO_DEBUG, ("doip_sent\n"));

	es = (struct doip_state*) arg;
	es->retries = 0;

	if (es->p != NULL) {
		/* still got pbufs to send */
		tcp_sent(tpcb, doip_sent);
		doip_send(tpcb, es);
	} else {
		/* no more pbufs to send */
		if (es->state == ES_CLOSING) {
			doip_close(tpcb, es);
		}
	}
	return ERR_OK;
}

void doip_send(struct tcp_pcb *tpcb, struct doip_state *es)
{
	struct pbuf *ptr;
	err_t wr_err = ERR_OK;
//	LWIP_DEBUGF(ECHO_DEBUG, ("doip_send\n"));

	while ((wr_err == ERR_OK) && (es->p != NULL)
			&& (es->p->len <= tcp_sndbuf(tpcb))) {
		ptr = es->p;

		/* enqueue data for transmission */
		wr_err = tcp_write(tpcb, ptr->payload, ptr->len, 1);
		if (wr_err == ERR_OK) {
			u16_t plen;
			u8_t freed;

			plen = ptr->len;
			/* continue with next pbuf in chain (if any) */
			es->p = ptr->next;
			if (es->p != NULL) {
				/* new reference! */
				pbuf_ref(es->p);
			}
			/* chop first pbuf from chain */
			do {
				/* try hard to free pbuf */
				freed = pbuf_free(ptr);
			} while (freed == 0);
			/* we can read more data now */
			tcp_recved(tpcb, plen);
		} else if (wr_err == ERR_MEM) {
			/* we are low on memory, try later / harder, defer to poll */
			es->p = ptr;
		} else {
			/* other problem ?? */
		}
	}
}

void doip_close(struct tcp_pcb *tpcb, struct doip_state *es)
{
	tcp_arg(tpcb, NULL);
	tcp_sent(tpcb, NULL);
	tcp_recv(tpcb, NULL);
	tcp_err(tpcb, NULL);
	tcp_poll(tpcb, NULL, 0);
//	LWIP_DEBUGF(ECHO_DEBUG, ("doip_close\n"));

	if (es != NULL) {
		mem_free(es);
	}
	tcp_close(tpcb);
}

#endif /* LWIP_TCP */
