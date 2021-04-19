/*	Author: kphan072
 *  Partner(s) Name: Kent Phan
 *	Lab Section:
 *	Assignment: Lab 4 Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char B;

enum SM1_STATES
{
	SM1_SMStart,
	SM1_Wait,
	SM1_ToggleLED,
	SM1_Press
} SM1_STATE;

void TickTurnOnLED()
{
	unsigned char A0 = PINA & 0x01;
	switch (SM1_STATE)
	{
	case SM1_SMStart:
		SM1_STATE = SM1_Wait;
		// B0 is initally on
		B = 0x01;
		break;
	case SM1_Wait:
		if (A0)
		{
			SM1_STATE = SM1_ToggleLED;
		}
		break;
	case SM1_ToggleLED:
		SM1_STATE = SM1_Wait;
		break;
	case SM1_Press:
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
	case SM1_ToggleLED:
		B = ~B & 0x03;
		break;
	case SM1_Press:
		break;
	}
}

int main(void)
{
	DDRA = 0x00;
	PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF;
	PORTB = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s

	// Initialize your state variable
	SM1_STATE = SM1_SMStart; // Indicates initial call to tick-fct

	while (1)
	{
		// Call your SM tick function below
		TickTurnOnLED();
		PORTB = B;
	}

	return 0;
}
