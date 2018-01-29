
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/tmr2.h"
#include "tc_pin_manager.h"
#include "displayLCD20x4.h"
#include "devices.h"
#include "tasks.h"
#include "mcc_generated_files/epwm1.h"
#include "mcc_generated_files/epwm2.h"
#include "epwm3.h"
#include "pwm4.h"
#include "pwm5.h"

#include "I2C.h"

#define DIVIDER_PERIOD				(10 * _100mSeg)
#define DIVIDER_PERIOD_ELAPSED()	(DividerTaskCounter > DIVIDER_PERIOD)

unsigned char DelayTimerTicked;		// Timer 2
unsigned char MotorTimerTicked;		// Timer 2
unsigned int DividerTaskCounter;	// Timer 2

unsigned int I2CMsgTimeout;

inline void Setup_Display_LCD();
inline void Update_Display_LCD();

inline void DividerTask(void);
inline void UpdateSensores(void);
inline void UpdateMotores(void);
inline void UpdateMuxPos(void);

inline void Timer2Tick();
inline void Timer4Tick();

inline void InitTasks()
{
    EPWM1_LoadDutyValue(0);
    EPWM3_LoadDutyValue(0);
    PWM4_LoadDutyValue(0);
    PWM5_LoadDutyValue(0);
    
	TMR2_SetInterruptHandler(Timer2Tick);
	TMR4_SetInterruptHandler(Timer4Tick);
	INTERRUPT_GlobalInterruptEnable();
	INTERRUPT_PeripheralInterruptEnable();
	
	TC_Devices_Init();
	Setup_Display_LCD();
	UpdateID(); // LCD
}
inline void MainTask()
{
}
inline void DividerTask()
{
	Me.Multiplexer.Hold.SEN_A = ADC_GetConversion(channel_AN0);
	Me.Multiplexer.Hold.SEN_B = ADC_GetConversion(channel_AN1);

	DividerTaskCounter = 0;
	Update_Display_LCD();
}

inline void Setup_Display_LCD()
{
	LCD_Init(); // Not before interrupts are enabled
	
	// Textos estáticos de la pantalla LCD
	//         01234567890123456789
	LCD_Write("FW: BF____ HW: ____ ", DISPLAY_LINEA(1), DISPLAY_OFFSET(0));
	LCD_Write("ID: __ Posicion: __ ", DISPLAY_LINEA(2), DISPLAY_OFFSET(0));
	LCD_Write("Pasos motor: _____  ", DISPLAY_LINEA(3), DISPLAY_OFFSET(0));
	LCD_Write("SEN A: ____ B: ____ ", DISPLAY_LINEA(4), DISPLAY_OFFSET(0));
	LCD_Write(VERSION_FIRMWARE, DISPLAY_LINEA(MUX_LINEA_FIRMWARE), DISPLAY_OFFSET(MUX_OFFSET_FIRMWARE));
	LCD_Write(VERSION_HARDWARE, DISPLAY_LINEA(MUX_LINEA_HARDWARE), DISPLAY_OFFSET(MUX_OFFSET_HARDWARE));	
}
inline void Update_Display_LCD()
{
	LCD_WriteInt(Me.Multiplexer.StepCount, 5, DISPLAY_LINEA(MUX_LINEA_PASOS), DISPLAY_OFFSET(MUX_OFFSET_PASOS));
	LCD_WriteInt(Me.Multiplexer.Hold.SEN_A, 4, DISPLAY_LINEA(MUX_LINEA_SEN_A_B), DISPLAY_OFFSET(MUX_OFFSET_SEN_A));
	LCD_WriteInt(Me.Multiplexer.Hold.SEN_B, 4, DISPLAY_LINEA(MUX_LINEA_SEN_A_B), DISPLAY_OFFSET(MUX_OFFSET_SEN_B));
}
inline void UpdateSensores(void)
{
	unsigned char newStatus;
	
	if (MotorTimerTicked == YES) newStatus = SENSOR_OPTO_HOME();
		
	if (Me.MuxHome.Detecting != newStatus)
	{
		Me.MuxHome.Detecting = newStatus;
		LCD_WriteChar(Me.MuxHome.Detecting ? Me.MuxHome.SymbolYes : Me.MuxHome.SymbolNo, DISPLAY_LINEA(MUX_LINEA_AT_HOME), DISPLAY_OFFSET(MUX_OFFSET_AT_HOME));
		Send_Status(COMMANDS_HIGH_SENSORES, COMMANDS_LOW_REFERENCIA, !Me.MuxHome.Detecting);
        MOTOR_REF_ENPOS_Low(); 
		if (Me.MuxHome.Detecting == YES) MOTOR_REF_LED_OFF();
		else MOTOR_REF_LED_ON();
	}
	
	// Si usa comunicación I2C con el motor paso a paso Fuera de la placa
	if ((Me.I2CMsgAvailable.Changed == YES) && (Me.I2CMsgAvailable.Detecting == YES))
	{
		//I2CMsgTimeout = 5 * _100mSeg;
	}
}
 inline void UpdateMotores()
{
	Me.Multiplexer.AtHome = !Me.MuxHome.Detecting;

	if (MotorTimerTicked == YES) 
    {
        //MOTOR_REF_ENPOS_High();
        StepperMotor_Update(&(Me.Multiplexer));
    }
	if (Me.Multiplexer.Changed == YES)
	{
		Me.Multiplexer.Changed = NO;

		if (Me.Multiplexer.Moving)
		{
			LCD_WriteChar(DISPLAY_SIMBOLO_CUADRADO_RELLENO, DISPLAY_LINEA(MUX_LINEA_MOVIENDO), DISPLAY_OFFSET(MUX_OFFSET_MOVIENDO));
			Send_Status(COMMANDS_HIGH_MOTOR_REFERENCIA, COMMANDS_LOW_MOVING, Me.Multiplexer.Moving);
		}
		else
		{
			UpdateMuxPos();
			LCD_WriteChar(DISPLAY_SIMBOLO_ESPACIO, DISPLAY_LINEA(MUX_LINEA_MOVIENDO), DISPLAY_OFFSET(MUX_OFFSET_MOVIENDO));
			Send_Status(COMMANDS_HIGH_MOTOR_REFERENCIA, COMMANDS_LOW_MOVING, Me.Multiplexer.Moving);
		}
	}
}
inline void UpdateMuxPos()
{
	LCD_WriteChar('-', DISPLAY_LINEA(MUX_LINEA_POSICION), DISPLAY_OFFSET(MUX_OFFSET_POSICION));
	LCD_WriteChar('-', DISPLAY_LINEA(MUX_LINEA_POSICION), DISPLAY_OFFSET(MUX_OFFSET_POSICION + 1));

	unsigned char i = 0;
	do
	{
		if (Me.Multiplexer.Signals.Multiplexer[i] == Me.Multiplexer.StepCount)
		{
			LCD_WriteInt(i + 1, 2, DISPLAY_LINEA(MUX_LINEA_POSICION), DISPLAY_OFFSET(MUX_OFFSET_POSICION));
			break;
		}
	} while (++i < MULTIPLEXER_CHANNEL_COUNT);
}
inline void UpdateID()
{
	LCD_WriteInt(Me.ID, 2, DISPLAY_LINEA(MUX_LINEA_ID), DISPLAY_OFFSET(MUX_OFFSET_ID));
}

inline void Timer2Tick()
{
	DividerTaskCounter++;
	DelayTimerTicked = YES;
	MotorTimerTicked = YES;
	// Si usa comunicación I2C con el motor paso a paso Fuera de la placa
	//if ((Me.I2CMsgAvailable.Detecting == YES) && (--I2CMsgTimeout == 0))
	//	asm("RESET");
}
void Delay(unsigned int Timeout)
{
	// Solo puede haber un Delay en ejecución
	// No se puede llamar a Delay desde interrupciones
	DelayTimerTicked = NO; // Timer2Tick cambia a YES
	while (Timeout > 0)
	{
		if (DelayTimerTicked)
		{
			Timeout--;
			DelayTimerTicked = NO;
		}
	}
}

inline void Timer4Tick()
{
	static unsigned int led_toggle_counter;
	if (++led_toggle_counter > 5 * 100) // Los #define _100mSeg son para Timer2
	{
		  LED_STATUS_Toggle();
		led_toggle_counter = 0;
	}
}
