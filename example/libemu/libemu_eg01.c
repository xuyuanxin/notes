/*libemu test*/
#include <emu/emu.h>
#include <emu/emu_shellcode.h>
#include <emu/emu_memory.h>

struct emu *emu;

char shellcode[] =  
"\xbe\x1f\x5e\x89\x76\x09\x31\xc0\x88\x46\x08\x89\x46\x0d\xb0\x0b"  
"\x89\xf3\x8d\x4e\x09\x8d\x56\x0d\xcd\x80\x31\xdb\x89\xd8\x40\xcd"  
"\x80\xe8\xdc\xff\xff\xff\x2f\x62\x69\x6e\x2f\x6c\x73\x00\xc9\xc3"; 

int main()
{
    emu = emu_new();
    if ( emu_shellcode_test(emu, (uint8_t *)shellcode, 48) >= 0 ) {
        fprintf(stderr, "suspecting shellcode\n");
    }
    emu_free(emu);
    return 0;
}

/*-----------------------------------------------------------------------------------
----> setup
Building from a Tarball

Installing using stable releases.

tar xfz libemu-VERSION.tar.gz
cd libemu-VERSION
./configure --prefix=/opt/libemu
make install

----> Makefile
export LD_RUN_PATH=/opt/libemu/lib/libemu:$LD_RUN_PATH
#export LD_LIBRARY_PATH=/opt/libemu/lib/libemu:$LD_LIBRARY_PATH
IN_SELFDIR=/opt/libemu/include 
LIB_SELFDIR=/opt/libemu/lib/libemu

all:	
	gcc -I$(IN_SELFDIR) -L$(LIB_SELFDIR) libemu_eg01.c -lemu

-----------------------------------------------------------------------------------*/
