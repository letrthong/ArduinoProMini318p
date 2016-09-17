/************************************************
*
*Creator : Thong LT
*Email   : letrthong@gmail.com
*Website : http://letrthong.blogspot.com
*
*************************************************/

#ifndef IR_REMOTE_DEF_H_
#define IR_REMOTE_DEF_H_

/*Remote control: BN59-01003A  48khz SAMSUNG TV */

#define IR_DEFAULT_CARRIER_FREQUENCY       38000
#define IR_DEFAULT_START_COMMAND            1000
#define IR_DEFAULT_START_MARK               460
#define IR_DEFAULT_START_SPACE              434
#define IR_DEFAULT_BIT_MARK                 67
#define IR_DEFAULT_BIT_ONE_SPACE            155
#define IR_DEFAULT_BIT_ZERO_SPACE           43
#define IR_DEFAULT_LENGTH                   32
#define IR_DEFAULT_INTERVAL                 10762
#define IR_DEFAULT_FIRST_TIME               1


#define IR_CONFIGURATION_CARRIER_FREQUENCY  0xF0
#define IR_CONFIGURATION_START_COMMAND      0xF1
#define IR_CONFIGURATION_START_MARK         0xF2
#define IR_CONFIGURATION_START_SPACE        0xF3
#define IR_CONFIGURATION_BIT_MARK           0xF4
#define IR_CONFIGURATION_BIT_ONE_SPACE      0xF5
#define IR_CONFIGURATION_BIT_ZERO_SPACE     0xF6
#define IR_CONFIGURATION_LENGTH             0xF7
#define IR_CONFIGURATION_INTERVAL           0xF8


#define IR_CONFIGURATION_ADD_CARRIER_FREQUENCY  0x000
#define IR_CONFIGURATION_ADD_START_COMMAND      0x002
#define IR_CONFIGURATION_ADD_START_MARK         0x004
#define IR_CONFIGURATION_ADD_START_SPACE        0x006
#define IR_CONFIGURATION_ADD_BIT_MARK           0x008
#define IR_CONFIGURATION_ADD_BIT_ONE_SPACE      0x00A
#define IR_CONFIGURATION_ADD_BIT_ZERO_SPACE     0x00C
#define IR_CONFIGURATION_ADD_LENGTH             0x00E
#define IR_CONFIGURATION_ADD_INTERVAL           0x010
#define IR_CONFIGURATION_ADD_FIRST_TIME         0x012

#define IR_START_COMMAND    0
#define IR_START_MARK	    1
#define IR_START_SPACE	    2
#define IR_BIT_MARK	        3
#define IR_BIT_SPACE	    4
#define IR_END              5

#define IR_TYPE_COMMNAD            0xF0
#define IR_TYPE_CONGIGURATION      0xF1
#define IR_TYPE_THE_LIGHTING       0xF2

/* Values for decode_type*/
typedef struct _IR_FORMAT
{
	unsigned long int  carrier_frequency;/*0kHz,33kHz,36kHz,38kHz,40kHz,etc*/
	unsigned int       time_start_command;
	unsigned int       time_start_mark;
	unsigned int       time_start_space;
	unsigned int       time_bit_mark;
	unsigned int       time_one_bit_space;
	unsigned int       time_zero_bit_space;
	unsigned int       data_length;
	unsigned int       time_interval;
	
}IR_FORMAT;

#endif /* IR_REMOTE_DEF_H_ */