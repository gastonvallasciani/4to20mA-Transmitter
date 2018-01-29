/*
 * File:   UART.c
 * Author: Nico Christie
 *
 * Created on 19 de febrero de 2016, 16:17
 */

#include "mcc_generated_files/eusart1.h"
#include "devices.h"
#include "UART.h"

#define UART_QUEUE_SIZE 10
tPacket UARTQueue[UART_QUEUE_SIZE];
static unsigned char UART_QueueInPointer;
static unsigned char UART_QueueOutPointer;

static unsigned int uart_index = 0;
static unsigned char uart_data_pending = NO;
static unsigned char uart_Paquete[MAX_PACKET_SIZE];

inline void UART_FillPacket(tPacket*);
inline void UART_Send_Packet(unsigned char*, unsigned char);
inline void UART_Checksum(unsigned char*, unsigned char);

void UART_GetNewMessages()
{
	if (!uart_data_pending)
	{
		// No characters were pending to receive
		uart_index = 0;
		unsigned char lastCharRead = 0;
		do
		{
			// Clear input buffer until SOH is found
			if (EUSART1_DataReady)
			{
				lastCharRead = getch();	// EUSART1_Read();
				uart_Paquete[0] = lastCharRead;
			}
			else break;
		}
		while (lastCharRead != SOH);
		
		// No SOH was found? return.
		if (lastCharRead != SOH) return;
		else { uart_data_pending = YES; uart_index++; } // Start receiving packet
	}
	else
	{
		// Characters are still required to complete a packet.
		do
		{
			// Read the input buffer until an EOT is found
			if (EUSART1_DataReady) uart_Paquete[uart_index] = getch();	// EUSART1_Read();
			else break;
		} while (uart_Paquete[uart_index++] != EOT);

		// Are characters still pending to receive?
		uart_data_pending = (uart_Paquete[uart_index - 1] != EOT);
		if (uart_data_pending) return;
		
		// I got a full packet in buffer.
		// Create a packet, process it, clear buffer.
		tPacket* msg = &UARTQueue[UART_QueueInPointer];
		UART_FillPacket(msg);
		
		// if packet checks out OK, main()->ProcessMessages() will take care of it.
		if (msg->Valid)	UART_QueueInPointer = (UART_QueueInPointer + 1) % UART_QUEUE_SIZE;
		//else { Send_NAK(msg, ERROR_CODE_CHECKSUM_FAILED); }
	}
}
void UART_ProcessMessages()
{
	// Process new packets to check requests.
	while (UART_QueueOutPointer != UART_QueueInPointer)
	{
		if (UART_ProcessPacket(&UARTQueue[UART_QueueOutPointer]))
		{
			// Message was processed correctly, skip it.
			UART_QueueOutPointer = (UART_QueueOutPointer + 1) % UART_QUEUE_SIZE;
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

void UART_Send(tPacket* msg)
{
	int i;
	unsigned char packet[MAX_PACKET_SIZE];
	packet[0] = msg->Start;
	packet[1] = msg->Direction | msg->ParamCount;
	packet[2] = msg->Class;
	packet[3] = msg->ID + '0';
	packet[4] = msg->CommandH;
	packet[5] = msg->CommandL;
	for (i = 0; i < msg->ParamCount; i++)
		packet[MSG_START_INDEX + i] = msg->Params[i];
	packet[MSG_START_INDEX + msg->ParamCount] = msg->Checksum;
	packet[MSG_START_INDEX + msg->ParamCount + 1] = msg->End;

	i = 0;
	unsigned char msg_size = MIN_PACKET_SIZE + msg->ParamCount;
	UART_Checksum(packet, msg_size);
	do
	{
		putch(packet[i]); // EUSART1_Write(*(packet + i));
	} while (packet[i++] != EOT);
}
void UART_Send_Debug(const unsigned char* msg)
{
	unsigned char msg_size = 0;
	unsigned char packet[128];
	
	while (*(msg + msg_size) != '\0') msg_size++;
	
	packet[0] = SOH;
	packet[1] = DEV_TO_PC;
	packet[2] = Me.Class;
	packet[3] = Me.ID + '0';
	packet[4] = COMMANDS_HIGH_DEBUG;
	packet[5] = COMMANDS_LOW_SET;
	for (int i = 0; i < msg_size; i++)
		packet[MSG_START_INDEX + i] = *(msg + i);
	packet[MSG_START_INDEX + msg_size + 0] = 'F';		// Checksum
	packet[MSG_START_INDEX + msg_size + 1] = EOT;

	int i = 0;
	msg_size += MIN_PACKET_SIZE;
	//UART_Checksum(packet, msg_size);
	do
	{
		putch(packet[i]); // EUSART1_Write(*(packet + i));
	} while (packet[i++] != EOT);
}

inline void UART_FillPacket(tPacket* msg)
{
	int i = 0;
	// Header
	msg->Start = uart_Paquete[i++];
	msg->Direction = uart_Paquete[i] & MASK_SENTIDO;
	msg->ParamCount = uart_Paquete[i++] & MASK_PARAMCOUNT;
	msg->Class = uart_Paquete[i++];
	msg->ID = uart_Paquete[i++] - '0';
	// Message
	msg->CommandH = uart_Paquete[i++];
	msg->CommandL = uart_Paquete[i++];
	for (int j = 0; j < msg->ParamCount; j++)
		msg->Params[j] = uart_Paquete[i++];
	// Footer
	msg->Checksum = uart_Paquete[i++];
	msg->End = uart_Paquete[i];

	msg->IOInterface = INTERFACE_UART;
	msg->Valid = YES;
}
inline void UART_Checksum(unsigned char* msg, unsigned char msg_size)
{
	msg[msg_size - 2] = 'F';
}
