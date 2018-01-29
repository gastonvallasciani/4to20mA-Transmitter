// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef TC_HEADER_PROPERTIES_H
#define	TC_HEADER_PROPERTIES_H

unsigned char MemoryIsInit(void);
void MemoryInit(void);

void SaveClass(unsigned char);
void SaveID(unsigned char);
void SaveMotorType(unsigned char);
void SaveTemperatureDuty(unsigned char);

unsigned char ReadClass(void);
unsigned char ReadID(void);
unsigned char ReadMotorType(void);
unsigned char ReadTemperatureDuty(void);

void SavePos(unsigned char, unsigned int);
void SaveOvershoot(unsigned char);
unsigned int ReadPos(unsigned char);
unsigned char ReadOvershoot();

void SaveDark(unsigned int);
void SaveReference(unsigned int);
void SaveProductStart(unsigned int);
void SaveProductEnd(unsigned int);
void SaveProductScanSpeed(unsigned int);
void SaveHoldDutyRef(unsigned char);
void SavePasosCompuerta(unsigned int);
void SaveHoldDutyComp(unsigned char);

unsigned int ReadDark(void);
unsigned int ReadReference(void);
unsigned int ReadProductStart(void);
unsigned int ReadProductEnd(void);
unsigned int ReadProductScanSpeed(void);
unsigned char ReadHoldDutyRef(void);
unsigned int ReadPasosCompuerta(void);
unsigned char ReadHoldDutyComp(void);

#endif	/* TC_HEADER_PROPERTIES_H */

