#include<stdio.h>

#define STACK_SIZE  50  /*Õ»µÄ´óÐ¡*/

int stack[STACK_SIZE];
int stack_top = -1;

int stack_empty()
{
    if(-1 == stack_top)
		return 1;

	return 0;
}

int stack_full()
{
    if(STACK_SIZE-1 == stack_top)
		return 1;

	return 0;
}

int stack_push(int value)
{
    if(stack_full())
    {
        printf("\r\npush error stack full");
		return 0;
    }

	stack_top++;

	stack[stack_top] = value;

	return 1;
}

int stack_pop()
{
    if(stack_empty())
    {        
        printf("\r\npop error stack empty");
	    return 0xffffffff;
    }

	return stack[stack_top--];
}


void stack_test01()
{
    int i;
	
    stack_push(1);
	i = stack_pop();

	printf("\r\ni=%d",i);

	printf("\r\nempty:%d full:%d",stack_empty(),stack_full());
}

void stack_test02()
{
    int i=0;
	
    stack_push(12);
	stack_push(13);
	stack_push(14);
	stack_push(15);
	stack_push(16);
	
	stack_push(17);

    while(!stack_empty())
    {
	    printf("\r\npop %d:%d",i++,stack_pop());
    }

    stack_pop();
    
	stack_push(17);
	
	stack_push(18);
	stack_push(19);
	i = 0;
	while(!stack_empty())
    {
	    printf("\r\npop %d:%d",i++,stack_pop());
    }
	printf("\r\nempty:%d full:%d",stack_empty(),stack_full());
}

int main_1()
{
    stack_test01();
	stack_test02();
}
