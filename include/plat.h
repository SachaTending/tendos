#ifndef PLAT_H
#define PLAT_H

#define IRQ_PIT 0
#define IRQ_PS2 1

#include "x86.h"

typedef void (*IRQHandler)(x86_iframe_t*);

void pic_init(void);
void pic_send_EOI(uint32_t);
void pic_disable(void);

void pit_init(uint32_t frequency);

void irq_register_handler(int irq, void (*handler)(x86_iframe_t*));
void irq_unregister_handler(int irq);

void handle_platform_irq(x86_iframe_t* frame);

void kernelpanic(char *message);

#define plat_reboot() out8(0x64, 0xFE)
#define plat_hide_cursor() out16(0x3D4,0x200A)

#endif