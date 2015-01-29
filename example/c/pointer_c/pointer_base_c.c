#include <stdio.h>

typedef void (*fp)(int); /* define a type(a pointer to function) */

fp func2 = NULL;       /* the same as func1 */
void (*func1)(int) = NULL; /* a pointer to function.*/
int flag = 0;

void (*farray2[10])(int);
fp farray1[10];

void info_show1(int flag1)
{
    printf("flag1 is %d\r\n",flag1);
}

void info_show2(int flag2)
{
    printf("flag2 is %d\r\n",flag2);
}

/*-----------------------------------------------------------------------------------
  @func_set() is a function.
  @func_set函数有两个入参，第一个是int型，第二个是函数指针(所指向的函数有一个int型入参
  ，这个函数的返回值为void)。
  @func_set返回值是一个函数指针(所指向的函数有一个int型入参，这个函数的返回值为void)。
-----------------------------------------------------------------------------------*/
void (*func_set(int signo,void (*func)(int)))(int)
{
    fp tmp = NULL;

	tmp = func1;

	func1 = func;
	func2 = func;
	flag  = signo;
	
	return tmp;
}

/* the same as func_set() */
fp func_set2(int signo,fp func)
{
    fp tmp = NULL;

	tmp = func1;

	func1 = func;
	func2 = func;
	flag  = signo;
	
	return tmp;    
}

void func_run(fp func)
{
    static int global_cnt = 0;
    printf("\r\n=================== func_run %d ===================\r\n",global_cnt++);
	
    printf("----> old func:\r\n");
	if(NULL == func){
		printf("func is null \r\n");  
	} else {
	    (*func)(flag);
	}	
    printf("----> current func:\r\n");
	if(NULL == func1){
		printf("func is null \r\n");  
	} else {
	    (*func1)(flag);
		func1(flag);
		(*func2)(flag);
	}		
}


void fp_array_test()
{
    printf("\r\n=================== function pointer array test =================== \r\n");
	
    farray1[0] = info_show1;
	(*farray1[0])(flag);
	
    farray1[1] = info_show2;	
	(*farray1[1])(flag);
	
    farray2[0] = info_show1;
	(*farray2[0])(flag);
	
    farray2[1] = info_show2;
	(*farray2[1])(flag);
}

int main()
{
	fp tmp = NULL;

    printf("func1:%p func2:%p\r\n",func1,func2);

	tmp = func_set(1,info_show1);
	func_run(tmp);

	tmp = func_set(2,info_show2);
	func_run(tmp);

	tmp = func_set(3,NULL);
	func_run(tmp);

	tmp = func_set2(1,info_show1);
	func_run(tmp);

	tmp = func_set2(2,info_show2);
	func_run(tmp);

	tmp = func_set2(3,NULL);
	func_run(tmp);

	fp_array_test();
	
    return 0;
}




