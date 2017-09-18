/* 
 * File:   properties.h
 * Author: Ariel L
 *
 * Created on 18 de septiembre de 2017, 9:11
 */

#ifndef PROPERTIES_H
#define	PROPERTIES_H

#ifdef	__cplusplus
extern "C" {
#endif
///////////////////////////////////////// RELAY CONTROL
#define RELAY1ON() RELAY_OUTPUT1_SetHigh()
#define RELAY2ON() RELAY_OUTPUT2_SetHigh()
#define RELAY1OFF() RELAY_OUTPUT1_SetLow()
#define RELAY2OFF() RELAY_OUTPUT1_SetLow()
///////////////////////////////////////// TRI-STATE CONTROL
#define TRI_STATE1ON() TRI_STATE_OUTPUT1_SetLow() 
#define TRI_STATE2ON() TRI_STATE_OUTPUT2_SetLow()
#define TRI_STATE1OFF() TRI_STATE_OUTPUT1_SetHigh()
#define TRI_STATE2OFF() TRI_STATE_OUTPUT1_SetHigh()


#ifdef	__cplusplus
}
#endif

#endif	/* PROPERTIES_H */

