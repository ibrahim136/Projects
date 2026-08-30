/*
 * Binary_Counting_LED_Blinking.c
 *
 * Created: 8/15/2026 3:38:39 AM
 * Author : Ibrahim Haggag
 */ 

#define F_CPU 16000000UL  //CPU 16 MHz frequency definition

#include <avr/io.h> //included to define input & output
#include <util/delay.h> //included for delay


#define wait(x) _delay_ms(x) //delay for x/1000 sec (x ms)

int main(void)
{
	DDRD = 0xFF;  //Hex: 0xFF	or		Binary: 0b11111111	or		Decimal: 255
	// DDR = Data Direction Register 0 for input & 1 for output
	
	while (1)
	{
		PORTD = 0;
		wait(1000); //delay for 1 sec (1000 ms)
		for (uint8_t i =0;i<=255;i++) 
		{
			PORTD = i; //setting the outputs to binary counting
			wait(200); //delay for 0.2 sec (200 ms)
		}
	}
}

