 /**
  MSSP1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    i2c1.c

  @Summary
    This is the generated header file for the MSSP1 driver using 
    MPLAB(c) Code Configurator

  @Description
    This header file provides APIs for driver for MSSP1.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 3.16
        Device            :  PIC18F46K22
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB 	          :  MPLAB X 3.20
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include "i2c1.h"
#include "../tc_pin_manager.h"
#include "../devices.h"
#include "../I2C.h"

typedef enum
{
    SLAVE_NORMAL_DATA,
    SLAVE_DATA_ADDRESS,
} SLAVE_WRITE_DATA_TYPE;

/**
 Section: Global Variables
*/
unsigned char messageForMe = 0;

unsigned char I2C_Address;
volatile uint8_t    I2C1_slaveWriteData      = 0x55;
volatile uint8_t    I2C1_targetAddress       = 0xAA;

/**
 Section: Local Functions
*/
void I2C1_StatusCallback(I2C1_SLAVE_DRIVER_STATUS i2c_bus_state);

/**
  Prototype:        void I2C1_Initialize(void)
  Input:            none
  Output:           none
  Description:      I2C1_Initialize is an
                    initialization routine that takes inputs from the GUI.
  Comment:          
  Usage:            I2C1_Initialize();

*/
void I2C1_Initialize(void)
{
	//I2C_Address = (I2C1_SHIFTED_SLAVE_ADDRESS1 << 1); // Placa Transmisora de 4 a 20mA A
    I2C_Address = (I2C1_SHIFTED_SLAVE_ADDRESS2 << 1); // Placa Transmisora de 4 a 20mA B
    //I2C_Address = (I2C1_SHIFTED_SLAVE_ADDRESS << 1);
	
    // initialize the hardware
    // SMP High Speed; CKE disabled; 
    SSP1STAT = 0x00;
    // SSPEN enabled; WCOL no_collision; CKP disabled; SSPM 7 Bit Polling; SSPOV no_overflow; 
    SSP1CON1 = 0x26;
    // ACKEN disabled; GCEN disabled; PEN disabled; ACKDT acknowledge; RSEN disabled; RCEN disabled; SEN disabled; 
    SSP1CON2 = 0x00;
	SSP1CON2bits.SEN = 1; // enable clock stretching

    // SBCDE disabled; BOEN disabled; SCIE enabled; PCIE enabled; DHEN disabled; SDAHT 100ns; AHEN disabled; 
    SSP1CON3 = 0x60;
    // MSK0 255; 
    SSP1MSK = (I2C1_SLAVE_MASK << 1);  // adjust UI mask for R/nW bit            
    // SSP1ADD 8; 
    SSP1ADD = I2C_Address;  // adjust UI address for R/nW bit

    // clear the slave interrupt flag
    PIR1bits.SSP1IF = 0;
    // enable the master interrupt
    PIE1bits.SSP1IE = 1;

}

void I2C1_ISR ( void )
{
    uint8_t i2c_data = 0x55;
    // NOTE: The slave driver will always acknowledge
    //       any address match.

    PIR1bits.SSP1IF = 0;        // clear the slave interrupt flag
    i2c_data        = SSP1BUF;  // read SSPBUF to clear BF
    if(1 == SSP1STATbits.R_nW)
    {
        if((1 == SSP1STATbits.D_nA) && (1 == SSP1CON2bits.ACKSTAT))
        {
            // callback routine can perform any post-read processing
            I2C1_StatusCallback(I2C1_SLAVE_READ_COMPLETED);
        }
        else
        {
            // callback routine should write data into SSPBUF
            I2C1_StatusCallback(I2C1_SLAVE_READ_REQUEST);
        }
    }
    else if(0 == SSP1STATbits.D_nA) // Data/_Address bit
    {
        // this is an I2C address
		I2C1_targetAddress = i2c_data;
		
        // callback routine should prepare to receive data from the master
        I2C1_StatusCallback(I2C1_SLAVE_WRITE_REQUEST);
    }
    else
    {
		I2C1_slaveWriteData = i2c_data;

		// callback routine should process I2C1_slaveWriteData from the master
		I2C1_StatusCallback(I2C1_SLAVE_WRITE_COMPLETED);
    }

    SSP1CON1bits.CKP = 1;    // release SCL
} // end I2C1_ISR()

void I2C1_StatusCallback(I2C1_SLAVE_DRIVER_STATUS i2c_bus_state)
{
	switch (i2c_bus_state)
    {
        case I2C1_SLAVE_WRITE_REQUEST:
			// Address received, check if it's for me
			messageForMe = (I2C1_targetAddress == I2C_Address);
            if (messageForMe){
                //LED_STATUS_On();
                //RELAY2ON();
                //RELAY1OFF();
            }else{
                //RELAY2OFF();
                //RELAY1ON();
            }
            break;

        case I2C1_SLAVE_WRITE_COMPLETED:
			if (messageForMe)
			{
                //LED_STATUS_On();
				// Receive Byte 
				I2C_Input.Buffer[I2C_Input.inPointer] = I2C1_slaveWriteData;
				I2C_Input.inPointer = (I2C_Input.inPointer + 1) % BUFFER_SIZE;
				if (I2C1_slaveWriteData == EOT) messageForMe = NO;
			}
			break;

        case I2C1_SLAVE_READ_REQUEST:
			if (I2C_Output.outPointer != I2C_Output.inPointer)
			{
				// Send Byte
				SSP1BUF = I2C_Output.Buffer[I2C_Output.outPointer];
				I2C_Output.outPointer = (I2C_Output.outPointer + 1) % BUFFER_SIZE;
			}
			else
			{
				// Master always reads MAX_PACKET_SIZE
				// If no more bytes available, fill with EOT
				SSP1BUF = EOT;
			}
			break;

        case I2C1_SLAVE_READ_COMPLETED:
			Me.I2CMsgAvailable.Changed = YES;
			Me.I2CMsgAvailable.Detecting = NO;
			break;
        default:
			break;
    } // end switch(i2c_bus_state)
}

unsigned char I2C1_DataReady()
{
	return (I2C_Input.outPointer != I2C_Input.inPointer);
}
unsigned char i2c_getch()
{
	unsigned char character = 0;
	if (I2C_Input.outPointer != I2C_Input.inPointer)
	{
		character = I2C_Input.Buffer[I2C_Input.outPointer];
		I2C_Input.outPointer = (I2C_Input.outPointer + 1) % BUFFER_SIZE;
	}
	return character;
}
void i2c_putch(unsigned char character)
{
	I2C_Output.Buffer[I2C_Output.inPointer] = character;
	I2C_Output.inPointer = (I2C_Output.inPointer + 1) % BUFFER_SIZE;	
}
