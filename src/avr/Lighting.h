/************************************************
*
*Creator : Thong LT
*Email   : letrthong@gmail.com
*Website : http://letrthong.blogspot.com
*
*************************************************/

#ifndef LIGHTING_H_
#define LIGHTING_H_

#define  TUNR_ON_PIN_A0 "A0A05F30"
#define  TUNR_OFF_PIN_A0 "A0A0305F"

#define  TUNR_ON_PIN_A1 "A0A05CC6"
#define  TUNR_OFF_PIN_A1 "A0A0C65C"

#define  TUNR_ON_PIN_A2 "A0A07E96"
#define  TUNR_OFF_PIN_A2 "A0A0967E"

#define  TUNR_ON_PIN_A3 "A0A07E98"
#define  TUNR_OFF_PIN_A3 "A0A0987E"

/*Remote SAMSUNG BN59-01003A*/
#define  TUNR_ON_PIN0_Test "E0E020DF"  /*Key1*/
#define  TUNR_OFF_PIN0_Test "E0E0A05F" /*Key2*/

#define  TUNR_ON_PIN1_Test "E0E0609F"  /*Key3*/
#define  TUNR_OFF_PIN1_Test "E0E010EF" /*Key4*/

#define  TUNR_ON_PIN2_Test "E0E0906F"  /*Key5*/
#define  TUNR_OFF_PIN2_Test "E0E050AF" /*Key6*/

#define  TUNR_ON_PIN3_Test  "E0E030CF"  /*Key7*/
#define  TUNR_OFF_PIN3_Test "E0E0B04F" /*Key8*/

/*Using Pin A0, A1, A2, A3 are output  pin to control the lighting,fan,etc.*/
void Light_init();
void Light_parse_command(unsigned char *ptrCommand, unsigned int length);
#endif /* LIGHTING_H_ */