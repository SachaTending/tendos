DRIVERS_OBJS = $(LINKDIR)floppy.o $(LINKDIR)keyboard.o $(LINKDIR)serial.o $(LINKDIR)smbios.o

include drivers/display/Makefile

driver: driver_display
	@echo Target: drivers
	@echo Drivers: [CC] smbios.o
	@gcc $(GCCOPTS) -o $(LINKDIR)smbios.o drivers/smbios.c
	@echo Drivers: [CC] serial.o
	@gcc $(GCCOPTS) -o $(LINKDIR)serial.o drivers/serial.c
	@echo Drivers: [CC] floppy.o
	@gcc $(GCCOPTS) -o $(LINKDIR)floppy.o drivers/floppy.c
	@echo Drivers: [CC] keyboard.o
	@gcc $(GCCOPTS) -o $(LINKDIR)keyboard.o drivers/keyboard.c
	@echo Drivers compilling done!