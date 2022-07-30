#include <x86.h>

#define PIC_MASTER_REG 0x20
#define PIC_MASTER_IMR 0x21
#define PIC_SLAVE_REG 0xA0
#define PIC_SLAVE_IMR 0xA1

#define PIC_ICW_1 0x11

void pic_init(void) {
    // ICW #1
    out8(PIC_MASTER_REG, PIC_ICW_1);
    out8(PIC_SLAVE_REG, PIC_ICW_1);

    // ICW #2 
    out8(PIC_MASTER_IMR, 0x20); // remapping IRQ0-IRQ7 to start from 0x20, i.e 32'th ISR
    out8(PIC_SLAVE_IMR, 0x28); // remapping IRQ8-IRQ15 to start from 0x28, i.e 32'th ISR

    // ICW #3 - MASTER/SLAVE coordination
    out8(PIC_MASTER_IMR, 0x4);
    out8(PIC_SLAVE_IMR, 0x2);

    // ICW #4 - set 80x86 mode
    out8(PIC_MASTER_IMR, 0x01);
    out8(PIC_SLAVE_IMR, 0x01);

    out8(PIC_MASTER_IMR, 0x0);
    out8(PIC_SLAVE_IMR, 0x0);
}

void pic_disable(void) {
    out8(PIC_MASTER_IMR, 0xff);
    out8(PIC_SLAVE_IMR, 0xff);
}

void pic_send_EOI(uint32_t irq) {
    if (irq >= 40) out8(PIC_SLAVE_REG, 0x20);
    out8(PIC_MASTER_REG, 0x20);
}

static uint64_t timer_delta_time;
static uint16_t divisor;

/* PIT (i8253) registers */
#define I8253_CONTROL_REG 0x43
#define I8253_DATA_REG  0x40

#define INTERNAL_FREQ 1193182ULL
#define INTERNAL_FREQ_3X 3579546ULL

void pit_init(uint32_t frequency) {
    uint32_t count, remainder;

    /* figure out the correct divisor for the desired frequency */
    if (frequency <= 18) {
        count = 0xffff;
    } else if (frequency >= INTERNAL_FREQ) {
        count = 1;
    } else {
        count = INTERNAL_FREQ_3X / frequency;
        remainder = INTERNAL_FREQ_3X % frequency;

        if (remainder >= INTERNAL_FREQ_3X / 2) count++;

        count /= 3;
        remainder = count % 3;

        if (remainder >= 1) count++;
    }

    divisor = count & 0xffff;

    timer_delta_time = (3685982306ULL * count) >> 10;

    out8(I8253_CONTROL_REG, 0x34);
    out8(I8253_DATA_REG, divisor & 0xff); // LSB
    out8(I8253_DATA_REG, divisor >> 8); // MSB
}