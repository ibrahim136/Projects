/*
 * Input_Output.c
 *
 * Created: 8/16/2026 4:22:04 PM
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
		if ((PINB & (1<<PINB0)) == 0 ) //check if pin B0 is low input
		{
			wait(1000); //delay for 1 sec (1000 ms)
			PORTD = 0xFF; //setting all of port D to be high (VCC)
			wait(1000); //delay for 1 sec (1000 ms)
			PORTD = 0x00;
		}
	}
}


