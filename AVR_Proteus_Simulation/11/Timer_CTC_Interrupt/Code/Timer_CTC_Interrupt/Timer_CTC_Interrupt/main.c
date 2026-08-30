/*
 * Timer_CTC_Interrupt.c
 *
 * Created: 8/18/2026 1:16:44 PM
 * Author : Ibrahim Haggag
 */ 

#define F_CPU 16000000UL  //CPU 16 MHz frequency definition

#include <avr/io.h> //included to define input & output
#include <util/delay.h> //included for delay
#include <avr/interrupt.h> //included for ISR (Interrupt Service Routine)

ISR(TIMER1_COMPA_vect)	// Interrupt Service Routine timer 1 counter with compare match A
{
	PINB |= (1<< PINB0); //toggling Port B0 between high (VCC) and low (GND)
}

//Timer functions declaration
void Timer_Frequency(uint16_t Freq);	//Timer_Frequency declaration

int main(void)
{
    DDRB = 0xFF; // setting all of Port B as output
	PORTB |= (1<<PORTB0); //setting Port B0 to high(VCC)
	
	sei();		//enable global Interrupt
	Timer_Frequency(4); //setting frequency to 4hz (ISR every 0.25 sec)
    while (1) 
    {
		
    }
}

//Timer_Frequency (setting timer frequency) function definition
void Timer_Frequency(uint16_t Freq){
	TCCR1B |= (1<<CS12);		// setting CS1[2] to 1 (CS1[0:2] = 100 to set prescaler to 256)
	TCCR1B |= (1<<WGM12);		// setting WGM1[2] to 1(WGM1[0:2] = 100 to set CTC mode)
	TIMSK1 |= (1<<OCIE1A);		// setting Timer/Counter 1, Output Compare A Match Interrupt Enable
	
	
	//Freq = F_CPU / (2 * N * ( 1 + OCRnx) )
	//OCRnx = ( F_CPU  / ( 2 * N * Freq ) ) - 1
	uint16_t N = 256;		//prescaler factor = N
	OCR1A = (F_CPU/ (2*N*Freq)) -1;		// modifying OCR1A to get desired frequency
	
}