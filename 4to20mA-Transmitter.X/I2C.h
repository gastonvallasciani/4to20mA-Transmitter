// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef TC_I2C_HEADER_TEMPLATE_H
#define	TC_I2C_HEADER_TEMPLATE_H

#include "devices.h"

#define I2C1_BASE_SLAVE_ADDRESS		0x90
#define I2C1_SLAVE_ID               0x02
#define I2C1_SLAVE_ID1              0x03
#define I2C1_SLAVE_ID2              0x04
#define I2C1_SHIFTED_SLAVE_ADDRESS	((I2C1_BASE_SLAVE_ADDRESS >> 1) + I2C1_SLAVE_ID)
#define I2C1_SHIFTED_SLAVE_ADDRESS1	((I2C1_BASE_SLAVE_ADDRESS >> 1) + I2C1_SLAVE_ID1)
#define I2C1_SHIFTED_SLAVE_ADDRESS2	((I2C1_BASE_SLAVE_ADDRESS >> 1) + I2C1_SLAVE_ID2)
#define I2C1_SLAVE_MASK				0xFF

void I2C_GetNewMessages();
void I2C_ProcessMessages();

void I2C_Send(tPacket*);

#endif	/* TC_I2C_HEADER_TEMPLATE_H */
