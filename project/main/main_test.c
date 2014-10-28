#include<stdio.h>
#include"bst.h"

void system_info()
{
    int a = 0x11223344;
	char *b = NULL;
	b = (char *)&a;

	if(0x11 == *b)
		printf("\r\nendian big");
	else if(0x44 == *b)
		printf("\r\nendian small");
	else
		printf("\r\nendian unknow");
	
    printf("\r\nsizeof    :");	
    printf("\r\nvoid *    : %d",sizeof(void *));	
    printf("\r\nlong      : %d",sizeof(long));	
    printf("\r\nint       : %d",sizeof(int));
    printf("\r\nlong long : %d",sizeof(long long));
	
    printf("\r\n");	
}



int main()
{
	system_info();

    //tree_test();
	//queue_test();
	bst_test();
	//queue_test();
    return 0;
}
