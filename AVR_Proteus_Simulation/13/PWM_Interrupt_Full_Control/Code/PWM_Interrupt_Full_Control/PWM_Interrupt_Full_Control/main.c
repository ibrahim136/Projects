/*
 * PWM_Interrupt_Full_Control.c
 *
 * Created: 8/18/2026 6:31:58 PM
 * Author : Ibrahim Haggag
 */ 

#define F_CPU 16000000UL  //CPU 16 MHz frequency definition

#include <avr/io.h> //included to define input & output
#include <util/delay.h> //included for delay
#include <avr/interrupt.h> //included for ISR (Interrupt Service Routine)


#define wait(x) _delay_ms(x) //delay for x/1000 sec (x ms)

// PWM_Timer functions declaration
void PWM_Init(void);
void PWM_Duty(uint8_t Time_Val);

ISR(TIMER0_COMPA_vect) //Interrupt Service Routine for ON mode
{
	uint16_t Period = OCR1A;
	
	OCR1B++; //Increasing duty cycle from 0 to OCR1A
	
	if (OCR1B >= Period) //check if OCR1B reached or exceeded the value of OCR1A
	{
		OCR1B = 0; //reset OCR1B to zero
	}
	
	//PORTB |= (1<<PORTB0);	//setting Port B0 to high (VCC) (ON Mode)
}
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
	
	OCR1A = 800;		//set OCR1A = 800 (freq)
	OCR1B = 20;			// set OCR1B = 20 (Duty Cycle)
	
	sei();		// enable global interrupt
	
	PWM_Init();		//Pulse Width Modulation Initialization
	PWM_Duty(4);	//setting duty time to 4 ms
	
	while (1)
	{
		
	}
}

//PWM_Init (Pulse Width Modulation Initialization) function definition
void PWM_Init(void)
{
	TIMSK1 |= ( (1<<OCIE1A) | (1<<OCIE1B) );		//enable OCRA & OCRB
	TCCR1B |= (1<<CS10); //setting CS1[0] to 1 ( CS1[0:2] = 001 for prescaler = 0)
	TCCR1B |= (1<<WGM12); // setting WGM1[2] = 1
	// WGM1[0:2] = 100 for CTC (Clear Time on Compare) mode operation
}

// PWM_Duty (Pulse Width Modulation Duty cycle) function definition
void PWM_Duty(uint8_t Time_Val)
{
	TCCR0A |= (1<<WGM01);	// setting WGM0[1] = 1
	// WGM1[0:2] = 010 for CTC (Clear Time on Compare) mode operation
	
	TCCR0B |= ( (1<<CS00) | (1<<CS02) ); //setting CS0[0] & CS0[2] to 1 ( CS0[0:2] = 101 for prescaler = 1024)
	
	TIMSK0 |= (1<<OCIE0A);		//set OCIE0A to 1 for Output Compare A Match Interrupt Enable
	
	uint16_t N = 1024;	// N = prescaler factor
	
	//Freq = F_CPU / (2 * N * ( 1 + OCRnx) )
	//OCRnx = ( F_CPU  / ( 2 * N * Freq ) ) - 1
	//OCRnx = ( (Time_in_ms * F_CPU)  / ( 1000 * N ) ) - 1
	OCR0A = ( (Time_Val * F_CPU)  / ( 1000 * N ) ) - 1;
	
	
	
}
