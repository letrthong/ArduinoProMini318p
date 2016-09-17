/************************************************
*
*Creator : Thong LT
*Email   : letrthong@gmail.com
*Website : http://letrthong.blogspot.com
*
*************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>

#include "Uart.h"
#include "Timer.h"

unsigned char gNewCommand  = 0;

void ADC_init(unsigned char channel)
{
	/*
	*Channel: 4 bits to select channel at Mux3:0 and Atmega328 has 8 channels 
	*/
	
	/*
	*REFS0 : AVCCwith external capacitor at AREF pin
	*/
	
	ADMUX |= channel |(1<<REFS1);
	
	/*
	*ADEN :ADC Enable 
	*ADC Prescaler Selections  = 128
	*ADIE: ADC Interrupt Enable
	*ADATE: ADC Auto Trigger Enable
	*/
	ADCSRA |= (1<<ADEN)|(1<<ADIE)|(1<<ADATE) |(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

void ADC_start()
{
	/*
    *ADSC :ADC Starts interruption
	*/
   ADCSRA |= (1<<ADSC);
}

void ADC_stop()
{   
	/*
    *ADSC :ADC stops interruption
	*/
	ADCSRA &= ~((1<<ADIE));
}
void ADC_resume()
{
	/*
    *ADSC :ADC resumes interruption
	*/
	ADCSRA |= (1<<ADIE);
}
unsigned int ADC_read()
{
    // ADCSRA |= (1<<ADSC);
	//while ( ADCSRA & (1<<ADSC));
	return ADC;
}

ISR(ADC_vect)
{   
	//unsigned int iCurrertValue = ADC;
	ADC_stop();
	/*
	* your code
	*/
	ADC_resume();
	/*
	*Start new session
	*/
}
