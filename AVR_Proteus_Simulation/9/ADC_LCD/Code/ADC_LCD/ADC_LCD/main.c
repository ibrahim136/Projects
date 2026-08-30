/*
 * ADC_LCD.c
 *
 * Created: 8/18/2026 9:35:23 AM
 * Author : Ibrahim Haggag
 */ 

#define F_CPU 16000000UL  //CPU 16 MHz frequency definition

#include <avr/io.h> //included to define input & output
#include <util/delay.h> //included for delay

#define wait(x) _delay_ms(x) //delay for x/1000 sec (x ms)

//Defining Control Signals & Data for LCD//
#define LCD_DATA PORTB		// setting port B to be LCD Data Port
#define LCD_SIGNALS PORTD	// setting port D to be LCD Signal Port
#define en PD2				// enable signal from port D pin no. 2
#define rw PD1				// read/write signal from port D pin no. 1
#define rs PD0				// register select signal from Port D pin no. 0

//LCD functions declaration
void init_LCD(void); //LCD initialization
void LCD_cmd(unsigned char cmd); //give command to LCD
void LCD_write(unsigned char data); //write character to LCD
void LCD_write_string(unsigned char ch[]); //write string to LCD
void Cursor_pos(unsigned char x_pos,unsigned char y_pos); //x_pos:0~1, y_pos:0~15

//ADC functions declaration
void init_ADC(void);
uint16_t ADC_read(uint8_t channel);

int main(void)
{
	DDRB = 0xFF;		//setting LCD Data Port for Port B as output
	DDRD = 0xFF;		//setting LCD signals (rs, rw, & en) for PORT D as output
	
	init_LCD();			// LCD initialization
	init_ADC();			// ADC initialization
	wait(100);			// Delay for 0.1 sec. (100 ms)
	
	LCD_cmd(0x0C);		// Display on, Cursor off
	wait (100);			// Delay for 0.1 sec. (100 ms)
	
	LCD_cmd(0x01);		// Clear LCD display screen
	wait(100);			// Delay for 0.1 sec. (100 ms)
	
	LCD_write_string("KPad="); //writing "TEMP=" in the first line
	
	LCD_cmd(0xC0);		//move cursor to the second line 0th position
	LCD_cmd(0x0C);		// Display on, cursor off
	
	LCD_write_string("Final ="); //writing "SPD=" in the second line
	
	
	uint16_t Data_final;		// creating 16 bit integer to store ADC value
	unsigned char ch[4] = {' '}; // defining ch array of 3 character to hold 3 numbers of r0 & r1
	
	while (1)
	{
		Data_final = ADC_read(0);		// assigning Data_final to ADC value of channel A0
		for (int i=0;i<4;i++) // clearing out ch array to be all of spaces
		{
			ch[i] = ' ';
		}
		Cursor_pos(1,8); //setting cursor on the first line, 6th column
		itoa(Data_final,ch,10); //integer to ASCII in decimal(10) format
		for (int i=0;i<4;i++) //writing character of ch array to LCD
		{
			if (ch[i] < '0' || ch[i] >'9') //if character if not a number
			{
				LCD_write(' '); // write space to LCD
			}
			else
			{
				LCD_write(ch[i]); //write the number to LCD
			}
		}
		
		wait(200);		//delay for 0.2 sec (200 ms)
	}
	
}

//init_LCD (LCD Initialization) function definition
void init_LCD(void)
{
	LCD_cmd(0x38);		//  Initialization of 16x2 LCD in 8 bit mode
	wait(1);			//  Delay 0.001 sec (1 ms)
	LCD_cmd(0x01);		//  Clear LCD display screen
	wait(1);			//  Delay 0.001 sec (1 ms)
	LCD_cmd(0x02);		//	Return to Home position
	wait(1);			//  Delay 0.001 sec (1 ms)
	LCD_cmd(0x06);		//	Increment cursor every write of 1 character
	wait(1);			//  Delay 0.001 sec (1 ms)
	LCD_cmd(0x80);		//	Go to the first line and 0th position
	wait(1);			//  Delay 0.001 sec (1 ms)
}

// reset (rs) = 0 for sending address & reset (rs) = 1 for sending data

//LCD_cmd (LCD command) function definition --- (en = enable, rs = reset, rw= read/write)
void LCD_cmd(unsigned char cmd)
{
	LCD_DATA = cmd;			//Data lines are set to send command (Port B = Data Lines)
	LCD_SIGNALS &= ~(1<<rs);	// resetting rs to low(GND) or 0 (sending address)
	LCD_SIGNALS &= ~(1<<rw);	// resetting rw to low(GND) or 0
	LCD_SIGNALS |= (1<<en);		// setting en to high(VCC) or 1
	wait(2);					// Delay for 0.002 sec. (2 ms)
	LCD_SIGNALS &= ~(1<<en);	// resetting en to low(GND) or 0
}

//LCD_write (LCD writing) function definition --- (en = enable, rs = reset, rw= read/write)
void LCD_write(unsigned char data)
{
	LCD_DATA = data;			//Data lines are set to send command (Port B = Data Lines)
	LCD_SIGNALS |= (1<<rs);	// resetting to high(VCC) or 1 (sending data)
	LCD_SIGNALS &= ~(1<<rw);	// resetting rw to low(GND) or 0
	LCD_SIGNALS |= (1<<en);		// setting en to high(VCC) or 1
	wait(2);					// Delay for 0.002 sec. (2 ms)
	LCD_SIGNALS &= ~(1<<en);	// resetting en to low(GND) or 0
}

//LCD_write_string (LCD writing string) function definition
void LCD_write_string(unsigned char ch[])
{
	for (uint8_t i = 0;ch[i]!= '\0';i++) // writing characters in ch array
	{
		LCD_write(ch[i]);			// writing each character in ch array
		wait(100);				// delay for 0.1 sec. (100 ms)
	}
}

//Cursor_pos (set cursor position) function definition
void Cursor_pos(unsigned char x_pos,unsigned char y_pos)
{
	uint8_t address =0;
	if (x_pos == 0)
	{
		address = 0x80; //setting address to the first line 0th position command
	}
	else if (x_pos ==1)
	{
		address = 0xC0; //setting address to the first line 0th position command
	}
	if (y_pos <16)
	{
		address += y_pos;
	}
	LCD_cmd(address); //passing the address to LCD_cmd function to execute signal to LCD
}

//init_ADC (Analog to Digital converter initialization) function definition
void init_ADC(void)
{
	ADMUX |= (1<<REFS0);	// setting REFS[0] to 1 to set reference Voltage from AVCC
	ADCSRA |= (1<<ADEN);	// setting ADEN bit to 1 to turn on ADC
	ADCSRA |= (1<<ADSC);	// setting ADSC bit to 1 to start analog to digital conversion
	ADCSRA |= ( (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0) );
	// setting ADPS[0:2] = 111 to set prescaler factor to 128
	// frequency of ADC = F_CPU / prescaler factor = 16MHz / 128 = 1/8 MHz = 125 KHz
	
	 
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