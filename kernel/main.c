#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <printf.h>
#include "screen.h"
#include "types.h"
#include "pci.h"
#include "inlineasm.h"
#include "init_base.h"
#include "plat.h"
#include "userland.h"
#include "multiboot.h"

struct multiboot_info minfo;

#define SYSTEM_TICKS_PER_SEC 10

 //Play sound using built in speaker
 static void play_sound(uint32_t nFrequence) {
 	uint32_t Div;
 	uint8_t tmp;
 
        //Set the PIT to the desired frequency
 	Div = 1193180 / nFrequence;
 	outb(0x43, 0xb6);
 	outb(0x42, (uint8_t) (Div) );
 	outb(0x42, (uint8_t) (Div >> 8));
 
        //And play the sound using the PC speaker
 	tmp = inb(0x61);
  	if (tmp != (tmp | 3)) {
 		outb(0x61, tmp | 3);
 	}
 }
 
 //make it shutup
void nosound() {
 	uint8_t tmp = inb(0x61) & 0xFC;
 
 	outb(0x61, tmp);
 }
 
void timer_wait(int ticks)
{
	unsigned int timer_ticks;
    unsigned int eticks;
 
    eticks = timer_ticks + ticks;
    while(timer_ticks < eticks) 
    {
        // _asm__ __volatile__ ("sti;hlt;cli");
    }
}

 //Make a beep
 void beep() {
 	 play_sound(1000);
 	 // slepp(10);
 	 // nosound();
          //set_PIT_2(old_frequency);
 }

void kernel_main(void) 
{
	clear_screen();
    init_serial();
    SERIAL_SET_FLAG_READY_PRINTF();
	printf("--- tendos started ---\n");     
	// beep(); // beep working      
	printf("Intializating base kernel...\n");
    printf2("Kernel: Kernel command line: %s", minfo.cmdline);
	// printf((char *) minfo.cmdline);
	// printf("cmdline = %s\n", (char *) minfo.cmdline);
    // printf(MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME);
    printf("\n");
	init_base();
	userland_setup();
    printf(readDisk(0));
	go_to_userland();
	printf("--- end of tendos(wtf) ---");
}