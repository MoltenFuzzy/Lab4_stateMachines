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

unsigned char A = 0;
unsigned char B = 0;

enum SM1_STATES
{
	SM1_SMStart,
	SM1_Init,
	SM1_Pound,
	SM1_Y,
	SM1_Lock,
	SM1_Unlock
} SM1_STATE;

void TickLockSystem()
{
	A = PINA;
	unsigned char A1 = PINA & 0x02;
	unsigned char A2 = PINA & 0x04;
	unsigned char A7 = PINA & 0x80;
	switch (SM1_STATE)
	{
	case SM1_SMStart:
		SM1_STATE = SM1_Init;
		B = 0;
		break;
	case SM1_Init:
		if (A2)
		{
			SM1_STATE = SM1_Pound;
		}
		else if (A7)
		{
			SM1_STATE = SM1_Lock;
		}
		else
		{
			SM1_STATE = SM1_Init;
		}
		break;
	case SM1_Pound:
		if (A1 && !A2) // making sure # is not pressed at the same time
		{
			SM1_STATE = SM1_Y;
		}
		break;
	case SM1_Y:
		SM1_STATE = SM1_Unlock;
		break;
	case SM1_Unlock:
		SM1_STATE = SM1_Init;
		break;
	case SM1_Lock:
		SM1_STATE = SM1_Init;
		break;
	default:
		SM1_STATE = SM1_Init;
		break;
	}

	switch (SM1_STATE)
	{
	case SM1_SMStart:
		break;
	case SM1_Init:
		B = 0;
		break;
	case SM1_Pound:
		break;
	case SM1_Y:
		break;
	case SM1_Unlock:
		B = 0x01;
		break;
	case SM1_Lock:
		B = 0x00;
		break;
	}
}

int main(void)
{
	DDRA = 0x00;
	PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF;
	PORTB = 0x00; // Configure port C's 8 pins as outputs, initialize to 0s
	DDRC = 0xFF;
	PORTC = 0x00; // Configure port C's 8 pins as outputs, initialize to 0s

	// Initialize your state variable
	SM1_STATE = SM1_SMStart; // Indicates initial call to tick-fct

	while (1)
	{
		// Call your SM tick function below
		TickLockSystem();
		PORTB = B;
	}

	return 0;
}
