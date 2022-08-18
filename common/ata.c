#include "types.h"

// old code

#define ATA_BASE 0x1f0
void read_sector(unsigned int addr, unsigned int count, unsigned char *buffer) {
    // FIXME: assert count <= 255

    // TODO: wait for ready

    unsigned char data;
    // how many sector
    data = count;
    outb(ATA_BASE + 2, data);

    // set addr
    data = addr & 0xff;
    outb(ATA_BASE + 3, data);
    data = addr >> 8 & 0xff;
    outb(ATA_BASE + 4, data);
    data = addr >> 16 & 0xff;
    outb(ATA_BASE + 5, data);
    data = (addr >> 24 & 0x0f) | 0xe0;
    outb(ATA_BASE + 6, data);

    // read command
    data = 0x20;
    outb(ATA_BASE + 7, data);

    // pool
    data = inb(ATA_BASE + 7);
    while ((data & 0x88) != 0x08) {
        data = inb(ATA_BASE + 7);
    }

    // read data
    int loop = count * 512;
    unsigned short d;
    int p = 0;
    while (loop--) {
        d = inw(ATA_BASE);
        buffer[p] = d;
        p += 1;
    }
    // printf("\n");
}


char readDisk(char LBA) {
    char readBuf[511];
    outb(0x1F6, 0xE0 | ((LBA >> 24) & 0x0F));   // drive select
    outb(0x1F1, 0x00);                          // wait
    outb(0x1F2, 1);                             // Sector count
    outb(0x1F3, LBA);                           // send LBA
    outb(0x1F4, LBA >> 8);                      // ...
    outb(0x1F5, LBA >> 16);                     // ...
    outb(0x1F7, 0x20);                          // Send Command READ
    while (!(inb(0x1F7) & 8));
    for (int i = 0; i < 256; i++) {
        char val = inw(0x1F0);
        readBuf[i * 2] = val & 0xff;
        readBuf[i * 2 + 1] = val >> 8;
    }
    return readBuf;
}