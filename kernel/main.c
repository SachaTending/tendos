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
 static void nosound() {
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
        __asm__ __volatile__ ("sti;hlt;cli");
    }
}

 //Make a beep
 void beep() {
 	 play_sound(1000);
 	 timer_wait(10);
 	 nosound();
          //set_PIT_2(old_frequency);
 }

void kernel_main(void) 
{
	clear_screen();
	printf("--- tendos started ---\n");     
	// beep(); // beep not works, vm rebooting           
	printf("Intializating base kernel...\n");
	init_base();
	userland_setup();
	go_to_userland();
	printf("--- end of tendos(wtf) ---");
}