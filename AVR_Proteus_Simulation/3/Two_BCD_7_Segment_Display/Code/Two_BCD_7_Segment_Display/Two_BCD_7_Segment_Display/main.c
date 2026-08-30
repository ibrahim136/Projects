/*
 * Two_BCD_7_Segment_Display.c
 *
 * Created: 8/16/2026 5:39:18 PM
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
	
	uint8_t DataPort;
	while (1)
	{
		DataPort = PINB; //setting DataPort to be initially equal to PINB
		if ( (DataPort & 0b00001111) > 0b00001001) //check if first 4 pins more than 9
		{
			DataPort &= 0b11110000;	//resetting all first 4 ports
		} 
		if ( (DataPort & 011110000) > 0b10010000) //check if last 4 pins more than 9
		{
			DataPort &= 0b00001111; //resetting all last 4 ports
		}
		PORTD = DataPort; //setting PORTD to final modification of DataPort
		
	}
}

