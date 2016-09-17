/************************************************
*
*Creator : Thong LT
*Email   : letrthong@gmail.com
*Website : http://letrthong.blogspot.com
*
*************************************************/


#ifndef IR_REMOTE_CONTROL_H_
#define IR_REMOTE_CONTROL_H_

#include "IRRemoteDef.h"

/*IR information */
extern IR_FORMAT g_ir_formal;

/*IR receiver*/
extern volatile unsigned int  g_IR_Time;
extern volatile unsigned char g_IR_State;
extern volatile unsigned char g_IR_Timeout;/*Two values : 0 or -1*/
extern volatile unsigned int  g_IR_stop;
extern volatile unsigned char g_IR_data_hex[8];

/*IR sender*/
extern volatile unsigned char g_IR_Send_Arr_Data[33] ;
extern volatile unsigned char g_IR_Send_Index_Data;
extern volatile unsigned char g_IR_Send_repeat;

/*Delay */
extern volatile unsigned int  g_sleep_microSeconds;

/*Receive IR data: Using PWM to create the IR signal*/
void INT0_init();//PD2 -D2
void Timer0_init();

/*Send IR data*/
void Timer2_init();
void Timer2_CTC_start();
void Timer2_CTC_stop();

void INT1_init();//PD3- D2

void sleepMicroSeconds(unsigned int microseconds);
void Timer2_mark(unsigned int microseconds);
void Timer2_space(unsigned int microseconds);

void IR_init();
/*Default 4 bytes*/
void IR_send(unsigned char *PtrCommand, unsigned int length);
void IR_reset();

#endif /* IR_REMOTE_CONTROL_H_ */