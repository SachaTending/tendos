#include "printf.h"
#include "floppy.h"
#include "pci.h"
#include "plat.h"
#include "fat_filelib.h"

extern void enable_A20();

char read_sector(unsigned int addr, unsigned int count, unsigned char *buffer);
char write_sector(char *data)
{
	printf("writing not implemented\n");
}

#define SYSTEM_TICKS_PER_SEC 10

void init_base()
{
	printf("Init base: Initializating...\n");
	gdt_setup();
	idt_install();
	irq_install();
	PCIScan();
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
	// asm volatile ("sti");
	pit_init(SYSTEM_TICKS_PER_SEC);
    pic_init();
	// timer_phase(SYSTEM_TICKS_PER_SEC);
	// asm volatile ("sti");
	timer_install();
    init_keyboard();
    _irq_handler("амогус");
    // asm volatile ("hlt");
    // char data = read_sector(1, 1, 1);
    char data;
    //schar data2 = read_sector(1, 512, data);
    // printf(data2);
	// asm volatile ("hlt");
	printf("Init base: Initializating floppy driver...\n");
	floppy_init();
	// nosound();
	//fl_init();                                                            
	//if (fl_attach_media(read_sector, write_sector) != FAT_INIT_OK)
	{
	//	printf("Fat io lib cannot attach to ata hdd\n");
	}
}