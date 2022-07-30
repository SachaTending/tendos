#include "printf.h"

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

#include <string.h>

const char* reverse(const char* str, char* buffer, int len){
	int i;
	for (i = 0; i <= len; i++){
		buffer[i] = str[len - i];
	}
	buffer[i] = '\0';
	return buffer;
}

char toStringRes[128];

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