#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

static void f1(int, int, int, int);
static void f2(void);
static jmp_buf jmpbuffer;
static int globval;

int main(void)
{
	int  autoval;
	register int regival;
	volatile int volaval;
	static int statval;
	
	globval = 1; 
	autoval = 2; 
	regival = 3; 
	volaval = 4; 
	statval = 5;
	
	if (setjmp(jmpbuffer) != 0) 
	{
	    printf("after longjmp:\n");
	    printf("globval = %d, autoval = %d, regival = %d,volaval = %d, statval = %d\n",
	           globval, autoval, regival, volaval, statval);
	    exit(0);
	}
	
	globval = 95; 
	autoval = 96; 
	regival = 97; 
	volaval = 98;
	statval = 99;
	
	f1(autoval, regival, volaval, statval); /* never returns */
	
	exit(0);
}

static void f1(int i, int j, int k, int l)
{
    printf("in f1():\n");
    printf("globval = %d, autoval = %d, regival = %d,volaval = %d, statval = %d\n",globval, i, j, k, l);
    f2();
}

static void f2(void)
{
    longjmp(jmpbuffer, 1);
}


/*
$gcc longjmp.c compile without any optimization
$./a.out
in f1():
globval = 95, autoval = 96, regival = 97, volaval = 98, statval = 99
after longjmp:
globval = 95, autoval = 96, regival = 97, volaval = 98, statval = 99

$gcc -O longjmp.c compile with full optimization
$./a.out
in f1():
globval = 95, autoval = 96, regival = 97, volaval = 98, statval = 99
after longjmp:
globval = 95, autoval = 2, regival = 3, volaval = 98, statval = 99

*/

/*
Note that the optimizations don't affect the global, static, and volatile variables; 
their values after the @longjmp are the last values that they assumed. The setjmp(3)
manual page on one system states that variables stored in memory will have values 
as of the time of the @longjmp,whereas variables in the CPU and floating-point 
registers are restored to their values when @setjmpwas called. This is indeed 
what we see when we run the program . Without optimization, all five variables 
are stored in memory (the register hint is ignored for regival). When we enable 
optimization,both autoval and regival go into registers, even though the former 
wasn't declared register,and the volatile variable stays in memory.The important 
thing to realize with this example is that you must use the volatile attribute 
if you're writing portable code that uses nonlocal jumps. Anything else can change 
from one system to the next.
*/

