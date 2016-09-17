/************************************************
*
*Creator : Thong LT
*Email   : letrthong@gmail.com
*Website : http://letrthong.blogspot.com
*
*************************************************/
#include <ctype.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "GPIO.h"
#include "Uart.h"

/*
#define PIN_A0  PC0
#define PIN_A1  PC1
#define PIN_A2  PC2
#define PIN_A3  PC3
#define PIN_A6  PC4
#define PIN_A7  PC5

#define PIN_2   PD2
#define PIN_3   PD3
#define PIN_4   PD4
#define PIN_5   PD5
#define PIN_6   PD6
#define PIN_7   PD7

#define PIN_8   PB0
#define PIN_9   PB1
#define PIN_10  PB2

#define PIN_11  PB3  //MOSI
#define PIN_12  PB4  //MISO
#define PIN_13  PB5  //SCK

#define PIN_RXI PD0
#define PIN_TXO PD1*/
void setZerobit(unsigned char *DDRX, char PCX)
{   
	*DDRX &= ~(1<<PCX);
}

void setOneBit(unsigned char *DDRX, char PCX)
{
	*DDRX |= (1<<PCX);
}

VALUE  getBit(unsigned char DDRX, char PCX)
{
	unsigned char  port =  DDRX<<PCX;
	if( (port&1) == 1 )
	{
		return HIGHT;
	}
	return  LOW;
}


void PinMode(PIN pin, MODE mode)
{  
	if (pin == PIN_A0)
	{
		if (mode == OUTPUT )
		{
			/*
			If PORTxn is written logic one when the pin is configured as an output pin, the port pin is driven
			high (one). If PORTxn is written logic zero when the pin is configured as an output pin, the port
			pin is driven low (zero).
			*/
			PORTC |= (1<<PORTC0);
			
			DDRC  |= (1<<DDC0);
			
			/*If PORTxn is written logic one when the pin is configured as an input pin, the pull-up resistor is
			activated. To switch the pull-up resistor off, PORTxn has to be written logic zero or the pin has to
			be configured as an output pin.*/
		}
		else//INPUT
		{   
			setZerobit((unsigned char *)&DDRC,PORTC0);
		}
	}else if (pin == PIN_A1)
	{
		if (mode == OUTPUT )
		{
			PORTC |= (1<<PORTC1);
			DDRC  |= (1<<DDC1);
		}
		else//INPUT
		{   
			setZerobit((unsigned char *)&DDRC,PORTC1);
		}
	}else if (pin == PIN_A2)
	{
		if (mode == OUTPUT )
		{
			PORTC |= (1<<PORTC2);
			DDRC  |= (1<<DDC2);
		}
		else//INPUT
		{
			setZerobit((unsigned char *)&DDRC,PORTC2);
		}
	}else if (pin == PIN_A3)
	{
		
		if (mode == OUTPUT )
		{
			PORTC |= (1<<PORTC3);
			DDRC  |= (1<<DDC3);
		}
		else//INPUT
		{
			setZerobit((unsigned char *)&DDRC,PORTC3);
		}
	}
}
void PinWrite(PIN pin, VALUE value)
{
	if (pin == PIN_A0)
	{
		if (value == HIGHT )
		{
			setOneBit( (unsigned char *)&PORTC,PORTC0) ;
		}
		else//LOW
		{
			setZerobit( (unsigned char *)&PORTC,PORTC0);
		}
	}else if (pin == PIN_A1)
	{
		if (value == HIGHT )
		{
			setOneBit( (unsigned char *)&PORTC,PORTC1) ;
		}
		else//LOW
		{
			setZerobit( (unsigned char *)&PORTC,PORTC1);
		}
	}else if (pin == PIN_A2)
	{
		if (value == HIGHT )
		{
			setOneBit( (unsigned char *)&PORTC,PORTC2) ;
		}
		else//LOW
		{
			setZerobit( (unsigned char *)&PORTC,PORTC2);
		}
	}else if (pin == PIN_A3)
	{
		if (value == HIGHT )
		{
			setOneBit( (unsigned char *)&PORTC,PORTC3) ;
		}
		else//LOW
		{
			setZerobit( (unsigned char *)&PORTC,PORTC3);
		}
	}
}
VALUE PinRead(PIN pin)
{
	if (pin == PIN_A0)
	{  
		return  getBit(PINC,PC0 );
	}
	
	return LOW;
}

