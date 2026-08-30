/*
 * LED_Blinking_using_define.c
 *
 * Created: 8/15/2026 2:41:54 AM
 * Author : Ibrahim Haggag
 */ 

#define F_CPU 16000000UL  //CPU 16 MHz frequency definition

#include <avr/io.h> //included to define input & output
#include <util/delay.h> //included for delay

#define LED_ON PORTD |= (1<<PIND5) // ON mode
#define LED_OFF PORTD &= ~(1<<PIND5) // OFF mode
#define wait(x) _delay_ms(x) //delay for x/1000 sec (x ms)

int main(void)
{
    DDRD = 0xFF;  //Hex: 0xFF	or		Binary: 0b11111111	or		Decimal: 255
    // DDR = Data Direction Register 0 for input & 1 for output
    PORTD = 0x00; // 0 for low(GND) & 1 for high (VCC)
    while (1) 
    {
		LED_ON;
		wait(500);
		LED_OFF;
		wait(500);
    }
}

