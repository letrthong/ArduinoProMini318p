/************************************************
*
*Creator : Thong LT
*Email   : letrthong@gmail.com
*Website : http://letrthong.blogspot.com
*
*************************************************/

#include <avr/eeprom.h>
#include <stdlib.h>

#include "Uart.h"
#include "Zigbee.h"
#include "ZigbeeDef.h"
#include "Utils.h"
#include "IRRemoteControl.h"
#include "Timer.h"
#include "GPIO.h"
#include "IRRemoteDef.h"

struct Zigbee_info gZigbeeInfo;

/*IR information */
IR_FORMAT g_ir_formal;


void Zigbee_init()
{
    gZigbeeInfo.PanId         = '\0';
    gZigbeeInfo.ShortAddresss = '\0';
    gZigbeeInfo.MacAddress    = '\0';
    gZigbeeInfo.PointType     = '\0';
    gZigbeeInfo.RadioChanel   = '\0';
}
void ZigBee_get_Config()
{
    unsigned int byte_read = 0;
    RequestCommand( ZIGBEE_READ_PAN_ID, &gZigbeeInfo.PanId, 2, &byte_read);
}

int isConnected()
{
    return 0;
}

int isRouter()
{
    return 0;
}

int verifyPanID()
{
    char hex[5] = {0};
    string_to_hex(gZigbeeInfo.PanId,2, hex);

    if (equal2strbytes(hex,ZIGBEE_RETURN_PAN_ID, 4) == 0)
    {
        return 0;
    }

    return -1;
}

int verifyChannel11()
{
    return 0;
}

int setPandID()
{
    return 0;
}

int setChannnel11()
{
    return 0;
}

void RequestCommand(const char *ptrZchRequest, unsigned char **ptrResponse, unsigned int length , unsigned int *byte_read)
{
    unsigned char command[8] = {0};
    unsigned char checksum;

    hex_to_string(ptrZchRequest,command);
    check_sum(command,6, &checksum);
    /*Add check sum */
    command[6] = checksum;
    /*make sure that the end of string*/
    command[7] = '\0';
    USART_Transmits(command,7);
    *ptrResponse = USART_Receives(length,byte_read);
}

void Zigbee_receive_data()
{
    /*Waiting new Data*/
    unsigned char  chr_pre_data ;

    int iRet = 0;

    /*
    * chr_pre_data  will receive data from  Zigbee module via UART protocol
    * if chr_pre_data = F -> remote control IR
    * if
    */
    while(1)
    {
        iRet = USART_Receive(&chr_pre_data);

        /*
        *start bit : 0XF0
        */
        if (iRet == 0 && chr_pre_data == 0xF0)
        {
            break;
        }
    }//End while()

    /*
    *get length of data 0XFF,etc.
    */
    iRet = USART_Receive(&chr_pre_data);
    if (iRet != 0)
    {
        return;
    }

    unsigned int length = chr_pre_data;
    unsigned int byte_read =0;
    unsigned char *ptr =  USART_Receives(length,&byte_read);

    if(*ptr == IR_TYPE_COMMNAD)
    {
        char *ptr_hexs = (char *)malloc( (length-1)*2+1);
        if (ptr_hexs == '\0')
        {
            return;
        }
        string_to_hex((ptr+1), (length-1),ptr_hexs);
        IR_send((unsigned char *) ptr_hexs,8);
        USART_Transmits("OK",2);
        /*Release memory*/
        free(ptr_hexs);
    }
    else if(*ptr == IR_TYPE_CONGIGURATION)
    {

        //F0 19 F1 F0 94 70 F1 03 E8 F2 01 BE F3 01 CE F4 00 37 F5 00 A6 F6 00 38 F7 00 20
        //      0 -1  2  3 -4  5  6 -7  8  9 -10 11 12-13 14 15-16 17 18-19 20 21-22 23 24
        unsigned int iValue = 0;

        if (*(ptr+1) == IR_CONFIGURATION_CARRIER_FREQUENCY)
        {
            iValue = 0;
            iValue = (unsigned int) *(ptr+2);
            iValue = iValue <<8;
            iValue = iValue  +  (unsigned int) *(ptr+3);
            eeprom_update_word(( uint16_t *) IR_CONFIGURATION_ADD_CARRIER_FREQUENCY, iValue);
            g_ir_formal.carrier_frequency = iValue;
        }

        if(*(ptr+4) == IR_CONFIGURATION_START_COMMAND)
        {
            iValue = 0;
            iValue = (unsigned int) *(ptr+5);
            iValue = iValue <<8;
            iValue = iValue  +  (unsigned int) *(ptr+6);
            eeprom_update_word(( uint16_t *) IR_CONFIGURATION_ADD_START_COMMAND, iValue);
            g_ir_formal.time_start_command = iValue;
        }

        if (*(ptr+7) == IR_CONFIGURATION_START_MARK)
        {
            iValue = 0;
            iValue = (unsigned int) *(ptr+8);
            iValue = iValue <<8;
            iValue = iValue  +  (unsigned int) *(ptr+9);
            eeprom_update_word(( uint16_t *) IR_CONFIGURATION_ADD_START_MARK, iValue);
            g_ir_formal.time_start_mark = iValue;
        }

        if (*(ptr+10) == IR_CONFIGURATION_START_SPACE)
        {
            iValue = 0;
            iValue = (unsigned int) *(ptr+11);
            iValue = iValue <<8;
            iValue = iValue  +  (unsigned int) *(ptr+12);
            eeprom_update_word(( uint16_t *) IR_CONFIGURATION_ADD_START_SPACE, iValue);
            g_ir_formal.time_start_space = iValue;
        }

        if (*(ptr+13) == IR_CONFIGURATION_BIT_MARK)
        {
            iValue = 0;
            iValue = (unsigned int) *(ptr+14);
            iValue = iValue <<8;
            iValue = iValue  +  (unsigned int) *(ptr+15);
            eeprom_update_word(( uint16_t *) IR_CONFIGURATION_ADD_BIT_MARK, iValue);
            g_ir_formal.time_bit_mark= iValue;
        }

        if (*(ptr+16) == IR_CONFIGURATION_BIT_ONE_SPACE)
        {
            iValue = 0;
            iValue = (unsigned int) *(ptr+17);
            iValue = iValue <<8;
            iValue = iValue  +  (unsigned int) *(ptr+18);
            eeprom_update_word(( uint16_t *) IR_CONFIGURATION_ADD_BIT_ONE_SPACE, iValue);
            g_ir_formal.time_one_bit_space= iValue;
        }

        if (*(ptr+19) == IR_CONFIGURATION_BIT_ZERO_SPACE)
        {
            iValue = 0;
            iValue = (unsigned int) *(ptr+20);
            iValue = iValue <<8;
            iValue = iValue  +  (unsigned int) *(ptr+21);
            eeprom_update_word(( uint16_t *) IR_CONFIGURATION_ADD_BIT_ZERO_SPACE, iValue);
            g_ir_formal.time_zero_bit_space= iValue;
        }

        if(*(ptr+22) == IR_CONFIGURATION_LENGTH)
        {
            iValue = 0;
            iValue = (unsigned int) *(ptr+23);
            iValue = iValue <<8;
            iValue = iValue  +  (unsigned int) *(ptr+24);
            eeprom_update_word(( uint16_t *) IR_CONFIGURATION_ADD_LENGTH, iValue);
            g_ir_formal.data_length=  iValue;
        }


        /*End configuration*/
    } else if (*ptr == IR_TYPE_THE_LIGHTING)
    {
        char *ptr_hexs = (char *)malloc( (length-1)*2+1);
        if (ptr_hexs == '\0')
        {
            return;
        }
        string_to_hex((ptr+1), (length-1),ptr_hexs);
        Light_parse_command((unsigned char *) ptr_hexs,8);
        USART_Transmits("OK",2);
        /*Release memory*/
        free(ptr_hexs);

    }

    /*Release memory*/
    if (ptr)
    {
        free(ptr);
        ptr = 0;
    }

}//End function
