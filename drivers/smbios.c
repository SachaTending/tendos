#include "printf.h";

void smbios_detect()
{
    char *mem = (unsigned char *) 0xF0000;
    int length, i;
    unsigned char checksum;
    while ((unsigned int) mem < 0x100000) {
        if (mem[0] == '_' && mem[1] == 'S' && mem[2] == 'M' && mem[3] == '_') {
            length = mem[5];
            checksum = 0;
            for(i = 0; i < length; i++) {
                checksum += mem[i];
            }
            if(checksum == 0) {
                printf("SMBIOS: SMBIOS Detected!\n");
                break;
            }
        }
        mem += 16;
    }
    if ((unsigned int) mem == 0x100000) {
        printf("SMBIOS: No SMBIOS found!\nSMBIOS: SMBIOS Support disabled.\n");
    }
}