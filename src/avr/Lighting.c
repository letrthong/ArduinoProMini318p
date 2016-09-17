/************************************************
*
*Creator : Thong LT
*Email   : letrthong@gmail.com
*Website : http://letrthong.blogspot.com
*
*************************************************/

#include "GPIO.h"
#include "Lighting.h"
#include "Utils.h"

void Light_init()
{
	PinMode(PIN_A0,OUTPUT);
	PinMode(PIN_A1,OUTPUT);
	PinMode(PIN_A2,OUTPUT);
	PinMode(PIN_A3,OUTPUT);
	
	PinWrite(PIN_A0, LOW);
	PinWrite(PIN_A1, LOW);
	PinWrite(PIN_A2, LOW);
	PinWrite(PIN_A3, LOW);
}


void Light_parse_command(unsigned char *ptrCommand, unsigned int length)
{   
	if ( equal2strUnsignedChars(ptrCommand,(unsigned char *) TUNR_ON_PIN_A0, 8) == 0)
	{
		PinWrite(PIN_A0, HIGHT);
		
	}else  if (equal2strUnsignedChars(ptrCommand,(unsigned char *) TUNR_OFF_PIN_A0, 8) == 0)
	{
		PinWrite(PIN_A0, LOW);
		
	}else if (equal2strUnsignedChars(ptrCommand,(unsigned char *) TUNR_ON_PIN_A1, 8) == 0)
	{  
		PinWrite(PIN_A1, HIGHT);
		
	}else if (equal2strUnsignedChars(ptrCommand,(unsigned char *) TUNR_OFF_PIN_A1, 8) == 0)
	{
		PinWrite(PIN_A1, LOW);
		
	}else if (equal2strUnsignedChars(ptrCommand,(unsigned char *) TUNR_ON_PIN_A2, 8) == 0)
	{
		 PinWrite(PIN_A2, HIGHT);
		 
	}else if (equal2strUnsignedChars(ptrCommand,(unsigned char *) TUNR_OFF_PIN_A2, 8) == 0)
	{
		PinWrite(PIN_A2, LOW);
		
	}else if (equal2strUnsignedChars(ptrCommand,(unsigned char *) TUNR_ON_PIN_A3, 8) == 0)
	{
		PinWrite(PIN_A3, HIGHT);
		
	}else if (equal2strUnsignedChars(ptrCommand,(unsigned char *) TUNR_OFF_PIN_A3, 8) == 0)
	{
		PinWrite(PIN_A3, LOW);
		/*Remote SAMSUNG*/
	}else if (equal2strUnsignedChars(ptrCommand,(unsigned char *) TUNR_ON_PIN0_Test, 8) == 0)
	{
		PinWrite(PIN_A0, HIGHT);
		
    }else if (equal2strUnsignedChars(ptrCommand,(unsigned char *) TUNR_OFF_PIN0_Test, 8) == 0)
    {
	   PinWrite(PIN_A0, LOW);
	   
    }else if (equal2strUnsignedChars(ptrCommand,(unsigned char *) TUNR_ON_PIN1_Test, 8) == 0)
    {
		PinWrite(PIN_A1, HIGHT);
		
    }else  if (equal2strUnsignedChars(ptrCommand,(unsigned char *) TUNR_OFF_PIN1_Test, 8) == 0)
    {
		PinWrite(PIN_A1, LOW);
		
    }else if (equal2strUnsignedChars(ptrCommand,(unsigned char *) TUNR_ON_PIN2_Test, 8) == 0)
    {
		PinWrite(PIN_A2, HIGHT);
		
    }else if(equal2strUnsignedChars(ptrCommand,(unsigned char *) TUNR_OFF_PIN2_Test, 8) == 0)
	{
		PinWrite(PIN_A2, LOW);
		
	}else if (equal2strUnsignedChars(ptrCommand,(unsigned char *) TUNR_ON_PIN3_Test, 8) == 0)
	{
		PinWrite(PIN_A3, HIGHT);
		
	}else if (equal2strUnsignedChars(ptrCommand,(unsigned char *) TUNR_OFF_PIN3_Test, 8) == 0)
	{
		PinWrite(PIN_A3, LOW);
	}
}
