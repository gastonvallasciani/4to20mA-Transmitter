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
        Product Revision  :  MPLAB(c) Code Configurator - 4.15
        Device            :  PIC16F1619
        Version           :  1.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40

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

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RELAY_OUTPUT1 aliases
#define RELAY_OUTPUT1_TRIS               TRISAbits.TRISA2
#define RELAY_OUTPUT1_LAT                LATAbits.LATA2
#define RELAY_OUTPUT1_PORT               PORTAbits.RA2
#define RELAY_OUTPUT1_WPU                WPUAbits.WPUA2
#define RELAY_OUTPUT1_OD                ODCONAbits.ODA2
#define RELAY_OUTPUT1_ANS                ANSELAbits.ANSA2
#define RELAY_OUTPUT1_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define RELAY_OUTPUT1_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define RELAY_OUTPUT1_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define RELAY_OUTPUT1_GetValue()           PORTAbits.RA2
#define RELAY_OUTPUT1_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define RELAY_OUTPUT1_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define RELAY_OUTPUT1_SetPullup()      do { WPUAbits.WPUA2 = 1; } while(0)
#define RELAY_OUTPUT1_ResetPullup()    do { WPUAbits.WPUA2 = 0; } while(0)
#define RELAY_OUTPUT1_SetPushPull()    do { ODCONAbits.ODA2 = 1; } while(0)
#define RELAY_OUTPUT1_SetOpenDrain()   do { ODCONAbits.ODA2 = 0; } while(0)
#define RELAY_OUTPUT1_SetAnalogMode()  do { ANSELAbits.ANSA2 = 1; } while(0)
#define RELAY_OUTPUT1_SetDigitalMode() do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set RA4 procedures
#define RA4_SetHigh()    do { LATAbits.LATA4 = 1; } while(0)
#define RA4_SetLow()   do { LATAbits.LATA4 = 0; } while(0)
#define RA4_Toggle()   do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define RA4_GetValue()         PORTAbits.RA4
#define RA4_SetDigitalInput()   do { TRISAbits.TRISA4 = 1; } while(0)
#define RA4_SetDigitalOutput()  do { TRISAbits.TRISA4 = 0; } while(0)
#define RA4_SetPullup()     do { WPUAbits.WPUA4 = 1; } while(0)
#define RA4_ResetPullup()   do { WPUAbits.WPUA4 = 0; } while(0)
#define RA4_SetAnalogMode() do { ANSELAbits.ANSA4 = 1; } while(0)
#define RA4_SetDigitalMode()do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set RA5 procedures
#define RA5_SetHigh()    do { LATAbits.LATA5 = 1; } while(0)
#define RA5_SetLow()   do { LATAbits.LATA5 = 0; } while(0)
#define RA5_Toggle()   do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define RA5_GetValue()         PORTAbits.RA5
#define RA5_SetDigitalInput()   do { TRISAbits.TRISA5 = 1; } while(0)
#define RA5_SetDigitalOutput()  do { TRISAbits.TRISA5 = 0; } while(0)
#define RA5_SetPullup()     do { WPUAbits.WPUA5 = 1; } while(0)
#define RA5_ResetPullup()   do { WPUAbits.WPUA5 = 0; } while(0)

// get/set RB4 procedures
#define RB4_SetHigh()    do { LATBbits.LATB4 = 1; } while(0)
#define RB4_SetLow()   do { LATBbits.LATB4 = 0; } while(0)
#define RB4_Toggle()   do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define RB4_GetValue()         PORTBbits.RB4
#define RB4_SetDigitalInput()   do { TRISBbits.TRISB4 = 1; } while(0)
#define RB4_SetDigitalOutput()  do { TRISBbits.TRISB4 = 0; } while(0)
#define RB4_SetPullup()     do { WPUBbits.WPUB4 = 1; } while(0)
#define RB4_ResetPullup()   do { WPUBbits.WPUB4 = 0; } while(0)
#define RB4_SetAnalogMode() do { ANSELBbits.ANSB4 = 1; } while(0)
#define RB4_SetDigitalMode()do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set RB6 procedures
#define RB6_SetHigh()    do { LATBbits.LATB6 = 1; } while(0)
#define RB6_SetLow()   do { LATBbits.LATB6 = 0; } while(0)
#define RB6_Toggle()   do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define RB6_GetValue()         PORTBbits.RB6
#define RB6_SetDigitalInput()   do { TRISBbits.TRISB6 = 1; } while(0)
#define RB6_SetDigitalOutput()  do { TRISBbits.TRISB6 = 0; } while(0)
#define RB6_SetPullup()     do { WPUBbits.WPUB6 = 1; } while(0)
#define RB6_ResetPullup()   do { WPUBbits.WPUB6 = 0; } while(0)
#define RB6_SetAnalogMode() do { ANSELBbits.ANSB6 = 1; } while(0)
#define RB6_SetDigitalMode()do { ANSELBbits.ANSB6 = 0; } while(0)

// get/set RELAY_OUTPUT2 aliases
#define RELAY_OUTPUT2_TRIS               TRISCbits.TRISC0
#define RELAY_OUTPUT2_LAT                LATCbits.LATC0
#define RELAY_OUTPUT2_PORT               PORTCbits.RC0
#define RELAY_OUTPUT2_WPU                WPUCbits.WPUC0
#define RELAY_OUTPUT2_OD                ODCONCbits.ODC0
#define RELAY_OUTPUT2_ANS                ANSELCbits.ANSC0
#define RELAY_OUTPUT2_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define RELAY_OUTPUT2_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define RELAY_OUTPUT2_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define RELAY_OUTPUT2_GetValue()           PORTCbits.RC0
#define RELAY_OUTPUT2_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define RELAY_OUTPUT2_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define RELAY_OUTPUT2_SetPullup()      do { WPUCbits.WPUC0 = 1; } while(0)
#define RELAY_OUTPUT2_ResetPullup()    do { WPUCbits.WPUC0 = 0; } while(0)
#define RELAY_OUTPUT2_SetPushPull()    do { ODCONCbits.ODC0 = 1; } while(0)
#define RELAY_OUTPUT2_SetOpenDrain()   do { ODCONCbits.ODC0 = 0; } while(0)
#define RELAY_OUTPUT2_SetAnalogMode()  do { ANSELCbits.ANSC0 = 1; } while(0)
#define RELAY_OUTPUT2_SetDigitalMode() do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set TRI_STATE_OUTPUT1 aliases
#define TRI_STATE_OUTPUT1_TRIS               TRISCbits.TRISC1
#define TRI_STATE_OUTPUT1_LAT                LATCbits.LATC1
#define TRI_STATE_OUTPUT1_PORT               PORTCbits.RC1
#define TRI_STATE_OUTPUT1_WPU                WPUCbits.WPUC1
#define TRI_STATE_OUTPUT1_OD                ODCONCbits.ODC1
#define TRI_STATE_OUTPUT1_ANS                ANSELCbits.ANSC1
#define TRI_STATE_OUTPUT1_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define TRI_STATE_OUTPUT1_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define TRI_STATE_OUTPUT1_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define TRI_STATE_OUTPUT1_GetValue()           PORTCbits.RC1
#define TRI_STATE_OUTPUT1_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define TRI_STATE_OUTPUT1_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define TRI_STATE_OUTPUT1_SetPullup()      do { WPUCbits.WPUC1 = 1; } while(0)
#define TRI_STATE_OUTPUT1_ResetPullup()    do { WPUCbits.WPUC1 = 0; } while(0)
#define TRI_STATE_OUTPUT1_SetPushPull()    do { ODCONCbits.ODC1 = 1; } while(0)
#define TRI_STATE_OUTPUT1_SetOpenDrain()   do { ODCONCbits.ODC1 = 0; } while(0)
#define TRI_STATE_OUTPUT1_SetAnalogMode()  do { ANSELCbits.ANSC1 = 1; } while(0)
#define TRI_STATE_OUTPUT1_SetDigitalMode() do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set TRI_STATE_OUTPUT2 aliases
#define TRI_STATE_OUTPUT2_TRIS               TRISCbits.TRISC2
#define TRI_STATE_OUTPUT2_LAT                LATCbits.LATC2
#define TRI_STATE_OUTPUT2_PORT               PORTCbits.RC2
#define TRI_STATE_OUTPUT2_WPU                WPUCbits.WPUC2
#define TRI_STATE_OUTPUT2_OD                ODCONCbits.ODC2
#define TRI_STATE_OUTPUT2_ANS                ANSELCbits.ANSC2
#define TRI_STATE_OUTPUT2_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define TRI_STATE_OUTPUT2_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define TRI_STATE_OUTPUT2_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define TRI_STATE_OUTPUT2_GetValue()           PORTCbits.RC2
#define TRI_STATE_OUTPUT2_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define TRI_STATE_OUTPUT2_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define TRI_STATE_OUTPUT2_SetPullup()      do { WPUCbits.WPUC2 = 1; } while(0)
#define TRI_STATE_OUTPUT2_ResetPullup()    do { WPUCbits.WPUC2 = 0; } while(0)
#define TRI_STATE_OUTPUT2_SetPushPull()    do { ODCONCbits.ODC2 = 1; } while(0)
#define TRI_STATE_OUTPUT2_SetOpenDrain()   do { ODCONCbits.ODC2 = 0; } while(0)
#define TRI_STATE_OUTPUT2_SetAnalogMode()  do { ANSELCbits.ANSC2 = 1; } while(0)
#define TRI_STATE_OUTPUT2_SetDigitalMode() do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()    do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()   do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()   do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()         PORTCbits.RC3
#define RC3_SetDigitalInput()   do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()  do { TRISCbits.TRISC3 = 0; } while(0)
#define RC3_SetPullup()     do { WPUCbits.WPUC3 = 1; } while(0)
#define RC3_ResetPullup()   do { WPUCbits.WPUC3 = 0; } while(0)
#define RC3_SetAnalogMode() do { ANSELCbits.ANSC3 = 1; } while(0)
#define RC3_SetDigitalMode()do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set LED_TEST aliases
#define LED_TEST_TRIS               TRISCbits.TRISC4
#define LED_TEST_LAT                LATCbits.LATC4
#define LED_TEST_PORT               PORTCbits.RC4
#define LED_TEST_WPU                WPUCbits.WPUC4
#define LED_TEST_OD                ODCONCbits.ODC4
#define LED_TEST_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define LED_TEST_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define LED_TEST_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define LED_TEST_GetValue()           PORTCbits.RC4
#define LED_TEST_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define LED_TEST_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define LED_TEST_SetPullup()      do { WPUCbits.WPUC4 = 1; } while(0)
#define LED_TEST_ResetPullup()    do { WPUCbits.WPUC4 = 0; } while(0)
#define LED_TEST_SetPushPull()    do { ODCONCbits.ODC4 = 1; } while(0)
#define LED_TEST_SetOpenDrain()   do { ODCONCbits.ODC4 = 0; } while(0)

// get/set RC5 procedures
#define RC5_SetHigh()    do { LATCbits.LATC5 = 1; } while(0)
#define RC5_SetLow()   do { LATCbits.LATC5 = 0; } while(0)
#define RC5_Toggle()   do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define RC5_GetValue()         PORTCbits.RC5
#define RC5_SetDigitalInput()   do { TRISCbits.TRISC5 = 1; } while(0)
#define RC5_SetDigitalOutput()  do { TRISCbits.TRISC5 = 0; } while(0)
#define RC5_SetPullup()     do { WPUCbits.WPUC5 = 1; } while(0)
#define RC5_ResetPullup()   do { WPUCbits.WPUC5 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()    do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()   do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()   do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()         PORTCbits.RC6
#define RC6_SetDigitalInput()   do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()  do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetPullup()     do { WPUCbits.WPUC6 = 1; } while(0)
#define RC6_ResetPullup()   do { WPUCbits.WPUC6 = 0; } while(0)
#define RC6_SetAnalogMode() do { ANSELCbits.ANSC6 = 1; } while(0)
#define RC6_SetDigitalMode()do { ANSELCbits.ANSC6 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/