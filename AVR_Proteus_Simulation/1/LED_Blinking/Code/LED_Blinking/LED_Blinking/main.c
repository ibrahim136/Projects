/*
 * LED_Blinking.c
 *
 * Created: 8/15/2026 2:12:50 AM
 * Author : Ibrahim Haggag
 */ 

#define F_CPU 16000000UL  //CPU 16 MHz frequency definition

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRD = 0xFF;  //Hex: 0xFF	or		Binary: 0b11111111	or		Decimal: 255
	// DDR = Data Direction Register 0 for input & 1 for output
	PORTD = 0x00; // 0 for low(GND) & 1 for high (VCC)
    while (1) 
    {
		PORTD |= (1<<PIND5) ; // setting pin no. 5 for D to be high
		_delay_ms(500); //delay for 0.5 sec (500 ms)
		PORTD &= ~(1<<PIND5) ; // resetting pin no. 5 for D to be low
		_delay_ms(500); //delay for 0.5 sec (500 ms)
    }
}

