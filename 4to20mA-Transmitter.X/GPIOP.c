//
//	GPIO Protocol
//
//	OnLine Rack/OLSEN Board		<-->	Multiplexer Board
//	(PORTA en PIC18F4680)				(PORTB en PIC18F46K22)
//	RA1-RA4								RB1-RB4
//
//	RA1: OUTPUT	(W/_R)			<-->	RB1: INPUT
//	RA2: INPUT					<-->	RB2: OUTPUT (W/_R)
//	RA3: INPUT/OUTPUT (DATA)	<-->	RB3: INPUT/OUTPUT (DATA)
//	RA4: OUTPUT (CLK)			<-->	RB4: INPUT (CLK)
//
//	La placa del Rack/OLSEN actúa como Master Clock. Ambas placas tienen
//	un pin de "quiero mandar un mensaje" por el canal de datos.
//
//	DATA arranca siempre en OUTPUT LOW.
//	W/_R arranca siempre en _R.
//	
//	Cuando una placa levanta _R a W, la otra da un ACK levantando y bajando 
//	su W/_R y cambia DATA a INPUT.
//	
//	Los bits se leen de DATA con el flanco descendente de CLK.
//	Los bits se escriben en DATA con el flanco ascendente de CLK.
//	El mensaje termina cuando W/_R vuelve a _R en el que inició la comunicación.
//	
//	Ejemplo:
//	(M) Master define el clock
//	(1) inicia comunicación con (2)
//		     ____      ____      ____      ____      ____      ____      ____
//	CLK     |    |    |    |    |    |    |    |    |    |    |    |    |    |
//	(M)	____|    |____|    |____|    |____|    |____|    |____|    |____|    |__
//	       _____________________________________________________________________
//	W/_R  | Write request
//	(1) __|      (si al bajar CLK leo _R en (2) no hay colisión)
//	               _________
//	W/_R          |   ACK   | 
//	(2) __________|         |___________________________________________________
//	                              _________                     _________
//	DATA                         |    1    |    0         0    |    1    |   
//  (1) _________________________|         |___________________|         |______
//	
//	
//		      ____      ____      ____      ____      ____      ____      ____
//	CLK  ... |    |    |    |    |    |    |    |    |    |    |    |    |    |
//	(M)	   __|    |____|    |____|    |____|    |____|    |____|    |____|    |_
//	        ____________________________________________________
//	W/_R ...                                                    | Write ended
//	(1)                                                         |_______________
//	    
//	W/_R ...
//	(2)     ____________________________________________________________________
//	           ___________________           _________ 
//	DATA ...  |    1         1    |    0    |    1    |    0
//  (1)     __|                   |_________|         |_________________________
//	
//	-> tantos bits como requiera el mensaje, separando en bytes

#include "tc_pin_manager.h"
#include "devices.h"
#include "GPIOP.h"

#include "displayLCD20x4.h"

#define ONLINE_RACK_OLSEN	NO

#if (ONLINE_RACK_OLSEN == YES)
// GPIO config for Rack/OLSEN Board (PIC18F4680)
#define CLK_Output()			IN0_OUTPUT()
#define CLK_Toggle()			IN0_Toggle()
#define CLK_High()				IN0_High()
#define CLK_Low()				IN0_Low()

#define W_R_Output()			IN1_OUTPUT()
#define W_R_Write()				IN1_High()
#define W_R_Read()				IN1_Low()

#define WriteRequest_Input()	IN2_INPUT()
#define WriteRequest()			IN2_GetValue()

#define DATA_Output()			IN3_OUTPUT()
#define DATA_Input()			IN3_INPUT()
#define DATA_Value()			IN3_GetValue()
#define DATA_High()				IN3_High()
#define DATA_Low()				IN3_Low()
#else
// GPIO config for Multiplexer Board (PIC18F46K22)
#define CLK_Input()				BTN5_MATRICIAL_OUTPUT()
#define CLK_Value()				BTN5_MATRICIAL()

#define W_R_Output()			BTN4_MATRICIAL_OUTPUT()
#define W_R_Write()				BTN4_High()
#define W_R_Read()				BTN4_Low()

#define WriteRequest_Input()	BTN3_MATRICIAL_INPUT()
#define WriteRequest()			BTN3_MATRICIAL()

#define DATA_Output()			BTN2_MATRICIAL_OUTPUT()
#define DATA_Input()			BTN2_MATRICIAL_INPUT()
#define DATA_Value()			BTN2_MATRICIAL()
#define DATA_High()				BTN2_High()
#define DATA_Low()				BTN2_Low()
#endif

#define BUFFER_SIZE		128

#define QUEUE_SIZE		10
tPacket GPIOPQueue[QUEUE_SIZE];
unsigned char QueueInPointer;
unsigned char QueueOutPointer;

int index = 0;
unsigned char data_pending = NO;
unsigned char Paquete[MAX_PACKET_SIZE];

typedef enum {
	IDLE,
	WRITE_INCOMING,
	WRITE_OUTGOING,
	WRITE_COLLISION,
	WAITING_ACK,
	ACK_RECEIVED,
	ACK_SENT,
	WRITE,
	WRITE_ENDED,
	READ,
	READ_ENDED
}eTransferStates;
typedef struct {
	unsigned char inPointer;
	unsigned char outPointer;
	unsigned char Buffer[BUFFER_SIZE];	
}tBuffer;
typedef struct {
	unsigned char Clock;
	unsigned char Timeout;
	unsigned char BitCounter;
	unsigned char DataPending;
	unsigned char AvailableMsgs;
	eTransferStates TransferStatus;

	tBuffer Input;
	tBuffer Output;
}tGPIOStatus;

tGPIOStatus Status;

inline void GPIOP_FillPacket(tPacket*);
inline void GPIOP_Checksum(tPacket*);

void GPIOP_Init()
{
	QueueInPointer = 0;
	QueueOutPointer = 0;
	
	Status.Clock = LOW;
	Status.Timeout = 0;
	Status.BitCounter = 0;
	Status.DataPending = NO;
	Status.AvailableMsgs = 0;
	Status.TransferStatus = IDLE;

	Status.Input.inPointer = 0;
	Status.Input.outPointer = 0;
	
	Status.Output.inPointer = 0;
	Status.Output.outPointer = 0;
	
	W_R_Output();
	W_R_Read();
	
	WriteRequest_Input();
	
	DATA_Output();
	DATA_Low();

#if (ONLINE_RACK_OLSEN == YES)
	// GPIO config for Rack/OLSEN Board (PIC18F4680))
	Status.Clock = LOW;
	CLK_Output();
	CLK_Low();
#else
	// GPIO config for Multiplexer Board (PIC18F46K22)
	CLK_Input();
#endif
}
void GPIOP_Task()
{
#if (ONLINE_RACK_OLSEN == YES)
	// GPIO config for Rack/OLSEN Board (PIC18F4680))
	CLK_Toggle();
	Status.Clock = !Status.Clock;
#else
	// GPIO config for Multiplexer Board (PIC18F46K22)	
	Status.Clock = CLK_Value();
#endif
	
	switch(Status.TransferStatus)
	{
		case IDLE:
			LCD_WriteChar('I', DISPLAY_LINEA(1), DISPLAY_OFFSET(0));
			if (WriteRequest()) Status.TransferStatus = WRITE_INCOMING;
			break;
		case WRITE_INCOMING:
			LCD_WriteChar('W', DISPLAY_LINEA(1), DISPLAY_OFFSET(1));
			W_R_Write(); // Start ACK
			Status.TransferStatus = ACK_SENT;
			break;
		case WRITE_OUTGOING:
			if (WriteRequest()) Status.TransferStatus = WRITE_COLLISION;
			else Status.TransferStatus = WAITING_ACK;
			break;
		case WRITE_COLLISION:
#if (ONLINE_RACK_OLSEN == YES)
			// GPIO config for Rack/OLSEN Board (PIC18F4680))
			Status.TransferStatus = IDLE;
#else
			// GPIO config for Multiplexer Board (PIC18F46K22)	
			if (Status.Timeout++ > 3)
			{
				Status.Timeout = 0;
				Status.TransferStatus = IDLE;
			}
#endif
			break;
		case WAITING_ACK:
			if (Status.Clock == LOW) // Read on Low flank
			{
				if (WriteRequest()) Status.TransferStatus = ACK_RECEIVED;
			}
			break;
		case ACK_RECEIVED:
			Status.Timeout = 0;
			Status.BitCounter = 0;
			Status.TransferStatus = WRITE;
			DATA_Output();
			break;
		case ACK_SENT:
			LCD_WriteChar('A', DISPLAY_LINEA(1), DISPLAY_OFFSET(2));
			W_R_Read(); // End ACK
			Status.Timeout = 0;
			Status.BitCounter = 0;
			Status.TransferStatus = READ;
			DATA_Input();
			break;
		case WRITE:
			if (Status.Clock == HIGH) // Write on High flank
			{
				if (Status.BitCounter < 8)
				{	
					unsigned char _bit = (Status.Output.Buffer[Status.Output.outPointer] >> Status.BitCounter) & 0x01;
					if (_bit) DATA_High(); else DATA_Low();
					Status.BitCounter++;
				}
				else
				{
					Status.BitCounter = 0;
					Status.Output.outPointer = (Status.Output.outPointer + 1) % BUFFER_SIZE;
					if (Status.Output.outPointer == Status.Output.inPointer)
						Status.TransferStatus = WRITE_ENDED;
				}
			}
			break;
		case WRITE_ENDED:
			W_R_Read();
			Status.TransferStatus = IDLE;
			break;
		case READ:
			LCD_WriteChar('R', DISPLAY_LINEA(1), DISPLAY_OFFSET(3));
			if (Status.Clock == LOW) // Read on Low flank
			{
				if (Status.BitCounter < 8)
				{	
					unsigned char _bit = DATA_Value();
					Status.Input.Buffer[Status.Input.inPointer] |= (_bit << (7 - Status.BitCounter));
					Status.BitCounter++;
				}
				else
				{
					Status.BitCounter = 0;
					Status.Input.inPointer = (Status.Input.inPointer + 1) % BUFFER_SIZE;
					if (WriteRequest() == 0)
						Status.TransferStatus = READ_ENDED;
				}
			}
			break;
		case READ_ENDED:
			LCD_WriteChar('E', DISPLAY_LINEA(1), DISPLAY_OFFSET(4));
			Status.AvailableMsgs++; // Not validated, just received
			Status.TransferStatus = IDLE;
			break;
		default:
			break;
	}
}

void GPIOP_GetNewMessages()
{
	while (Status.AvailableMsgs > 0)
	{
		if (!data_pending)
		{
			// No characters were pending to receive
			index = 0;
			unsigned char lastCharRead = 0;
			do
			{
				// Clear input buffer until SOH is found
				if (Status.Input.inPointer != Status.Input.outPointer)
				{
					lastCharRead = Status.Input.Buffer[Status.Input.outPointer++];
					Paquete[0] = lastCharRead;
				}
				else break;
			}
			while (lastCharRead != SOH);

			// No SOH was found? return.
			if (lastCharRead != SOH) return;
			else { data_pending = YES; index++; } // Start receiving packet
		}
		else
		{
			// Characters are still required to complete a packet.
			do
			{
				// Read the input buffer until an EOT is found
				if (Status.Input.inPointer != Status.Input.outPointer)
					Paquete[index] = Status.Input.Buffer[Status.Input.outPointer++];
				else break;
			} while (Paquete[index++] != EOT);

			// Are characters still pending to receive?
			data_pending = (Paquete[index - 1] != EOT);
			if (data_pending) return;

			// I got a full packet in buffer.
			// Create a packet, process it, clear buffer.
			tPacket* msg = &GPIOPQueue[QueueInPointer];
			GPIOP_FillPacket(msg);

			// if packet checks out OK, main()->ProcessMessages() will take care of it.
			if (msg->Valid) { QueueInPointer = (QueueInPointer + 1) % QUEUE_SIZE; }
			//else { Send_NAK(msg, ERROR_CODE_CHECKSUM_FAILED); }
		}
		
	}
}
void GPIOP_ProcessMessages()
{
	// Process new packets to check requests.
	while (QueueOutPointer != QueueInPointer)
	{
		if (GPIOP_ProcessPacket(&GPIOPQueue[QueueOutPointer]))
		{
			// Message was processed correctly, skip it.
			QueueOutPointer = (QueueOutPointer + 1) % QUEUE_SIZE;
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

void GPIOP_Send(tPacket* msg)
{
	Status.Output.Buffer[Status.Output.inPointer] = msg->Start;
	Status.Output.inPointer = (Status.Output.inPointer + 1) % BUFFER_SIZE;

	Status.Output.Buffer[Status.Output.inPointer] = msg->Direction;
	Status.Output.inPointer = (Status.Output.inPointer + 1) % BUFFER_SIZE;

	Status.Output.Buffer[Status.Output.inPointer] = msg->Class;
	Status.Output.inPointer = (Status.Output.inPointer + 1) % BUFFER_SIZE;

	Status.Output.Buffer[Status.Output.inPointer] = msg->ID;
	Status.Output.inPointer = (Status.Output.inPointer + 1) % BUFFER_SIZE;

	Status.Output.Buffer[Status.Output.inPointer] = msg->CommandH;
	Status.Output.inPointer = (Status.Output.inPointer + 1) % BUFFER_SIZE;

	Status.Output.Buffer[Status.Output.inPointer] = msg->CommandL;
	Status.Output.inPointer = (Status.Output.inPointer + 1) % BUFFER_SIZE;

	for (int i = 0; i < msg->ParamCount; i++)
	{
		Status.Output.Buffer[Status.Output.inPointer] = msg->Params[i];
		Status.Output.inPointer = (Status.Output.inPointer + 1) % BUFFER_SIZE;
	}
	
	Status.Output.Buffer[Status.Output.inPointer] = msg->Checksum;
	Status.Output.inPointer = (Status.Output.inPointer + 1) % BUFFER_SIZE;

	Status.Output.Buffer[Status.Output.inPointer] = msg->End;
	Status.Output.inPointer = (Status.Output.inPointer + 1) % BUFFER_SIZE;
	
	Status.TransferStatus = WRITE_OUTGOING;
}

inline void GPIOP_FillPacket(tPacket* msg)
{
	int i = 0;
	// Header
	msg->Start = Paquete[i++];
	msg->Direction = Paquete[i++];
	msg->Class = Paquete[i++];
	msg->ID = Paquete[i++] - '0';
	// Message
	msg->CommandH = Paquete[i++];
	msg->CommandL = Paquete[i++];
	msg->ParamCount = index - MIN_PACKET_SIZE;
	for (int j = 0; j < msg->ParamCount; j++)
		msg->Params[j] = Paquete[i++];
	// Footer
	msg->Checksum = Paquete[i++];
	msg->End = Paquete[i];

	msg->IOInterface = INTERFACE_UART;
	msg->Valid = YES;
}
inline void GPIOP_Checksum(tPacket* msg)
{
	msg->Checksum = 'F';
}
