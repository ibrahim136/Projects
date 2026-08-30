/*
 * Liquid_Crystal_Display_LCD.c
 *
 * Created: 8/16/2026 6:36:10 PM
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

int main(void)
{
	DDRB = 0xFF;		//setting LCD Data Port for Port B as output
	DDRD = 0xFF;		//setting LCD signals (rs, rw, & en) for PORT D as output
	
	init_LCD();			// LCD initialization
	wait(100);			// Delay for 0.1 sec. (100 ms)
	
	LCD_cmd(0x0C);		// Display on, Cursor off
	wait (100);			// Delay for 0.1 sec. (100 ms)
	
	while (1)
	{
		LCD_write_string("     Ibrahim");
		//****************************************************//
		LCD_cmd(0xC0);		// Move cursor to 2nd line at 0th position
		wait(100);				// delay for 0.1 sec. (100 ms)
		//****************************************************//
		LCD_cmd(0x0C);		// Display on, Cursor off
		wait (100);			// Delay for 0.1 sec. (100 ms)
		//****************************************************//
		LCD_write_string("     Haggag");
		
		LCD_cmd(0x0E);			// Display on, Cursor on
		wait(1000);				// delay for 1 sec. (1000 ms)
		LCD_cmd(0x01);		//  Clear LCD display screen
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
