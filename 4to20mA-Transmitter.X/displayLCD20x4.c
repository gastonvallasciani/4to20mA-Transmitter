/******************************* Program Notes ******************************
  
        All time delays are longer than those specified in most datasheets
        in order to accommodate slower than normal LCD modules.  This
        requirement is well documented but almost always ignored.  The
        information is in a note at the bottom of the right hand
        (Execution Time) column of the instruction set.
 
  ***************************************************************************
                 -------------                   ----------
                | PIC18F46K22 |                 |   LCD    |
                |             |                 |          |
                |          RD3|---------------->|D7        |
                |          RD2|---------------->|D6        |
                |          RD1|---------------->|D5        |
                |          RD0|---------------->|D4        |
                |             |                 |D3        |
                |             |                 |D2        |
                |             |                 |D1        |
                |             |                 |D0        |
                |             |                 |          |
                |          RA5|---------------->|EN        |
                |          RE0|---------------->|BL        |
                |          RE1|---------------->|RS        |
                 -------------                   ----------
  **************************************************************************/

#include "tc_pin_manager.h"
#include "displayLCD20x4.h"
#include "tasks.h"

// LCD module information
#define lcd_LineOne			0x00                // start of line 1
#define lcd_LineTwo			0x40                // start of line 2
#define lcd_LineThree		0x14                // start of line 3 (20x4)
#define lcd_lineFour		0x54                // start of line 4 (20x4)
//#define lcd_LineThree		0x10                // start of line 3 (16x4)
//#define lcd_lineFour		0x50                // start of line 4 (16x4)

// LCD instructions
#define lcd_Clear           0b00000001          // replace all characters with ASCII 'space'
#define lcd_Home            0b00000010          // return cursor to first position on first line
#define lcd_EntryMode       0b00000110          // shift cursor from left to right on read/write
#define lcd_DisplayOff      0b00001000          // turn display off
#define lcd_DisplayOn       0b00001100          // display on, cursor off, don't blink character
#define lcd_FunctionReset   0b00110000          // reset the LCD
#define lcd_FunctionSet4bit 0b00101000          // 4-bit data, 2-line display, 5 x 7 font
#define lcd_SetCursor       0b10000000          // set cursor position

// Function Prototypes
void lcd_write_4(unsigned char);
void lcd_write_instruction_4d(unsigned char);
void lcd_write_character_4d(unsigned char);
void lcd_write_string_4d(const unsigned char*);
void lcd_init_4d(void);

/******************************* Public Functions *************************/
void LCD_Init(void)
{
	PANTALLA_EN_BL_ON();

	// initialize the LCD controller as determined by the defines (LCD instructions)
    lcd_init_4d(); // initialize the LCD display for a 4-bit interface
}

void LCD_Write(const unsigned char* string, unsigned char linea, unsigned char offset)
{
	unsigned char dlinea = lcd_LineOne;
	
	// set cursor to start of requested line
	switch(linea)
	{
		case DISPLAY_LINEA(1):
			dlinea = lcd_LineOne;
			break;
		case DISPLAY_LINEA(2):
			dlinea = lcd_LineTwo;
			break;
		case DISPLAY_LINEA(3):
			dlinea = lcd_LineThree;
			break;
		case DISPLAY_LINEA(4):
			dlinea = lcd_lineFour;
			break;
	}

	lcd_write_instruction_4d(lcd_SetCursor | dlinea + offset);
	lcd_write_string_4d(string);
}
void LCD_WriteChar(unsigned char character, unsigned char linea, unsigned char offset)
{
	unsigned char dlinea = lcd_LineOne;
	
	// set cursor to start of requested line
	switch(linea)
	{
		case DISPLAY_LINEA(1):
			dlinea = lcd_LineOne;
			break;
		case DISPLAY_LINEA(2):
			dlinea = lcd_LineTwo;
			break;
		case DISPLAY_LINEA(3):
			dlinea = lcd_LineThree;
			break;
		case DISPLAY_LINEA(4):
			dlinea = lcd_lineFour;
			break;
	}

	lcd_write_instruction_4d(lcd_SetCursor | dlinea + offset);
	lcd_write_character_4d(character);
}
void LCD_WriteInt(unsigned int number, unsigned char digitos, unsigned char linea, unsigned char offset)
{
	unsigned char string[6];
	unsigned char unidades = (number % 10);
	unsigned char decenas  = (((number - unidades) / 10) % 10);
	unsigned char centenas = (((number - unidades - decenas) / 100) % 10);
	unsigned char miles    = (((number - unidades - decenas - centenas) / 1000) % 10);
	unsigned char decmiles = (((number - unidades - decenas - centenas - miles) / 10000) % 10);
	
	if (digitos > 5) digitos = 5;
	
	unsigned char i = 0;
	string[i++] = '0' + decmiles;
	string[i++] = '0' + miles;
	string[i++] = '0' + centenas;
	string[i++] = '0' + decenas;
	string[i++] = '0' + unidades;
	string[i++] = '\0';
	LCD_Write(string + (5 - digitos), linea, offset);
}

/*============================== 4-bit LCD Functions ======================*/
/*
  Name:     lcd_init_4d
  Purpose:  initialize the LCD module for a 4-bit data interface
  Entry:    equates (LCD instructions) set up for the desired operation
  Exit:     no parameters
  Notes:    uses time delays rather than checking the busy flag
*/
void lcd_init_4d(void)
{
	// Power-up delay
    Delay(1 * _100mSeg);                            // initial 40 mSec delay

	// IMPORTANT - At this point the LCD module is in the 8-bit mode and it is expecting to receive  
	//	 8 bits of data, one bit on each of its 8 data lines, each time the 'E' line is pulsed.
	//
	// Since the LCD module is wired for the 4-bit mode, only the upper four data lines are connected to 
	//   the microprocessor and the lower four data lines are typically left open.  Therefore, when 
	//   the 'E' line is pulsed, the LCD controller will read whatever data has been set up on the upper 
	//   four data lines and the lower four data lines will be high (due to internal pull-up circuitry).
	//
	// Fortunately the 'FunctionReset' instruction does not care about what is on the lower four bits so  
	//   this instruction can be sent on just the four available data lines and it will be interpreted 
	//   properly by the LCD controller.  The 'lcd_write_4' subroutine will accomplish this if the 
	//   control lines have previously been configured properly.

	// Set up the RS and E lines for the 'lcd_write_4' subroutine.
	PANTALLA_RS_Low();
    PANTALLA_EN_LCD_Low();

	// Reset the LCD controller
    lcd_write_4(lcd_FunctionReset);                 // first part of reset sequence
    Delay(10 * _1mSeg);                             // 4.1 mS delay (min)

    lcd_write_4(lcd_FunctionReset);                 // second part of reset sequence
    Delay(2 * _75uSeg);                             // 100uS delay (min)

    lcd_write_4(lcd_FunctionReset);                 // third part of reset sequence
    Delay(1 * _75uSeg);                             // this delay is omitted in the data sheet

	// Preliminary Function Set instruction - used only to set the 4-bit mode.
	// The number of lines or the font cannot be set at this time since the controller is still in the
	//  8-bit mode, but the data transfer mode can be changed since this parameter is determined by one 
	//  of the upper four bits of the instruction.
 
    lcd_write_4(lcd_FunctionSet4bit);               // set 4-bit mode
    Delay(1 * _75uSeg);                             // 40uS delay (min)

	// Function Set instruction
    lcd_write_instruction_4d(lcd_FunctionSet4bit);  // set mode, lines, and font
    Delay(1 * _75uSeg);                             // 40uS delay (min)

	// The next three instructions are specified in the data sheet as part of the initialization routine, 
	//  so it is a good idea (but probably not necessary) to do them just as specified and then redo them 
	//  later if the application requires a different configuration.

	// Display On/Off Control instruction
    lcd_write_instruction_4d(lcd_DisplayOff);       // turn display OFF
    Delay(1 * _75uSeg);                             // 40uS delay (min)

	// Clear Display instruction
    lcd_write_instruction_4d(lcd_Clear);            // clear display RAM
    Delay(2 * _1mSeg);                              // 1.64 mS delay (min)

	// ; Entry Mode Set instruction
    lcd_write_instruction_4d(lcd_EntryMode);        // set desired shift characteristics
    Delay(1 * _75uSeg);                             // 40uS delay (min)

	// This is the end of the LCD controller initialization as specified in the data sheet, but the display
	//  has been left in the OFF condition.  This is a good time to turn the display back ON.
 
	// Display On/Off Control instruction
    lcd_write_instruction_4d(lcd_DisplayOn);        // turn the display ON
    Delay(1 * _75uSeg);                             // 40uS delay (min)
}

/*...........................................................................
  Name:     lcd_write_string_4d
; Purpose:  display a string of characters on the LCD
  Entry:    (theString) is the string to be displayed
  Exit:     no parameters
  Notes:    uses time delays rather than checking the busy flag
*/
void lcd_write_string_4d(const unsigned char *theString)
{
    volatile int i = 0;                             // character counter*/
    while (theString[i] != 0)
    {
        lcd_write_character_4d(theString[i]);
        Delay(1 * _75uSeg);                         // 40 uS delay (min)
        i++;
    }
}

/*...........................................................................
  Name:     lcd_write_character_4d
  Purpose:  send a byte of information to the LCD data register
  Entry:    (theData) is the information to be sent to the data register
  Exit:     no parameters
  Notes:    does not deal with RW (busy flag is not implemented)
*/

void lcd_write_character_4d(unsigned char theData)
{
	PANTALLA_RS_High();
    PANTALLA_EN_LCD_Low();
    lcd_write_4(theData);                           // write the upper 4-bits of the data
    lcd_write_4(theData << 4);                      // write the lower 4-bits of the data
}

/*...........................................................................
  Name:     lcd_write_instruction_4d
  Purpose:  send a byte of information to the LCD instruction register
  Entry:    (theInstruction) is the information to be sent to the instruction register
  Exit:     no parameters
  Notes:    does not deal with RW (busy flag is not implemented)
*/
void lcd_write_instruction_4d(unsigned char theInstruction)
{
	PANTALLA_RS_Low();
    PANTALLA_EN_LCD_Low();
    lcd_write_4(theInstruction);                    // write the upper 4-bits of the data
    lcd_write_4(theInstruction << 4);               // write the lower 4-bits of the data
}

/*...........................................................................
  Name:     lcd_write_4
  Purpose:  send a byte of information to the LCD module
  Entry:    (theByte) is the information to be sent to the desired LCD register
            RS is configured for the desired LCD register
            E is low
            RW is low
  Exit:     no parameters
  Notes:    use either time delays or the busy flag
*/
void lcd_write_4(unsigned char theByte)
{
    if (theByte & (1 << 7)) PANTALLA_D7_ON(); // make data = '1' if necessary
    else PANTALLA_D7_OFF();
	
    if (theByte & 1<<6) PANTALLA_D6_ON();
    else PANTALLA_D6_OFF();

    if (theByte & 1<<5) PANTALLA_D5_ON();
    else PANTALLA_D5_OFF();

    if (theByte & 1<<4) PANTALLA_D4_ON();
    else PANTALLA_D4_OFF();

	// write the data
    // 'Address set-up time' (40 nS)
    PANTALLA_EN_LCD_High();                         // Enable pin high
    Delay(1 * _75uSeg);                             // implement 'Data set-up time' (80 nS) and 'Enable pulse width' (230 nS)
    PANTALLA_EN_LCD_Low();			                // Enable pin low
    Delay(1 * _75uSeg);                             // implement 'Data hold time' (10 nS) and 'Enable cycle time' (500 nS)
}