/*
 * PWM_ADC_Motor.c
 *
 * Created: 8/18/2026 3:57:54 PM
 * Author : Ibrahim Haggag
 */ 

#define F_CPU 16000000UL  //CPU 16 MHz frequency definition

#include <avr/io.h> //included to define input & output
#include <util/delay.h> //included for delay

#define wait(x) _delay_ms(x) //delay for x/1000 sec (x ms)


// Pulse Width Modulation functions declaration
void PWM_Init(void);

//ADC functions declaration
void init_ADC(void);
uint16_t ADC_read(uint8_t channel);

int main(void)
{
	DDRD |= (1<<DDD4); //setting Port D4 as output which is OCB1
	
	PWM_Init();		// Pulse Width Modulation initialization
	init_ADC();			// ADC initialization
	
	//Freq = F_CPU / ( N * ( 1 + OCRnx) )
	//OCRnx = ( F_CPU  / ( N * Freq ) ) - 1
	OCR1A = 800;	// Controls the frequency
	OCR1B = 0;	// Controls the duty cycle which is 0-1023 (10-bit PWM)
	while (1)
	{
		OCR1B = 800 - (  ((uint32_t)ADC_read(0) * 800) /1023  );
		wait(200); //delay for 0.2 sec. (200 ms)
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
	TCCR1B |= ( (1<<CS11) | (1<<CS10) ); //setting CS1[0:1] to 11 ( CS1[0:2] = 011 for prescaler = 64)
	
	TCCR1B |= (1<<WGM13);	// setting WGM1[3] = 1 to enable controlling TOP with OCR1A
}

//init_ADC (Analog to Digital converter initialization) function definition
void init_ADC(void)
{
	ADMUX |= (1<<REFS0);	// setting REFS[0] to 1 to set reference Voltage from AVCC
	ADCSRA |= ( (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0) );
	// setting ADPS[0:2] = 111 to set prescaler factor to 128
	// frequency of ADC = F_CPU / prescaler factor = 16MHz / 128 = 1/8 MHz = 125 KHz
	ADCSRA |= (1<<ADEN);	// setting ADEN bit to 1 to turn on ADC
	
	
}

//ADC_read (Analog to Digital converter reading value) function definition
uint16_t ADC_read(uint8_t channel)
{
	ADMUX &= 0xF0;			// resetting old read value
	ADMUX |= channel;		// setting the target reading channel
	ADCSRA |= (1<<ADSC);	// setting ADSC bit to 1 to start new analog to digital single conversion
	while (ADCSRA & (1<<ADSC) );	// looping until ADSC is zero (ADC completed)
	return ADC;		//return ADC value (ADCH + ADCL) of the chosen channel
}