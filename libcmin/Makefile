LIBC_OBJS = $(LINKDIR)libcmin.o

.PHONY: libc
libc: libc.fatio
	@echo Target: libc
	@echo LIBC: [CC] libcmin.o
	@gcc $(GCCOPTS) -o $(LINKDIR)libcmin.o libcmin/libc_min.c
	@echo LIBC Minimal provider compiled!

include libcmin/fatiolib/Makefile