#include <stdio.h>

unsigned long get_esp(void) 
{
   __asm__("movl %esp,%eax");
}

void active (int idx,int value)
{   
    int flag=0x33334444;
    int a = 0;
    printf("active--> ret:0x%x &a:0x%x 0x%x\n",*((int *)&a + 2),&a,&a+2);
	printf("active--> esp:0x%x \n",get_esp());
	*(&a+idx) = value;
    printf("active--> %d \n",a);
}

void deactive()
{
    printf("deactive--> haha\n");
}

int main(int argc,char *argv[]) 
{
    int flag=0x11112222;
    int idx,value;

	printf("main--> esp1:0x%x \n",get_esp());
	
	if(argc != 3){
		printf("Usage: %s idx value\n",argv[0]);
		return -1;
	}

	idx = atoi(argv[1]);
	value = atoi(argv[2]);
	printf("main-->idx:%d value:0x%x\n",idx,value);	
	printf("main--> esp2:0x%x \n",get_esp());
    active(idx,value); 
    return 0; 
}

/*


*/
