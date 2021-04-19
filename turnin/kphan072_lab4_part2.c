/*	Author: kphan072
 *  Partner(s) Name: Kent Phan
 *	Lab Section:
 *	Assignment: Lab 4 Exercise 2
 *	Exercise Description: Buttons are connected to PA0 and PA1. Output for PORTC is initially 
 *	7. Pressing PA0 increments PORTC once (stopping at 9). Pressing PA1 decrements PORTC once (stopping at 0). 
 *	If both buttons are depressed (even if not initially simultaneously), PORTC resets to 0.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char C;
unsigned char A0_was_pressed = 0;
unsigned char A1_was_pressed = 0;

enum SM1_STATES
{
	SM1_SMStart,
	SM1_Wait,
	SM1_PressInc,
	SM1_PressDec,
	SM1_Reset
} SM1_STATE;

void TickCounter()
{
	unsigned char A0 = PINA & 0x01;
	unsigned char A1 = PINA & 0x02;
	switch (SM1_STATE)
	{
	case SM1_SMStart:
		SM1_STATE = SM1_Wait;
		C = 7;
		break;
	case SM1_Wait:
		// to prevent holding of button by checking previous A0 state
		if ((C <= 9) && A0 && !A0_was_pressed)
		{
			SM1_STATE = SM1_PressInc;
		}
		else if ((C > 0) && A1 && !A1_was_pressed)
		{
			SM1_STATE = SM1_PressDec;
		}
		else if (A0 && A1)
		{
			SM1_STATE = SM1_Reset;
		}
		break;
	case SM1_PressInc:
		if ((C <= 9) && A0 && !A0_was_pressed)
		{
			SM1_STATE = SM1_PressInc;
		}
		else if ((C > 0) && A1 && !A1_was_pressed)
		{
			SM1_STATE = SM1_PressDec;
		}
		else if (A0 && A1)
		{
			SM1_STATE = SM1_Reset;
		}
		else
			SM1_STATE = SM1_Wait;
		break;
	case SM1_PressDec:
		if ((C <= 9) && A0 && !A0_was_pressed)
		{
			SM1_STATE = SM1_PressInc;
		}
		else if ((C > 0) && A1 && !A1_was_pressed)
		{
			SM1_STATE = SM1_PressDec;
		}
		else if (A0 && A1)
		{
			SM1_STATE = SM1_Reset;
		}
		else
			SM1_STATE = SM1_Wait;
		break;
	case SM1_Reset:
		if ((C <= 9) && A0 && !A0_was_pressed)
		{
			SM1_STATE = SM1_PressInc;
		}
		else if ((C > 0) && A1 && !A1_was_pressed)
		{
			SM1_STATE = SM1_PressDec;
		}
		else if (A0 && A1)
		{
			SM1_STATE = SM1_Reset;
		}
		else
			SM1_STATE = SM1_Wait;
		break;
	default:
		SM1_STATE = SM1_Wait;
		break;
	}

	switch (SM1_STATE)
	{
	case SM1_SMStart:
		break;
	case SM1_Wait:
		break;
	case SM1_PressInc:
		C += 1;
		A0_was_pressed = A0;
		break;
	case SM1_PressDec:
		C -= 1;
		A1_was_pressed = A1;
		break;
	case SM1_Reset:
		C = 0;
		break;
	}
}

int main(void)
{
	DDRA = 0x00;
	PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRC = 0xFF;
	PORTC = 0x00; // Configure port C's 8 pins as outputs, initialize to 0s

	// Initialize your state variable
	SM1_STATE = SM1_SMStart; // Indicates initial call to tick-fct

	while (1)
	{
		// Call your SM tick function below
		TickCounter();
		PORTC = C;
	}

	return 0;
}
