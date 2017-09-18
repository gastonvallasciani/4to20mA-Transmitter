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
#include "properties.h"


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
    if (Timer1Ticked == 1)
    {
        Ticked++;
    }
    switch (HardwarePowerState){
        case HardwarePowerON:
            if (Ticked == DelayON)
            {
                RELAY1ON();
                RELAY2ON(); 
                TRI_STATE1ON();
                TRI_STATE2ON();
                
                HardwarePowerState = HardwarePowerOFF;
            }
            break;
        case HardwarePowerOFF:
            if (Ticked == DelayOFF)
            {
                RELAY1OFF();
                RELAY2OFF();
                TRI_STATE1OFF();
                TRI_STATE2OFF();
                
                HardwarePowerState = HardwarePowerON;
            }
            break;
    }
}
