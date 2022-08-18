COMMON_OBJS = $(LINKDIR)pci.o $(LINKDIR)gdt.o $(LINKDIR)A20.o $(LINKDIR)ata.o $(LINKDIR)irq2.o $(LINKDIR)interrupts.o $(LINKDIR)timer.o $(LINKDIR)printf.o $(LINKDIR)irq.o $(LINKDIR)panic.o $(LINKDIR)inlineasm.o $(LINKDIR)screen.o $(LINKDIR)pic_and_pit.o

common_build:
	@echo Target: common
	@echo Common: [CC] gdt.o
	@gcc $(GCCOPTS) -o $(LINKDIR)gdt.o common/gdt.c
	@echo Common: [AS] A20.o
	@nasm -felf32 -o $(LINKDIR)A20.o common/A20.s
	@echo Common: [CC] printf.o
	@gcc $(GCCOPTS) -o $(LINKDIR)printf.o common/printf.c
	@echo Common: [CC] screen.o
	@gcc $(GCCOPTS) -o $(LINKDIR)screen.o common/screen.c
	@echo Common: [CC] pci.o
	@gcc $(GCCOPTS) -o $(LINKDIR)pci.o common/pci.c
	@echo Common: [CC] inlineasm.o
	@gcc $(GCCOPTS) -o $(LINKDIR)inlineasm.o common/inlineasm.c
	@echo Common: [CC] pic_and_pit.o
	@gcc $(GCCOPTS) -o $(LINKDIR)pic_and_pit.o common/pic_and_pit.c
	@echo Common: [CC] irq.o
	@gcc $(GCCOPTS) -o $(LINKDIR)irq.o common/irq.c
	@echo Common: [CC] panic.o
	@gcc $(GCCOPTS) -o $(LINKDIR)panic.o common/panic.c
	@echo Common: [CC] timer.o
	@gcc $(GCCOPTS) -o $(LINKDIR)timer.o common/timer.c
	@echo Common: [CC] irq2.o
	@gcc $(GCCOPTS) -o $(LINKDIR)irq2.o common/irq.cpp
	@echo Common: [CC] interrupts.o
	@nasm -felf32 -o $(LINKDIR)interrupts.o common/interrupts.s
	@echo Common: [CC] ata.o
	@gcc $(GCCOPTS) -o $(LINKDIR)ata.o common/ata.c
	@echo Common compilling done!