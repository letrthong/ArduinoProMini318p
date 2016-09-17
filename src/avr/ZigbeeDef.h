/**********************************************************
*
*Creator  : Thong LT
*Email    : letrthong@gmail.com
*Website  : http://letrthong.blogspot.com
*
************************************************************/
#ifndef ZIGBEE_CONFIG_H
#define ZIGBEE_CONFIG_H

//It is hex format, we will add checksum

#define  ZIGBEE_READ_PAN_ID                "FC009103A3B3"
#define  ZIGBEE_WRITE_PAN_ID               "FC029101B1C3"      //reset
#define  ZIGBEE_RETURN_PAN_ID              "B1C3"

#define  ZIGBEE_READ_MAC_ADDRESS           "FC009108A8B8"
#define  ZIGBEE_READ_SHORT_ADDRESS         "FC009104C4D4"

//Module type
#define  ZIGBEE_SET_AS_COORDINATOR         "FC009109A9C9"       //reset
#define  ZIGBEE_RETURN_AS_COORDINATOR      "436F6F72643B0019"
#define  ZIGBEE_SET_AS_ROUTER              "FC00910ABADA"       //reset
#define  ZIGBEE_RETURN_AS_ROUTER           "526F7574653B0019"

#define  ZIGBBE_POINT_TYPE                 "FC00910BCBEB"
#define  ZIGBEE_RETURN_TYPE_COORDINATOR    "436F6F726469"
#define  ZIGBEE_RETURN_TYPE_ROUTER         "526F75746572"

#define  ZIGBEE_READ_CHANNEL                "FC00910D342B"
#define  ZIGBEE_CHANNEL_11                  "00000800520B"
#define  ZIGBEE_WRITE_CHANNEL               "FC01910C161A"
#define  ZIGBEE_RETURN_CHANNEL              "000800000B"

#endif
