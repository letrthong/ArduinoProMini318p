/************************************************
*
*Creator : Thong LT
*Email   : letrthong@gmail.com
*Website : http://letrthong.blogspot.com
*
*************************************************/


#ifndef GPIO_H_
#define GPIO_H_

typedef enum  
{
	INPUT,
	OUTPUT
	}MODE;

typedef enum   
{
	LOW,
	HIGHT
	}VALUE;
	
typedef enum
{
	PIN_A0,
	PIN_A1,
    PIN_A2,
	PIN_A3,
	PIN_A6,
	PIN_A7,
    PIN_2,
    PIN_3,
	PIN_4,
	PIN_5,
	PIN_6,
	PIN_7,
	PIN_8,
	PIN_9,
	PIN_10,
	PIN_11,
	PIN_12,
	PIN_13,
	PIN_RXI,
	PIN_TXO
	}PIN;
	
void  PinMode(PIN pin, MODE mode);
void  PinWrite(PIN pin, VALUE value);
VALUE PinRead(PIN pin);

#endif /* GPIO_H_ */