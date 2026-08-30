/*
 * USART.c
 *
 * Created: 8/19/2026 11:44:10 AM
 * Author : Ibrahim Haggag
 */ 

#define F_CPU 16000000UL  //CPU 16 MHz frequency definition

#include <avr/io.h> //included to define input & output
#include <util/delay.h> //included for delay


#define wait(x) _delay_ms(x) //delay for x/1000 sec (x ms)


#define FOSC 16000000UL // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

//USART (Universal Synchronous/Asynchronous Receiver-Transmitter) functions declarations
void USART_Init( unsigned int ubrr);  //USART Initialization
unsigned char USART_Receive(void);		//USART Receiver
void USART_Transmit(unsigned char data);	//USART Transmitter

int main(void)
{
    USART_Init(MYUBRR);
    while (1) 
    {
		USART_Transmit(USART_Receive());
    }
}

//USART_Init (Universal Synchronous/Asynchronous Receiver-Transmitter Initialization) function definition
void USART_Init(unsigned int ubrr)
{
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);		//USART BAUD rate register high
	UBRR0L = (unsigned char)ubrr;			//USART BAUD rate register low
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN)|(1<<TXEN);			//USART Control Status register 0 B
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (3<<UCSZ0); // character size (8-bit)
	// by default it's 1 stop bit
	//UCSR0C |= (1<<USBS);	// 2 stop bits
} 

//USART_Receive (USART Receive) function definition
unsigned char USART_Receive(void)
{
	/* wait for the data to be received */
	while ( !(UCSR0A & (1<<RXC) ) ); // waiting for RXC to be true (unread data)
	//RXC = 1 for unread data (full buffer) 
	// RXC = 0 for empty buffer (no data received)
	
	/* get and return received data from buffer */
	return UDR0;		//returning UDR0 8 bit content and clearing content
	//after that RXC will turn to be 0 (empty buffer)
}

//USART_Transmit (USART Transmission) function definition
void USART_Transmit(unsigned char data)
{
	/* wait for buffer to be empty */
	while ( !(UCSR0A & (1<<UDRE) ) ); // waiting for UDRE to be true (unread data)
	//UDRE = 1 for empty buffer (ready to be written)
	// UDRE = 0 for full buffer (NOT ready to be written)
	
	/* put data in the buffer and send the data */
	UDR0 = data;		//sending data to UDR0 8 bit content
}