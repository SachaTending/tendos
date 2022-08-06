LINKDIR = tmp/
LDOPTS = -Tlink.ld -build-id=none -b pei-i386
GCCOPTS = -std=gnu99 -ffreestanding -O2 -w -nostdlib -I include -g -fno-exceptions -c

build: 
	@make -j4 buildc
	@make link

include common/Makefile
include init/Makefile 
include drivers/Makefile
include user/Makefile
include libcmin/Makefile

buildc: libc compile common_build userland init_base driver

clean:
	@echo Clearing...
	@rm -rf tmp/*.o

clean_and_build:
	@echo Clearing...
	@del tmp\* /q
	@make -j4 buildc


compile:
	@echo Target: kernel
	@echo Kernel: [AS] boot.o
	@nasm -f elf32 loader/loader.asm -o $(LINKDIR)boot.o
	@echo Kernel: [CC] kernel.o
	@gcc $(GCCOPTS) -fno-builtins -o $(LINKDIR)kernel.o kernel/main.c
	@echo Kernel compilling done!

.c.o:
	@echo [CC] $@
	@gcc $(GCCOPTS) -o $@ -c

link:
	@echo [LD] preelf.o
	@ld $(LINKDIR)boot.o $(LINKDIR)kernel.o $(LIBC_OBJS) $(COMMON_OBJS) $(USER_OBJS) $(DRIVERS_OBJS) $(LINKDIR)init_base.o $(LDOPTS) -o $(LINKDIR)preelf.o
	@echo [OBJCOPY] out.kern
	@objcopy -O elf32-i386 $(LINKDIR)preelf.o out.kern

run:
	@qemu-system-i386 -kernel out.kern -m 2m -serial stdio -d guest_errors -d page -d cpu_reset -d strace -fda floppy.img


rungdb:
	@qemu-system-i386 -kernel out.kern -m 2m -serial stdio -d guest_errors -d page -d cpu_reset -d strace -s -S -fda floppy.img
