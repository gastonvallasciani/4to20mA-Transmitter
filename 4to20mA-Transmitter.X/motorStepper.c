/*
 * File:   motorStepper.c
 * Author: Nico Christie
 *
 * Created on 9 de marzo de 2016, 11:18
 */

#include "mcc_generated_files/epwm1.h"
#include "mcc_generated_files/epwm2.h"
#include "tc_pin_manager.h"					// Needed for Phases
#include "motorStepper.h"
#include "devices.h"
#include "tasks.h"							// Needed for 'UpdateMotores'

// Driver para motores paso a paso Sanyo Denki

// Sanyo Denki 103H7123-0710 (más grande)
// Sanyo Denki 103-547-52500 (más chico)
//	- 1.8 grados por paso normal/wave
//	- 0.9 grados por paso microstep
//	- Una vuelta son 200 pasos normal/wave
//	- Una vuelta son 400 pasos microstep

#define FORWARD				1
#define BACKWARD			0
#define HIGH				1
#define LOW					0
#define YES					1
#define NO					0

#define DEFAULT_MAX_COUNT	32500	// signed int
#define DEFAULT_POS_DARK	0
#define DEFAULT_POS_REF		10
#define DEFAULT_POS_PROD_S	20
#define DEFAULT_POS_PROD_E	30		// Ojo con este default que tambien lo va a usar para Pasos Compuerta
#define DEFAULT_POS_MUX_X	100

#define TOP_SPEED			600
#define	DEFAULT_SPEED		480

#define PHASE1				1
#define PHASE2				2
#define PHASE3				3
#define PHASE4				4
#define PHASE5				5
#define PHASE6				6
#define PHASE7				7
#define PHASE8				8
#define PHASE_COUNT			8

#define INVERT_FWD_BWD		YES

void StepperMove(tStepperMotor*);
void SetSteps(tStepperMotor*, signed int);
void Step(tStepperMotor*, unsigned char);

// Private Functions
void StepperMove(tStepperMotor* Motor)
{
	// TMR2 interrupts every 100us.
	// StepperMotor_Update is called every ~100us.
    //Me.Multiplexer.Speed = Me.Multiplexer.ScanSpeed;
	//unsigned int MaxDelta = TOP_SPEED - Motor->Speed;
    unsigned int MaxDelta = 40;
	if (++Motor->SpeedCounter == MaxDelta)
	{
		Motor->SpeedCounter = 0;
		if (Motor->PendingSteps > 0)
		{
#if (INVERT_FWD_BWD == NO)
			Step(Motor, FORWARD);
#else
			Step(Motor, BACKWARD);
#endif
			Motor->PhaseHandler(Motor);
		}
		else if (Motor->PendingSteps < 0)
		{
#if (INVERT_FWD_BWD == NO)
			Step(Motor, BACKWARD);
#else
			Step(Motor, FORWARD);
#endif
			Motor->PhaseHandler(Motor);
		}
		else
		{
			Motor->ReleaseHandler(Motor);
			Motor->Changed = YES;
			Motor->Moving = NO;
		}
	}
}
void SetSteps(tStepperMotor* Motor, signed int Steps)
{
	Motor->OverShootCount = Motor->OverShoot;
	Motor->PendingSteps = Steps;
	Motor->Changed = YES;
	Motor->Moving = YES;
}
void Step(tStepperMotor* Motor, unsigned char Direction)
{
#if (INVERT_FWD_BWD == NO)
	// Origin check
	if ((Direction == BACKWARD) && Motor->AtHome)
	{
		Motor->PendingSteps = 0;
		Motor->StepCount = 0;
		return;
	}
	
	switch (Motor->DriveMode)
	{
		case NormalDrive:
			Motor->Phase.Current = (Direction == FORWARD ? Motor->Phase.Current->Normal.Next : Motor->Phase.Current->Normal.Prev);
			break;
		case WaveDrive:
			Motor->Phase.Current = (Direction == FORWARD ? Motor->Phase.Current->WaveDrive.Next : Motor->Phase.Current->WaveDrive.Prev);
			break;
		case MicroStep:
			Motor->Phase.Current = (Direction == FORWARD ? Motor->Phase.Current->MicroStep.Next : Motor->Phase.Current->MicroStep.Prev);
			break;
	}
	
	// A step was performed, update StepCount and PendingSteps
	if (Direction == FORWARD)
	{
		Motor->StepCount++;
		Motor->PendingSteps--;
	}
	else
	{
		Motor->StepCount--;
		Motor->PendingSteps++;
	}
#else
	// Origin check
	if ((Direction == FORWARD) && Motor->AtHome && (Motor->OverShootCount-- == 0))
	{
		Motor->PendingSteps = 0;
		Motor->StepCount = 0;
		return;
	}
	
	switch (Motor->DriveMode)
	{
		case NormalDrive:
			Motor->Phase.Current = (Direction == FORWARD ? Motor->Phase.Current->Normal.Next : Motor->Phase.Current->Normal.Prev);
			break;
		case WaveDrive:
			Motor->Phase.Current = (Direction == FORWARD ? Motor->Phase.Current->WaveDrive.Next : Motor->Phase.Current->WaveDrive.Prev);
			break;
		case MicroStep:
			Motor->Phase.Current = (Direction == FORWARD ? Motor->Phase.Current->MicroStep.Next : Motor->Phase.Current->MicroStep.Prev);
			break;
	}
	
	// A step was performed, update StepCount and PendingSteps
	if (Direction == BACKWARD)
	{
		Motor->StepCount++;
		Motor->PendingSteps--;
	}
	else
	{
		Motor->StepCount--;
		Motor->PendingSteps++;
	}
#endif
}

// Public Functions
void Referencia_SetPhase(tStepperMotor* Motor)
{
	// Apply phase
	switch (Motor->Phase.Current->Tag)
	{
		case PHASE1:
			MOTOR_REF_FASE_1();
			break;
		case PHASE2:
			MOTOR_REF_FASE_2();
			break;
		case PHASE3:
			MOTOR_REF_FASE_3();
			break;
		case PHASE4:
			MOTOR_REF_FASE_4();
			break;
		case PHASE5:
			MOTOR_REF_FASE_5();
			break;
		case PHASE6:
			MOTOR_REF_FASE_6();
			break;
		case PHASE7:
			MOTOR_REF_FASE_7();
			break;
		case PHASE8:
			MOTOR_REF_FASE_8();
			break;
		default:
			MOTOR_REF_FASE_0();
			break;
	}
}
void Referencia_SetTorque(tStepperMotor* Motor, unsigned char Duty)
{
	// dutyValue = 115 = 100% duty - Mi Duty va de 0 a 10
	EPWM1_LoadDutyValue((uint16_t)(11.5*Duty));
	EPWM2_LoadDutyValue((uint16_t)(11.5*Duty));
}
void Referencia_Block(tStepperMotor* Motor)
{
	// dutyValue = 115 = 100% duty - Mi Duty va de 0 a 10
	EPWM1_LoadDutyValue((uint16_t)(11.5*Motor->Hold.DutyOff));
	EPWM2_LoadDutyValue((uint16_t)(11.5*Motor->Hold.DutyOff));
}

void StepperMotor_Init(tStepperMotor* Motor)
{
	Motor->Phase.Current = &(Motor->Phase.Phase1);
	Motor->AtHome = NO;
	Motor->OverShoot = 0;
	Motor->OverShootCount = 0;
	Motor->StepCount = 0;
	Motor->Speed = High;
	Motor->ScanSpeed = High;
	Motor->MaxCount = DEFAULT_MAX_COUNT;
	Motor->Signals.Dark = DEFAULT_POS_DARK;
	Motor->Signals.Reference = DEFAULT_POS_REF;
	Motor->Signals.ProductStart = DEFAULT_POS_PROD_S;
	Motor->Signals.ProductEnd = DEFAULT_POS_PROD_E;
	for (int i = 0; i < MULTIPLEXER_CHANNEL_COUNT; i++)
		Motor->Signals.Multiplexer[i] = 400 + (DEFAULT_POS_MUX_X * (i + 1));
	Motor->DriveMode = MicroStep;
	Motor->Hold.DutyOff = 3;
	
	Motor->Phase.Phase0.Normal.Next = &(Motor->Phase.Phase1);
	Motor->Phase.Phase0.Normal.Prev = &(Motor->Phase.Phase7);
	Motor->Phase.Phase0.WaveDrive.Next = &(Motor->Phase.Phase2);
	Motor->Phase.Phase0.WaveDrive.Prev = &(Motor->Phase.Phase8);
	Motor->Phase.Phase0.MicroStep.Next = &(Motor->Phase.Phase1);
	Motor->Phase.Phase0.MicroStep.Prev = &(Motor->Phase.Phase8);
	
	// Normal Drive
	Motor->Phase.Phase1.Tag = PHASE1;
	Motor->Phase.Phase1.Normal.Next = &(Motor->Phase.Phase3);
	Motor->Phase.Phase1.Normal.Prev = &(Motor->Phase.Phase7);
	Motor->Phase.Phase1.WaveDrive.Next = &(Motor->Phase.Phase2);	// Condición irregular cuando
	Motor->Phase.Phase1.WaveDrive.Prev = &(Motor->Phase.Phase8);	// cambia de un modo a otro
	Motor->Phase.Phase1.MicroStep.Next = &(Motor->Phase.Phase2);
	Motor->Phase.Phase1.MicroStep.Prev = &(Motor->Phase.Phase8);

	Motor->Phase.Phase3.Tag = PHASE3;
	Motor->Phase.Phase3.Normal.Next = &(Motor->Phase.Phase5);
	Motor->Phase.Phase3.Normal.Prev = &(Motor->Phase.Phase1);
	Motor->Phase.Phase3.WaveDrive.Next = &(Motor->Phase.Phase4);	// Condición irregular cuando
	Motor->Phase.Phase3.WaveDrive.Prev = &(Motor->Phase.Phase2);	// cambia de un modo a otro
	Motor->Phase.Phase3.MicroStep.Next = &(Motor->Phase.Phase4);
	Motor->Phase.Phase3.MicroStep.Prev = &(Motor->Phase.Phase2);

	Motor->Phase.Phase5.Tag = PHASE5;
	Motor->Phase.Phase5.Normal.Next = &(Motor->Phase.Phase7);
	Motor->Phase.Phase5.Normal.Prev = &(Motor->Phase.Phase3);
	Motor->Phase.Phase5.WaveDrive.Next = &(Motor->Phase.Phase6);	// Condición irregular cuando
	Motor->Phase.Phase5.WaveDrive.Prev = &(Motor->Phase.Phase4);	// cambia de un modo a otro
	Motor->Phase.Phase5.MicroStep.Next = &(Motor->Phase.Phase6);
	Motor->Phase.Phase5.MicroStep.Prev = &(Motor->Phase.Phase4);

	Motor->Phase.Phase7.Tag = PHASE7;
	Motor->Phase.Phase7.Normal.Next = &(Motor->Phase.Phase1);
	Motor->Phase.Phase7.Normal.Prev = &(Motor->Phase.Phase5);
	Motor->Phase.Phase7.WaveDrive.Next = &(Motor->Phase.Phase8);	// Condición irregular cuando
	Motor->Phase.Phase7.WaveDrive.Prev = &(Motor->Phase.Phase6);	// cambia de un modo a otro
	Motor->Phase.Phase7.MicroStep.Next = &(Motor->Phase.Phase8);
	Motor->Phase.Phase7.MicroStep.Prev = &(Motor->Phase.Phase6);

	// Wave Drive
	Motor->Phase.Phase2.Tag = PHASE2;
	Motor->Phase.Phase2.Normal.Next = &(Motor->Phase.Phase3);		// Condición irregular cuando
	Motor->Phase.Phase2.Normal.Prev = &(Motor->Phase.Phase1);		// cambia de un modo a otro
	Motor->Phase.Phase2.WaveDrive.Next = &(Motor->Phase.Phase4);
	Motor->Phase.Phase2.WaveDrive.Prev = &(Motor->Phase.Phase8);
	Motor->Phase.Phase2.MicroStep.Next = &(Motor->Phase.Phase3);
	Motor->Phase.Phase2.MicroStep.Prev = &(Motor->Phase.Phase1);

	Motor->Phase.Phase4.Tag = PHASE4;
	Motor->Phase.Phase4.Normal.Next = &(Motor->Phase.Phase5);		// Condición irregular cuando
	Motor->Phase.Phase4.Normal.Prev = &(Motor->Phase.Phase3);		// cambia de un modo a otro
	Motor->Phase.Phase4.WaveDrive.Next = &(Motor->Phase.Phase6);
	Motor->Phase.Phase4.WaveDrive.Prev = &(Motor->Phase.Phase2);
	Motor->Phase.Phase4.MicroStep.Next = &(Motor->Phase.Phase5);
	Motor->Phase.Phase4.MicroStep.Prev = &(Motor->Phase.Phase3);

	Motor->Phase.Phase6.Tag = PHASE6;
	Motor->Phase.Phase6.Normal.Next = &(Motor->Phase.Phase7);		// Condición irregular cuando
	Motor->Phase.Phase6.Normal.Prev = &(Motor->Phase.Phase5);		// cambia de un modo a otro
	Motor->Phase.Phase6.WaveDrive.Next = &(Motor->Phase.Phase8);
	Motor->Phase.Phase6.WaveDrive.Prev = &(Motor->Phase.Phase4);
	Motor->Phase.Phase6.MicroStep.Next = &(Motor->Phase.Phase7);
	Motor->Phase.Phase6.MicroStep.Prev = &(Motor->Phase.Phase5);

	Motor->Phase.Phase8.Tag = PHASE8;
	Motor->Phase.Phase8.Normal.Next = &(Motor->Phase.Phase1);		// Condición irregular cuando
	Motor->Phase.Phase8.Normal.Prev = &(Motor->Phase.Phase7);		// cambia de un modo a otro
	Motor->Phase.Phase8.WaveDrive.Next = &(Motor->Phase.Phase2);
	Motor->Phase.Phase8.WaveDrive.Prev = &(Motor->Phase.Phase6);
	Motor->Phase.Phase8.MicroStep.Next = &(Motor->Phase.Phase1);
	Motor->Phase.Phase8.MicroStep.Prev = &(Motor->Phase.Phase7);
}
void StepperMotor_Update(tStepperMotor* Motor) { if (Motor->Moving) StepperMove(Motor); }
void StepperMotor_GoHome(tStepperMotor* Motor) { Motor->StepCount = Motor->MaxCount; SetSteps(Motor, -Motor->MaxCount); }
void StepperMotor_GotoDark(tStepperMotor* Motor) { SetSteps(Motor, Motor->Signals.Dark - Motor->StepCount); }
void StepperMotor_GotoReference(tStepperMotor* Motor) { SetSteps(Motor, Motor->Signals.Reference - Motor->StepCount); }
void StepperMotor_GotoProductStart(tStepperMotor* Motor) { SetSteps(Motor, Motor->Signals.ProductStart - Motor->StepCount); }
void StepperMotor_GotoProductEnd(tStepperMotor* Motor) { SetSteps(Motor, Motor->Signals.ProductEnd - Motor->StepCount); }
void StepperMotor_Offset(tStepperMotor* Motor, signed int Steps) { SetSteps(Motor, Steps); }
