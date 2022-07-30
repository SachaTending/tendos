#include "printf.h"
#include "floppy.h"
#include "pci.h"
#include "plat.h"

extern void enable_A20();

#define SYSTEM_TICKS_PER_SEC 10

void init_base()
{
	printf("Init base: Initializating...\n");
	// PCIScan();
	// TODO: Write base init code
	// init_serial();
	// printf("Kernel: Enabling A20...\n");
	// enable_A20();
	detect_floppy();
	smbios_detect();
	libc_init();
	printf("Init base: The factorial of 10 is: ");
	printf(factorial(10));
	printf("\n");
	pit_init(SYSTEM_TICKS_PER_SEC);
    pic_init();
    init_serial();
    init_keyboard();
}