// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef TC_HEADER_MOTOR_STEPPER_H
#define	TC_HEADER_MOTOR_STEPPER_H

#define MOTOR_REFERENCIA    1
#define MOTOR_COMPUERTA     0

typedef struct
{
    volatile unsigned int Dark;              // Target step count for Dark acquisition
    volatile unsigned int Reference;         // Target step count for Reference acquisition
    volatile unsigned int ProductStart;      // Target step count for Product acquisition
    volatile unsigned int ProductEnd;        // Target step count for Product acquisition in sweep mode
    
    volatile unsigned int Multiplexer[10];   // Target step count for Multiplexer positions
}tPaPPredefLocations;

typedef struct
{
    volatile unsigned char Counter;          // Hold counter
    volatile unsigned char DutyOff;          // When holding, DutyOn = 1, DutyOff = ?
    
    volatile unsigned int SEN_A;             // Current value for AN0
    volatile unsigned int SEN_B;             // Current value for AN1
}tBlockStatus;

/*      Fases
 *      1       0001
 *      2       0101
 *      3       0100
 *      4       0110
 *      5       0010
 *      6       1010
 *      7       1000
 *      8       1001

        1       1000 <- 0001 -> 0100    Normal
                1001 <- 0001 -> 0101    WaveDrive
                1001 <- 0001 -> 0101    MicroStep

        2       0001 <- 0101 -> 0100    Normal
                1001 <- 0101 -> 0110    WaveDrive
                0001 <- 0101 -> 0100    MicroStep

        3       0001 <- 0100 -> 0010    Normal
                0101 <- 0100 -> 0110    WaveDrive
                0101 <- 0100 -> 0110    MicroStep

        4       0100 <- 0110 -> 0010    Normal
                0101 <- 0110 -> 1010    WaveDrive
                0100 <- 0110 -> 0010    MicroStep

        5       0100 <- 0010 -> 1000    Normal
                0110 <- 0010 -> 1010    WaveDrive
                0110 <- 0010 -> 1000    MicroStep

        6       0010 <- 1010 -> 1000    Normal
                0110 <- 1010 -> 1001    WaveDrive
                0010 <- 1010 -> 1000    MicroStep

        7       0010 <- 1000 -> 0001    Normal
                1010 <- 1000 -> 1001    WaveDrive
                1010 <- 1000 -> 1001    MicroStep

        8       1000 <- 1001 -> 0001    Normal
                1010 <- 1001 -> 0101    WaveDrive
                1000 <- 1001 -> 0001    MicroStep
 */

typedef struct _tHandlers tHandlers;

typedef struct _tPhase tPhase;
typedef struct _tStepMode tStepMode;
typedef struct _tStepperMotor tStepperMotor;

struct _tHandlers
{
	void (*FadeIn)(unsigned char);
	void (*FadeOut)(unsigned char);
	void (*Target)(tStepperMotor*, unsigned char, unsigned char);
};

struct _tStepMode
{
	tPhase* Next;
	tPhase* Prev;
};

struct _tPhase
{
	tStepMode Normal;
	tStepMode WaveDrive;
	tStepMode MicroStep;
    volatile unsigned char Tag;
};

typedef struct
{
    tPhase Phase0;
    tPhase Phase1;
    tPhase Phase2;
    tPhase Phase3;
    tPhase Phase4;
    tPhase Phase5;
    tPhase Phase6;
    tPhase Phase7;
    tPhase Phase8;

    tPhase* Current;
}tPhases;

struct _tStepperMotor
{
    volatile unsigned char Changed;         // Started/Stopped moving?
    volatile unsigned char AtHome;          // Is the Stepper Motor positioned at 0?
    volatile unsigned char OverShoot;       // How many steps should the motor overshoot Home?
    volatile unsigned char OverShootCount;  // Counter for above.
    volatile unsigned char Moving;          // Is the Stepper Motor moving?
    volatile unsigned int Speed;            // Ver STEPPERSPEED
    volatile unsigned int ScanSpeed;        // Ver STEPPERSPEED
    volatile unsigned int SpeedCounter;     // Counts (MaxSpeed - Speed))
    volatile unsigned char DriveMode;       // Should the Motor drive normal, wave or micro-step?
    volatile unsigned int StepCount;        // Current step count
    volatile unsigned int MaxCount;         // Maximum step count
    volatile signed int PendingSteps;       // Steps still to be performed (Timer 2, tmr2.c)
    tPaPPredefLocations Signals;            // Step count for predefined signal locations
    
    tBlockStatus Hold;              // Status when holding phase
    tPhases Phase;                  // Polarization phase
    tHandlers Handlers;
    
    void (*PhaseHandler)(tStepperMotor*);
    void (*TorqueHandler)(tStepperMotor*, unsigned char);
    void (*ReleaseHandler)(tStepperMotor*);
    unsigned char (*StatusHandler)(void);
};

#define BASE_STEPPER_SPEED  280//280
#define TOP_STEPPER_SPEED   480//480
enum DRIVEMODE { NormalDrive = 0, WaveDrive = 1, MicroStep = 2 };
enum STEPPERSPEED { 
    Top = (TOP_STEPPER_SPEED - 1),//5
    High = (TOP_STEPPER_SPEED - 3),//10
    Medium = (TOP_STEPPER_SPEED - 5),//50
    Low = (TOP_STEPPER_SPEED - 10 )//100
};

void Referencia_SetPhase(tStepperMotor*);
void Referencia_SetTorque(tStepperMotor*, unsigned char);
void Referencia_Block(tStepperMotor*);
// To be defined in main.c (or whichever defines current use)
extern unsigned char Referencia_Status(void);

void Compuerta_SetPhase(tStepperMotor*);
void Compuerta_SetTorque(tStepperMotor*, unsigned char);
void Compuerta_Block(tStepperMotor*);
// To be defined in main.c (or whichever defines current use)
extern unsigned char Compuerta_Status(void);

void StepperMotor_Init(tStepperMotor*);
void StepperMotor_Update(tStepperMotor*);
void StepperMotor_GoHome(tStepperMotor*);
void StepperMotor_GotoDark(tStepperMotor*);
void StepperMotor_GotoReference(tStepperMotor*);
void StepperMotor_GotoProductStart(tStepperMotor*);
void StepperMotor_GotoProductEnd(tStepperMotor*);
void StepperMotor_Offset(tStepperMotor*, signed int);

#endif	/* TC_HEADER_MOTOR_STEPPER_H */
