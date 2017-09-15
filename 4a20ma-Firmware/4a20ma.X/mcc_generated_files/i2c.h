/**
  MSSP Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    i2c.h

  @Summary
    This is the generated header file for the MSSP driver using MPLAB(c) Code Configurator

  @Description
    This header file provides APIs for driver for MSSP.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.15
        Device            :  PIC16F1619
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB 	          :  MPLAB X 3.40
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

#ifndef _I2C_H
#define _I2C_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <xc.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  I2C Slave Driver Status

  @Summary
    Defines the different status that the slave driver has
    detected over the i2c bus.

  @Description
    This defines the different status that the slave driver has
    detected over the i2c bus. The status is passed to the
    I2C_StatusCallback() callback function that is implemented by
    the user of the slave driver as a parameter to inform the user
    that there was a change in the status of the driver due to
    transactions on the i2c bus. User of the slave driver can use these
    to manage the read or write buffers.

 */

typedef enum
{
    I2C_SLAVE_WRITE_REQUEST,
    I2C_SLAVE_READ_REQUEST,
    I2C_SLAVE_WRITE_COMPLETED,
    I2C_SLAVE_READ_COMPLETED,
} I2C_SLAVE_DRIVER_STATUS;

#define I2C_SLAVE_DEFAULT_ADDRESS          0x08

/**
    @Summary
        Initializes and enables the i2c slave instance : 

    @Description
        This routine initializes the i2c slave driver instance for : 
        index, making it ready for clients to open and use it.

    @Preconditions
        None

    @Param
        None

    @Returns
        None

    @Example
        <code>
            // initialize the i2c slave driver
            I2C_Initialize();

        </code>
*/

void I2C_Initialize(void);

/**
   @Summary
        This function process the I2C interrupts generated by
        bus activity

    @Description
        This function calls a callback function with 1 of 4
        possible parameters.
            I2C_SLAVE_WRITE_REQUEST
            I2C_SLAVE_READ_REQUEST
            I2C_SLAVE_WRITE_COMPLETED
            I2C_SLAVE_READ_COMPLETED

        The callback function should contain application specific
        code to process I2C bus activity from the I2C master.
        A basic EEPROM emulator is provided as an example.
 */

void I2C_ISR ( void );

/**
   @Summary
        This varible contains the last data written to the I2C slave
*/

extern volatile uint8_t    I2C_slaveWriteData;


#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif  // _I2C_H
