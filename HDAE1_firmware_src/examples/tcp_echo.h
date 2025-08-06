#ifndef EXAMPLES_TCP_ECHO_H_
#define EXAMPLES_TCP_ECHO_H_

/* ECHO_DEBUG: Enable debugging in tcp_echo.c */
#ifndef ECHO_DEBUG
#define ECHO_DEBUG  LWIP_DBG_ON
#endif

void TcpEchoInit(void);                                                    /* Function to initialize the ECHO program  */

#endif /* EXAMPLES_TCP_ECHO_H_ */
