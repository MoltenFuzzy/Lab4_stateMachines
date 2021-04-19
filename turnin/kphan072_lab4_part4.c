/*	Author: kphan072
 *  Partner(s) Name: Kent Phan
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void)
{
	DDRA = 0x00;
	PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF;
	PORTB = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
	DDRC = 0xFF;
	PORTC = 0x00; // Configure port C's 8 pins as outputs, initialize to 0s

	// unsigned char tmpA = 0;
	unsigned char tmpB = 0;
	unsigned char tmpC = 0;
	while (1)
	{
		tmpB = 0;
		tmpC = 0;
		tmpB = (PINA >> 4) | tmpB;
		tmpC = (PINA << 4) | tmpC;
		PORTB = tmpB;
		PORTC = tmpC;
	}
	return 0;
}
