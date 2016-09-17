/************************************************
*
*Creator : Thong LT
*Email   : letrthong@gmail.com
*Website : http://letrthong.blogspot.com
*
*************************************************/

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/eeprom.h>

#include <stdio.h>
#include <stdlib.h>

#include "IRRemoteControl.h"
#include "IRRemoteDef.h"
#include "Uart.h"
#include "Utils.h"
#include "GPIO.h"
#include "Lighting.h"

/*IR information */
IR_FORMAT g_ir_formal;

/*Receive IR data*/
volatile unsigned int  g_IR_Time;
volatile unsigned char g_IR_State;
volatile unsigned char g_IR_Timeout;/*Two values : 0 or -1*/
volatile unsigned int  g_IR_stop;
volatile unsigned char g_IR_data_8hexs[8];
volatile unsigned char g_IR_data_4bits;
volatile unsigned int  g_IR_possition_hex;

/*IR sender*/
volatile unsigned char  g_IR_Send_Arr_Data[33] ;
volatile unsigned char  g_IR_Send_Index_Data;
volatile unsigned char  g_IR_Send_repeat;

/*Delay */
volatile unsigned int  g_sleep_microSeconds;

void Timer0_init()
{
    g_IR_State =IR_START_COMMAND;
    g_IR_Timeout = -1;
    g_IR_stop  = 0;
    g_IR_data_4bits = 0;
    g_IR_possition_hex = 0;

    TCCR0A |= (1 << WGM01);
    /*
    * Prescaler = 8
    * 8/(16000000) = 0.0000005
    */

    TCCR0B |=(1<<CS01);

    /*Top = OCR0A */
    TCNT0=0x00;

    /*Set Compare Value*/
    //OCR0A = 200;
    OCR0A = 20;
    /*
    * 8*200/16000000 = 0.0001s ->100 us  FFFF->65535
    * 8*20/16000000 = 0.00001s ->10 us  FFFF->65535
    */

    /*
    *TOIE0 : Timer/Counter0 Overflow Interrupt Enable
    *OCIE0A Timer/Counter0 Output Compare Match A Interrupt Enable
    */
    TIMSK0 |= (1 << OCIE0A)/*|(1 << TOIE0)*/;

    sei();
}

/*
*Interrupt service routine
* Timer0 overflow
*/
ISR(TIMER0_COMPA_vect)
{
    g_IR_Time ++;

    if (g_IR_Timeout == 0 && g_IR_Time > g_ir_formal.time_interval)
    {
        IR_reset();
        g_IR_Timeout = -1;
    }

    g_sleep_microSeconds ++;
}

void INT0_init()
{
    /*
    * PD2 - Pin D2
    *Any logical change on INT0 generates an interrupt request.
    */
    EICRA  |=(1<<ISC00) ;

    /* External Interrupt Request 0 Enable*/
    EIMSK  |=(1<<INT0);

    /*Turn on interrupts*/
    sei();
}

ISR(INT0_vect)
{
    unsigned int TempTime = g_IR_Time;

    g_IR_Time = 0;
    TCNT0 = 0x00;
    g_IR_Timeout = 0;

    switch(g_IR_State)
    {
    case IR_START_COMMAND:
    {
        if (TempTime > g_ir_formal.time_start_command)
        {
            g_IR_State = IR_START_MARK;
        }
		
        break;
    }
    case IR_START_MARK:
    {
        if (TempTime > (g_ir_formal.time_start_mark -50 )
                && TempTime < (g_ir_formal.time_start_mark +75) )
        {
            g_IR_State = IR_START_SPACE;
        }
        else
        {
            IR_reset();
        }

        break;
    }
    case IR_START_SPACE:
    {
       
        if (TempTime > (g_ir_formal.time_start_space -50) && TempTime <  (g_ir_formal.time_start_space +50))
        {
            g_IR_State = IR_BIT_MARK;
            //USART_Transmits("_",1);
        }
        else
        {
            IR_reset();
        }
        break;
    }
    case IR_BIT_MARK:
    {
        if ( TempTime <= g_ir_formal.time_start_mark)
        {
            g_IR_State = IR_BIT_SPACE;
        }
        else
        {
            IR_reset();
        }

        break;
    }
    case IR_BIT_SPACE:
    {
        unsigned int i =  g_IR_stop%4;

        if (g_IR_stop > (g_ir_formal.data_length -1) )
        {
            IR_reset();
            return;
        }

        if (g_ir_formal.time_one_bit_space > g_ir_formal.time_zero_bit_space)
        {
            if ( TempTime > (g_ir_formal.time_one_bit_space - 50) )
            {
                g_IR_data_4bits = (g_IR_data_4bits<<1 ) + 1 ;
            }
            else
            {
                g_IR_data_4bits = g_IR_data_4bits<<1 ;
            }
        }
        else
        {
            if ( TempTime > (g_ir_formal.time_zero_bit_space- 50) )
            {
                g_IR_data_4bits = (g_IR_data_4bits<<1 ) + 1 ;
            }
            else
            {
                g_IR_data_4bits = g_IR_data_4bits<<1 ;
            }
        }

        if (i == 3)
        {
            char byte = 0 ;
            dec_to_hex(g_IR_data_4bits, &byte );
            g_IR_data_4bits = 0;

            g_IR_data_8hexs[g_IR_possition_hex] = byte;
            g_IR_possition_hex++;
            if (g_IR_possition_hex == 8)
            {
               USART_Transmits(g_IR_data_8hexs,8);
			   Light_parse_command(g_IR_data_8hexs,8);
            }
        }
		
		
        g_IR_State = IR_BIT_MARK;
        g_IR_stop ++;
		
        break;
    }
    default:
	{
        break;
	}
	
    }//End switch()
   
}//End function()

void Timer2_init()
{
    /*
    * The OC2A value will not be visible on the port pin unless the data direction for
    * the pin is set to output
    */
    //PORTB |= (1<<PORTB3);
    DDRB  |= (1<<DDB3);

    /*
    *F_OCnx = [f_clk_I/O]/[2*N*( OCRnx +1)]
    *F_OCnx = 38000Hz
    *f_clk_I/O = 16000000
    *2*N*( OCRnx +1) = 2.1*(210)
    *N = 1 -> ( OCRnx +1)  =  (OCRnx =210) +1;
    *The N variable represents the prescale factor (1, 8, 32, 64, 128, 256, or 1024).
    *  16000000/(2*8*26) = 38461
    */

    /*
    *WGM21 : Set to CTC Mode
    */
    TCCR2A |=  (1<<COM2A0)|(1<<WGM21);

    /*
    * Prescaler N =1 and starts PWM
    *
    */
    //TCCR2B =(1<<CS20);

    /*Top = OCR0A */
    TCNT2=0x00;

    /*
    *Set Compare Value
    * 8/(16000000) = 0.0000005
    * Timer =  0.0000005*26  = 0.000013s
    */
    unsigned  int   iTemp  = 16000000L/(g_ir_formal.carrier_frequency*2);
    OCR2A =( unsigned char ) iTemp  -1;
    /*
    *OCIE2A Timer/Counter0 Output Compare Match A Interrupt Enable
    */

    /*
    TIMSK2 |= (1 << OCIE2A);

    sei();*/
}

void Timer2_CTC_start()
{
    /*
    *Prescaler N = 1 and start PWM
    */
    TCCR2B |= (1<<CS20);

    /*wait for registers update*/
    while (ASSR & ((1<<TCN2UB)|(1<<TCR2BUB)));
}

void Timer2_CTC_stop()
{

    /*No clock source (Timer/Counter stopped)*/

    /*
    * Prescaler N = 1 and Stop PWM
    *
    */
    TCCR2B &= ~((1<<CS20)|(1<<CS21)|(1<<CS22));

    /*wait for registers update*/
    while (ASSR & ((1<<TCN2UB)|(1<<TCR2BUB)));

}

ISR(TIMER2_COMPA_vect)
{
}

void INT1_init()
{
    /*
    * PD3 - Pin D3
    *Any logical change on INT1 generates an interrupt request.
    */
     EICRA  |=(1<<ISC10) ;

    /* External Interrupt Request 0 Enable*/
    EIMSK  |=(1<<INT1);

    /*Turn on interrupts*/
    sei();
}

ISR(INT1_vect)
{
}

void sleepMicroSeconds(unsigned int microseconds)
{
    if (microseconds < 1)
    {
        return;
    }
	
    g_sleep_microSeconds = 0;
    while (g_sleep_microSeconds <= microseconds);

}

void Timer2_mark(unsigned int microseconds)
{
    Timer2_CTC_start();
    sleepMicroSeconds(microseconds);
}

void Timer2_space(unsigned int microseconds)
{
    Timer2_CTC_stop();
    sleepMicroSeconds(microseconds);
}

void IR_init()
{
    unsigned char readByte = eeprom_read_byte(( uint8_t *) IR_CONFIGURATION_ADD_FIRST_TIME);
	
    if (readByte != IR_DEFAULT_FIRST_TIME )
    {
		/*Store default ->Remote control: BN59-01003A  48khz SAMSUNG TV */
        eeprom_update_word(( uint16_t *) IR_CONFIGURATION_ADD_CARRIER_FREQUENCY, IR_DEFAULT_CARRIER_FREQUENCY);
        eeprom_update_word(( uint16_t *) IR_CONFIGURATION_ADD_START_COMMAND, IR_DEFAULT_START_COMMAND);
        eeprom_update_word(( uint16_t *) IR_CONFIGURATION_ADD_START_MARK, IR_DEFAULT_START_MARK);
        eeprom_update_word(( uint16_t *) IR_CONFIGURATION_ADD_START_SPACE, IR_DEFAULT_START_SPACE);
        eeprom_update_word(( uint16_t *) IR_CONFIGURATION_ADD_BIT_MARK, IR_DEFAULT_BIT_MARK);
        eeprom_update_word(( uint16_t *) IR_CONFIGURATION_ADD_BIT_ONE_SPACE, IR_DEFAULT_BIT_ONE_SPACE);
        eeprom_update_word(( uint16_t *) IR_CONFIGURATION_ADD_BIT_ZERO_SPACE, IR_DEFAULT_BIT_ZERO_SPACE);
        eeprom_update_word(( uint16_t *) IR_CONFIGURATION_ADD_LENGTH, IR_DEFAULT_LENGTH);
        eeprom_update_word(( uint16_t *) IR_CONFIGURATION_ADD_INTERVAL, IR_DEFAULT_INTERVAL);
    }
	
    eeprom_update_byte(( uint8_t *) IR_CONFIGURATION_ADD_FIRST_TIME,IR_DEFAULT_FIRST_TIME);
     
	/*Read configuration*/
    g_ir_formal.carrier_frequency   = eeprom_read_word (( uint16_t *) IR_CONFIGURATION_ADD_CARRIER_FREQUENCY);
    g_ir_formal.time_start_command  = eeprom_read_word (( uint16_t *) IR_CONFIGURATION_ADD_START_COMMAND);
    g_ir_formal.time_start_mark     = eeprom_read_word (( uint16_t *) IR_CONFIGURATION_ADD_START_MARK);
    g_ir_formal.time_start_space    = eeprom_read_word (( uint16_t *) IR_CONFIGURATION_ADD_START_SPACE);
    g_ir_formal.time_bit_mark       = eeprom_read_word (( uint16_t *) IR_CONFIGURATION_ADD_BIT_MARK);
    g_ir_formal.time_one_bit_space  = eeprom_read_word (( uint16_t *) IR_CONFIGURATION_ADD_BIT_ONE_SPACE);
    g_ir_formal.time_zero_bit_space = eeprom_read_word (( uint16_t *) IR_CONFIGURATION_ADD_BIT_ZERO_SPACE);
    g_ir_formal.data_length         = eeprom_read_word (( uint16_t *) IR_CONFIGURATION_ADD_LENGTH);
    g_ir_formal.time_interval       = eeprom_read_word (( uint16_t *) IR_CONFIGURATION_ADD_INTERVAL);
}

void IR_send(unsigned char  *PtrCommand, unsigned int length)
{
    g_IR_Send_Index_Data = 0;
     
    /*Parse data */
    for (unsigned int i = 0; i< length ; i++)
    {
        char temp[5] = {};
        hex_to_binary(PtrCommand[i],temp);
        for (int j = 0 ; j<4; j++)
        {
            g_IR_Send_Arr_Data[g_IR_Send_Index_Data] = temp[j];
            g_IR_Send_Index_Data++;
        }
    }

    /*
    *Send data
    */
 
    /*Start bit*/
    Timer2_mark(g_ir_formal.time_start_mark);
    Timer2_space(g_ir_formal.time_start_space);

    /* 4 bytes*/
    for (unsigned int i = 0; i< g_ir_formal.data_length ; i++)
    {
        if (g_IR_Send_Arr_Data[i] == '1')
        {
             (g_ir_formal.time_bit_mark);
            Timer2_space(g_ir_formal.time_one_bit_space);
        }
        else
        {
            Timer2_mark(g_ir_formal.time_bit_mark);
            Timer2_space(g_ir_formal.time_zero_bit_space);
        }
    }

    /*End bit */
    Timer2_mark(g_ir_formal.time_bit_mark);
    Timer2_space(0);
}

void  IR_reset()
{
    g_IR_State = IR_START_COMMAND;
    g_IR_stop = 0;
    g_IR_possition_hex = 0;
}
