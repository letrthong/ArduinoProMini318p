/************************************************
*
*Creator : Thong LT
*Email   : letrthong@gmail.com
*Website : http://letrthong.blogspot.com
*
*************************************************/

#ifndef UTILS_H_
#define UTILS_H_

void swap_char( char *ptr1, char *ptr2);
void reverse_chars( char *ptr);

void hex_to_ascii(const char *hex, unsigned char *chr);
void hex_to_string(const char *hex, unsigned char *chr);
void hex_to_binary(const char hex, char *bin);
void hex_to_dec(const char *hex, unsigned int *dec);


void dec_to_hex(const unsigned char dec, char *hex);
void ascii_to_hex(const unsigned char *chr, char *hex);
void string_to_hex(const unsigned char *chr, unsigned int length, char *hex);

void ascii_to_binary(const unsigned char *chr, char *bin);
void binary_to_ascii(const char *bin, unsigned char *value);

//sum for the bytes
void check_sum(const unsigned char *ptr, unsigned int length, unsigned char *checksum);


int equal2strbytes(const  char *ptr1 ,const char *ptr2, unsigned int length);
int equal2strUnsignedChars(const unsigned char *ptr1 ,const unsigned char *ptr2, unsigned int length);
#endif /* UTILS_H_ */