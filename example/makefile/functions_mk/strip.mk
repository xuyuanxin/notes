#$(strip string)
#Remove excess whitespace characters from string.

aa=foo.c    bar.c
bb:=$(strip $(aa))
all:
	@echo "aa=$(aa)"
	@echo "bb=$(bb)"
#$ make -f strip.mk all
#aa=foo.c    bar.c
#bb=foo.c bar.c
	