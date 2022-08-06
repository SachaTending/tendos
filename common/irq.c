#include <plat.h>

char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void kernelpanic(char *message);

void handle_exception(uint32_t vector) {
	kernelpanic(exception_messages[vector]);
}

void x86_exception_handler(x86_iframe_t* iframe) {
	if (iframe->vector <= 31) handle_exception(iframe->vector);
	else if (iframe->vector <= 47) handle_platform_irq(iframe);
	else handle_exception(16);
}

IRQHandler irq_routines[16];

void handle_platform_irq(x86_iframe_t* frame) {
	int irq = frame->vector - 32;
    IRQHandler handler = irq_routines[irq];

    if (handler != NULL) handler(frame);
    
    if (irq != IRQ_PIT) pic_send_EOI(irq);
}

void irq_register_handler(int irq, IRQHandler handler) {
	irq_routines[irq & 0b1111] = handler;
}

void irq_unregister_handler(int irq) {
    irq_routines[irq & 0b1111] = NULL;
}

void irq_wait(int n){
    while(!irq_routines[n]){};
    irq_routines[n] = 0;

}

void irq_remap(void)
{
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}

void irq0();
void irq1();
void irq2();
void irq3();
void irq4();
void irq5();
void irq6();
void irq7();
void irq8();
void irq9();
void irq10();
void irq11();
void irq12();
void irq13();
void irq14();
void irq15();

void irq_install()
{
    irq_remap();

    idt_set_gate(32, (unsigned)0, 0x08, 0x8E);
    idt_set_gate(33, (unsigned)1, 0x08, 0x8E);
    idt_set_gate(34, (unsigned)2, 0x08, 0x8E);
    idt_set_gate(35, (unsigned)3, 0x08, 0x8E);
    idt_set_gate(36, (unsigned)4, 0x08, 0x8E);
    idt_set_gate(37, (unsigned)5, 0x08, 0x8E);
    idt_set_gate(38, (unsigned)6, 0x08, 0x8E);
    idt_set_gate(39, (unsigned)7, 0x08, 0x8E);
    idt_set_gate(40, (unsigned)8, 0x08, 0x8E);
    idt_set_gate(41, (unsigned)9 , 0x08, 0x8E);
    idt_set_gate(42, (unsigned)10, 0x08, 0x8E);
    idt_set_gate(43, (unsigned)11, 0x08, 0x8E);
    idt_set_gate(44, (unsigned)12, 0x08, 0x8E);
    idt_set_gate(45, (unsigned)13, 0x08, 0x8E);
    idt_set_gate(46, (unsigned)14, 0x08, 0x8E);
    idt_set_gate(47, (unsigned)15, 0x08, 0x8E);

    for(int i = 0; i < 16; i++){
        irq_routines[i] = 0;
    }
}


// IDT Code starts
struct idt_entry			// IDT structure
{
	unsigned short base_lo;
	unsigned short sel;	
	unsigned char always0;	
	unsigned char flags;	
	unsigned short base_hi;
} __attribute__((packed));

struct idt_ptr				// IDT poiner
{
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));



struct idt_entry idt[256];
struct idt_ptr _idtp;

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
	
	idt[num].base_lo = (base & 0xFFFF);
	idt[num].base_hi = (base >> 16) & 0xFFFF;

	
	idt[num].sel = sel;
	idt[num].always0 = 0;
	idt[num].flags = flags;
}


void idt_install()
{
	
	_idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
	_idtp.base = (unsigned int)&idt;

	/* Clear out the entire IDT, initalizing it to zeros */
	memset2(&idt, 0, sizeof(struct idt_entry) * 256);

	/* Add any new ISRs to the IDT here using idt_set_gate */

	/* Points the processor's internal register to the new IDT */
	_idt_load();
}

void _irq_handler(char *r)
{


    outb(0x20, 0x20);
}