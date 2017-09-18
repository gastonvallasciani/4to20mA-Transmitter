/* 
 * File:   HardwareReset.h
 * Author: Gaston Vallasciani
 *
 * Created on 15 de septiembre de 2017, 9:04
 */

#ifndef HARDWARERESET_H
#define	HARDWARERESET_H

#include "mcc_generated_files/mcc.h"


////////////////////Protoype Functions
void HardwareResetMEF_ini( void );
void HardwareResetMEF_act ( uint16_t DelayON, uint8_t DelayOFF );
////////////////////////////////////
#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* HARDWARERESET_H */

