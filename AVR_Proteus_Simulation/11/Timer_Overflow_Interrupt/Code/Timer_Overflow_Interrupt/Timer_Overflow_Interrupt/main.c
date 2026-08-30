/*
 * Timer_Overflow_Interrupt.c
 *
 * Created: 8/18/2026 12:10:54 PM
 * Author : Ibrahim Haggag
 */ 

#define F_CPU 16000000UL  //CPU 16 MHz frequency definition

#include <avr/io.h> //included to define input & output
#include <util/delay.h> //included for delay
#include <avr/interrupt.h> //included for ISR (Interrupt Service Routine)

#define wait(x) _delay_ms(x) //delay for x/1000 sec (x ms)

ISR(TIMER1_OVF_vect) // Interrupt Service Routine timer 1 overflow
{
	while(1)
	{
		PORTB |= ( (1<<PORTB0) | (1<<PORTB1) );		//setting Port B0,B1 to high(VCC)
		wait(1000);		//delay for 1 sec. (1000 ms)
		PORTB &= ~( (1<<PORTB0) | (1<<PORTB1) );		//setting Port B0,B1 to low(VCC)
		wait(1000);		//delay for 1 sec. (1000 ms)
	}
}


int main(void)
{
    DDRB = 0xFF; // setting all of Port B as output
	PORTB |= (1<<PORTB0); 
	
	TCCR1B |= (1<<CS12);		// setting CS1[2] to 1 (CS1[0:2] = 100 to set prescaler to 256)
	TIMSK1 |= (1<<TOIE1);		// enable timer overflow counter for timer 1
	
	sei();		//enable global ISR (Interrupt Service Routine)
	
    while (1) 
    {
		PORTB = 0x00;		//setting all of Port B to low(VCC)
    }
}

