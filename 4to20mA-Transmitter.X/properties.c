/*
 * File:   properties.c
 * Author: Nico Christie
 *
 * Created on 29 de marzo de 2016, 15:55
 */

#include "mcc_generated_files/mcc.h"
#include "properties.h"
#include "devices.h"

#define MEMORY_ADDRESS_MAX					0x400 // 1024 Bytes en PIC18F46K22
#define MEMORY_ADDRESS_BASE					0x100

#define MEMORY_SIZE_OF_BASE					1

#define SIZEOF_DEVICE_CLASS					1
#define SIZEOF_DEVICE_ID					1
#define SIZEOF_DEVICE_MOTORTYPE				1
#define SIZEOF_TEMPERATURE_DUTY				1

#define SIZEOF_MUX_POS_X					2
#define SIZEOF_MUX_OVERSHOOT				1

#define SIZEOF_REF_DARK						2
#define SIZEOF_REF_REFERENCE				2
#define SIZEOF_REF_PRODUCT_START			2
#define SIZEOF_REF_PRODUCT_END				2
#define SIZEOF_REF_SPEED					2
#define SIZEOF_REF_DUTY						1
#define SIZEOF_COMP_STEPS					2

#define MEMORY_ADDRESS_MEMORY_INIT			MEMORY_ADDRESS_BASE
#define MEMORY_ADDRESS_DEVICE_CLASS			MEMORY_ADDRESS_MEMORY_INIT + MEMORY_SIZE_OF_BASE
#define MEMORY_ADDRESS_DEVICE_ID			MEMORY_ADDRESS_DEVICE_CLASS + SIZEOF_DEVICE_CLASS
#define MEMORY_ADDRESS_DEVICE_MOTORTYPE		MEMORY_ADDRESS_DEVICE_ID + SIZEOF_DEVICE_ID
#define MEMORY_ADDRESS_TEMPERATURE_DUTY		MEMORY_ADDRESS_DEVICE_MOTORTYPE + SIZEOF_DEVICE_MOTORTYPE

#define MUX_AVAILABLE_POSITIONS				MULTIPLEXER_CHANNEL_COUNT // devices.h
#define MEMORY_ADDRESS_MUX_POS_FIRST		MEMORY_ADDRESS_TEMPERATURE_DUTY + SIZEOF_TEMPERATURE_DUTY
#define MEMORY_ADDRESS_MUX_POS(x)			MEMORY_ADDRESS_MUX_POS_FIRST + (x * SIZEOF_MUX_POS_X)
#define MEMORY_ADDRESS_MUX_POS_LAST			MEMORY_ADDRESS_MUX_POS_FIRST + (MUX_AVAILABLE_POSITIONS * SIZEOF_MUX_POS_X)
#define MEMORY_ADDRESS_MUX_OVERSHOOT		MEMORY_ADDRESS_MUX_POS_LAST + SIZEOF_MUX_POS_X

#define MEMORY_ADDRESS_REF_DARK				MEMORY_ADDRESS_MUX_OVERSHOOT + SIZEOF_MUX_OVERSHOOT
#define MEMORY_ADDRESS_REF_REFERENCE		MEMORY_ADDRESS_REF_DARK + SIZEOF_REF_DARK
#define MEMORY_ADDRESS_REF_PRODUCT_START	MEMORY_ADDRESS_REF_REFERENCE + SIZEOF_REF_REFERENCE
#define MEMORY_ADDRESS_REF_PRODUCT_END		MEMORY_ADDRESS_REF_PRODUCT_START + SIZEOF_REF_PRODUCT_START
#define MEMORY_ADDRESS_REF_SPEED			MEMORY_ADDRESS_REF_PRODUCT_END + SIZEOF_REF_PRODUCT_END
#define MEMORY_ADDRESS_REF_DUTY_REF			MEMORY_ADDRESS_REF_SPEED + SIZEOF_REF_SPEED
#define MEMORY_ADDRESS_REF_DUTY_COMP		MEMORY_ADDRESS_REF_DUTY_REF + SIZEOF_REF_DUTY
#define MEMORY_ADDRESS_COMP_STEPS			MEMORY_ADDRESS_REF_DUTY_COMP + SIZEOF_REF_DUTY

#define MEMORY_INIT_CHAR					'Y'

unsigned char MemoryIsInit() {
	return (DATAEE_ReadByte(MEMORY_ADDRESS_MEMORY_INIT) == MEMORY_INIT_CHAR);
}
void MemoryInit() {
	DATAEE_WriteByte(MEMORY_ADDRESS_MEMORY_INIT, MEMORY_INIT_CHAR);
}

void SaveClass(unsigned char class) {
	DATAEE_WriteByte(MEMORY_ADDRESS_DEVICE_CLASS, class);
}
void SaveID(unsigned char id) {
	DATAEE_WriteByte(MEMORY_ADDRESS_DEVICE_ID, id);
}
void SaveMotorType(unsigned char id) {
	DATAEE_WriteByte(MEMORY_ADDRESS_DEVICE_MOTORTYPE, id);
}
void SaveTemperatureDuty(unsigned char duty) {
	DATAEE_WriteByte(MEMORY_ADDRESS_TEMPERATURE_DUTY, duty);
}

unsigned char ReadClass() {
	return DATAEE_ReadByte(MEMORY_ADDRESS_DEVICE_CLASS);
}
unsigned char ReadID() {
	return DATAEE_ReadByte(MEMORY_ADDRESS_DEVICE_ID);
}
unsigned char ReadMotorType() {
	return DATAEE_ReadByte(MEMORY_ADDRESS_DEVICE_MOTORTYPE);
}
unsigned char ReadTemperatureDuty() {
	return DATAEE_ReadByte(MEMORY_ADDRESS_TEMPERATURE_DUTY);
}

void SavePos(unsigned char pos, unsigned int stepcount) {
	if (pos > 9) return;
	DATAEE_WriteByte(MEMORY_ADDRESS_MUX_POS(pos), (unsigned char)((stepcount >> 8) & 0x00FF));
	DATAEE_WriteByte(MEMORY_ADDRESS_MUX_POS(pos) + 1, (unsigned char)(stepcount & 0x00FF));		
}
void SaveOvershoot(unsigned char stepcount) {
	DATAEE_WriteByte(MEMORY_ADDRESS_MUX_OVERSHOOT, stepcount);
}
unsigned int ReadPos(unsigned char pos) {
	if (pos > 9) return 0;
	unsigned char int_H = DATAEE_ReadByte(MEMORY_ADDRESS_MUX_POS(pos));
	unsigned char int_L = DATAEE_ReadByte(MEMORY_ADDRESS_MUX_POS(pos) + 1);
	return (int_H << 8) + int_L;	
}
unsigned char ReadOvershoot(){
	return DATAEE_ReadByte(MEMORY_ADDRESS_MUX_OVERSHOOT);
}

void SaveDark(unsigned int pos) {
	DATAEE_WriteByte(MEMORY_ADDRESS_REF_DARK, (unsigned char)((pos >> 8) & 0x00FF));
	DATAEE_WriteByte(MEMORY_ADDRESS_REF_DARK + 1, (unsigned char)(pos & 0x00FF));	
}
void SaveReference(unsigned int pos) {
	DATAEE_WriteByte(MEMORY_ADDRESS_REF_REFERENCE, (unsigned char)((pos >> 8) & 0x00FF));
	DATAEE_WriteByte(MEMORY_ADDRESS_REF_REFERENCE + 1, (unsigned char)(pos & 0x00FF));	
}
void SaveProductStart(unsigned int pos) {
	DATAEE_WriteByte(MEMORY_ADDRESS_REF_PRODUCT_START, (unsigned char)((pos >> 8) & 0x00FF));
	DATAEE_WriteByte(MEMORY_ADDRESS_REF_PRODUCT_START + 1, (unsigned char)(pos & 0x00FF));	
}
void SaveProductEnd(unsigned int pos) {
	DATAEE_WriteByte(MEMORY_ADDRESS_REF_PRODUCT_END, (unsigned char)((pos >> 8) & 0x00FF));
	DATAEE_WriteByte(MEMORY_ADDRESS_REF_PRODUCT_END + 1, (unsigned char)(pos & 0x00FF));	
}
void SaveProductScanSpeed(unsigned int speed) {
	DATAEE_WriteByte(MEMORY_ADDRESS_REF_SPEED, (unsigned char)((speed >> 8) & 0x00FF));
	DATAEE_WriteByte(MEMORY_ADDRESS_REF_SPEED + 1, (unsigned char)(speed & 0x00FF));	
}
void SaveHoldDutyRef(unsigned char duty) {
	DATAEE_WriteByte(MEMORY_ADDRESS_REF_DUTY_REF, duty);	
}
void SaveHoldDutyComp(unsigned char duty) {
	DATAEE_WriteByte(MEMORY_ADDRESS_REF_DUTY_COMP, duty);	
}
void SavePasosCompuerta(unsigned int steps) {
	DATAEE_WriteByte(MEMORY_ADDRESS_COMP_STEPS, (unsigned char)((steps >> 8) & 0x00FF));
	DATAEE_WriteByte(MEMORY_ADDRESS_COMP_STEPS + 1, (unsigned char)(steps & 0x00FF));	
}

unsigned int ReadDark() {
	unsigned char int_H = DATAEE_ReadByte(MEMORY_ADDRESS_REF_DARK);
	unsigned char int_L = DATAEE_ReadByte(MEMORY_ADDRESS_REF_DARK + 1);
	return (int_H << 8) + int_L;
}
unsigned int ReadReference() {
	unsigned char int_H = DATAEE_ReadByte(MEMORY_ADDRESS_REF_REFERENCE);
	unsigned char int_L = DATAEE_ReadByte(MEMORY_ADDRESS_REF_REFERENCE + 1);
	return (int_H << 8) + int_L;
}
unsigned int ReadProductStart() {
	unsigned char int_H = DATAEE_ReadByte(MEMORY_ADDRESS_REF_PRODUCT_START);
	unsigned char int_L = DATAEE_ReadByte(MEMORY_ADDRESS_REF_PRODUCT_START + 1);
	return (int_H << 8) + int_L;
}
unsigned int ReadProductEnd() {
	unsigned char int_H = DATAEE_ReadByte(MEMORY_ADDRESS_REF_PRODUCT_END);
	unsigned char int_L = DATAEE_ReadByte(MEMORY_ADDRESS_REF_PRODUCT_END + 1);
	return (int_H << 8) + int_L;
}
unsigned int ReadProductScanSpeed() {
	unsigned char int_H = DATAEE_ReadByte(MEMORY_ADDRESS_REF_SPEED);
	unsigned char int_L = DATAEE_ReadByte(MEMORY_ADDRESS_REF_SPEED + 1);
	return (int_H << 8) + int_L;
}
unsigned char ReadHoldDutyRef() {
	return DATAEE_ReadByte(MEMORY_ADDRESS_REF_DUTY_REF);
}
unsigned char ReadHoldDutyComp() {
	return DATAEE_ReadByte(MEMORY_ADDRESS_REF_DUTY_COMP);
}
unsigned int ReadPasosCompuerta() {
	unsigned char int_H = DATAEE_ReadByte(MEMORY_ADDRESS_COMP_STEPS);
	unsigned char int_L = DATAEE_ReadByte(MEMORY_ADDRESS_COMP_STEPS + 1);
	return (int_H << 8) + int_L;
}