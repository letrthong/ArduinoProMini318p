/************************************************
*
*Creator : Thong LT
*Email   : letrthong@gmail.com
*Website : http://letrthong.blogspot.com
*
*************************************************/


#ifndef ZIGBEE_H_
#define ZIGBEE_H_

struct Zigbee_info
{
	unsigned char *PanId;
	unsigned char *ShortAddresss;
	unsigned char *MacAddress;
	unsigned char *PointType;
	unsigned char *RadioChanel;
	long lBaudRate;
}; 

extern struct Zigbee_info gZigbeeInfo;

void Zigbee_init();
void ZigBee_get_Config();

//return 0 is true 
int isConnected();
int isRouter();
int verifyPanID();
int verifyChannel11();
int setPandID();
int setChannnel11();
 
void RequestCommand(const char *ptrZchRequest, unsigned char **ptrResponse, unsigned int length,unsigned int *byte_read);
void Zigbee_receive_data();
#endif /* ZIGBEE_H_ */