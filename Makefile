LINKDIR = tmp/
LDOPTS = -Tlink.ld -build-id=none -b pei-i386
GCCOPTS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostdlib

build: clean compile link

clean:
	@echo Clearing...
	@del tmp\* /s /q

compile:
	@echo [AS] boot.o
	@nasm -f elf32 loader/loader.asm -o $(LINKDIR)boot.o
	@echo [CC] kernel.o
	@gcc $(GCCOPTS) -o $(LINKDIR)kernel.o kernel/main.c

link:
	@echo [LD] preelf.o
	@ld $(LINKDIR)boot.o $(LINKDIR)kernel.o $(LDOPTS) -o $(LINKDIR)preelf.o
	@echo [OBJCOPY] out.kern
	@objcopy -O elf32-i386 $(LINKDIR)preelf.o out.kern

run:
	@qemu-system-i386 -kernel out.kern