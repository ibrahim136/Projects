/*
 * LCD_Keypad_3_digits.c
 *
 * Created: 8/17/2026 4:48:36 PM
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

//Keypad functions declaration
uint8_t Keypad(void);
uint16_t Keypad_Num(void);

int main(void)
{
	DDRB = 0xFF;		//setting LCD Data Port for Port B as output
	DDRD = 0xFF;		//setting LCD signals (rs, rw, & en) for PORT D as output
	
	DDRA = 0x0F;		//setting A0,A1,A2,A3 as output to keypad & A3,A5,A6,A7 as input to keypad
	PORTA = 0xFF;		// setting high(VCC) for A0,A1,A2,A3 and enable all pull ups for A3,A5,A6,A7
	
	init_LCD();			// LCD initialization
	wait(100);			// Delay for 0.1 sec. (100 ms)
	
	LCD_cmd(0x0C);		// Display on, Cursor off
	wait (100);			// Delay for 0.1 sec. (100 ms)
	
	LCD_cmd(0x01);		// Clear LCD display screen
	wait(100);			// Delay for 0.1 sec. (100 ms)
	
	LCD_write_string("KPad="); //writing "KPad=" in the first line
	
	LCD_cmd(0xC0);		//move cursor to the second line 0th position
	LCD_cmd(0x0C);		// Display on, cursor off
	
	LCD_write_string("Final ="); //writing "Final =" in the second line
	
	
	
	unsigned char ch[4] = {' '}; //ch array to hold ASCII character of the numbers
	uint16_t Data_final;	//Data_final variable to hold the final value that will be displayed on LCD screen
	while (1)
	{
		wait(200);			// Delay for 0.2 sec. (200 ms)
		Data_final = Keypad_Num(); //return Num to Data_final & display Num on first line
		if (Keypad() == 50)		// Check if Enter(D) is pressed
		{
			for (int i=0;i<4;i++)	// looping on ch array
			{
				ch[i] = ' ';	//setting every element to a space in ch array
			}
			Cursor_pos(1,8);	// Start from second line, 9th column
			itoa(Data_final,ch,10);	// integer from Num to ASCII in the ch array (10 to convert in decimal form)
			for (int i=0;i<4;i++) // looping on ch array
			{
				if (ch[i] < '0' || ch[i] >'9') // check if the current ch array element is not a number
				{
					LCD_write(' '); // write a space to the LCD screen
				}
				else
				{
					LCD_write(ch[i]); // write ch array element to the LCD screen
				}
			}
		}
	}
	return 0;
	
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

//Keypad (reading integers and enter from keypad) function definition
uint8_t Keypad(void)
{
	PORTA = 0xF1;	// set A0 to high(VCC);
	wait(1);		//delay for 0.001 sec. (1 ms)
	if ( (PINA & 0b00010000) ) return 1; // if A4 is high input then 1 is pressed
	if ( (PINA & 0b00100000) ) return 2; // if A5 is high input then 2 is pressed
	if ( (PINA & 0b01000000) ) return 3; // if A6 is high input then 3 is pressed
	if ( (PINA & 0b10000000) ) return 'A'; // if A7 is high input then A is pressed
	
	PORTA = 0xF2;	// set A1 to high(VCC);
	wait(1);		//delay for 0.001 sec. (1 ms)
	if ( (PINA & 0b00010000) ) return 4; // if A4 is high input then 4 is pressed
	if ( (PINA & 0b00100000) ) return 5; // if A5 is high input then 5 is pressed
	if ( (PINA & 0b01000000) ) return 6; // if A6 is high input then 6 is pressed
	if ( (PINA & 0b10000000) ) return 'B'; // if A7 is high input then B is pressed
	
	PORTA = 0xF4;	// set A2 to high(VCC);
	wait(1);		//delay for 0.001 sec. (1 ms)
	if ( (PINA & 0b00010000) ) return 7; // if A4 is high input then 7 is pressed
	if ( (PINA & 0b00100000) ) return 8; // if A5 is high input then 8 is pressed
	if ( (PINA & 0b01000000) ) return 9; // if A6 is high input then 9 is pressed
	if ( (PINA & 0b10000000) ) return 'C'; // if A7 is high input then C is pressed
	
	PORTA = 0xF8;	// set A3 to high(VCC);
	wait(1);		//delay for 0.001 sec. (1 ms)
	if ( (PINA & 0b00010000) ) return '*'; // if A4 is high input then * is pressed
	if ( (PINA & 0b00100000) ) return 0; // if A5 is high input then 0 is pressed
	if ( (PINA & 0b01000000) ) return '#'; // if A6 is high input then # is pressed
	if ( (PINA & 0b10000000) ) return 50; // if A7 is high input then D is pressed
	
	return 100;
}

//Keypad_Num (handling values entered on keypad) function definition
uint16_t Keypad_Num(void)
{
	static uint16_t Num =0;		// declare and initialize static variable to hold a value 
	unsigned char ch[4] = {' '} ;	//ch array to hold ASCII character of the numbers
	if (Keypad() <10)		//check if the pressed button is a number less than 10 (1,2,3,4,5,6,7,8,9)
	{
		Num*= 10;		//shift old value to the left and put zero at the end
		Num += Keypad();		// add the new value to change the zero that was put in the last order
		if (Num >255)		//check if Num exceeded the maximum range of 255
		{
			Num =0;		//reset Num to zero
		}
		for (int i=0;i<4;i++)	// looping on ch array
		{
			ch[i] = ' ';	//setting every element to a space in ch array
		}
		
		Cursor_pos(0,5);	// Start from first line, 6th column
		itoa(Num,ch,10);	// integer from Num to ASCII in the ch array (10 to convert in decimal form)
		for (int i=0;i<4;i++) // looping on ch array
		{
			if (ch[i] < '0' || ch[i] >'9') // check if the current ch array element is not a number
			{
				LCD_write(' '); // write a space to the LCD screen
			}
			else
			{
				LCD_write(ch[i]); // write ch array element to the LCD screen
			}
		}
	}
	return Num;
	
	
	
}