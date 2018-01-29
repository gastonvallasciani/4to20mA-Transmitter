// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef TC_UART_HEADER_TEMPLATE_H
#define	TC_UART_HEADER_TEMPLATE_H

#include "devices.h"

#define UART_BROADCAST_ID	0

void UART_GetNewMessages(void);
void UART_ProcessMessages(void);

void UART_Send(tPacket*);
void UART_Send_Debug(const unsigned char*);

#endif	/* TC_UART_HEADER_TEMPLATE_H */
