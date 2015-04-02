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



/*
int f( int );
int (*pf)( int ) = &f;

The ampersand(&) in the initialization is optional, because the compiler always conv-
erts function names to function pointers wherever they are used. The ampersand does -
explicitly what the compiler would have done implicitly anyway.

int ans;
ans = f( 25 );
ans = (*pf)( 25 );
ans = pf( 25 );
ans = (*f)(25); // ok


The first statement simply calls the function f by name, though its evaluation is pr-
obably not what you expected . The function name f is first converted to a pointer to
the function ; the pointer specifies where the function is located. The function call
operator then invokes the function by executing the code beginning at this address.

The second statement applies indirection to pf, which converts the function pointer -
to a function name. This conversion is not really necessary, because the compiler co-
nverts it back to a pointer before applying the function call operator. Nevertheless, 
this statement has exactly the same effect as the first one.

The third statement has the same effect as the first two . Indirection is not needed, 
because the compiler wants a pointer to the function anyway. This example shows how -
function pointers are usually used.

http://www.cnblogs.com/CBDoctor/archive/2012/10/15/2725219.html
int f( int );
int (*pf)( int ) = &f;
1 其实，f的函数名与pf函数指针都是一样的，即都是函数指针。f函数名是一个函数指针常量，
  而pf是一个函数数指针变量，这是它们的关系。
2 但函数名调用如果都得如(*f)(10)；这样，那书写与读起来都是不方便和不习惯的。所以C语言
  的设计者们才会设计成又可允许f(10);这种形式地调用（这样方便多了并与数学中的函数形式一
  样，不是吗？）。
3 为统一起见，pf函数指针变量也可以pf(10)的形式来调用。
4 赋值时，即可fp=&f形式，也可fp=f。

*/

