*
/*
*http://www.learningaboutelectronics.com/…/AVR-blinking-LED-…
*https://electrosome.com/push-button-switch-atmega32-microc…/
*/
#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
DDRD= 0xFF; //Nakes PORTDas Output
for(int i= 0;i<10;i++)
{
PORTD = 0xFF; //Turns ON All LEDs
_delay_ms(1000); //1 second delay
PORTD= 0x00; //Turns OFF All LEDs
_delay_ms(1000); //1 second delay 
}

DDRC &= ~(1<<PC0);//Makes firs pin of PORTD as Input
// OR DDRD = 0x00; //Makes all pins of PORTD input

unsigned int count =0;
while(1) //infinite loop
{
_delay_ms(10); //1 second delay 
if(PINC& (1<<PC0) == 1) //If switch is pressed
{
//PORTD = 0xFF; //Turns ON All LEDs
PORTD = 0xFB; //Turns ON All LEDs
count = 1;
}
else
{
// PORTD= 0x00; //Turns OFF All LEDs
if( count >= 12000)
{
count == 0;
}
if(count == 0)
{
PORTD= 0x04; //Turns OFF All LEDs
}else
{
count++;
}
}

}
}