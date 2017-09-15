/*
 * 
 * Author: Gaston Vallasciani
 * File: "HardwareReset.c"
 * 
 * Description: Hardware Reset for Ledesma, make by 2 relays and 2 Tri-State buffers placed on the 4to20mA-Transmitter PCB.
 * Created on 15 de septiembre de 2017, 9:04
 */
//#include "mcc.h"
#include "HardwareReset.h"
#include "mcc_generated_files/mcc.h"

#define _30seg 30;
#define _1min 60;
#define _10min 600;
#define _1h 3600;
#define _12min 43200;

extern uint8_t Timer1Ticked;
int16_t Ticked;

typedef enum
{
    HardwarePowerON,
    HardwarePowerOFF
}t_HardwarePowerMEF;

t_HardwarePowerMEF HardwarePowerState;

void HardwareResetMEF_ini( void )
{
    HardwarePowerState = HardwarePowerON;  
    Ticked = 0;
}

void HardwareResetMEF_act ( uint16_t DelayON, uint8_t DelayOFF )
{   
    //uint16_t DelayON = _1min; 
    //uint8_t DelayOFF = _30seg;
    if (Timer1Ticked == 1)
    {
        Ticked++;
    }
    switch (HardwarePowerState){
        case HardwarePowerON:
            if (Ticked == DelayON)
            //if (Ticked == 60)
            {
                RELAY_OUTPUT1_SetHigh();
                RELAY_OUTPUT2_SetHigh(); 
                TRI_STATE_OUTPUT1_SetLow();
                TRI_STATE_OUTPUT2_SetLow();
                
                HardwarePowerState = HardwarePowerOFF;
            }
            break;
        case HardwarePowerOFF:
            if (Ticked == DelayOFF)
            //if (Ticked == 30)
            {
                RELAY_OUTPUT1_SetLow();
                RELAY_OUTPUT2_SetLow();
                TRI_STATE_OUTPUT1_SetHigh();
                TRI_STATE_OUTPUT2_SetHigh();
                
                HardwarePowerState = HardwarePowerON;
            }
            break;
    }
}