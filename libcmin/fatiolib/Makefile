LIBC_OBJS +=  $(LINKDIR)fat_access.o $(LINKDIR)fat_cache.o $(LINKDIR)fat_filelib.o $(LINKDIR)fat_format.o $(LINKDIR)fat_misc.o $(LINKDIR)fat_string.o $(LINKDIR)fat_table.o $(LINKDIR)fat_write.o

libc.fatio:
	@echo Target: LIBCMin.fatiolib
	@echo LIBCMin.fatiolib: fat_access.o
	@gcc $(GCCOPTS) -o $(LINKDIR)fat_access.o libcmin/fatiolib/fat_access.c
	@echo LIBCMin.fatiolib: fat_cache.o
	@gcc $(GCCOPTS) -o $(LINKDIR)fat_cache.o libcmin/fatiolib/fat_cache.c
	@echo LIBCMin.fatiolib: fat_filelib.o
	@gcc $(GCCOPTS) -o $(LINKDIR)fat_filelib.o libcmin/fatiolib/fat_filelib.c
	@echo LIBCMin.fatiolib: fat_format.o
	@gcc $(GCCOPTS) -o $(LINKDIR)fat_format.o libcmin/fatiolib/fat_format.c
	@echo LIBCMin.fatiolib: fat_misc.o
	@gcc $(GCCOPTS) -o $(LINKDIR)fat_misc.o libcmin/fatiolib/fat_misc.c
	@echo LIBCMin.fatiolib: fat_string.o
	@gcc $(GCCOPTS) -o $(LINKDIR)fat_string.o libcmin/fatiolib/fat_string.c
	@echo LIBCMin.fatiolib: fat_table.o
	@gcc $(GCCOPTS) -o $(LINKDIR)fat_table.o libcmin/fatiolib/fat_table.c
	@echo LIBCMin.fatiolib: fat_write.o
	@gcc $(GCCOPTS) -o $(LINKDIR)fat_write.o libcmin/fatiolib/fat_write.c
	@echo LIBCMin.fatiolib compilling done!