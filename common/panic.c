#include "printf.h"

void kernelpanic(char *message)
{
	printf("\nKernel: KERNEL PANIC!!!");
	printf("\nThere is a error in tendos kernel: ");
	printf(message);
	printf("\nPlease send error to https://github.com/SachaTending/tendos/issues and reboot the system");
	printf("\nKernel: system halted");
	asm volatile ("cli \n hlt"); //halt
}