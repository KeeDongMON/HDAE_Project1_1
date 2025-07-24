#include "can-ethernet.h"
#include "lwip/opt.h"
#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"
#include "etc.h"
#include "can.h"

#if LWIP_TCP

static struct tcp_pcb *can_eth_pcb;

enum can_eth_states
{
	ES_NONE = 0,
	ES_ACCEPTED,
	ES_RECEIVED,
	ES_CLOSING
};

struct can_eth_state
{
	u8_t state;
	u8_t retries;
	struct tcp_pcb *pcb;
	/* pbuf (chain) to recycle */
	struct pbuf *p;
};

err_t can_eth_accept(void *arg, struct tcp_pcb *newpcb, err_t err);
err_t can_eth_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
void can_eth_error(void *arg, err_t err);
err_t can_eth_poll(void *arg, struct tcp_pcb *tpcb);
err_t can_eth_sent(void *arg, struct tcp_pcb *tpcb, u16_t len);
void can_eth_send(struct tcp_pcb *tpcb, struct can_eth_state *es);
void can_eth_close(struct tcp_pcb *tpcb, struct can_eth_state *es);

void EthToCAN1(struct pbuf *p);
void EthToCAN2(struct pbuf *p);
void EthToCAN3(struct pbuf *p);

void tcp_can_eth_init(void)
{
	can_eth_pcb = tcp_new();
	if (can_eth_pcb != NULL) {
		err_t err;

		err = tcp_bind(can_eth_pcb, IP_ADDR_ANY, 7);
		if (err == ERR_OK) {
			can_eth_pcb = tcp_listen(can_eth_pcb);
			tcp_accept(can_eth_pcb, can_eth_accept);
		} else {
			/* abort? output diagnostic? */
		}
	} else {
		/* abort? output diagnostic? */
	}
}

err_t can_eth_accept(void *arg, struct tcp_pcb *newpcb, err_t err)
{
	err_t ret_err;
	struct can_eth_state *es;

	LWIP_UNUSED_ARG(arg);
	LWIP_UNUSED_ARG(err);
//	LWIP_DEBUGF(ECHO_DEBUG, ("echo_accept\n"));

	/* Unless this pcb should have NORMAL priority, set its priority now.
	 When running out of pcbs, low priority pcbs can be aborted to create
	 new pcbs of higher priority. */
	tcp_setprio(newpcb, TCP_PRIO_MIN);

	es = (struct can_eth_state*) mem_malloc(sizeof(struct can_eth_state));
	if (es != NULL) {
		es->state = ES_ACCEPTED;
		es->pcb = newpcb;
		es->retries = 0;
		es->p = NULL;
		/* pass newly allocated es to our callbacks */
		tcp_arg(newpcb, es);
		tcp_recv(newpcb, can_eth_recv);
		tcp_err(newpcb, can_eth_error);
		tcp_poll(newpcb, can_eth_poll, 0);
		ret_err = ERR_OK;
		es->state = ES_RECEIVED;
	} else {
		ret_err = ERR_MEM;
	}
	return ret_err;
}

err_t can_eth_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
	struct can_eth_state *es;
	err_t ret_err;

	LWIP_ASSERT("arg != NULL", arg != NULL);
//	LWIP_DEBUGF(ECHO_DEBUG, ("echo_recv\n"));
	es = (struct can_eth_state*) arg;
	if (p == NULL) {
		/* remote host closed connection */
		es->state = ES_CLOSING;
		if (es->p == NULL) {
			/* we're done sending, close it */
			can_eth_close(tpcb, es);
		} else {
			/* we're not done yet */
			tcp_sent(tpcb, can_eth_sent);
			can_eth_send(tpcb, es);
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
		tcp_sent(tpcb, can_eth_sent);
		can_eth_send(tpcb, es);
		ret_err = ERR_OK;
	} else if (es->state == ES_RECEIVED) {
		/* read some more data */
		if (es->p == NULL) {
			es->p = p;
			tcp_sent(tpcb, can_eth_sent);
//			can_eth_send(tpcb, es);
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

void can_eth_error(void *arg, err_t err)
{
	struct can_eth_state *es;
//	LWIP_DEBUGF(ECHO_DEBUG, ("echo_error\n"));

	LWIP_UNUSED_ARG(err);

	es = (struct can_eth_state*) arg;
	if (es != NULL) {
		mem_free(es);
	}
}

err_t can_eth_poll(void *arg, struct tcp_pcb *tpcb)
{
	err_t ret_err;
	struct can_eth_state *es;
//	LWIP_DEBUGF(ECHO_DEBUG, ("echo_poll\n"));

	es = (struct can_eth_state*) arg;
	if (es != NULL) {
		if (es->p != NULL) {
			/* there is a remaining pbuf (chain)  */
			tcp_sent(tpcb, can_eth_sent);
			can_eth_send(tpcb, es);
		} else {
			/* no remaining pbuf (chain)  */
			if (es->state == ES_CLOSING) {
				can_eth_close(tpcb, es);
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

err_t can_eth_sent(void *arg, struct tcp_pcb *tpcb, u16_t len)
{
	struct can_eth_state *es;

	LWIP_UNUSED_ARG(len);
//	LWIP_DEBUGF(ECHO_DEBUG, ("echo_sent\n"));

	es = (struct can_eth_state*) arg;
	es->retries = 0;

	if (es->p != NULL) {
		/* still got pbufs to send */
		tcp_sent(tpcb, can_eth_sent);
		can_eth_send(tpcb, es);
	} else {
		/* no more pbufs to send */
		if (es->state == ES_CLOSING) {
			can_eth_close(tpcb, es);
		}
	}
	return ERR_OK;
}

void can_eth_send(struct tcp_pcb *tpcb, struct can_eth_state *es)
{
	struct pbuf *ptr;
	err_t wr_err = ERR_OK;
//	LWIP_DEBUGF(ECHO_DEBUG, ("echo_send\n"));

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

void can_eth_close(struct tcp_pcb *tpcb, struct can_eth_state *es)
{
	tcp_arg(tpcb, NULL);
	tcp_sent(tpcb, NULL);
	tcp_recv(tpcb, NULL);
	tcp_err(tpcb, NULL);
	tcp_poll(tpcb, NULL, 0);
//	LWIP_DEBUGF(ECHO_DEBUG, ("echo_close\n"));

	if (es != NULL) {
		mem_free(es);
	}
	tcp_close(tpcb);
}

/* Automotive Ethernet Practice 2-1. Ethernet->CAN */
void EthToCAN1(struct pbuf *p)
{
	volatile int i = 0, txCnt = 0;
	uint8 dlc;
	/* Calculate CAN transmit count */
	if (p->len <= 8) {
		txCnt = 1;
	} else {
		txCnt = p->len / 8;

		if (p->len % 8 != 0) {
			txCnt += 1;
		}
	}

	/* Transmit CAN frame */
	for (i = 0; i < txCnt; i++) {
		if (p->len % 8 != 0 && i == txCnt -1) {
			dlc = p->len - (i * 8);
		} else {
			dlc = 8;
		}
//		Set_CAN_msgObject(0, 0, i, dlc, 0);
		Can_SendMsg(0, ((char *)(p->payload) + (i*8)), dlc);
		delay_ms(100);
	}
}

/* Automotive Ethernet Practice 2-2. Ethernet Single PDU->CAN */
void EthToCAN2(struct pbuf *p)
{
	uint8 pdu_id = *(uint8*)(p->payload);
	uint16 pdu_len = *(((uint8*)p->payload) + 1) << 8;
	pdu_len |= *(((uint8*)p->payload) + 2);
	uint8 pdu_data[pdu_len];
	int i;
	for (i = 0; i < pdu_len; i++) {
		pdu_data[i] = *(((uint8*)p->payload) + 3 + i);
	}

	/* if pdu_id is 0, then transmit pdu_data via CAN(id: 0x200) */
	if (pdu_id == 0) {
		int j = 0, txCnt = 0;
		uint8 dlc;
		/* Calculate CAN transmit count */
		if (pdu_len <= 8) {
			txCnt = 1;
		} else {
			txCnt = pdu_len / 8;

			if (pdu_len % 8 != 0) {
				txCnt += 1;
			}
		}

		/* Transmit CAN frame */
		for (j = 0; j < txCnt; j++) {
			if (pdu_len % 8 != 0 && j == txCnt -1) {
				dlc = pdu_len - (j * 8);
			} else {
				dlc = 8;
			}
//			Set_CAN_msgObject(0, 0, 0x200, dlc, 0);
			Can_SendMsg(0x200, (char *)pdu_data + j * 8, dlc);

//			printf_CAN(0, pdu_data + j * 8);
			delay_ms(100);
		}
	}
}

/* Automotive Ethernet Practice 2-2. Ethernet Multiple PDU->CAN */
void EthToCAN3(struct pbuf *p)
{
	uint16 pdu_len;

	int i = 0;
	while (i < p->tot_len) {
		pdu_len = *(((uint8*)p->payload) + i + 1) << 8;
		pdu_len |= *(((uint8*)p->payload) + i + 2);
		EthToCAN2(p + i);
		i += 3 + pdu_len;
	}
}

#endif /* LWIP_TCP */
