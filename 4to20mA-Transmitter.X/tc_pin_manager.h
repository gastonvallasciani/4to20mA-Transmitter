// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef TC_PIN_MANAGER_TEMPLATE_H
#define	TC_PIN_MANAGER_TEMPLATE_H

// IDE: MPLAB X
// Compiler: Microchip XC8
// Placas: Placa de control únicamente.
// Device: PIC18F46K22

// PIN_MANAGER.H NO DEBERIA SER INCLUIDO EN NINGUN OTRO ARCHIVO
// EL MAPEO DE PINES DEL PIC A LA PLACA DE TC SE HACE ACA Y ASI
// SI CAMBIA ALGUN PIN DE LA PLACA, SE REDEFINE ESE PIN Y SOLO 
// CAMBIA PIN_MANAGER.H Y ESTE ARCHIVO
#include <xc.h>
#include "mcc_generated_files/pin_manager.h"

#define YES 1
#define NO  0

#define LED_STATUS_On()             IO_RA0_unused_SetHigh()
#define LED_STATUS_Off()            IO_RA0_unused_SetLow()
#define LED_STATUS_Toggle()         IO_RA0_unused_Toggle()

#define BTN5_MATRICIAL_OUTPUT()     IO_RB1_BTN5_MATRICIAL_SetDigitalOutput()
#define BTN5_MATRICIAL_INPUT()      IO_RB1_BTN5_MATRICIAL_SetDigitalInput()
#define BTN5_MATRICIAL()            IO_RB1_BTN5_MATRICIAL_GetValue()
#define BTN5_High()                 IO_RB1_BTN5_MATRICIAL_SetHigh()
#define BTN5_Low()                  IO_RB1_BTN5_MATRICIAL_SetLow()

#define BTN4_MATRICIAL_OUTPUT()     IO_RB2_BTN4_MATRICIAL_SetDigitalOutput()
#define BTN4_MATRICIAL_INPUT()      IO_RB2_BTN4_MATRICIAL_SetDigitalInput()
#define BTN4_MATRICIAL()            IO_RB2_BTN4_MATRICIAL_GetValue()
#define BTN4_High()                 IO_RB2_BTN4_MATRICIAL_SetHigh()
#define BTN4_Low()                  IO_RB2_BTN4_MATRICIAL_SetLow()

#define BTN3_MATRICIAL_OUTPUT()     IO_RB3_BTN3_MATRICIAL_SetDigitalOutput()
#define BTN3_MATRICIAL_INPUT()      IO_RB3_BTN3_MATRICIAL_SetDigitalInput()
#define BTN3_MATRICIAL()            IO_RB3_BTN3_MATRICIAL_GetValue()
#define BTN3_High()                 IO_RB3_BTN3_MATRICIAL_SetHigh()
#define BTN3_Low()                  IO_RB3_BTN3_MATRICIAL_SetLow()

#define BTN2_MATRICIAL_OUTPUT()     IO_RB4_BTN2_MATRICIAL_SetDigitalOutput()
#define BTN2_MATRICIAL_INPUT()      IO_RB4_BTN2_MATRICIAL_SetDigitalInput()
#define BTN2_MATRICIAL()            IO_RB4_BTN2_MATRICIAL_GetValue()
#define BTN2_High()                 IO_RB4_BTN2_MATRICIAL_SetHigh()
#define BTN2_Low()                  IO_RB4_BTN2_MATRICIAL_SetLow()

#define BTN1_MATRICIAL_OUTPUT()     IO_RB5_BTN1_MATRICIAL_SetDigitalOutput()
#define BTN1_MATRICIAL_INPUT()      IO_RB5_BTN1_MATRICIAL_SetDigitalInput()
#define BTN1_MATRICIAL()            IO_RB5_BTN1_MATRICIAL_GetValue()
#define BTN1_High()                 IO_RB5_BTN1_MATRICIAL_SetHigh()
#define BTN1_Low()                  IO_RB5_BTN1_MATRICIAL_SetLow()

#define BUZZER_ON                   IO_RB0_SONIDO_SetHigh()
#define BUZZER_OFF                  IO_RB0_SONIDO_SetLow()

#define SENSOR_B_OPTO_HOME_INPUT()  IO_RB4_BTN2_MATRICIAL_SetDigitalInput()
#define SENSOR_C_OPTO_HOME_INPUT()  IO_RB3_BTN3_MATRICIAL_SetDigitalInput()
#define SENSOR_OPTO_HOME()          IO_RB3_BTN3_MATRICIAL_GetValue()

// Pin de señalización hacia la placa de Control OnLine
#define MOTOR_REF_ENPOS_OUTPUT()    IO_RD4_MOTOR_REF_ENPOS_SetDigitalOutput()
#define MOTOR_REF_ENPOS_High()      IO_RD4_MOTOR_REF_ENPOS_SetHigh()
#define MOTOR_REF_ENPOS_Low()       IO_RD4_MOTOR_REF_ENPOS_SetLow()

// LED indicador de detección de Home de motor
#define MOTOR_REF_LED_Toggle()      IO_RC5_MOTOR_REF_ENPOS_LED_Toggle()
#define MOTOR_REF_LED_ON()          IO_RC5_MOTOR_REF_ENPOS_LED_SetHigh()
#define MOTOR_REF_LED_OFF()         IO_RC5_MOTOR_REF_ENPOS_LED_SetLow()

// Motor Paso a Paso de Referencia
#define RELAY2ON()         IO_RD6_MOTOR_REF_EN_A_SetHigh()
#define RELAY2OFF()        IO_RD6_MOTOR_REF_EN_A_SetLow()
#define RELAY1ON()         IO_RD7_MOTOR_REF_EN_B_SetHigh()
#define RELAY1OFF()        IO_RD7_MOTOR_REF_EN_B_SetLow()

// IN 1
#define MOTOR_REF_IN1_SET(x)        LATC2 = x
#define MOTOR_REF_IN1_OFF()         IO_RC2_MOTOR_REF_IN_A_SetLow()
#define MOTOR_REF_IN1_ON()          IO_RC2_MOTOR_REF_IN_A_SetHigh()
// IN 2
#define MOTOR_REF_IN2_SET(x)        LATD5 = x
#define MOTOR_REF_IN2_OFF()         IO_RD5_MOTOR_REF_IN_B_SetLow()
#define MOTOR_REF_IN2_ON()          IO_RD5_MOTOR_REF_IN_B_SetHigh()
// IN 3
#define MOTOR_REF_IN3_SET(x)        LATC1 = x
#define MOTOR_REF_IN3_OFF()         IO_RC1_MOTOR_REF_IN_C_SetLow()
#define MOTOR_REF_IN3_ON()          IO_RC1_MOTOR_REF_IN_C_SetHigh()
// IN 4
#define MOTOR_REF_IN4_SET(x)        LATC0 = x
#define MOTOR_REF_IN4_OFF()         IO_RC0_MOTOR_REF_IN_D_SetLow()
#define MOTOR_REF_IN4_ON()          IO_RC0_MOTOR_REF_IN_D_SetHigh()

// Fases para el motor de Referencia
#define MOTOR_REF_FASE_0000()       MOTOR_REF_IN1_OFF(); MOTOR_REF_IN2_OFF(); MOTOR_REF_IN3_OFF(); MOTOR_REF_IN4_OFF()
#define MOTOR_REF_FASE_0001()       MOTOR_REF_IN1_OFF(); MOTOR_REF_IN2_OFF(); MOTOR_REF_IN3_OFF(); MOTOR_REF_IN4_ON()
#define MOTOR_REF_FASE_0010()       MOTOR_REF_IN1_OFF(); MOTOR_REF_IN2_OFF(); MOTOR_REF_IN3_ON();  MOTOR_REF_IN4_OFF()
#define MOTOR_REF_FASE_0100()       MOTOR_REF_IN1_OFF(); MOTOR_REF_IN2_ON();  MOTOR_REF_IN3_OFF(); MOTOR_REF_IN4_OFF()
#define MOTOR_REF_FASE_1000()       MOTOR_REF_IN1_ON();  MOTOR_REF_IN2_OFF(); MOTOR_REF_IN3_OFF(); MOTOR_REF_IN4_OFF()
#define MOTOR_REF_FASE_0101()       MOTOR_REF_IN1_OFF(); MOTOR_REF_IN2_ON();  MOTOR_REF_IN3_OFF(); MOTOR_REF_IN4_ON()
#define MOTOR_REF_FASE_0110()       MOTOR_REF_IN1_OFF(); MOTOR_REF_IN2_ON();  MOTOR_REF_IN3_ON();  MOTOR_REF_IN4_OFF()
#define MOTOR_REF_FASE_1010()       MOTOR_REF_IN1_ON();  MOTOR_REF_IN2_OFF(); MOTOR_REF_IN3_ON();  MOTOR_REF_IN4_OFF()
#define MOTOR_REF_FASE_1001()       MOTOR_REF_IN1_ON();  MOTOR_REF_IN2_OFF(); MOTOR_REF_IN3_OFF(); MOTOR_REF_IN4_ON()

#define MOTOR_REF_PWM_OFF           PSTR1CON = 0x00; PSTR2CON = 0x00
#define MOTOR_REF_PWM_IN1           PSTR1CON = 0x01; PSTR2CON = 0x00
#define MOTOR_REF_PWM_IN2           PSTR1CON = 0x02; PSTR2CON = 0x00
#define MOTOR_REF_PWM_IN3           PSTR1CON = 0x00; PSTR2CON = 0x01
#define MOTOR_REF_PWM_IN4           PSTR1CON = 0x00; PSTR2CON = 0x02
#define MOTOR_REF_PWM_IN2_IN4       PSTR1CON = 0x02; PSTR2CON = 0x02
#define MOTOR_REF_PWM_IN2_IN3       PSTR1CON = 0x02; PSTR2CON = 0x01
#define MOTOR_REF_PWM_IN1_IN3       PSTR1CON = 0x01; PSTR2CON = 0x01
#define MOTOR_REF_PWM_IN1_IN4       PSTR1CON = 0x01; PSTR2CON = 0x02

// Free
#define MOTOR_REF_FASE_0()          MOTOR_REF_PWM_OFF //; MOTOR_REF_FASE_0000()
// Normal
#define MOTOR_REF_FASE_1()          MOTOR_REF_PWM_IN4 //; MOTOR_REF_FASE_0001()
#define MOTOR_REF_FASE_3()          MOTOR_REF_PWM_IN2 //; MOTOR_REF_FASE_0100()
#define MOTOR_REF_FASE_5()          MOTOR_REF_PWM_IN3 //; MOTOR_REF_FASE_0010()
#define MOTOR_REF_FASE_7()          MOTOR_REF_PWM_IN1 //; MOTOR_REF_FASE_1000()
// Wave drive
#define MOTOR_REF_FASE_2()          MOTOR_REF_PWM_IN2_IN4 //; MOTOR_REF_FASE_0101()
#define MOTOR_REF_FASE_4()          MOTOR_REF_PWM_IN2_IN3 //; MOTOR_REF_FASE_0110()
#define MOTOR_REF_FASE_6()          MOTOR_REF_PWM_IN1_IN3 //; MOTOR_REF_FASE_1010()
#define MOTOR_REF_FASE_8()          MOTOR_REF_PWM_IN1_IN4 //; MOTOR_REF_FASE_1001()

// Pantalla
#define PANTALLA_EN_LCD_High()        IO_RA5_PANTALLA_EN_LCD_SetHigh()
#define PANTALLA_EN_LCD_Low()       IO_RA5_PANTALLA_EN_LCD_SetLow()
#define PANTALLA_EN_BL_ON()         IO_RE0_PANTALLA_EN_BL_SetHigh()
#define PANTALLA_EN_BL_OFF()        IO_RE0_PANTALLA_EN_BL_SetLow()
#define PANTALLA_RS_High()          IO_RE1_PANTALLA_RS_SetHigh()
#define PANTALLA_RS_Low()           IO_RE1_PANTALLA_RS_SetLow()

#define PANTALLA_D4_ON()            IO_RD0_PANTALLA_D4_SetHigh()
#define PANTALLA_D4_OFF()           IO_RD0_PANTALLA_D4_SetLow()
#define PANTALLA_D5_ON()            IO_RD1_PANTALLA_D5_SetHigh()
#define PANTALLA_D5_OFF()           IO_RD1_PANTALLA_D5_SetLow()
#define PANTALLA_D6_ON()            IO_RD2_PANTALLA_D6_SetHigh()
#define PANTALLA_D6_OFF()           IO_RD2_PANTALLA_D6_SetLow()
#define PANTALLA_D7_ON()            IO_RD3_PANTALLA_D7_SetHigh()
#define PANTALLA_D7_OFF()           IO_RD3_PANTALLA_D7_SetLow()

/*
#define RA0 PORTAbits.RA0
#define RA1 PORTAbits.RA1
#define RA2 PORTAbits.RA2
#define RA3 PORTAbits.RA3
#define RA4 PORTAbits.RA4
#define RA5 PORTAbits.RA5
#define RA6 PORTAbits.RA6
#define RA7 PORTAbits.RA7

#define RB0 PORTBbits.RB0
#define RB1 PORTBbits.RB1
#define RB2 PORTBbits.RB2
#define RB3 PORTBbits.RB3
#define RB4 PORTBbits.RB4
#define RB5 PORTBbits.RB5
#define RB6 PORTBbits.RB6
#define RB7 PORTBbits.RB7

#define RC0 PORTCbits.RC0
#define RC1 PORTCbits.RC1
#define RC2 PORTCbits.RC2
#define RC3 PORTCbits.RC3
#define RC4 PORTCbits.RC4
#define RC5 PORTCbits.RC5
#define RC6 PORTCbits.RC6
#define RC7 PORTCbits.RC7

#define RD0 PORTDbits.RD0
#define RD1 PORTDbits.RD1
#define RD2 PORTDbits.RD2
#define RD3 PORTDbits.RD3
#define RD4 PORTDbits.RD4
#define RD5 PORTDbits.RD5
#define RD6 PORTDbits.RD6
#define RD7 PORTDbits.RD7

#define RE0 PORTEbits.RE0
#define RE1 PORTEbits.RE1
#define RE2 PORTEbits.RE2
#define RE3 PORTEbits.RE3 
*/

#endif	/* TC_PIN_MANAGER_TEMPLATE_H */
