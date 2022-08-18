#include "printf.h"
#include "types.h"

void libc_init()
{
	printf("LIBC Minimal: LIBC Minimal version: 0.1 special for TendOS.\n");
}

int factorial(int n) {
	int f = 1;
	int i = 1;
	while (i <= n) {
		f = f * i;
		i++;
	}
	return f;	
}

// #include <string.h>

int strlen(char s[]) {
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}

int strcmp(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}

int strncmp ( const char * str1, const char * str2, unsigned int num )
{
for ( ; num > 0; str1++, str2++, --num)
{
if (*str1 != *str2)
return ((*(unsigned char *)str1 < *(unsigned char *)str2) ? -1 : +1);
		else if (*str1 == '\0')
			return 0;
	}
return 0;
}

void *memcpy(void *__restrict dst, const void *__restrict src, size_t count)
{
   char *__restrict s = (char *) src;
   char *__restrict d = (char *) dst;
   
   while (count-- > 0)
      *s++ = *d++;
      
   return dst;
}

char* strncpy ( char * dst, const char * src, unsigned int num )
{
	if (num != 0)
	{
		char *d = dst;
		const char *s = src;
		do
		{
		if ((*d++ = *s++) == 0)
			{
				while (--num) 
					*d++ = 0;
				break;
			}
		}
		while (--num);
	}
	return dst;
}

const char* reverse(const char* str, char* buffer, int len){
	int i;
	for (i = 0; i <= len; i++){
		buffer[i] = str[len - i];
	}
	buffer[i] = '\0';
	return buffer;
}

char toStringRes[128];

void* memset(void* dest, unsigned char val, int count){ 
	unsigned char* destC = (unsigned char*)dest;
	int i;
	for (i = 0; i < count; i++)
		destC[i] = val;
	return dest;
}

const char* toString(int n, int base) {

	char* buffer = toStringRes;
	
	int m = n;
	int i = 0;
    
    if(n < 0){                 // Negative integers
        m = -n;
    }
	
    while(m != 0){
		buffer[i] = (char)((m % base)+ (m % base > 9 ? 55 : 48));
		m = m / base;
		i++;
	}
    
    if(n < 0){
        buffer[i] = '-';
        i++;
    }
    
    if(n == 0){
        buffer[i] = '0';
        i++;
    }
	
	buffer[i] = '\0';
	char revBuf[128];
	//asm volatile("1: jmp 1b");
	return reverse(buffer, revBuf, i-1);
} 

int oct2bin(unsigned char *str, int size) {
    int n = 0;
    unsigned char *c = str;
    while (size-- > 0) {
        n *= 8;
        n += *c - '0';
        c++;
    }
    return n;
}

int hex2bin(unsigned char *str, int size) {
    int n = 0;
    unsigned char *c = str;
    while(size-- > 0) {
        n *= 16;
        if(n >= '0' && n <= '9') n += *c - '0';
        else if (n >= 'A' && n <= 'F') n += *c - 55;
        c++;
    }
    return n;
}