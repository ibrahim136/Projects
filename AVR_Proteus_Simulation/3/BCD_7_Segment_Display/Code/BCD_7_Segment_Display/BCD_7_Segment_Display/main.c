/*
 * BCD_7_Segment_Display.c
 *
 * Created: 8/16/2026 4:58:21 PM
 * Author : Ibrahim Haggag
 */ 

#define F_CPU 16000000UL  //CPU 16 MHz frequency definition

#include <avr/io.h> //included to define input & output
#include <util/delay.h> //included for delay


#define wait(x) _delay_ms(x) //delay for x/1000 sec (x ms)


int main(void)
{
	DDRD = 0xFF; //setting all of port D to be output
	PORTD = 0x00; //setting all of port D to be low (GND)
	DDRB = 0x00; //setting all of port B to be input
	PORTB = 0xFF; //enable pull up for all of port B
	while (1)
	{
		switch(PINB)
		{
			case 1 : PORTD = 1; break;
			case 2 : PORTD = 2; break;
			case 3 : PORTD = 3; break;
			case 4 : PORTD = 4; break;
			case 5 : PORTD = 5; break;
			case 6 : PORTD = 6; break;
			case 7 : PORTD = 7; break;
			case 8 : PORTD = 8; break;
			case 9 : PORTD = 9; break;
			default: PORTD = 0; break;
		}
		wait(100); //delay for 0.1 sec (100 ms)
	}
}


