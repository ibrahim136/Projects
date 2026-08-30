/*
 * LED_Blinking_using_define_toggle.c
 *
 * Created: 8/15/2026 2:51:38 AM
 * Author : Ibrahim Haggag
 */ 

#define F_CPU 16000000UL  //CPU 16 MHz frequency definition

#include <avr/io.h> //included to define input & output
#include <util/delay.h> //included for delay

#define LED_TOGGLE PIND |= (1<<PIND5) //by using PIN instead of PORT we toggle the bit
#define wait(x) _delay_ms(x) //delay for x/1000 sec (x ms)

int main(void)
{
	DDRD = 0xFF;  //Hex: 0xFF	or		Binary: 0b11111111	or		Decimal: 255
	// DDR = Data Direction Register 0 for input & 1 for output
	PORTD = 0x00; // 0 for low(GND) & 1 for high (VCC)
	while (1)
	{
		LED_TOGGLE;
		wait(500);
		LED_TOGGLE;
		wait(500);
	}
}