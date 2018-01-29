/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB(c) Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 3.16
        Device            :  PIC18F46K22
        Version           :  1.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.20

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

    Microchip licenses to you the right to use, modify, copy and distribute
    Software only when embedded on a Microchip microcontroller or digital signal
    controller that is integrated into your product or third party product
    (pursuant to the sublicense terms in the accompanying license agreement).

    You should refer to the license agreement accompanying this Software for
    additional information regarding your rights and obligations.

    SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
    EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
    MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
    IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
    CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
    OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
    CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
    SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*/


#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

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

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set IO_RA0_unused aliases
#define IO_RA0_unused_TRIS               TRISA0
#define IO_RA0_unused_LAT                LATA0
#define IO_RA0_unused_PORT               RA0
#define IO_RA0_unused_ANS                ANSA0
#define IO_RA0_unused_SetHigh()    do { LATA0 = 1; } while(0)
#define IO_RA0_unused_SetLow()   do { LATA0= 0; } while(0)
#define IO_RA0_unused_Toggle()   do { LATA0 = ~LATA0; } while(0)
#define IO_RA0_unused_GetValue()         RA0
#define IO_RA0_unused_SetDigitalInput()    do { TRISA0 = 1; } while(0)
#define IO_RA0_unused_SetDigitalOutput()   do { TRISA0 = 0; } while(0)

#define IO_RA2_unused_SetAnalogMode()   do { ANSA2 = 1; } while(0)
#define IO_RA2_unused_SetDigitalMode()   do { ANSA2 = 0; } while(0)

// get/set IO_RA2_unused aliases
#define IO_RA2_unused_TRIS               TRISA2
#define IO_RA2_unused_LAT                LATA2
#define IO_RA2_unused_PORT               RA2
#define IO_RA2_unused_ANS                ANSA2
#define IO_RA2_unused_SetHigh()    do { LATA2 = 1; } while(0)
#define IO_RA2_unused_SetLow()   do { LATA2 = 0; } while(0)
#define IO_RA2_unused_Toggle()   do { LATA2 = ~LATA2; } while(0)
#define IO_RA2_unused_GetValue()         RA2
#define IO_RA2_unused_SetDigitalInput()    do { TRISA2 = 1; } while(0)
#define IO_RA2_unused_SetDigitalOutput()   do { TRISA2 = 0; } while(0)

#define IO_RA2_unused_SetAnalogMode()   do { ANSA2 = 1; } while(0)
#define IO_RA2_unused_SetDigitalMode()   do { ANSA2 = 0; } while(0)


// get/set IO_RA3_unused aliases
#define IO_RA3_unused_TRIS               TRISA3
#define IO_RA3_unused_LAT                LATA3
#define IO_RA3_unused_PORT               RA3
#define IO_RA3_unused_ANS                ANSA3
#define IO_RA3_unused_SetHigh()    do { LATA3 = 1; } while(0)
#define IO_RA3_unused_SetLow()   do { LATA3 = 0; } while(0)
#define IO_RA3_unused_Toggle()   do { LATA3 = ~LATA3; } while(0)
#define IO_RA3_unused_GetValue()         RA3
#define IO_RA3_unused_SetDigitalInput()    do { TRISA3 = 1; } while(0)
#define IO_RA3_unused_SetDigitalOutput()   do { TRISA3 = 0; } while(0)

#define IO_RA3_unused_SetAnalogMode()   do { ANSA3 = 1; } while(0)
#define IO_RA3_unused_SetDigitalMode()   do { ANSA3 = 0; } while(0)


// get/set IO_RA4_unused aliases
#define IO_RA4_unused_TRIS               TRISA4
#define IO_RA4_unused_LAT                LATA4
#define IO_RA4_unused_PORT               RA4
#define IO_RA4_unused_SetHigh()    do { LATA4 = 1; } while(0)
#define IO_RA4_unused_SetLow()   do { LATA4 = 0; } while(0)
#define IO_RA4_unused_Toggle()   do { LATA4 = ~LATA4; } while(0)
#define IO_RA4_unused_GetValue()         RA4
#define IO_RA4_unused_SetDigitalInput()    do { TRISA4 = 1; } while(0)
#define IO_RA4_unused_SetDigitalOutput()   do { TRISA4 = 0; } while(0)



// get/set IO_RA5_PANTALLA_EN_LCD aliases
#define IO_RA5_PANTALLA_EN_LCD_TRIS               TRISA5
#define IO_RA5_PANTALLA_EN_LCD_LAT                LATA5
#define IO_RA5_PANTALLA_EN_LCD_PORT               RA5
#define IO_RA5_PANTALLA_EN_LCD_ANS                ANSA5
#define IO_RA5_PANTALLA_EN_LCD_SetHigh()    do { LATA5 = 1; } while(0)
#define IO_RA5_PANTALLA_EN_LCD_SetLow()   do { LATA5 = 0; } while(0)
#define IO_RA5_PANTALLA_EN_LCD_Toggle()   do { LATA5 = ~LATA5; } while(0)
#define IO_RA5_PANTALLA_EN_LCD_GetValue()         RA5
#define IO_RA5_PANTALLA_EN_LCD_SetDigitalInput()    do { TRISA5 = 1; } while(0)
#define IO_RA5_PANTALLA_EN_LCD_SetDigitalOutput()   do { TRISA5 = 0; } while(0)

#define IO_RA5_PANTALLA_EN_LCD_SetAnalogMode()   do { ANSA5 = 1; } while(0)
#define IO_RA5_PANTALLA_EN_LCD_SetDigitalMode()   do { ANSA5 = 0; } while(0)


// get/set IO_RB0_SONIDO aliases
#define IO_RB0_SONIDO_TRIS               TRISB0
#define IO_RB0_SONIDO_LAT                LATB0
#define IO_RB0_SONIDO_PORT               RB0
#define IO_RB0_SONIDO_WPU                WPUB0
#define IO_RB0_SONIDO_ANS                ANSB0
#define IO_RB0_SONIDO_SetHigh()    do { LATB0 = 1; } while(0)
#define IO_RB0_SONIDO_SetLow()   do { LATB0 = 0; } while(0)
#define IO_RB0_SONIDO_Toggle()   do { LATB0 = ~LATB0; } while(0)
#define IO_RB0_SONIDO_GetValue()         RB0
#define IO_RB0_SONIDO_SetDigitalInput()    do { TRISB0 = 1; } while(0)
#define IO_RB0_SONIDO_SetDigitalOutput()   do { TRISB0 = 0; } while(0)

#define IO_RB0_SONIDO_SetPullup()    do { WPUB0 = 1; } while(0)
#define IO_RB0_SONIDO_ResetPullup()   do { WPUB0 = 0; } while(0)
#define IO_RB0_SONIDO_SetAnalogMode()   do { ANSB0 = 1; } while(0)
#define IO_RB0_SONIDO_SetDigitalMode()   do { ANSB0 = 0; } while(0)


// get/set IO_RB1_BTN5_MATRICIAL aliases
#define IO_RB1_BTN5_MATRICIAL_TRIS               TRISB1
#define IO_RB1_BTN5_MATRICIAL_LAT                LATB1
#define IO_RB1_BTN5_MATRICIAL_PORT               RB1
#define IO_RB1_BTN5_MATRICIAL_WPU                WPUB1
#define IO_RB1_BTN5_MATRICIAL_ANS                ANSB1
#define IO_RB1_BTN5_MATRICIAL_SetHigh()    do { LATB1 = 1; } while(0)
#define IO_RB1_BTN5_MATRICIAL_SetLow()   do { LATB1 = 0; } while(0)
#define IO_RB1_BTN5_MATRICIAL_Toggle()   do { LATB1 = ~LATB1; } while(0)
#define IO_RB1_BTN5_MATRICIAL_GetValue()         RB1
#define IO_RB1_BTN5_MATRICIAL_SetDigitalInput()    do { TRISB1 = 1; } while(0)
#define IO_RB1_BTN5_MATRICIAL_SetDigitalOutput()   do { TRISB1 = 0; } while(0)

#define IO_RB1_BTN5_MATRICIAL_SetPullup()    do { WPUB1 = 1; } while(0)
#define IO_RB1_BTN5_MATRICIAL_ResetPullup()   do { WPUB1 = 0; } while(0)
#define IO_RB1_BTN5_MATRICIAL_SetAnalogMode()   do { ANSB1 = 1; } while(0)
#define IO_RB1_BTN5_MATRICIAL_SetDigitalMode()   do { ANSB1 = 0; } while(0)


// get/set IO_RB2_BTN4_MATRICIAL aliases
#define IO_RB2_BTN4_MATRICIAL_TRIS               TRISB2
#define IO_RB2_BTN4_MATRICIAL_LAT                LATB2
#define IO_RB2_BTN4_MATRICIAL_PORT               RB2
#define IO_RB2_BTN4_MATRICIAL_WPU                WPUB2
#define IO_RB2_BTN4_MATRICIAL_ANS                ANSB2
#define IO_RB2_BTN4_MATRICIAL_SetHigh()    do { LATB2 = 1; } while(0)
#define IO_RB2_BTN4_MATRICIAL_SetLow()   do { LATB2 = 0; } while(0)
#define IO_RB2_BTN4_MATRICIAL_Toggle()   do { LATB2 = ~LATB2; } while(0)
#define IO_RB2_BTN4_MATRICIAL_GetValue()         RB2
#define IO_RB2_BTN4_MATRICIAL_SetDigitalInput()    do { TRISB2 = 1; } while(0)
#define IO_RB2_BTN4_MATRICIAL_SetDigitalOutput()   do { TRISB2 = 0; } while(0)

#define IO_RB2_BTN4_MATRICIAL_SetPullup()    do { WPUB2 = 1; } while(0)
#define IO_RB2_BTN4_MATRICIAL_ResetPullup()   do { WPUB2 = 0; } while(0)
#define IO_RB2_BTN4_MATRICIAL_SetAnalogMode()   do { ANSB2 = 1; } while(0)
#define IO_RB2_BTN4_MATRICIAL_SetDigitalMode()   do { ANSB2 = 0; } while(0)


// get/set IO_RB3_BTN3_MATRICIAL aliases
#define IO_RB3_BTN3_MATRICIAL_TRIS               TRISB3
#define IO_RB3_BTN3_MATRICIAL_LAT                LATB3
#define IO_RB3_BTN3_MATRICIAL_PORT               RB3
#define IO_RB3_BTN3_MATRICIAL_WPU                WPUB3
#define IO_RB3_BTN3_MATRICIAL_ANS                ANSB3
#define IO_RB3_BTN3_MATRICIAL_SetHigh()    do { LATB3 = 1; } while(0)
#define IO_RB3_BTN3_MATRICIAL_SetLow()   do { LATB3 = 0; } while(0)
#define IO_RB3_BTN3_MATRICIAL_Toggle()   do { LATB3 = ~LATB3; } while(0)
#define IO_RB3_BTN3_MATRICIAL_GetValue()         RB3
#define IO_RB3_BTN3_MATRICIAL_SetDigitalInput()    do { TRISB3 = 1; } while(0)
#define IO_RB3_BTN3_MATRICIAL_SetDigitalOutput()   do { TRISB3 = 0; } while(0)

#define IO_RB3_BTN3_MATRICIAL_SetPullup()    do { WPUB3 = 1; } while(0)
#define IO_RB3_BTN3_MATRICIAL_ResetPullup()   do { WPUB3 = 0; } while(0)
#define IO_RB3_BTN3_MATRICIAL_SetAnalogMode()   do { ANSB3 = 1; } while(0)
#define IO_RB3_BTN3_MATRICIAL_SetDigitalMode()   do { ANSB3 = 0; } while(0)


// get/set IO_RB4_BTN2_MATRICIAL aliases
#define IO_RB4_BTN2_MATRICIAL_TRIS               TRISB4
#define IO_RB4_BTN2_MATRICIAL_LAT                LATB4
#define IO_RB4_BTN2_MATRICIAL_PORT               RB4
#define IO_RB4_BTN2_MATRICIAL_WPU                WPUB4
#define IO_RB4_BTN2_MATRICIAL_ANS                ANSB4
#define IO_RB4_BTN2_MATRICIAL_SetHigh()    do { LATB4 = 1; } while(0)
#define IO_RB4_BTN2_MATRICIAL_SetLow()   do { LATB4 = 0; } while(0)
#define IO_RB4_BTN2_MATRICIAL_Toggle()   do { LATB4 = ~LATB4; } while(0)
#define IO_RB4_BTN2_MATRICIAL_GetValue()         RB4
#define IO_RB4_BTN2_MATRICIAL_SetDigitalInput()    do { TRISB4 = 1; } while(0)
#define IO_RB4_BTN2_MATRICIAL_SetDigitalOutput()   do { TRISB4 = 0; } while(0)

#define IO_RB4_BTN2_MATRICIAL_SetPullup()    do { WPUB4 = 1; } while(0)
#define IO_RB4_BTN2_MATRICIAL_ResetPullup()   do { WPUB4 = 0; } while(0)
#define IO_RB4_BTN2_MATRICIAL_SetAnalogMode()   do { ANSB4 = 1; } while(0)
#define IO_RB4_BTN2_MATRICIAL_SetDigitalMode()   do { ANSB4 = 0; } while(0)


// get/set IO_RB5_BTN1_MATRICIAL aliases
#define IO_RB5_BTN1_MATRICIAL_TRIS               TRISB5
#define IO_RB5_BTN1_MATRICIAL_LAT                LATB5
#define IO_RB5_BTN1_MATRICIAL_PORT               RB5
#define IO_RB5_BTN1_MATRICIAL_WPU                WPUB5
#define IO_RB5_BTN1_MATRICIAL_ANS                ANSB5
#define IO_RB5_BTN1_MATRICIAL_SetHigh()    do { LATB5 = 1; } while(0)
#define IO_RB5_BTN1_MATRICIAL_SetLow()   do { LATB5 = 0; } while(0)
#define IO_RB5_BTN1_MATRICIAL_Toggle()   do { LATB5 = ~LATB5; } while(0)
#define IO_RB5_BTN1_MATRICIAL_GetValue()         RB5
#define IO_RB5_BTN1_MATRICIAL_SetDigitalInput()    do { TRISB5 = 1; } while(0)
#define IO_RB5_BTN1_MATRICIAL_SetDigitalOutput()   do { TRISB5 = 0; } while(0)

#define IO_RB5_BTN1_MATRICIAL_SetPullup()    do { WPUB5 = 1; } while(0)
#define IO_RB5_BTN1_MATRICIAL_ResetPullup()   do { WPUB5 = 0; } while(0)
#define IO_RB5_BTN1_MATRICIAL_SetAnalogMode()   do { ANSB5 = 1; } while(0)
#define IO_RB5_BTN1_MATRICIAL_SetDigitalMode()   do { ANSB5 = 0; } while(0)


// get/set IO_RB6_LED_TEST aliases
#define IO_RB6_LED_TEST_TRIS               TRISB6
#define IO_RB6_LED_TEST_LAT                LATB6
#define IO_RB6_LED_TEST_PORT               RB6
#define IO_RB6_LED_TEST_WPU                WPUB6
#define IO_RB6_LED_TEST_SetHigh()    do { LATB6 = 1; } while(0)
#define IO_RB6_LED_TEST_SetLow()   do { LATB6 = 0; } while(0)
#define IO_RB6_LED_TEST_Toggle()   do { LATB6 = ~LATB6; } while(0)
#define IO_RB6_LED_TEST_GetValue()         RB6
#define IO_RB6_LED_TEST_SetDigitalInput()    do { TRISB6 = 1; } while(0)
#define IO_RB6_LED_TEST_SetDigitalOutput()   do { TRISB6 = 0; } while(0)

#define IO_RB6_LED_TEST_SetPullup()    do { WPUB6 = 1; } while(0)
#define IO_RB6_LED_TEST_ResetPullup()   do { WPUB6 = 0; } while(0)


// get/set IO_RC0_MOTOR_REF_IN_D aliases
#define IO_RC0_MOTOR_REF_IN_D_TRIS               TRISC0
#define IO_RC0_MOTOR_REF_IN_D_LAT                LATC0
#define IO_RC0_MOTOR_REF_IN_D_PORT               RC0
#define IO_RC0_MOTOR_REF_IN_D_SetHigh()    do { LATC0 = 1; } while(0)
#define IO_RC0_MOTOR_REF_IN_D_SetLow()   do { LATC0 = 0; } while(0)
#define IO_RC0_MOTOR_REF_IN_D_Toggle()   do { LATC0 = ~LATC0; } while(0)
#define IO_RC0_MOTOR_REF_IN_D_GetValue()         RC0
#define IO_RC0_MOTOR_REF_IN_D_SetDigitalInput()    do { TRISC0 = 1; } while(0)
#define IO_RC0_MOTOR_REF_IN_D_SetDigitalOutput()   do { TRISC0 = 0; } while(0)



// get/set IO_RC1_MOTOR_REF_IN_C aliases
#define IO_RC1_MOTOR_REF_IN_C_TRIS               TRISC1
#define IO_RC1_MOTOR_REF_IN_C_LAT                LATC1
#define IO_RC1_MOTOR_REF_IN_C_PORT               RC1
#define IO_RC1_MOTOR_REF_IN_C_SetHigh()    do { LATC1 = 1; } while(0)
#define IO_RC1_MOTOR_REF_IN_C_SetLow()   do { LATC1 = 0; } while(0)
#define IO_RC1_MOTOR_REF_IN_C_Toggle()   do { LATC1 = ~LATC1; } while(0)
#define IO_RC1_MOTOR_REF_IN_C_GetValue()         RC1
#define IO_RC1_MOTOR_REF_IN_C_SetDigitalInput()    do { TRISC1 = 1; } while(0)
#define IO_RC1_MOTOR_REF_IN_C_SetDigitalOutput()   do { TRISC1 = 0; } while(0)



// get/set IO_RC2_MOTOR_REF_IN_A aliases
#define IO_RC2_MOTOR_REF_IN_A_TRIS               TRISC2
#define IO_RC2_MOTOR_REF_IN_A_LAT                LATC2
#define IO_RC2_MOTOR_REF_IN_A_PORT               RC2
#define IO_RC2_MOTOR_REF_IN_A_ANS                ANSC2
#define IO_RC2_MOTOR_REF_IN_A_SetHigh()    do { LATC2 = 1; } while(0)
#define IO_RC2_MOTOR_REF_IN_A_SetLow()   do { LATC2 = 0; } while(0)
#define IO_RC2_MOTOR_REF_IN_A_Toggle()   do { LATC2 = ~LATC2; } while(0)
#define IO_RC2_MOTOR_REF_IN_A_GetValue()         RC2
#define IO_RC2_MOTOR_REF_IN_A_SetDigitalInput()    do { TRISC2 = 1; } while(0)
#define IO_RC2_MOTOR_REF_IN_A_SetDigitalOutput()   do { TRISC2 = 0; } while(0)

#define IO_RC2_MOTOR_REF_IN_A_SetAnalogMode()   do { ANSC2 = 1; } while(0)
#define IO_RC2_MOTOR_REF_IN_A_SetDigitalMode()   do { ANSC2 = 0; } while(0)


// get/set IO_RC2_MOTOR_REF_IN_A aliases
#define IO_RC2_MOTOR_REF_IN_A_TRIS               TRISC2
#define IO_RC2_MOTOR_REF_IN_A_LAT                LATC2
#define IO_RC2_MOTOR_REF_IN_A_PORT               RC2
#define IO_RC2_MOTOR_REF_IN_A_ANS                ANSC2
#define IO_RC2_MOTOR_REF_IN_A_SetHigh()    do { LATC2 = 1; } while(0)
#define IO_RC2_MOTOR_REF_IN_A_SetLow()   do { LATC2 = 0; } while(0)
#define IO_RC2_MOTOR_REF_IN_A_Toggle()   do { LATC2 = ~LATC2; } while(0)
#define IO_RC2_MOTOR_REF_IN_A_GetValue()         RC2
#define IO_RC2_MOTOR_REF_IN_A_SetDigitalInput()    do { TRISC2 = 1; } while(0)
#define IO_RC2_MOTOR_REF_IN_A_SetDigitalOutput()   do { TRISC2 = 0; } while(0)

#define IO_RC2_MOTOR_REF_IN_A_SetAnalogMode()   do { ANSC2 = 1; } while(0)
#define IO_RC2_MOTOR_REF_IN_A_SetDigitalMode()   do { ANSC2 = 0; } while(0)


// get/set IO_RC2_MOTOR_REF_IN_A aliases
#define IO_RC2_MOTOR_REF_IN_A_TRIS               TRISC2
#define IO_RC2_MOTOR_REF_IN_A_LAT                LATC2
#define IO_RC2_MOTOR_REF_IN_A_PORT               RC2
#define IO_RC2_MOTOR_REF_IN_A_ANS                ANSC2
#define IO_RC2_MOTOR_REF_IN_A_SetHigh()    do { LATC2 = 1; } while(0)
#define IO_RC2_MOTOR_REF_IN_A_SetLow()   do { LATC2 = 0; } while(0)
#define IO_RC2_MOTOR_REF_IN_A_Toggle()   do { LATC2 = ~LATC2; } while(0)
#define IO_RC2_MOTOR_REF_IN_A_GetValue()         RC2
#define IO_RC2_MOTOR_REF_IN_A_SetDigitalInput()    do { TRISC2 = 1; } while(0)
#define IO_RC2_MOTOR_REF_IN_A_SetDigitalOutput()   do { TRISC2 = 0; } while(0)

#define IO_RC2_MOTOR_REF_IN_A_SetAnalogMode()   do { ANSC2 = 1; } while(0)
#define IO_RC2_MOTOR_REF_IN_A_SetDigitalMode()   do { ANSC2 = 0; } while(0)


// get/set IO_RC5_MOTOR_REF_ENPOS_LED aliases
#define IO_RC5_MOTOR_REF_ENPOS_LED_TRIS               TRISC5
#define IO_RC5_MOTOR_REF_ENPOS_LED_LAT                LATC5
#define IO_RC5_MOTOR_REF_ENPOS_LED_PORT               RC5
#define IO_RC5_MOTOR_REF_ENPOS_LED_ANS                ANSC5
#define IO_RC5_MOTOR_REF_ENPOS_LED_SetHigh()    do { LATC5 = 1; } while(0)
#define IO_RC5_MOTOR_REF_ENPOS_LED_SetLow()   do { LATC5 = 0; } while(0)
#define IO_RC5_MOTOR_REF_ENPOS_LED_Toggle()   do { LATC5 = ~LATC5; } while(0)
#define IO_RC5_MOTOR_REF_ENPOS_LED_GetValue()         RC5
#define IO_RC5_MOTOR_REF_ENPOS_LED_SetDigitalInput()    do { TRISC5 = 1; } while(0)
#define IO_RC5_MOTOR_REF_ENPOS_LED_SetDigitalOutput()   do { TRISC5 = 0; } while(0)

#define IO_RC5_MOTOR_REF_ENPOS_LED_SetAnalogMode()   do { ANSC5 = 1; } while(0)
#define IO_RC5_MOTOR_REF_ENPOS_LED_SetDigitalMode()   do { ANSC5 = 0; } while(0)


// get/set IO_RD0_PANTALLA_D4 aliases
#define IO_RD0_PANTALLA_D4_TRIS               TRISD0
#define IO_RD0_PANTALLA_D4_LAT                LATD0
#define IO_RD0_PANTALLA_D4_PORT               RD0
#define IO_RD0_PANTALLA_D4_ANS                ANSD0
#define IO_RD0_PANTALLA_D4_SetHigh()    do { LATD0 = 1; } while(0)
#define IO_RD0_PANTALLA_D4_SetLow()   do { LATD0 = 0; } while(0)
#define IO_RD0_PANTALLA_D4_Toggle()   do { LATD0 = ~LATD0; } while(0)
#define IO_RD0_PANTALLA_D4_GetValue()         RD0
#define IO_RD0_PANTALLA_D4_SetDigitalInput()    do { TRISD0 = 1; } while(0)
#define IO_RD0_PANTALLA_D4_SetDigitalOutput()   do { TRISD0 = 0; } while(0)

#define IO_RD0_PANTALLA_D4_SetAnalogMode()   do { ANSD0 = 1; } while(0)
#define IO_RD0_PANTALLA_D4_SetDigitalMode()   do { ANSD0 = 0; } while(0)


// get/set IO_RD1_PANTALLA_D5 aliases
#define IO_RD1_PANTALLA_D5_TRIS               TRISD1
#define IO_RD1_PANTALLA_D5_LAT                LATD1
#define IO_RD1_PANTALLA_D5_PORT               RD1
#define IO_RD1_PANTALLA_D5_ANS                ANSD1
#define IO_RD1_PANTALLA_D5_SetHigh()    do { LATD1 = 1; } while(0)
#define IO_RD1_PANTALLA_D5_SetLow()   do { LATD1 = 0; } while(0)
#define IO_RD1_PANTALLA_D5_Toggle()   do { LATD1 = ~LATD1; } while(0)
#define IO_RD1_PANTALLA_D5_GetValue()         RD1
#define IO_RD1_PANTALLA_D5_SetDigitalInput()    do { TRISD1 = 1; } while(0)
#define IO_RD1_PANTALLA_D5_SetDigitalOutput()   do { TRISD1 = 0; } while(0)

#define IO_RD1_PANTALLA_D5_SetAnalogMode()   do { ANSD1 = 1; } while(0)
#define IO_RD1_PANTALLA_D5_SetDigitalMode()   do { ANSD1 = 0; } while(0)


// get/set IO_RD2_PANTALLA_D6 aliases
#define IO_RD2_PANTALLA_D6_TRIS               TRISD2
#define IO_RD2_PANTALLA_D6_LAT                LATD2
#define IO_RD2_PANTALLA_D6_PORT               RD2
#define IO_RD2_PANTALLA_D6_ANS                ANSD2
#define IO_RD2_PANTALLA_D6_SetHigh()    do { LATD2 = 1; } while(0)
#define IO_RD2_PANTALLA_D6_SetLow()   do { LATD2 = 0; } while(0)
#define IO_RD2_PANTALLA_D6_Toggle()   do { LATD2 = ~LATD2; } while(0)
#define IO_RD2_PANTALLA_D6_GetValue()         RD2
#define IO_RD2_PANTALLA_D6_SetDigitalInput()    do { TRISD2 = 1; } while(0)
#define IO_RD2_PANTALLA_D6_SetDigitalOutput()   do { TRISD2 = 0; } while(0)

#define IO_RD2_PANTALLA_D6_SetAnalogMode()   do { ANSD2 = 1; } while(0)
#define IO_RD2_PANTALLA_D6_SetDigitalMode()   do { ANSD2 = 0; } while(0)


// get/set IO_RD3_PANTALLA_D7 aliases
#define IO_RD3_PANTALLA_D7_TRIS               TRISD3
#define IO_RD3_PANTALLA_D7_LAT                LATD3
#define IO_RD3_PANTALLA_D7_PORT               RD3
#define IO_RD3_PANTALLA_D7_ANS                ANSD3
#define IO_RD3_PANTALLA_D7_SetHigh()    do { LATD3 = 1; } while(0)
#define IO_RD3_PANTALLA_D7_SetLow()   do { LATD3 = 0; } while(0)
#define IO_RD3_PANTALLA_D7_Toggle()   do { LATD3 = ~LATD3; } while(0)
#define IO_RD3_PANTALLA_D7_GetValue()         RD3
#define IO_RD3_PANTALLA_D7_SetDigitalInput()    do { TRISD3 = 1; } while(0)
#define IO_RD3_PANTALLA_D7_SetDigitalOutput()   do { TRISD3 = 0; } while(0)

#define IO_RD3_PANTALLA_D7_SetAnalogMode()   do { ANSD3 = 1; } while(0)
#define IO_RD3_PANTALLA_D7_SetDigitalMode()   do { ANSD3 = 0; } while(0)


// get/set IO_RD4_MOTOR_REF_ENPOS aliases
#define IO_RD4_MOTOR_REF_ENPOS_TRIS               TRISD4
#define IO_RD4_MOTOR_REF_ENPOS_LAT                LATD4
#define IO_RD4_MOTOR_REF_ENPOS_PORT               RD4
#define IO_RD4_MOTOR_REF_ENPOS_ANS                ANSD4
#define IO_RD4_MOTOR_REF_ENPOS_SetHigh()    do { LATD4 = 1; } while(0)
#define IO_RD4_MOTOR_REF_ENPOS_SetLow()   do { LATD4 = 0; } while(0)
#define IO_RD4_MOTOR_REF_ENPOS_Toggle()   do { LATD4 = ~LATD4; } while(0)
#define IO_RD4_MOTOR_REF_ENPOS_GetValue()         RD4
#define IO_RD4_MOTOR_REF_ENPOS_SetDigitalInput()    do { TRISD4 = 1; } while(0)
#define IO_RD4_MOTOR_REF_ENPOS_SetDigitalOutput()   do { TRISD4 = 0; } while(0)

#define IO_RD4_MOTOR_REF_ENPOS_SetAnalogMode()   do { ANSD4 = 1; } while(0)
#define IO_RD4_MOTOR_REF_ENPOS_SetDigitalMode()   do { ANSD4 = 0; } while(0)


// get/set IO_RD5_MOTOR_REF_IN_B aliases
#define IO_RD5_MOTOR_REF_IN_B_TRIS               TRISD5
#define IO_RD5_MOTOR_REF_IN_B_LAT                LATD5
#define IO_RD5_MOTOR_REF_IN_B_PORT               RD5
#define IO_RD5_MOTOR_REF_IN_B_ANS                ANSD5
#define IO_RD5_MOTOR_REF_IN_B_SetHigh()    do { LATD5 = 1; } while(0)
#define IO_RD5_MOTOR_REF_IN_B_SetLow()   do { LATD5 = 0; } while(0)
#define IO_RD5_MOTOR_REF_IN_B_Toggle()   do { LATD5 = ~LATD5; } while(0)
#define IO_RD5_MOTOR_REF_IN_B_GetValue()         RD5
#define IO_RD5_MOTOR_REF_IN_B_SetDigitalInput()    do { TRISD5 = 1; } while(0)
#define IO_RD5_MOTOR_REF_IN_B_SetDigitalOutput()   do { TRISD5 = 0; } while(0)

#define IO_RD5_MOTOR_REF_IN_B_SetAnalogMode()   do { ANSD5 = 1; } while(0)
#define IO_RD5_MOTOR_REF_IN_B_SetDigitalMode()   do { ANSD5 = 0; } while(0)


// get/set IO_RD6_MOTOR_REF_EN_A aliases
#define IO_RD6_MOTOR_REF_EN_A_TRIS               TRISD6
#define IO_RD6_MOTOR_REF_EN_A_LAT                LATD6
#define IO_RD6_MOTOR_REF_EN_A_PORT               RD6
#define IO_RD6_MOTOR_REF_EN_A_ANS                ANSD6
#define IO_RD6_MOTOR_REF_EN_A_SetHigh()    do { LATD6 = 1; } while(0)
#define IO_RD6_MOTOR_REF_EN_A_SetLow()   do { LATD6 = 0; } while(0)
#define IO_RD6_MOTOR_REF_EN_A_Toggle()   do { LATD6 = ~LATD6; } while(0)
#define IO_RD6_MOTOR_REF_EN_A_GetValue()         RD6
#define IO_RD6_MOTOR_REF_EN_A_SetDigitalInput()    do { TRISD6 = 1; } while(0)
#define IO_RD6_MOTOR_REF_EN_A_SetDigitalOutput()   do { TRISD6 = 0; } while(0)

#define IO_RD6_MOTOR_REF_EN_A_SetAnalogMode()   do { ANSD6 = 1; } while(0)
#define IO_RD6_MOTOR_REF_EN_A_SetDigitalMode()   do { ANSD6 = 0; } while(0)


// get/set IO_RD7_MOTOR_REF_EN_B aliases
#define IO_RD7_MOTOR_REF_EN_B_TRIS               TRISD7
#define IO_RD7_MOTOR_REF_EN_B_LAT                LATD7
#define IO_RD7_MOTOR_REF_EN_B_PORT               RD7
#define IO_RD7_MOTOR_REF_EN_B_ANS                ANSD7
#define IO_RD7_MOTOR_REF_EN_B_SetHigh()    do { LATD7 = 1; } while(0)
#define IO_RD7_MOTOR_REF_EN_B_SetLow()   do { LATD7 = 0; } while(0)
#define IO_RD7_MOTOR_REF_EN_B_Toggle()   do { LATD7 = ~LATD7; } while(0)
#define IO_RD7_MOTOR_REF_EN_B_GetValue()         RD7
#define IO_RD7_MOTOR_REF_EN_B_SetDigitalInput()    do { TRISD7 = 1; } while(0)
#define IO_RD7_MOTOR_REF_EN_B_SetDigitalOutput()   do { TRISD7 = 0; } while(0)

#define RELAY1_Toggle() IO_RD7_MOTOR_REF_EN_B_Toggle()

#define IO_RD7_MOTOR_REF_EN_B_SetAnalogMode()   do { ANSD7 = 1; } while(0)
#define IO_RD7_MOTOR_REF_EN_B_SetDigitalMode()   do { ANSD7 = 0; } while(0)


// get/set IO_RE0_PANTALLA_EN_BL aliases
#define IO_RE0_PANTALLA_EN_BL_TRIS               TRISE0
#define IO_RE0_PANTALLA_EN_BL_LAT                LATE0
#define IO_RE0_PANTALLA_EN_BL_PORT               RE0
#define IO_RE0_PANTALLA_EN_BL_ANS                ANSE0
#define IO_RE0_PANTALLA_EN_BL_SetHigh()    do { LATE0 = 1; } while(0)
#define IO_RE0_PANTALLA_EN_BL_SetLow()   do { LATE0 = 0; } while(0)
#define IO_RE0_PANTALLA_EN_BL_Toggle()   do { LATE0 = ~LATE0; } while(0)
#define IO_RE0_PANTALLA_EN_BL_GetValue()         RE0
#define IO_RE0_PANTALLA_EN_BL_SetDigitalInput()    do { TRISE0 = 1; } while(0)
#define IO_RE0_PANTALLA_EN_BL_SetDigitalOutput()   do { TRISE0 = 0; } while(0)

#define IO_RE0_PANTALLA_EN_BL_SetAnalogMode()   do { ANSE0 = 1; } while(0)
#define IO_RE0_PANTALLA_EN_BL_SetDigitalMode()   do { ANSE0 = 0; } while(0)


// get/set IO_RE1_PANTALLA_RS aliases
#define IO_RE1_PANTALLA_RS_TRIS               TRISE1
#define IO_RE1_PANTALLA_RS_LAT                LATE1
#define IO_RE1_PANTALLA_RS_PORT               RE1
#define IO_RE1_PANTALLA_RS_ANS                ANSE1
#define IO_RE1_PANTALLA_RS_SetHigh()    do { LATE1 = 1; } while(0)
#define IO_RE1_PANTALLA_RS_SetLow()   do { LATE1 = 0; } while(0)
#define IO_RE1_PANTALLA_RS_Toggle()   do { LATE1 = ~LATE1; } while(0)
#define IO_RE1_PANTALLA_RS_GetValue()         RE1
#define IO_RE1_PANTALLA_RS_SetDigitalInput()    do { TRISE1 = 1; } while(0)
#define IO_RE1_PANTALLA_RS_SetDigitalOutput()   do { TRISE1 = 0; } while(0)

#define IO_RE1_PANTALLA_RS_SetAnalogMode()   do { ANSE1 = 1; } while(0)
#define IO_RE1_PANTALLA_RS_SetDigitalMode()   do { ANSE1 = 0; } while(0)


// get/set IO_RE2_unused aliases
#define IO_RE2_unused_TRIS               TRISE2
#define IO_RE2_unused_LAT                LATE2
#define IO_RE2_unused_PORT               RE2
#define IO_RE2_unused_ANS                ANSE2
#define IO_RE2_unused_SetHigh()    do { LATE2 = 1; } while(0)
#define IO_RE2_unused_SetLow()   do { LATE2 = 0; } while(0)
#define IO_RE2_unused_Toggle()   do { LATE2 = ~LATE2; } while(0)
#define IO_RE2_unused_GetValue()         RE2
#define IO_RE2_unused_SetDigitalInput()    do { TRISE2 = 1; } while(0)
#define IO_RE2_unused_SetDigitalOutput()   do { TRISE2 = 0; } while(0)

#define IO_RE2_unused_SetAnalogMode()   do { ANSE2 = 1; } while(0)
#define IO_RE2_unused_SetDigitalMode()   do { ANSE2 = 0; } while(0)



/**
 * @Param
    none
 * @Returns
    none
 * @Description
    GPIO and peripheral I/O initialization
 * @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);





#endif // PIN_MANAGER_H
/**
 End of File
*/