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
#include "GeneralUtils.h"

void unsigned_int_to_string(unsigned char *pChr, const unsigned int number)
{
	unsigned int a ;
	unsigned int b; 
	a = number;
	
	while(a>0)
	{
		if (pChr == '\0')
		{
			break;
		}
		
		b = a%10;
		a = a/10;
		
		*pChr = b + '0';
		pChr++;
	}
}
