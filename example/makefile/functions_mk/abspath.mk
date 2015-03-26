#$(abspath names¡­)
#For each file name in names return an absolute name that does not contain any . or .. 
#components, nor any repeated path separators (/). Note that, in contrast to realpath 
#function, abspath does not resolve symlinks and does not require the file names to -
#refer to an existing file or directory. Use the wildcard function to test for exist-
#ence.

pathc=$(abspath /usr/../lib)
all:
	@echo $(pathc)

#root
#  lib
#  usr
#$ make -f abspath.mk all
#/lib
