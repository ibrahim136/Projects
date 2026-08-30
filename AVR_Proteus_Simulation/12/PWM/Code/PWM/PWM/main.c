/*
 * PWM.c
 *
 * Created: 8/18/2026 2:06:59 PM
 * Author : Ibrahim Haggag
 */ 

#define F_CPU 16000000UL  //CPU 16 MHz frequency definition

#include <avr/io.h> //included to define input & output
#include <util/delay.h> //included for delay

#define wait(x) _delay_ms(x) //delay for x/1000 sec (x ms)


// Pulse Width Modulation functions declaration
void PWM_Init(void);

int main(void)
{
    DDRD |= (1<<DDD4); //setting Port D4 as output which is OCRB1
	
	PWM_Init();		// Pulse Width Modulation initialization
	
	//Freq = F_CPU / ( N * ( 1 + OCRnx) )
	//OCRnx = ( F_CPU  / ( N * Freq ) ) - 1
	OCR1A = 800;	// Controls the frequency
	OCR1B = 0;	// Controls the duty cycle which is 0-1023 (10-bit PWM)
    while (1) 
    {
		while (OCR1B<OCR1A) // looping until duty cycle = 1 (OCR1B = max)
		{
			OCR1B++;		//increment OCR1B (duty cycle) by 1 (increase light intensity)
			wait(5);		//delay for 0.005 sec. (5 ms)
			
		}
		OCR1B =0;
		wait(1000);
		OCR1B= OCR1A;		//delay for 1 sec. (1000 ms)
		while (OCR1B>0) // looping until duty cycle = 0 (OCR1B = min)
		{
			OCR1B--;		//decrement OCR1B (duty cycle) by 1 (decrease light intensity)
			wait(5);		//delay for 0.005 sec. (5 ms)
		}
    }
}

//PWM_Init (Pulse Width Modulation initialization) function definition
void PWM_Init(void)
{
	TCCR1A |= (1<<COM1B1);		// setting COMP1B1 to 1
	//Clear OC1A/OC1B on Compare Match (Set output to low level).
	TCCR1A |= ( (1<<WGM10) | (1<<WGM11) ); // setting WGM1[0:1] = 11
	TCCR1B |= (1<<WGM12); // setting WGM1[2] = 1
	// WGM1[0:2] = 111 for Fast PWM, 10-bit mode operation
	TCCR1B |= (1<<CS10); //setting CS1[0] to 1 ( CS1[0:2] = 001 for prescaler = 0)
	
	TCCR1B |= (1<<WGM13);	// setting WGM1[3] = 1 to enable controlling TOP with OCR1A
}
