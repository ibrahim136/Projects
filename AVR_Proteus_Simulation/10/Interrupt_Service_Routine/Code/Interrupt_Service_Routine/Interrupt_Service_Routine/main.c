/*
 * Interrupt_Service_Routine.c
 *
 * Created: 8/18/2026 11:06:25 AM
 * Author : Ibrahim Haggag
 */ 

#define F_CPU 16000000UL  //CPU 16 MHz frequency definition

#include <avr/io.h> //included to define input & output
#include <util/delay.h> //included for delay
#include <avr/interrupt.h> //included for ISR (interrupt service routine)

#define wait(x) _delay_ms(x) //delay for x/1000 sec (x ms)

ISR(PCINT3_vect) //Interrupt Service Routine for PCINT3 (group 3 of all of PIN D)
{
	PORTB &= ~(1<<PORTB7);	//setting Port B7 to low(GND) output
	while (PIND & (1<<PIND7))  //while PIND7 is high (VCC) input
	{
		PORTB |= ( (1<<PORTB0) | (1<<PORTB1) );		//setting Port B0,B1 to high(VCC) output
		wait(200);		//delay for 0.2 sec. (200 ms)
		PORTB &= ~( (1<<PORTB0) | (1<<PORTB1) );	//setting Port B0,B1 to low(GND) output
		wait(200);		//delay for 0.2 sec. (200 ms)
	}
}

int main(void)
{
	DDRB = 0xFF;		// set Port B as output for all pins
	
	
    DDRD = 0x00;		// set Port D as input for all pins
	PORTD = 0xFF;		// enable pull up for all pins
	
	// Enabling Pin Change interrupt for PIN D7 
	PCMSK3 |= (1<<PCINT31);		//setting PCINT31 (PIND 7) to 1 in PCMSK1
	PCICR |= (1<<PCIE3);		//Enabling Pin Change interrupt for PCMSK1
	// PCIE3 means enable all of group no. 3 which includes all of PIN D 
	
	sei();		//setting global interrupt
    while (1) 
    {
		PORTB |= (1<<PORTB7);	//setting Port B7 to high(VCC) output
		wait(1000);		//delay for 1 sec. (1000 ms)
		PORTB &= ~(1<<PORTB7);	//setting Port B7 to low(GND) output
		wait(1000);		//delay for 1 sec. (1000 ms)
    }
}

