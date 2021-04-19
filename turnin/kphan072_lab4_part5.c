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
	DDRD = 0x00;
	PORTD = 0xFF; // Configure port D's 8 pins as inputs
	DDRB = 0xFF;
	PORTB = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s

	unsigned short weight = 0;
	unsigned char tmpB = 0;
	while (1)
	{
		tmpB = 0;
		weight = PIND;
		weight = (weight << 1) | (PINB & 0x01);
		if (weight >= 70)
		{
			// PB1 = 1;
			tmpB = (tmpB | 0x02);
		}
		else if (weight > 5 && weight < 70)
		{
			// PB1 = 0;
			// PB2 = 1;
			tmpB = (tmpB | 0x04);
		}
		PORTB = tmpB;
	}
	return 0;
}
