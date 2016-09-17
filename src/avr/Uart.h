/************************************************
*
*Creator : Thong LT
*Email   : letrthong@gmail.com
*Website : http://letrthong.blogspot.com
*
*************************************************/

#ifndef UART_H_
#define UART_H_

void USART_Init(unsigned int ubrr);

int USART_Transmit(unsigned char data );
void USART_Transmits(unsigned char *ptr,unsigned int length);

int USART_Receive(unsigned char *data);
unsigned char* USART_Receives(unsigned int length, unsigned int *byte_read);

#endif /* UART_H_ */