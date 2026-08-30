/*
 * Sequential_LED_Blinking.c
 *
 * Created: 8/15/2026 3:09:01 AM
 * Author : Ibrahim Haggag
 */ 

#define F_CPU 16000000UL  //CPU 16 MHz frequency definition

#include <avr/io.h> //included to define input & output
#include <util/delay.h> //included for delay


#define wait(x) _delay_ms(x) //delay for x/1000 sec (x ms)

int main(void)
{
	DDRD = 0xFF;  //Hex: 0xFF	or		Binary: 0b11111111	or		Decimal: 255
	// DDR = Data Direction Register 0 for input & 1 for output
	while (1)
	{
		int myBit =0; //declaring myBit variable
		PORTD = 0; //resetting all pins of D
		wait(1000); //delay 1 sec (1000 ms)
		
		for (int i =0; i<=7;i++)
		{
			myBit =1; //starting every loop with myBit with value of 1
			for (int j = 1 ; j<=i;j++)
			{
				myBit *= 2; //multiplying the 1 of myBit by 2 times to get the next target pin
			}
			PORTD = myBit; //setting the target pin and resetting the others
			wait(200); //delay for 0.2 sec (200 ms)
		}
	}
}