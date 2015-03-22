#include <stdio.h>

unsigned long get_esp(void) {
   __asm__("movl %esp,%eax");
}


void dump_stack()
{
    int *stacktop,*beg,i;
	int dumpsize = 4*20;

	stacktop = (int *)get_esp();
    beg = stacktop + dumpsize;
	
	for(i = 0; i < dumpsize/4+4*20; ++i)
	{
	    printf("\n0x%x: %x",(int)(beg-i),*(beg-i));
	}
}

int main()
{
	char *buff, *ptr=(char *)0x11223344,*ptr2;

	printf("\n&buff:0x%x buff:0x%x 0x%x",&buff,buff,ptr2);

	dump_stack();

	return 0;
}
