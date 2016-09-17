/************************************************
*
*Creator : Thong LT
*Email   : letrthong@gmail.com
*Website : http://letrthong.blogspot.com
*
*************************************************/
#define FOSC 16000000L/*Clock Speed - stands for 16MHz - VCC = 5V*/
#define BAUD 38400
#define MYUBRR FOSC/16/BAUD-1

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>

#include "Timer.h"
#include "GPIO.h"
#include "Uart.h"
#include "Utils.h"
#include "Zigbee.h"
#include "ADC.h"
#include "GeneralUtils.h"
#include "IRRemoteControl.h"
#include "Lighting.h"

struct Zigbee_info gZigbeeInfo;


void setup()
{
	Light_init();
	
	/*Atmega328 communication with ZIGBEE module*/
	USART_Init(MYUBRR);
	
	Zigbee_init();
	
	/*IR_init() has to call before IR starts */
	IR_init();
	
	/*Receiver IR*/
    Timer0_init();
	INT0_init();
	
	/*sleep()*/
	Timer1_init();
	
	/*SenderIR*/ 
	Timer2_init();
	/*Timer2 will start before INIT1 */
    INT1_init();
}

int main(void)
{ 
    setup();
    ZigBee_get_Config();
	
	 PinWrite(PIN_A0, LOW); 
     if( verifyPanID() ==  0)
     {
	     PinWrite(PIN_A0, HIGHT);
     }
    
	/*unsigned char key ;
	unsigned char key_power[] ="E0E040BF";
	unsigned char key_1[] = "E0E020DF";
	unsigned char key_2[] = "E0E0A05F";
	unsigned char key_3[] = "E0E0609F";
	unsigned char key_4[] = "E0E010EF";
	unsigned char key_5[] = "E0E0906F";
	unsigned char key_6[] = "E0E050AF";
	unsigned char key_7[] = "E0E030CF";
	unsigned char key_8[] = "E0E0B04F";
	unsigned char key_9[] = "E0E0708F";
	unsigned char key_0[] = "E0E08877";
	unsigned char key_led0[] ="A0A05F30";*/
	while(1)
	{ 
	    Zigbee_receive_data();
		 /*key ='B';   
		 USART_Receive(&key);
		 if (key =='p')
		 {
			  IR_send(key_power,8);
		 }else if (key =='1')
		{
		   IR_send(key_1,8);
	    }else if (key =='2')
	    {
		  IR_send(key_2,8);
	    }else if (key =='3')
	    {
			IR_send(key_3,8);
	    }else if (key =='4')
	    {
			IR_send(key_4,8);
	    }else if (key =='5')
	    {
			IR_send(key_5,8);
	    }else if (key =='6')
	    {
			IR_send(key_6,8);
	    }else if (key =='7')
	    {
			IR_send(key_7,8);
	    }else if (key =='8')
	    {
			IR_send(key_8,8);
	    }else if (key =='9')
	    {
			IR_send(key_9,8);
	    }else if (key =='0')
	    {
			IR_send(key_0,8);
	    }else if (key =='l')
	    {
			IR_send(key_led0,8);
	    }*/
	}
	
}//End main