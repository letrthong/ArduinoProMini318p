/************************************************
*
*Creator : Thong LT
*Email   : letrthong@gmail.com
*Website : http://letrthong.blogspot.com
*
*************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>

#include "Timer.h"
#include "Uart.h"
#include "GPIO.h"

volatile uint8_t g_flag_timeout = 0 ;

void sleep(int second)
{
	TCNT1 = 0x0000;
	for (int i = 0 ; i< second; i++)
	{
		for(unsigned int j = 0;j<40 ; j++)
		{
			/*65535 -15535 = 50000
			* 8/16000000   = 0.0000005 
			*50000*(0.0000005 ) *40  = 1s;
			*/
			Timer1_setTimeout(15535);
			while(g_flag_timeout == 0);
		}
	}	
}


void Timer1_init()
{
	/*
	* Prescaler = 8
	* 8/(16000000) = 0.0000005 
	*/
	TCCR1B = (1<<CS11);
    TCNT1 = 0x0000 ; //Top = 0xFFFF->65535
	TIMSK1 |= (1 << TOIE1);
	sei();    
}

void Timer1_setTimeout(unsigned int i)
{
	unsigned char sreg;
	/* Save global interrupt flag*/
	sreg = SREG;
	/* Disable interrupts*/
	cli();
	/* Set TCNT1to i */
	TCNT1= i;
	/* Restore global interrupt flag*/
	SREG = sreg;
	g_flag_timeout = 0;
	sei();   
	
}

int  Timer1_check_timeout()
{
	return g_flag_timeout;
}
void Timer1_stop()
{
	TCCR1B &= ~(1<<CS11);
	TIMSK1 &= ~(1 << OCIE0A);
}


unsigned int Timer1_read_ReadTCNT1()
{
	/*
	*To Do : check again
	*/
	return TCNT1;
}

/*
*Interrupt service routine
* Timer1 overflow
*/
ISR(TIMER1_OVF_vect)
{
	g_flag_timeout = -1;
}