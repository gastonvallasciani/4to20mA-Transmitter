// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef TC_HEADER_DEVICES_H
#define	TC_HEADER_DEVICES_H

#include "motorStepper.h"

#define YES 1
#define NO  0
#define UNKNOWN 2

#define UNKNOWN_DEVICE                      '!'
#define CLASS_ONLINE_4TO20                  'V' // gav
#define CLASS_ONLINE_RACK                   'R'
#define CLASS_ONLINE_OLSEN                  'O'
#define CLASS_ONLINE_MUX                    'm'
#define CLASS_INLAB                         'I'
#define CLASS_INLAB_PLUS                    'P'
#define CLASS_NIREX                         'N'
#define CLASS_DYNACUP                       'D'
#define CLASS_DYNAFLUX                      'F'
#define CLASS_DYNASPEC                      'S'
#define CLASS_MULTIPLEX                     'M'
#define CLASS_CROPQ                         '1' // Cosechadora
#define CLASS_SEEDQ                         '2' // Semillas
#define CLASS_FORAGEQ                       '3' // Forage
#define CLASS_COB_SCANNER                   'C' // Choclo matic
#define CLASS_TRUCK_SCANNER                 'T' // Calador
#define CLASS_FLUID                         'G'
#define CLASS_REFLECTANCE                   'U'

// Todos los comandos que tengan que ver con alguno
// de estos dispositivos/sensores/actuadores van a
// comenzar con algún comando 'HIGH' seguido de un
// comando 'LOW'
//
//  Por ejemplo: 
//   - 'RD': Comando para que el motor de Referencia posicione en Dark
//   - 'DC': Comando para guardar la clase del dispositivo
#define COMMANDS_HIGH_DEVICE_QUERY          '?'
#define COMMANDS_HIGH_MOTOR_REFERENCIA      'R'
#define COMMANDS_HIGH_MOTOR_COMPUERTA       'C'
#define COMMANDS_HIGH_SENSORES              'S'
#define COMMANDS_HIGH_BOTONES               'B'
#define COMMANDS_HIGH_DEBUG                 '>'
#define COMMANDS_HIGH_4TO20TX               'X'         //gav

// Comandos Low para Device Query
#define COMMANDS_LOW_GET_FIRMWARE           'F'
#define COMMANDS_LOW_GET_HARDWARE           'H'
#define COMMANDS_LOW_SAVE_CLASS             'C'
#define COMMANDS_LOW_SAVE_ID                'I'
#define COMMANDS_LOW_FLUSH                  'f'
#define COMMANDS_LOW_HARD_RESET             'r'

// Comandos Low para identificación de constituyente     //gav
#define COMMANDS_LOW_CONSTITUYENTE1         's'          //gav  
#define COMMANDS_LOW_CONSTITUYENTE2         't'          //gav
#define COMMANDS_LOW_CONSTITUYENTE3         'u'          //gav
#define COMMANDS_LOW_CONSTITUYENTE4         'v'          //gav
#define COMMANDS_LOW_CONSTITUYENTE5         'w'          //gav
#define COMMANDS_LOW_CONSTITUYENTE6         'x'          //gav
#define COMMANDS_LOW_CONSTITUYENTE7         'y'          //gav
#define COMMANDS_LOW_CONSTITUYENTE8         'z'          //gav

// Comandos Low para motores
#define COMMANDS_LOW_SEEKHOME               'H'
#define COMMANDS_LOW_GOTODARK               'D'
#define COMMANDS_LOW_GOTOREFERENCE          'R'
#define COMMANDS_LOW_GOTOPRODUCTSTART       'A'
#define COMMANDS_LOW_GOTOPRODUCTEND         'Z'
#define COMMANDS_LOW_GOTO_MUX_POS           'G'
#define COMMANDS_LOW_CLOSE                  COMMANDS_LOW_GOTOPRODUCTEND  // Compuerta
#define COMMANDS_LOW_MOVEFORWARDS           'F'
#define COMMANDS_LOW_MOVEBACKWARDS          'B'
#define COMMANDS_LOW_SPEED                  'S'
#define COMMANDS_LOW_DRIVEMODE              'd'
#define COMMANDS_LOW_HOLD_DUTY              '%'
#define COMMANDS_LOW_MOVING                 'M'
#define COMMANDS_LOW_STEPCOUNT              'C'
#define COMMANDS_LOW_OVERSHOOT              'O'
#define COMMANDS_LOW_SENSADO_A              'a'
#define COMMANDS_LOW_SENSADO_B              'b'
#define COMMANDS_LOW_SAVE_DARK              '0'
#define COMMANDS_LOW_SAVE_REFERENCE         '1'
#define COMMANDS_LOW_SAVE_PRODUCTSTART      '2'
#define COMMANDS_LOW_SAVE_PRODUCTEND        '3'
#define COMMANDS_LOW_SAVE_MUX_POS           'P'
#define COMMANDS_LOW_SAVE_OFFSET            COMMANDS_LOW_SAVE_PRODUCTEND // Compuerta

// Consultas
#define COMMANDS_LOW_GET                    '?'
#define COMMANDS_LOW_SET                    '>'

// Comandos Low para sensores
#define COMMANDS_LOW_APERTURA               'A' // Toma muestra OLSEN
#define COMMANDS_LOW_CIERRE                 'Z' // Toma muestra OLSEN
#define COMMANDS_LOW_CAJON                  'K' // Cajon/Frasco
#define COMMANDS_LOW_COMPUERTA              'C'
#define COMMANDS_LOW_LAMPARA                'L'
#define COMMANDS_LOW_MUESTRA                'M'
#define COMMANDS_LOW_REFERENCIA             'R'
#define COMMANDS_LOW_TEMPERATURA            'T'
#define COMMANDS_LOW_SENSOR_ERROR           'e' // Luego Param[0] = COMMANDS_LOW_x

// Comandos Low para botones
#define COMMANDS_LOW_BOTONSTART             'S'
#define COMMANDS_LOW_BOTONPOWER             'P'
#define COMMANDS_LOW_BOTONCOMPUERTA         'C'

// Errores
#define ERROR_CODE_CHECKSUM_FAILED          '0'
#define ERROR_CODE_WRONG_DIRECTION          '1'
#define ERROR_CODE_WRONG_CLASS              '2'
#define ERROR_CODE_WRONG_ID                 '3'
#define ERROR_CODE_COMMAND_HIGH_UNKNOWN     '4'
#define ERROR_CODE_COMMAND_LOW_UNKNOWN      '5'
#define ERROR_CODE_COMMAND_LOW_NOTSUPPORTED '6'
#define ERROR_CODE_INVALID_PARAMETER        '7'

// Tipos de motor de Referencia
#define MOTORTYPE_STEPPER                   'S'
#define MOTORTYPE_LINEAR_MOTION             'L'
#define MOTORTYPE_SERVO                     'V'

// Packet Description
// (               HEADER               )(               MENSAJE               )(   FOOTER    )
// <SOH>(SENTIDO | PARAMCOUNT)(CLASE)(ID)(COMANDO HIGH)(COMANDO LOW)(PARAMETROS)(CHECKSUM)<EOT>
#define SOH				0x01	// Start of Header, packet start
#define DEV_TO_PC   	0x10	// 0x40 (Device to PC)
#define PC_TO_DEV       0x20    // 0x23 (PC to Device)
#define CAN_BRIDGE      0x30    // 0xhh (PC/Device to Device/PC over Device)
#define I2C_BRIDGE      0x40    // 0xhh (PC/Device to Device/PC over Device)
#define EOT				0x04	// End of Transmission, packet end

#define ACK				0x06	// Acknowledge
#define NAK				0x15	// Not Acknowledge

#define MASK_SENTIDO    0xF0    // 0b11110000
#define MASK_PARAMCOUNT 0x0F    // 0b00001111

#define MSG_START_INDEX 6       // Parameter start index
#define MIN_PACKET_SIZE	8		// SOH, <direction>, <class>, <ID>, <command high>, <command low>, <chechsum>, EOT
#define COMMAND_ID_SIZE 2
#define MAX_PARAM_COUNT	5
#define MAX_PACKET_SIZE MIN_PACKET_SIZE + COMMAND_ID_SIZE + MAX_PARAM_COUNT

#define INTERFACE_UART	1
#define INTERFACE_CAN	2
#define INTERFACE_I2C	3

#define MULTIPLEXER_CHANNEL_COUNT   10

typedef struct {
    unsigned char Start;
    unsigned char Direction;
    unsigned char Class;
    unsigned char ID;
    unsigned char CommandH;
    unsigned char CommandL;
    unsigned char Params[MAX_PARAM_COUNT];
    unsigned char Checksum;
    unsigned char End;
	
	unsigned char ParamCount;
    unsigned char IOInterface;
	unsigned char Valid;
} tPacket;

typedef struct {
    unsigned char Changed;      // Did the sensor status change?
    unsigned char Detecting;    // Is the sensor detecting?
    unsigned char Error;        // Should I have detected and didn't?
    unsigned char SymbolYes;    // Symbol on LCD screen('Y'/'N', '1'/'0')
    unsigned char SymbolNo;     // Symbol on LCD screen('Y'/'N', '1'/'0')
} tSensorState;

typedef struct {
    /** Class - What kind of Device is this?
        Should be set by the Controller (PC), defaults to UNKNOWN_DEVICE.
        Once set, it will be read from EEPROM                 */
    unsigned char Class;
    
    /** ID - Instance of this Device Class
        Should be set by the Controller (PC), defaults to 1.  */
    unsigned char ID;
    
    tSensorState MuxHome;
    tStepperMotor Multiplexer;
    tSensorState I2CMsgAvailable;
} tGeneric_Device;

extern tGeneric_Device Me; // declared in devices.c

extern const char VERSION_FIRMWARE[]; // declared in devices.c, used in tasks.c (LCD)
extern const char VERSION_HARDWARE[]; // declared in devices.c, used in tasks.c (LCD)

void TC_Devices_Init(void);

unsigned char UART_ProcessPacket(tPacket*);
unsigned char I2C_ProcessPacket(tPacket*);

void Send_Status(unsigned char, unsigned char, unsigned char);

#endif	/* TC_HEADER_DEVICES_H */
