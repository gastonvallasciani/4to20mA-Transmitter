/*
 * File:   main.c
 * Author: Nico Christie
 *
 * Created on 1 de septiembre de 2016, 11:10
 */

#include "mcc_generated_files/mcc.h"
#include "tasks.h"
#include "UART.h"
#include "I2C.h"
#include "devices.h"
#include "mcc_generated_files/epwm1.h"
#include "mcc_generated_files/epwm2.h"
#include "epwm3.h"
#include "pwm4.h"
#include "pwm5.h"

//#pragma warning disable 752 // Conversion to shorter data type

void main(void)
{
	// Las versiones de Firmware y Hardware
	// que reporta el micro están en 'comm.c'
	
	// Code Configurator v3
	// El micro está configurado para tener un
	// clock de 64MHz, pero corre a 16MIPS, por
	// lo que parecería que no se pueden usar 
	// interrupciones de Timer a intervalos 
	// menores a aprox 100us
	
	// Ojo con el uso multiplexado de P2B en RC0
	// #pragma config P2BMX = PORTC0
	
	SYSTEM_Initialize();	// NADA ANTES QUE ESTO (1).
	InitTasks();			// NADA ANTES QUE ESTO (2).
    //EPWM1_LoadDutyValue(682); //
    //EPWM3_LoadDutyValue(682);
    //PWM4_LoadDutyValue(682);
    //PWM5_LoadDutyValue(682);
	
	//UART_Send_Debug("Brainiac Firmware");
	while (true)
	{
		I2C_GetNewMessages();
		I2C_ProcessMessages();
       

        //UART_GetNewMessages();		// Recibe mensajes nuevos
        //UART_ProcessMessages();		// Procesa comandos recibidos

            MainTask();	// Actualiza estados de sensores, botones y motores
	}
	return;
}
