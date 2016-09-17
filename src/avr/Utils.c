/************************************************
*
*Creator : Thong LT
*Email   : letrthong@gmail.com
*Website : http://letrthong.blogspot.com
*
*************************************************/
#include <string.h>
#include <limits.h>
#include <stdio.h>

void swap_char(char *ptr1, char *ptr2)
{
	char temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
}

void reverse_chars( char *ptr)
{
	unsigned int first = 0;
	unsigned int last = 0;
	last = strlen(ptr);
	while(first < last)
	{
		if( ((ptr+ first) != '\0' )&& ((ptr+ last) != '\0' ) )
		{
			swap_char((ptr+ first), (ptr+ last));
			first++;
			last--;
		}
	}
}

void hex_to_binary(const char hex, char *bin)
{
	switch(hex)
	{
		case '0':
		strcpy(bin,"0000");
		break;
		case '1':
		strcpy(bin,"0001");
		break;
		case '2':
		strcpy(bin,"0010");
		break;
		case '3':
		strcpy(bin,"0011");
		break;
		case '4':
		strcpy(bin,"0100");
		break;
		case '5':
		strcpy(bin,"0101");
		break;
		case '6':
		strcpy(bin,"0110");
		break;
		case '7':
		strcpy(bin,"0111");
		break;
		case '8':
		strcpy(bin,"1000");
		break;
		case '9':
		strcpy(bin,"1001");
		break;
		case 'A':
		strcpy(bin,"1010");
		break;
		case 'B':
		strcpy(bin,"1011");
		break;
		case 'C':
		strcpy(bin,"1100");
		break;
		case 'D':
		strcpy(bin,"1101");
		break;
		case 'E':
		strcpy(bin,"1110");
		break;
		case 'F':
		strcpy(bin,"1111");
		break;
		case 'a':
		strcpy(bin,"1010");
		break;
		case 'b':
		strcpy(bin,"1011");
		break;
		case 'c':
		strcpy(bin,"1100");
		break;
		case 'd':
		strcpy(bin,"1101");
		break;
		case 'e':
		strcpy(bin,"1110");
		break;
		case 'f':
		strcpy(bin,"1111");
		break;
		default:
		break;
	}
}
void hex_to_dec(const char *hex ,unsigned int *dec)
{

	if( (*hex >= '0') &&( *hex <= '9') )
	{
		*dec = *hex - '0';
	}
	else
	{
		if( (*hex >= 'A') &&( *hex <= 'F') )
		{
			*dec =10 + (*hex - 'A');
		}
	}
}

void dec_to_hex(const unsigned char dec , char *hex)
{
	if(dec < 10)
	{
		*hex = dec + '0';
	}
	else
	{
		if(dec<16)
		{
			*hex = (dec%10)+ 'A';
		}
	}
}

void ascii_to_hex(const unsigned char *chr,char *hex)
{
	unsigned char firstHex =(*chr)>>4;
	unsigned char lastHex = ((*chr)<<4);
	lastHex =lastHex>>4;
	if( (hex != '\0') && (hex+1 != '\0') )
	{
		char hextemp;
		dec_to_hex(firstHex, &hextemp);
		*hex = hextemp;
		dec_to_hex(lastHex, &hextemp);
		*(hex+1) = hextemp;
	}
}

void string_to_hex(const unsigned char *chr, unsigned int length, char *hex)
{
	for(unsigned int i = 0; i< length; i++)
	{
		char buffer[3] = {0};
		ascii_to_hex(chr,buffer);

		*hex = buffer[0] ;
		hex++;
		*hex = buffer[1] ;
		hex++;

		chr++;
	}
}

void binary_to_ascii(const char *bin, unsigned char *value)
{
	int last =  strlen(bin);
	*value = 0;
	int tem  = SCHAR_MAX +1 ;//128
	for(  int i= 0 ; i< last; i++)
	{
		if( *(bin+i) == '1')
		{
			*value = *value + tem;
		}
		tem=tem>>1;
	}
}

void hex_to_ascii(const char *hex, unsigned char *chr)
{
	char binary[9] = {0};
	char firstbinary[5] = {0};
	char lastbinary[5] = {0};
	char firtHex;
	char lastHex;

	if ( (hex+0 == '\0') || (hex+1 == '\0'))
	{
		return;
	}

	firtHex = *(hex+0);
	lastHex = *(hex+1);

	hex_to_binary(firtHex,firstbinary );
	hex_to_binary(lastHex,lastbinary );

	sprintf(binary,"%s%s", firstbinary,lastbinary);
	binary_to_ascii(binary,chr);
}

void hex_to_string(const char *hex,unsigned char *chr)
{
	unsigned int ilen = strlen(hex);
	for (unsigned int i = 0 ; i < ilen ; i= i+2)
	{
		unsigned char buffer[3] = {0};
		unsigned char temp ;

		buffer[0] = hex[i];
		buffer[1] = hex[i+1];
		hex_to_ascii((const char *)buffer,&temp);
		if(chr != '\0')
		{
			*chr = temp;
			chr++;
		}
	}
}

void ascii_to_binary(const unsigned char  *chr, char *bin)
{
	while (*chr> 0)
	{
		break;
	}
}

void check_sum(const unsigned char *ptr,unsigned int length, unsigned char *checksum)
{
	*checksum = '\0';
	for (unsigned int i = 0; i< length ; i++)
	{
		*checksum =*checksum + ptr[i];
	}
}

int equal2strbytes(const  char *ptr1 ,const char *ptr2, unsigned int length)
{
	
	for (unsigned int i = 0; i< length; i++)
	{
		if(*ptr1  != *ptr2)
		{
			return -1;
		}
		ptr1++;
		ptr2++;
	}
	return 0;
}

int equal2strUnsignedChars(const unsigned char *ptr1 ,const unsigned char *ptr2, unsigned int length)
{
	for (unsigned int i = 0; i< length; i++)
	{
		if(*ptr1  != *ptr2)
		{
			return -1;
		}
		ptr1++;
		ptr2++;
	}
	return 0;
}