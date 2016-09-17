/************************************************
*
*Creator : Thong LT
*Email   : letrthong@gmail.com
*Website : http://letrthong.blogspot.com
*
*************************************************/
#ifndef ADC_H_
#define ADC_H_

void ADC_init(unsigned char channel);
void ADC_start();
void ADC_stop();
void ADC_resume();
unsigned int ADC_read();

#endif /* ADC_H_ */