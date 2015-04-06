#include <stdio.h>
#include <stdlib.h>

unsigned long get_esp(void) 
{
   __asm__("movl %esp,%eax");
}

unsigned long get_ebp(void) 
{
   __asm__("movl %ebp,%eax");
}

void dump_stack()
{
    int a = 0xaabbccdd;
	int i = 0;
	int *beg;

	beg = &a+128;
	printf("stack--> esp:0x%x ebp:0x%x &a:0x%x:%d &i:0x%x:%d &beg:0x%x 0x%x\n",
		   get_esp(),get_ebp(),&a,a,&i,i,&beg,beg);
	
	for(i = 0; i < 128+64; i+=4)
	{
	    printf("0x%x: %08x %08x %08x %08x\n",(int)(beg-i),
			   *(beg-i),*(beg-i-1),*(beg-i-2),*(beg-i-3));
	}
	
	printf("stack--> esp:0x%x ebp:0x%x &a:0x%x:%d &i:0x%x:%d\n",get_esp(),get_ebp(),&a,a,&i,i);
}

void active (int idx,int value)
{   
    int flag=0x33333333;
    int a = 0x44444444;
	
	printf("active--> esp1:0x%x ebp1:0x%x &flag:0x%x\n",get_esp(),get_ebp(),&flag);
	dump_stack();
    //fflush();
	*(&a+idx) = value;
}

int deactive()
{
    printf("deactive--> haha\n");
	exit(0);
}

int main(int argc,char *argv[]) 
{
    int flag1=0x11111111;
    int idx,value;
	int flag2=0x22222222;

	printf("main--> esp1:0x%x ebp1:0x%x &flag1:0x%x &flag2:0x%x\n",
		   get_esp(),get_ebp(),&flag1,&flag2);
	
	if(argc != 3){
		printf("Usage: %s idx value\n",argv[0]);
		return -1;
	}

	idx = atoi(argv[1]);
	value = atoi(argv[2]);
	printf("main--> idx:%d value:0x%x\n",idx,value);	
	printf("main--> esp2:0x%x ebp2:0x%x\n",get_esp(),get_ebp());
    active(idx,value); 
    return 0; 
}

/*


*/
