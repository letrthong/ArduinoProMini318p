/************************************************
*
*Creator : Thong LT
*Email   : letrthong@gmail.com
*Website : http://letrthong.blogspot.com
*
*************************************************/

#include <ctype.h>
#include <avr/io.h>
#include <stdlib.h>
#include <string.h>

void USART_Init(unsigned int ubrr)
{
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/*Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	//UCSR0C = (1<<USBS0)|(3<<UCSZ00);
   /* Set frame format: 8data, 1 stop bit */
	UCSR0C = (1<<UCSZ00) | (1 << UCSZ01);
}

int USART_Transmit( unsigned char data)
{
	/* Wait for empty transmit buffer*/
	unsigned int counter = 0;
	while( !( UCSR0A & (1<<UDRE0)) )
	{
		 counter++;
		//Timeout
		if(counter> 20000)
		{
			return -1;
		}
	}
	/* Put data into buffer, sends the data*/
	UDR0 = data;
	return 0;
}

int USART_Transmits( unsigned char *ptr,unsigned int length)
{
	for(unsigned int i = 0; i< length; i++ )
	{
	   if(  USART_Transmit(ptr[i]) != 0)
	   {
		   return i;
	   }
	}
	return 0;
}

int USART_Receive(unsigned char *data)
{   
	/* Wait for data to be received*/
	unsigned int counter = 0;
	while( !(UCSR0A & (1<<RXC0)) )
	{
		//Timeout
		 counter++;
		 //Timeout
		 if(counter> 20000)
		 {
			 return -1;
		 }
	}
	/* Get and return received data from buffer*/
	*data = UDR0;
	return 0;
}

unsigned char* USART_Receives(unsigned int length, unsigned int *byte_read)
{
	 *byte_read = 0;
	unsigned char *ptr  = (unsigned char *)malloc( sizeof(unsigned char) *length + 1);
	if(ptr == '\0')
	{
		return ptr;
	}
	
	for(unsigned int i = 0; i< length ; i++)
	{
		unsigned char data ;
		if(USART_Receive(&data) == 0)
		{
			ptr[i] =data;
			*byte_read =*byte_read+1;
		}
	}
	
	return ptr;
}
