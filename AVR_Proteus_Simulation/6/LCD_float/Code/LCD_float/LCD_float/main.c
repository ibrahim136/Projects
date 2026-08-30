/*
 * LCD_float.c
 *
 * Created: 8/17/2026 2:17:38 AM
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

int main(void)
{
	DDRB = 0xFF;		//setting LCD Data Port for Port B as output
	DDRD = 0xFF;		//setting LCD signals (rs, rw, & en) for PORT D as output
	
	init_LCD();			// LCD initialization
	wait(100);			// Delay for 0.1 sec. (100 ms)
	
	LCD_cmd(0x0C);		// Display on, Cursor off
	wait (100);			// Delay for 0.1 sec. (100 ms)
	
	LCD_cmd(0x01);		// Clear LCD display screen
	wait(100);			// Delay for 0.1 sec. (100 ms)
	
	LCD_write_string("TEMP="); //writing "TEMP=" in the first line
	
	LCD_cmd(0xC0);		//move cursor to the second line 0th position
	LCD_cmd(0x0C);		// Display on, cursor off
	
	LCD_write_string("SPD="); //writing "SPD=" in the second line
	
	
	float r0 =768.3,r1 = 1.1457; //defining the two integers: one for 1st row and other for 2nd row
	unsigned char ch[10] = {' '}; // defining ch array of 3 character to hold 3 numbers of r0 & r1
	
	while (1)
	{
		for (int i=0;i<10;i++) // clearing out ch array to be all of spaces
		{
			ch[i] = ' ';
		}
		Cursor_pos(0,5); //setting cursor on the first line, 6th column
		sprintf(ch,"%4.2f",r0); // convert float of r0 to string for ch array with 4 digits before dot and 2 digits after dot
		for (int i=0;i<10;i++) //writing character of ch array to LCD
		{
			if ( (ch[i] != '.') && (ch[i] < '0' || ch[i] >'9') ) //if character if not a number or dot
			{
				LCD_write(' '); // write space to LCD
			}
			else
			{
				LCD_write(ch[i]); //write the number to LCD
			}
		}
		r0++;
		if (r0>999) //if it reached it's max (999)
		{
			r0 = 0.3; //reseting r0 to 0.3 again
		}
		
		for (int i=0;i<10;i++) // clearing out ch array to be all of spaces
		{
			ch[i] = ' ';
		}
		Cursor_pos(1,4); //setting cursor on the first line, 6th column
		sprintf(ch,"%4.4f",r1); // convert float of r0 to string for ch array with 4 digits before dot and 4 digits after dot
		for (int i=0;i<10;i++) //writing character of ch array to LCD
		{
			if ( (ch[i] != '.') && (ch[i] < '0' || ch[i] >'9') ) //if character if not a number or dot
			{
				LCD_write(' '); // write space to LCD
			}
			else
			{
				LCD_write(ch[i]); //write the number to LCD
			}
		}
		r1++;
		if (r1>999) //if it reached it's max (999)
		{
			r1 = 0.1457; //reseting r1 to 0.1457 again
		}
		wait(250);
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