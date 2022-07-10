LINKDIR = tmp/
LDOPTS = -Tlink.ld -build-id=none -m elf_i386
GCCOPTS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostdlib

build: clean compile link

clean:
	@echo Clearing...
	@rm tmp/*

compile:
	@echo [AS] boot.o
	@nasm -f elf32 loader/loader.asm -o $(LINKDIR)boot.o
	@echo [CC] kernel.o
	@gcc $(GCCOPTS) -o $(LINKDIR)kernel.o kernel/main.c

link:
	@echo [LD] out.kern
	@ld $(LINKDIR)boot.o $(LINKDIR)kernel.o $(LDOPTS) -o out.kern

run:
	@qemu-system-i386 -kernel out.kern
