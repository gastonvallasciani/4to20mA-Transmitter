
/**
  ECCP3 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    eccp3.c

  @Summary
    This is the generated driver implementation file for the ECCP3 driver using MPLAB(c) Code Configurator

  @Description
    This source file provides APIs for ECCP3.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.15
        Device            :  PIC18F46K22
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40
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

/**
  Section: Included Files
*/

#include <xc.h>
#include "epwm3.h"

/**
  Section: Macro Declarations
*/

#define PWM3_INITIALIZE_DUTY_VALUE    0

/**
  Section: EPWM Module APIs
*/

void EPWM3_Initialize (void)
{
    // Set the PWM to the options selected in MPLAB(c) Code Configurator
    
    // CCP3M P3A,P3C: active high; P3B,P3D: active high; DC3B 0; P3M single; 
    CCP3CON = 0x0C;
    
    // CCP3ASE operating; PSS3BD low; PSS3AC low; CCP3AS disabled; 
    ECCP3AS = 0x00;
    
    // P3RSEN automatic_restart; P3DC 0; 
    PWM3CON = 0x80;
    
    // STR3D P3D_to_port; STR3C P3C_to_port; STR3B P3B_to_port; STR3A P3A_to_CCP3M; STR3SYNC start_at_begin; 
    PSTR3CON = 0x01;
    
    // CCPR3L 0; 
    CCPR3L = 0x00;
    
    // CCPR3H 0; 
    CCPR3H = 0x00;
    
    
    // Selecting Timer6
    CCPTMRS0bits.C3TSEL = 0x2;
}

void EPWM3_LoadDutyValue(uint16_t dutyValue)
{
   // Writing to 8 MSBs of pwm duty cycle in CCPRL register
    CCPR3L = ((dutyValue & 0x03FC)>>2);
    
   // Writing to 2 LSBs of pwm duty cycle in CCPCON register
    CCP3CON = (CCP3CON & 0xCF) | ((dutyValue & 0x0003)<<4);
}
/**
 End of File
*/
