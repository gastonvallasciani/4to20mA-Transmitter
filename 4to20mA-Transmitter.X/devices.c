/*
 * File:   devices.c
 * Author: Nico Christie
 *
 * Created on 30 de marzo de 2016, 11:37
 */

#include "mcc_generated_files/epwm1.h"
#include "mcc_generated_files/epwm2.h"
#include "epwm3.h"
#include "pwm4.h"
#include "pwm5.h"
#include "tc_pin_manager.h"
#include "properties.h"
#include "devices.h"
#include "tasks.h"
#include "UART.h"
#include "I2C.h"

#include <math.h>

#define HARDWARE_FIRMWARE_VERSION_SIZE 4
const char VERSION_FIRMWARE[] = "1.0";
const char VERSION_HARDWARE[] = "2.0";		// Placa 4TO20 Transmitter 2.0

tGeneric_Device Me;

void Send_ACK(tPacket*);
void Send_NAK(tPacket*, unsigned char);
void Send_Firmware(tPacket*);
void Send_Hardware(tPacket*);
void Send(tPacket*);

unsigned char ProcessDevice(tPacket*);
unsigned char ProcessPaPReferencia(tPacket*);
unsigned char ProcessLnLReferencia(tPacket*);
unsigned char ProcessSrVReferencia(tPacket*);
unsigned char ProcessCompuerta(tPacket*);
unsigned char ProcessSensores(tPacket*);
unsigned char ProcessBotones(tPacket*);
unsigned char ProcessForward(tPacket*);
unsigned char Process4TO20Transmitter(tPacket* msg);

void TC_Devices_Init()
{
	if (MemoryIsInit())
	{
		// Read stored values
		Me.ID = ReadID();
		Me.Class = ReadClass();
    }
	else
	{
		// Save defaults
		Me.Class = CLASS_ONLINE_4TO20;
		Me.ID = 1;
		
		SaveClass(Me.Class);
		SaveID(Me.ID);
        
		MemoryInit();
        
	}
}

void Send_Status(unsigned char CommandH, unsigned char CommandL, unsigned char Status)
{
	static tPacket msg;
	msg.Start = SOH;
	msg.Class = Me.Class;
	msg.ID = Me.ID;
	msg.CommandH = CommandH;
	msg.CommandL = CommandL;
	msg.Params[0] = Status + '0';
	msg.Checksum = 'F';
	msg.End = EOT;
	
	msg.ParamCount = 1;

	switch (Me.Class)
	{
		case CLASS_ONLINE_RACK:
			msg.Direction = DEV_TO_PC;
			msg.IOInterface = INTERFACE_UART;
			break;
		case CLASS_ONLINE_OLSEN:
			msg.Direction = CAN_BRIDGE;
			msg.IOInterface = INTERFACE_CAN;
			break;
		case CLASS_ONLINE_MUX:
			msg.Direction = I2C_BRIDGE;
			msg.IOInterface = INTERFACE_I2C;
			Send(&msg);
			msg.Direction = DEV_TO_PC;
			msg.IOInterface = INTERFACE_UART;
			break;
        case CLASS_ONLINE_4TO20:
			//msg.Direction = I2C_BRIDGE;
			//msg.IOInterface = INTERFACE_I2C;
			//Send(&msg);
			break;
		default:
			msg.Direction = DEV_TO_PC;
			msg.IOInterface = INTERFACE_UART;
			break;
	}
	Send(&msg);
}

void Send_ACK(tPacket* msg)
{
	msg->Class = Me.Class;
	msg->ID = Me.ID;
	msg->CommandH = ACK;
	msg->CommandL = ACK;
	msg->ParamCount = 0;
	Send(msg);
}
void Send_NAK(tPacket* msg, unsigned char errCode)
{
	msg->Class = Me.Class;
	msg->ID = Me.ID;
	msg->CommandH = NAK;
	msg->CommandL = NAK;
	msg->Params[0] = errCode;
	msg->ParamCount = 1;
	Send(msg);
}
void Send_Firmware(tPacket* msg)
{
	msg->Class = Me.Class;
	msg->ID = Me.ID;
	msg->CommandH = COMMANDS_HIGH_DEVICE_QUERY;
	msg->CommandL = COMMANDS_LOW_GET_FIRMWARE;
	for (int i = 0; i < HARDWARE_FIRMWARE_VERSION_SIZE; i++)
		msg->Params[i] = VERSION_FIRMWARE[i];
	msg->ParamCount = HARDWARE_FIRMWARE_VERSION_SIZE;
	Send(msg);
}
void Send_Hardware(tPacket* msg)
{
	msg->Class = Me.Class;
	msg->ID = Me.ID;
	msg->CommandH = COMMANDS_HIGH_DEVICE_QUERY;
	msg->CommandL = COMMANDS_LOW_GET_HARDWARE;
	for (int i = 0; i < HARDWARE_FIRMWARE_VERSION_SIZE; i++)
		msg->Params[i] = VERSION_HARDWARE[i];
	msg->ParamCount = HARDWARE_FIRMWARE_VERSION_SIZE;
	Send(msg);
}

void Send(tPacket* msg)
{
	switch(msg->IOInterface)
	{
		case INTERFACE_UART:
			UART_Send(msg);
			break;
		case INTERFACE_CAN:
			//CAN_Send(msg);
			break;
		case INTERFACE_I2C:
			//Delay(5 * _100mSeg);
			I2C_Send(msg);
			break;
	}
	Delay(_1mSeg); // Margen en caso de encadenamiento de mensajes
}

unsigned char UART_ProcessPacket(tPacket* msg)
{
	unsigned char result = 1;

	// Falta filtrar Me.Class
	if ((msg->Direction == PC_TO_DEV) && 
		((msg->ID != Me.ID) && (msg->ID != UART_BROADCAST_ID)))
	{
		Send_NAK(msg, ERROR_CODE_WRONG_ID);
		return result;
	}

	switch (msg->Direction)
	{
		case PC_TO_DEV:
			switch (msg->CommandH)
			{
				case COMMANDS_HIGH_DEVICE_QUERY:
					result = ProcessDevice(msg);
					break;
				case COMMANDS_HIGH_MOTOR_REFERENCIA:
					result = ProcessPaPReferencia(msg);
					break;
				case COMMANDS_HIGH_MOTOR_COMPUERTA:
					result = ProcessCompuerta(msg);
					break;
				case COMMANDS_HIGH_SENSORES:
					result = ProcessSensores(msg);
					break;
				case COMMANDS_HIGH_BOTONES:
					result = ProcessBotones(msg);
					break;
                case COMMANDS_HIGH_4TO20TX:
				//	result = Process4TO20Transmitter(msg);
					break;
				default:
					Send_NAK(msg, ERROR_CODE_COMMAND_HIGH_UNKNOWN);
					break;
			}
			break;
		case CAN_BRIDGE:
		case I2C_BRIDGE:
			result = ProcessForward(msg);
			break;
		case DEV_TO_PC:
			Send_NAK(msg, ERROR_CODE_WRONG_DIRECTION);
			break;
		default:
			Send_NAK(msg, ERROR_CODE_WRONG_DIRECTION);
			break;
	}
	return result;
}
unsigned char I2C_ProcessPacket(tPacket* msg)
{
	unsigned char result = 1;
	
	switch (msg->Direction)
	{
		case PC_TO_DEV:
            //LED_STATUS_On();
			//msg->Direction = I2C_BRIDGE;
			switch (msg->CommandH)
			{
				case COMMANDS_HIGH_DEVICE_QUERY:
					result = ProcessDevice(msg);
					break;
				case COMMANDS_HIGH_MOTOR_REFERENCIA:
					result = ProcessPaPReferencia(msg);
					break;
				case COMMANDS_HIGH_MOTOR_COMPUERTA:
					result = ProcessCompuerta(msg);
					break;
				case COMMANDS_HIGH_SENSORES:
					result = ProcessSensores(msg);
					break;
				case COMMANDS_HIGH_BOTONES:
					result = ProcessBotones(msg);
					break;
                case COMMANDS_HIGH_4TO20TX:
                    //LED_STATUS_On();
                    result = Process4TO20Transmitter(msg);
                    break;
				default:
					//Send_NAK(msg, ERROR_CODE_COMMAND_HIGH_UNKNOWN);
					break;
			}
			break;
		case I2C_BRIDGE:
			msg->Direction = DEV_TO_PC;
			result = ProcessForward(msg);
			break;
		case CAN_BRIDGE:
		case DEV_TO_PC:
			//Send_NAK(msg, ERROR_CODE_WRONG_DIRECTION);
			break;			
		default:
			break;
	}
	return result;
}

unsigned char Process4TO20Transmitter(tPacket* msg)
{
    unsigned char result = 1;
    uint16_t Data_Received = 0 ;
    float Online_data = 0;
    uint16_t PWM_Duty = 0;
      switch (msg->CommandL)
        {
            case COMMANDS_LOW_CONSTITUYENTE1:
                    //LED_STATUS_On(); 
                    RELAY1_Toggle();
                    Data_Received = ((msg->Params[0])<<8)
					  + ((msg->Params[1]));
                    Online_data = (((float)(Data_Received))/100);
                    Online_data = ((Online_data)*682)/100;
                    PWM_Duty = (uint16_t)(Online_data);
                    EPWM1_LoadDutyValue(round(PWM_Duty));
                break;                                                                //gav  
            case COMMANDS_LOW_CONSTITUYENTE2:
                    //LED_STATUS_On();
                    RELAY1_Toggle();
                    Data_Received = ((msg->Params[0])<<8)
					  + ((msg->Params[1]));
                    Online_data = (((float)(Data_Received))/100);
                    Online_data = ((Online_data)*682)/100;
                    PWM_Duty = (uint16_t)(Online_data);
                    EPWM3_LoadDutyValue(round(PWM_Duty));
                break;                                                              //gav
            case COMMANDS_LOW_CONSTITUYENTE3:     
                    //LED_STATUS_On();
                    RELAY1_Toggle();
                    Data_Received = ((msg->Params[0])<<8)
					  + ((msg->Params[1]));
                    Online_data = (((float)(Data_Received))/100);
                    Online_data = ((Online_data)*682)/100;
                    PWM_Duty = (uint16_t)(Online_data);
                    PWM4_LoadDutyValue(round(PWM_Duty));
                break;
            case COMMANDS_LOW_CONSTITUYENTE4:                                       //gav
                    //LED_STATUS_On();
                    RELAY1_Toggle();
                    Data_Received = ((msg->Params[0])<<8)
					  + ((msg->Params[1]));
                    Online_data = (((float)(Data_Received))/100);
                    Online_data = ((Online_data)*682)/100;
                    PWM_Duty = (uint16_t)(Online_data);
                    PWM5_LoadDutyValue(round(PWM_Duty));
                break;
            case COMMANDS_LOW_CONSTITUYENTE5:                                       //gav
                    //LED_STATUS_On();
                    RELAY1_Toggle();
                    Data_Received = ((msg->Params[0])<<8)
					  + ((msg->Params[1]));
                    Online_data = (((float)(Data_Received))/100);
                    Online_data = ((Online_data)*682)/100;
                    PWM_Duty = (uint16_t)(Online_data);
                    EPWM1_LoadDutyValue(round(PWM_Duty));
                break;
            case COMMANDS_LOW_CONSTITUYENTE6:                                       //gav
                    //LED_STATUS_On();
                    RELAY1_Toggle();
                    Data_Received = ((msg->Params[0])<<8)
					  + ((msg->Params[1]));
                    Online_data = (((float)(Data_Received))/100);
                    Online_data = ((Online_data)*682)/100;
                    PWM_Duty = (uint16_t)(Online_data);
                    EPWM3_LoadDutyValue(round(PWM_Duty));
                break;
            case COMMANDS_LOW_CONSTITUYENTE7:                                       //gav
                    //LED_STATUS_On();
                    RELAY1_Toggle();
                    Data_Received = ((msg->Params[0])<<8)
					  + ((msg->Params[1]));
                    Online_data = (((float)(Data_Received))/100);
                    Online_data = ((Online_data)*682)/100;
                    PWM_Duty = (uint16_t)(Online_data);
                    PWM4_LoadDutyValue(round(PWM_Duty));
                break;
            case COMMANDS_LOW_CONSTITUYENTE8:
                    //LED_STATUS_On();
                    RELAY1_Toggle();
                    Data_Received = ((msg->Params[0] - '0')<<8)
					  + ((msg->Params[1] - '0'));
                    Online_data = (((float)(Data_Received))/100);
                    if (Online_data>100){Online_data = 100;}
                    if (Online_data<0){Online_data = 0;}
                    PWM_Duty = (((uint16_t)(Online_data))*682)/100;
                    PWM5_LoadDutyValue(round(PWM_Duty));
                break;
            default:
                //Send_NAK(msg, ERROR_CODE_COMMAND_LOW_UNKNOWN);
                break;
    }
    return result;
}
unsigned char ProcessDevice(tPacket* msg)
{
	// CommandH es COMMANDS_HIGH_DEVICE_PROPERTIES
	unsigned char Result = 1;
	
	switch (msg->CommandL)
	{
		case COMMANDS_LOW_GET_FIRMWARE:
			Send_ACK(msg);
			Send_Firmware(msg);
			break;
		case COMMANDS_LOW_GET_HARDWARE:
			Send_ACK(msg);
			Send_Hardware(msg);
			break;
		case COMMANDS_LOW_SAVE_CLASS:
			if (Me.Class != msg->Params[0])
			{
				Send_ACK(msg);
				Me.Class = msg->Params[0];
				SaveClass(Me.Class);
			}
			break;
		case COMMANDS_LOW_SAVE_ID:
			if (Me.ID != msg->Params[0] - '0')
			{
				if (msg->Params[0] != '0')
				{
					Send_ACK(msg);
					Me.ID = msg->Params[0] - '0';
					SaveID(Me.ID);
					UpdateID(); // LCD
				}
				else
				{
					Send_NAK(msg, ERROR_CODE_INVALID_PARAMETER);
				}
			}
			break;
		case COMMANDS_LOW_GET:
			Send_ACK(msg); // Pedido de vida
			break;
		case COMMANDS_LOW_FLUSH:
			// Software is receiving with errors, try to flush UART
			for (int k = 0; k < 10; k++) Send_ACK(msg);
			break;
		case COMMANDS_LOW_HARD_RESET:
			asm("RESET");
			break;
		default:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_UNKNOWN);
			break;
	}
	return Result;
}
unsigned char ProcessPaPReferencia(tPacket* msg)
{
	// CommandH es COMMANDS_HIGH_MOTOR_REFERENCIA
	unsigned char result = 1;
	
	switch (msg->CommandL)
	{
		case COMMANDS_LOW_GET:
            Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_SET:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_SEEKHOME:
            Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_GOTO_MUX_POS:
            Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_SAVE_MUX_POS:
            Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);			
			break;
		case COMMANDS_LOW_GOTODARK:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
            break;
		case COMMANDS_LOW_GOTOREFERENCE:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
            break;
		case COMMANDS_LOW_GOTOPRODUCTSTART:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
            break;
		case COMMANDS_LOW_GOTOPRODUCTEND:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
            break;
		case COMMANDS_LOW_MOVEFORWARDS:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
            break;
		case COMMANDS_LOW_MOVEBACKWARDS:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
            break;
		case COMMANDS_LOW_SPEED:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
            break;
		case COMMANDS_LOW_DRIVEMODE:
            Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_HOLD_DUTY:
            Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_STEPCOUNT:
            Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_OVERSHOOT:
            Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_SAVE_DARK:
            Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_SAVE_REFERENCE:
            Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_SAVE_PRODUCTSTART:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_SAVE_PRODUCTEND:
            Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		default:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_UNKNOWN);
			break;
	}
	return result;
}
unsigned char ProcessLnLReferencia(tPacket* msg)
{
	// CommandH es COMMANDS_HIGH_MOTOR_REFERENCIA
	unsigned char result = 1;
	
	switch (msg->CommandL)
	{
		case COMMANDS_LOW_GET:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_SET:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_SEEKHOME:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_GOTODARK:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_GOTOREFERENCE:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_GOTOPRODUCTSTART:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_GOTOPRODUCTEND:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_MOVEFORWARDS:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_MOVEBACKWARDS:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_SPEED:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_STEPCOUNT:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_SAVE_DARK:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_SAVE_REFERENCE:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_SAVE_PRODUCTSTART:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_SAVE_PRODUCTEND:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		default:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_UNKNOWN);
			break;
	}
	return result;
}
unsigned char ProcessSrVReferencia(tPacket* msg)
{
	// CommandH es COMMANDS_HIGH_MOTOR_REFERENCIA
	unsigned char result = 1;
	
	switch (msg->CommandL)
	{
		case COMMANDS_LOW_GET:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_SET:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_SEEKHOME:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_GOTODARK:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_GOTOREFERENCE:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_GOTOPRODUCTSTART:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_GOTOPRODUCTEND:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_MOVEFORWARDS:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_MOVEBACKWARDS:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_SPEED:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_DRIVEMODE:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_HOLD_DUTY:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_STEPCOUNT:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_SAVE_DARK:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_SAVE_REFERENCE:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_SAVE_PRODUCTSTART:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_SAVE_PRODUCTEND:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		default:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_UNKNOWN);
			break;
	}
	return result;
}
unsigned char ProcessCompuerta(tPacket* msg)
{
	unsigned char result = 1;
	
	// CommandH es COMMANDS_HIGH_MOTOR_COMPUERTA
	switch (msg->CommandL)
	{
		case COMMANDS_LOW_SEEKHOME:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_CLOSE:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_MOVEFORWARDS:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_MOVEBACKWARDS:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_SPEED:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_STEPCOUNT:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_HOLD_DUTY:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_SAVE_OFFSET:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		default:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_UNKNOWN);
			break;
	}
	return result;
}
unsigned char ProcessSensores(tPacket* msg)
{
	unsigned char result = 1;
	
	// CommandH es COMMANDS_HIGH_SENSORES
	switch (msg->CommandL)
	{
		case COMMANDS_LOW_GET:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_CAJON:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_COMPUERTA:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_LAMPARA:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_MUESTRA:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_REFERENCIA:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_TEMPERATURA:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		default:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_UNKNOWN);
			break;
	}
	return result;
}
unsigned char ProcessBotones(tPacket* msg)
{
	unsigned char result = 1;
	
	// CommandH es COMMANDS_HIGH_BOTONES
	switch (msg->CommandL)
	{
		case COMMANDS_LOW_GET:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_BOTONSTART:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		case COMMANDS_LOW_BOTONPOWER:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_NOTSUPPORTED);
			break;
		default:
			Send_NAK(msg, ERROR_CODE_COMMAND_LOW_UNKNOWN);
			break;
	}
	return result;
}
unsigned char ProcessForward(tPacket* msg)
{
	unsigned char result = 1;
	switch(msg->IOInterface)
	{
		case INTERFACE_UART:
			switch (msg->Direction)
			{
				case CAN_BRIDGE:
					msg->Direction = PC_TO_DEV;
					msg->IOInterface = INTERFACE_CAN;
					break;
				case I2C_BRIDGE:
					msg->Direction = PC_TO_DEV;
					msg->IOInterface = INTERFACE_I2C;
					break;
				default:
					Send_NAK(msg, ERROR_CODE_WRONG_DIRECTION);
					break;
			}
			break;
		case INTERFACE_CAN:
		case INTERFACE_I2C:
			msg->Direction = DEV_TO_PC;
			msg->IOInterface = INTERFACE_UART;
			break;
	}
	Send(msg);
	return result;
}
