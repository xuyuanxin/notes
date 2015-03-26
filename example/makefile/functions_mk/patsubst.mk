#$(patsubst pattern,replacement,text)
#Replace words matching @pattern with @replacement in @text.

.PHONY: all
mixed=foo.c bar.c main.o
objects:=$(patsubst %.c,%.o,$(mixed))

all:
	@echo $(objects)

#$ make -f patsubst.mk all
#foo.o bar.o main.o
