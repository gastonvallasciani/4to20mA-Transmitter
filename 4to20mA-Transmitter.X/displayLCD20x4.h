// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef TC_HEADER_DISPLAY_LCD_20X4
#define	TC_HEADER_DISPLAY_LCD_20X4

#define DISPLAY_LINEA(x)            x   // Estos #defines no hacen nada, es 
#define DISPLAY_OFFSET(x)           x   // para pura legibilidad del codigo

#define RACK_LINEA_FIRMWARE         1
#define RACK_LINEA_HARDWARE         RACK_LINEA_FIRMWARE
#define RACK_LINEA_ID               2
#define RACK_LINEA_OLSEN_COUNT      RACK_LINEA_ID
#define RACK_LINEA_TEMP_TEC         3
#define RACK_LINEA_TEMP_RACK		4

#define RACK_OFFSET_FIRMWARE		6
#define RACK_OFFSET_HARDWARE		15
#define RACK_OFFSET_ID              4
#define RACK_OFFSET_OLSEN_COUNT     17
#define RACK_OFFSET_TEMP_TEC_S      6                           // Signo
#define RACK_OFFSET_TEMP_TEC_H      RACK_OFFSET_TEMP_TEC_S + 1  // Enteros
#define RACK_OFFSET_TEMP_TEC_L      RACK_OFFSET_TEMP_TEC_H + 3  // Decimales
#define RACK_OFFSET_TEMP_TEC_G      RACK_OFFSET_TEMP_TEC_L + 2  // Simbolo grados
#define RACK_OFFSET_TEMP_TEC_DUTY   RACK_OFFSET_TEMP_TEC_G + 4  // Duty Peltier
#define RACK_OFFSET_TEMP_RACK_S     6
#define RACK_OFFSET_TEMP_RACK_H     RACK_OFFSET_TEMP_RACK_S + 1
#define RACK_OFFSET_TEMP_RACK_L     RACK_OFFSET_TEMP_RACK_H + 3
#define RACK_OFFSET_TEMP_RACK_G     RACK_OFFSET_TEMP_RACK_L + 2

#define MUX_LINEA_FIRMWARE          RACK_LINEA_FIRMWARE
#define MUX_LINEA_HARDWARE          MUX_LINEA_FIRMWARE
#define MUX_LINEA_ID                RACK_LINEA_ID
#define MUX_LINEA_POSICION          MUX_LINEA_ID
#define MUX_LINEA_PASOS             3
#define MUX_LINEA_MOVIENDO          MUX_LINEA_PASOS
#define MUX_LINEA_AT_HOME           MUX_LINEA_PASOS
#define MUX_LINEA_SEN_A_B           4

#define MUX_OFFSET_FIRMWARE         6
#define MUX_OFFSET_HARDWARE         15
#define MUX_OFFSET_ID               RACK_OFFSET_ID
#define MUX_OFFSET_POSICION         17
#define MUX_OFFSET_PASOS            13
#define MUX_OFFSET_MOVIENDO         18
#define MUX_OFFSET_AT_HOME          19
#define MUX_OFFSET_SEN_A            7
#define MUX_OFFSET_SEN_B            15

#define OLSEN_LINEA_FIRMWARE        1
#define OLSEN_LINEA_HARDWARE        OLSEN_LINEA_FIRMWARE
#define OLSEN_LINEA_ID              OLSEN_LINEA_FIRMWARE

#define OLSEN_OFFSET_FIRMWARE		2
#define OLSEN_OFFSET_HARDWARE		7
#define OLSEN_OFFSET_ID             15

#define OLSEN_LINEA_ESTADO_SENSORES         2

#define OLSEN_OFFSET_ESTADO_REFERENCIA      2
#define OLSEN_OFFSET_ESTADO_FRASCO          6
#define OLSEN_OFFSET_ESTADO_APERTURA        10
#define OLSEN_OFFSET_ESTADO_CIERRE          11
#define OLSEN_OFFSET_ESTADO_BOTON_COMP      15

#define DISPLAY_SIMBOLO_FLECHA_DERECHA      '\x7E'
#define DISPLAY_SIMBOLO_FLECHA_IZQUIERDA    '\x7F'
#define DISPLAY_SIMBOLO_CUADRADO_RELLENO    '\xFF'
#define DISPLAY_SIMBOLO_ESPACIO             ' '
#define DISPLAY_SIMBOLO_GUION_MEDIO         '-'

#define DISPLAY_CLEAR_LINE(x)               LCD_Write("                    ", DISPLAY_LINEA(x), DISPLAY_OFFSET(0))

// Template de configuración de la pantalla LCD (20x4)
// Indice:    01234567890123456789
// LCD_Write("FW: BF____ HW: ____ ", DISPLAY_LINEA(LINEA_FIRMWARE), DISPLAY_OFFSET(0));
// lCD_Write("ID: __ Sensores: __ ", DISPLAY_LINEA(LINEA_ID), DISPLAY_OFFSET(0));
// LCD_Write("Temp TEC:  -__.__ºC ", DISPLAY_LINEA(LINEA_TEMP_TEC), DISPLAY_OFFSET(0));
// LCD_Write("Temp Rack: -__.__ºC ", DISPLAY_LINEA(LINEA_TEMP_RACK), DISPLAY_OFFSET(0));

// Template de configuración de la pantalla LCD (16x2)
// Indice:    0123456789012345
// LCD_Write("V:____|____ ID:_", DISPLAY_LINEA(OLSEN_LINEA_FIRMWARE), DISPLAY_OFFSET(0));
// LCD_Write("Ref:_ Fr:_ Cmp:_", DISPLAY_LINEA(OLSEN_LINEA_ESTADO_SENSORES), DISPLAY_OFFSET(0));

void LCD_Init(void);

void LCD_Write(const unsigned char*, unsigned char, unsigned char);
void LCD_WriteChar(unsigned char, unsigned char, unsigned char);
void LCD_WriteInt(unsigned int, unsigned char, unsigned char, unsigned char);

#endif	/* TC_HEADER_DISPLAY_LCD_20X4 */
