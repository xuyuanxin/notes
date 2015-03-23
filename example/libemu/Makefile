export LD_RUN_PATH=/opt/libemu/lib/libemu:$LD_RUN_PATH
#export LD_LIBRARY_PATH=/opt/libemu/lib/libemu:$LD_LIBRARY_PATH

IN_SELFDIR=/opt/libemu/include 
LIB_SELFDIR=/opt/libemu/lib/libemu

all:
	gcc -I$(IN_SELFDIR) -L$(LIB_SELFDIR) libemu_eg01.c -lemu
