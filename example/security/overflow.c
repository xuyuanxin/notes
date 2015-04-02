#include <stdio.h>

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

	beg = &a+740;
	printf("stack--> esp:0x%x ebp:0x%x &a:0x%x\n",get_esp(),get_ebp(),&a);
	for(i = 0; i < 1024+64; i+=4)
	{
	    printf("\n0x%x: %08x %08x %08x %08x",(int)(beg-i),
			   *(beg-i),*(beg-i-1),*(beg-i-2),*(beg-i-3));
	}
}

void active (int idx,int value)
{   
    int flag=0x33334444;
    int a = 0;
	printf("active--> esp1:0x%x ebp1:0x%x &flag:0x%x\n",get_esp(),get_ebp(),&flag);
	
    printf("active--> ret:0x%x &a:0x%x 0x%x\n",*((int *)&a + 2),&a,&a+2);
	printf("active--> esp:0x%x \n",get_esp());
	*(&a+idx) = value;
    printf("active--> %d \n",a);
	
	printf("active--> esp2:0x%x ebp2:0x%x\n",get_esp(),get_ebp());
	dump_stack();
}

void deactive()
{
    printf("deactive--> haha\n");
}

int main(int argc,char *argv[]) 
{
    int flag=0x11112222;
    int idx,value;

	printf("main--> esp1:0x%x ebp1:0x%x &flag:0x%x\n",get_esp(),get_ebp(),&flag);
	
	if(argc != 3){
		printf("Usage: %s idx value\n",argv[0]);
		return -1;
	}

	idx = atoi(argv[1]);
	value = atoi(argv[2]);
	printf("main-->idx:%d value:0x%x\n",idx,value);	
	printf("main--> esp2:0x%x ebp2:0x%x\n",get_esp(),get_ebp());
    active(idx,value); 
    return 0; 
}

/*


*/
