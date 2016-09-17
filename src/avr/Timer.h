/************************************************
*
*Creator : Thong LT
*Email   : letrthong@gmail.com
*Website : http://letrthong.blogspot.com
*
*************************************************/


#ifndef TIMER_H_
#define TIMER_H_

void sleep(int second);

/*16 bits*/
void Timer1_init();
void Timer1_setTimeout(unsigned int i);
int  Timer1_check_timeout();
void Timer1_stop();
void sleep(int second);
unsigned int Timer1_read_ReadTCNT1();
#endif /* TIMER_H_ */