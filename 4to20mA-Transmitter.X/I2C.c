/*
 * File:   I2C.c
 * Author: Nico Christie
 *
 * Created on 12 de octubre de 2016, 12:00
 */

#include "mcc_generated_files/i2c1.h"
#include "tc_pin_manager.h"
#include "devices.h"
#include "tasks.h"
#include "I2C.h"

#include "displayLCD20x4.h"

#define ONLINE_RACK_BOARD	NO

#define I2C_QUEUE_SIZE 10
tPacket I2CQueue[I2C_QUEUE_SIZE];
static unsigned char I2C_QueueInPointer;
static unsigned char I2C_QueueOutPointer;

static unsigned int i2c_index = 0;
static unsigned char i2c_data_pending = NO;
static unsigned char i2c_Paquete[MAX_PACKET_SIZE];

#if (ONLINE_RACK_BOARD == YES)
I2C1_MESSAGE_STATUS status = I2C1_MESSAGE_PENDING;
unsigned char MUX_Write(unsigned char*, unsigned char);
unsigned char MUX_Read(unsigned char*, unsigned char);
#endif

inline void I2C_FillPacket(tPacket*);
inline void I2C_Checksum(unsigned char*, unsigned char);

void I2C_GetNewMessages()
{
#if (ONLINE_RACK_BOARD == YES)
	// Messages will not be sent by slaves
	// Poll Multiplexer for available data
	while (MUX_MSG_AVAILABLE() == YES)
	{
		Delay(_100mSeg); // Allow all data to be received
		static unsigned char tempBuffer[MAX_PACKET_SIZE + 1], i;
		for (int j = 0; j < MAX_PACKET_SIZE + 1; j++) tempBuffer[j] = NULL;
		
		if (MUX_Read(tempBuffer, MAX_PACKET_SIZE))
		{
			/* BUG: No estoy recibiendo el SOH que determina el inicio de
			mensaje. Sin eso, todo lo que recibe termina descartado por no
			ser reconcido el inicio. Insertar a mano un SOH en el buffer no
			debería afectar la mensajería ya que partimos de la base que el
			Mux avisó que tenía algo para comunicar con MUX_MSG_AVAILABLE() */
			I2C_Input.Buffer[I2C_Input.inPointer] = SOH;
			I2C_Input.inPointer = (I2C_Input.inPointer + 1) % BUFFER_SIZE;

			i = 0;
			while ((tempBuffer[i] != NULL) && (i < MAX_PACKET_SIZE))
			{
				I2C_Input.Buffer[I2C_Input.inPointer] = tempBuffer[i++];
				I2C_Input.inPointer = (I2C_Input.inPointer + 1) % BUFFER_SIZE;
			}
		}
		else return; // Reset I2C?
	}
#endif
	
	if (!i2c_data_pending)
	{
		// No characters were pending to receive
		i2c_index = 0;
		unsigned char i2c_lastCharRead = NULL;
		do
		{
			// Clear input buffer until SOH is found
			if (I2C1_DataReady())
			{
				i2c_lastCharRead = i2c_getch();
				i2c_Paquete[0] = i2c_lastCharRead;
			}
			else break;
		}
		while (i2c_lastCharRead != SOH);
		
		// No SOH was found? return.
		if (i2c_lastCharRead != SOH) return;
		else { i2c_data_pending = true; i2c_index++; } // Start receiving packet
	}
	else
	{
		// Characters are still required to complete a packet.
		do
		{
			// Read the input buffer until an EOT is found
			if (I2C1_DataReady()) 
			{
				i2c_Paquete[i2c_index] = i2c_getch();
				LCD_WriteChar(i2c_Paquete[i2c_index], DISPLAY_LINEA(3), i2c_index);
			}
			else break;
		} while (i2c_Paquete[i2c_index++] != EOT);

		// Are characters still pending to receive?
		i2c_data_pending = (i2c_Paquete[i2c_index - 1] != EOT);
		if (i2c_data_pending) return;
		
		// I got a full packet in buffer.
		// Create a packet, process it, clear buffer.
		tPacket* msg = &I2CQueue[I2C_QueueInPointer];
		I2C_FillPacket(msg);
		
		// if packet checks out OK, main()->ProcessMessages() will take care of it.
		if (msg->Valid) { I2C_QueueInPointer = (I2C_QueueInPointer + 1) % I2C_QUEUE_SIZE; }
		//else { Send_NAK(msg, ERROR_CODE_CHECKSUM_FAILED); }
	}
}
void I2C_ProcessMessages()
{
	// Process new packets to check requests.
	while (I2C_QueueOutPointer != I2C_QueueInPointer)
	{
		if (I2C_ProcessPacket(&I2CQueue[I2C_QueueOutPointer]))
		{
			// Message was processed correctly, skip it.
			I2C_QueueOutPointer = (I2C_QueueOutPointer + 1) % I2C_QUEUE_SIZE;
		}
		else
		{
			// A new message conflicts with an ongoing operation
			// such as receiving a 'move' command for a motor 
			// that is already moving.
			// Break this run and return to main().
			break;
		}
	}
}

void I2C_Send(tPacket* msg)
{
#if (ONLINE_RACK_BOARD == YES)
	// MUX_Write() does not support cyclic buffer
	I2C_Output.inPointer = 0;
	I2C_Output.outPointer = 0;
#endif
	
	// Load output buffer (and wait for Master Poll if Mux)
	i2c_putch(msg->Start);
	i2c_putch(msg->Direction | msg->ParamCount);
	i2c_putch(msg->Class);
	i2c_putch(msg->ID + '0');
	i2c_putch(msg->CommandH);
	i2c_putch(msg->CommandL);
	for (int i = 0; i < msg->ParamCount; i++)
		i2c_putch(msg->Params[i]);
	i2c_putch(msg->Checksum);
	i2c_putch(msg->End);
	
#if (ONLINE_RACK_BOARD == YES)	
	// Write message to device
	MUX_Write(I2C_Output.Buffer, I2C_Output.inPointer);
#else
    Me.I2CMsgAvailable.Changed = YES;
	Me.I2CMsgAvailable.Detecting = YES;
#endif
}

inline void I2C_FillPacket(tPacket* msg)
{
	int i = 0;
	// Header
	msg->Start = i2c_Paquete[i++];
	msg->Direction = i2c_Paquete[i] & MASK_SENTIDO;
	msg->ParamCount = i2c_Paquete[i++] & MASK_PARAMCOUNT;
	msg->Class = i2c_Paquete[i++];
	msg->ID = i2c_Paquete[i++] - '0';
	// Message
	msg->CommandH = i2c_Paquete[i++];
	msg->CommandL = i2c_Paquete[i++];
	for (int j = 0; j < msg->ParamCount; j++)
		msg->Params[j] = i2c_Paquete[i++];
	// Footer
	msg->Checksum = i2c_Paquete[i++];
	msg->End = i2c_Paquete[i];

	msg->IOInterface = INTERFACE_I2C;
	msg->Valid = YES;
}
inline void I2C_Checksum(unsigned char* msg, unsigned char msg_size)
{
	msg[msg_size - 2] = 'F';
}

#if (ONLINE_RACK_BOARD == YES)
unsigned char MUX_Write(unsigned char* msg_buffer_out, unsigned char pCount)
{
	unsigned int readOpTimeout = 0;
	unsigned int pendingOpTimeout = 0;
	status = I2C1_MESSAGE_PENDING;
	while(status != I2C1_MESSAGE_FAIL)
	{
		I2C1_MasterWrite(msg_buffer_out, pCount, I2C1_SHIFTED_SLAVE_ADDRESS, &status);

		// wait for the message to be sent or status has changed.
		while (status == I2C1_MESSAGE_PENDING) { }
		//while ((status == I2C1_MESSAGE_PENDING) && (pendingOpTimeout++ < 60000)) { }
		//if (pendingOpTimeout >= 60000) LED_TEST2_On();
		
		if (status == I2C1_MESSAGE_COMPLETE) break;

		// if status is  I2C1_MESSAGE_ADDRESS_NO_ACK,
		//               or I2C1_DATA_NO_ACK,
		// The device may be busy and needs more time for the last
		// write so we can retry writing the data, this is why we
		// use a while loop here
		if (readOpTimeout++ > 5) status = I2C1_MESSAGE_FAIL;
	}
	return (status == I2C1_MESSAGE_COMPLETE);
}
unsigned char MUX_Read(unsigned char* msg_buffer_in, unsigned char pCount)
{
	unsigned int readOpTimeout = 0;
	unsigned int pendingOpTimeout = 0;
	status = I2C1_MESSAGE_PENDING;
	while(status != I2C1_MESSAGE_FAIL)
	{
		I2C1_MasterRead(msg_buffer_in, pCount, I2C1_SHIFTED_SLAVE_ADDRESS, &status);

		// wait for the message to be sent or status has changed.
		while (status == I2C1_MESSAGE_PENDING) { }
		//while ((status == I2C1_MESSAGE_PENDING) && (pendingOpTimeout++ < 60000)) { }
		//if (pendingOpTimeout >= 60000) LED_TEST3_On();
		
		if (status == I2C1_MESSAGE_COMPLETE) break;

		// if status is  I2C1_MESSAGE_ADDRESS_NO_ACK,
		//               or I2C1_DATA_NO_ACK,
		// The device may be busy and needs more time for the last
		// write so we can retry writing the data, this is why we
		// use a while loop here
		if (readOpTimeout++ > 5) status = I2C1_MESSAGE_FAIL;
	}
	return (status == I2C1_MESSAGE_COMPLETE);
}
#endif
