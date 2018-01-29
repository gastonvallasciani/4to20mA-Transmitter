// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef TC_GPIOP_HEADER_TEMPLATE_H
#define	TC_GPIOP_HEADER_TEMPLATE_H

#include "devices.h"

void GPIOP_Init(void);
void GPIOP_Task(void);

void GPIOP_GetNewMessages(void);
void GPIOP_ProcessMessages(void);

void GPIOP_Send(tPacket*);

#endif	/* TC_GPIOP_HEADER_TEMPLATE_H */
