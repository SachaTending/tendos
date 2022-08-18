MOBJS = $(LINKDIR)intr.o # metalkit compiled objects

.PHONY: metalkit
metalkit:
	@echo Target: metalkit
	@echo Metalkit taken from https://github.com/scanlime/metalkit
	@echo Metalkit: CC intr.c
	@gcc $(GCCOPTS) -o $(LINKDIR)intr.o metalkit/intr.c
	@echo Metalkit compilling done!