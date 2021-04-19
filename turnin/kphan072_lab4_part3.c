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
	DDRC = 0xFF;
	PORTC = 0x00; // Configure port C's 8 pins as outputs, initialize to 0s

	unsigned char A4 = 0;
	unsigned char A5 = 0;
	unsigned char A6 = 0;

	unsigned char tmpA = 0;
	unsigned char tmpC = 0;
	while (1)
	{
		tmpA = PINA & 0x0F;
		tmpC = 0;
		// if fuel level is 1-2 PC5 lights
		// if fuel level is 3-4 PC5 and PC4 lights
		// if fuel level is 5-6 PC5, PC4, PC3 lights
		// if fuel level is 7-9 PC5, PC4, PC3, PC2
		// if fuel level is 10-12 PC5, PC4, PC3, PC2, PC1
		// if fuel level is 13-15 PC5, PC4, PC3, PC2, PC1, PC0
		// if fuel level is <= 4, PC6 lights up for low fuel
		if (tmpA > 0 && tmpA < 3)
		{
			tmpC = tmpC | 0x20;
		}
		else if (tmpA > 0 && tmpA < 5)
		{
			tmpC = tmpC | 0x30;
		}
		else if (tmpA > 0 && tmpA < 7)
		{
			tmpC = tmpC | 0x38;
		}
		else if (tmpA > 0 && tmpA < 10)
		{
			tmpC = tmpC | 0x3C;
		}
		else if (tmpA > 0 && tmpA < 13)
		{
			tmpC = tmpC | 0x3E;
		}
		else if (tmpA > 0 && tmpA < 16)
		{
			tmpC = tmpC | 0x3F;
		}

		if (tmpA <= 4)
		{
			tmpC = tmpC | 0x40;
		}

		// 1) Read input of input A at 0010000 so at 4
		A4 = PINA & 0x10;
		// 1) Read input of input A at 0100000 so at 5
		A5 = PINA & 0x20;
		// 1) Read input of input A at 1000000 so at 6
		A6 = PINA & 0x40;

		// PA4 is 1 if a key is in the ignition,
		// PA5 is one if a driver is seated,
		// and PA6 is 1 if the driver's seatbelt is fastened.
		// PC7 should light a "Fasten seatbelt" icon if a key is in the ignition, the driver is seated, but the belt is not fastened.
		if (A4 && A5 && !A6)
		{
			// set C7 to 1
			tmpC = tmpC | 0x80;
		}

		PORTC = tmpC;
	}
	return 0;
}
