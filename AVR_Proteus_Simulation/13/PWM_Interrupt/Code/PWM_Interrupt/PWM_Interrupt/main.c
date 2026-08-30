/*
 * PWM_Interrupt.c
 *
 * Created: 8/18/2026 5:56:44 PM
 * Author : Ibrahim Haggag
 */ 

#define F_CPU 16000000UL  //CPU 16 MHz frequency definition

#include <avr/io.h> //included to define input & output
#include <util/delay.h> //included for delay
#include <avr/interrupt.h> //included for ISR (Interrupt Service Routine)


#define wait(x) _delay_ms(x) //delay for x/1000 sec (x ms)

// PWM_Timer functions declaration
void PWM_Init(uint16_t OCR_val);

ISR(TIMER1_COMPA_vect) //Interrupt Service Routine for ON mode
{
	PORTB |= (1<<PORTB0);	//setting Port B0 to high (VCC) (ON Mode)
}
ISR(TIMER1_COMPB_vect) //Interrupt Service Routine for ON mode
{
	PORTB &= ~(1<<PORTB0);	//setting Port B0 to low (GND) (OFF Mode)
}

int main(void)
{
	DDRB |= (1<<DDB0);		//set Port B0 as output 
	
	sei();		// enable global interrupt
	
    while (1) 
    {
		for (uint16_t duty = 1;duty<=99;duty++)
		{
			PWM_Init(duty);		// ON OCR, between 1-99
			wait(10);		//delay for 0.01 sec (10 ms)	
		}
		for (uint16_t duty = 99;duty>=1;duty--)
		{
			PWM_Init(duty);		// ON OCR, between 99-1
			wait(10);		//delay for 0.01 sec (10 ms)
		}
    }
}

//PWM_Init (Pulse Width Modulation Initialization) function definition
void PWM_Init(uint16_t OCR_val)
{
	TIMSK1 |= ( (1<<OCIE1A) | (1<<OCIE1B) );		//enable OCR1A & OCR1B
	TCCR1B |= (1<<CS10); //setting CS1[0] to 1 ( CS1[0:2] = 001 for prescaler = 1)
	TCCR1B |= (1<<WGM12); // setting WGM1[2] = 1
	// WGM1[0:2] = 100 for CTC (Clear Time on Compare) mode operation
	
	//Freq = F_CPU / (2 * N * ( 1 + OCRnx) )
	//OCRnx = ( F_CPU  / ( 2 * N * Freq ) ) - 1
	if (OCR_val > 100) //check if input OCR_val argument more than 100
	{
		OCR_val = 100; //set OCR_val to 100 as maximum value
	}
	OCR1A = 10000;	//assign OCR1A to OCR_val * 100
	OCR1B = OCR_val * 100;	//assign OCR1B to 10000 -OCR_val * 100
}
