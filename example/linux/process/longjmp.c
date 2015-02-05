#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

static void f1(int, int, int, int);
static void f2(void);
static jmp_buf jmpbuffer;
static int globval;

/*-----------------------------------------------------------------------------------
Note that the optimizations don't affect the global, static, and volatile variables; 
their values after the @longjmp are the last values that they assumed. The setjmp(3)
manual page on one system states that variables stored in memory will have values a-
s of the time of the @longjmp, whereas variables in the CPU and floating-point regi-
sters are restored to their values when @setjmp was called. This is indeed what we -
see when we run the program . Without optimization, all five variables are stored in 
memory (the register hint is ignored for regival). When we enable optimization, both 
autoval and regival go into registers, even though the former wasn't declared regis-
ter, and the volatile variable stays in memory . The important thing to realize with 
this example  is that you must use the volatile attribute if you're writing portable 
code that uses nonlocal jumps. Anything else can change from one system to the next.

$gcc longjmp.c  <---- compile without any optimization
$./a.out
in f1():
globval = 95, autoval = 96, regival = 97, volaval = 98, statval = 99
after longjmp:
globval = 95, autoval = 96, regival = 97, volaval = 98, statval = 99

$gcc -O longjmp.c  <---- compile with full optimization
$./a.out
in f1():
globval = 95, autoval = 96, regival = 97, volaval = 98, statval = 99
after longjmp:
globval = 95, autoval = 2, regival = 3, volaval = 98, statval = 99
-----------------------------------------------------------------------------------*/
int longjmp_eg01(void)
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

/*-----------------------------------------------------------------------------------
 we call @setjmp, which records whatever information it needs to in the variable @jmpbuffer 
 and returns 0.
-----------------------------------------------------------------------------------*/    
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

/*-----------------------------------------------------------------------------------
 Calling @longjmp causes the @setjmp in @longjmp_eg01 to return, but this time it re-
 turns with a value of 1 ( the second argument for @longjmp ).

 after calling @longjmp, What are the states of the automatic variables and register 
 variables in the longjmp_eg01 function? When we return to @longjmp_eg01 as a result 
 of the @longjmp, do these variables have values corresponding to those when the @setjmp 
 was previously called (i.e., aretheir values rolled back), Unfortunately, the answer 
 is "It depends". Most implementations do not try to roll back these automatic varia-
 bles and register variables, but the standards say only that their values are indet-
 erminate. If you have  an automatic variable that you don't want rolled back, define 
 it with the volatile attribute . Variables that are declared as global or static are 
 left alone when @longjmp is executed.
-----------------------------------------------------------------------------------*/
static void f2(void)
{
    longjmp(jmpbuffer, 1);
}

int main()
{
    longjmp_eg01();
    return 0;
}


/*-----------------------------------------------------------------------------------
Potential Problem with Automatic Variables
    Having looked at the way stack frames are usually handled, it is worth looking at 
    a potential error  in dealing with automatic variables. The basic rule is that an 
    automatic variable can never be referenced after the function that declared it r-
    eturns. Numerous warnings about this can be found throughout the UNIX System man-
    uals.

    The problem is that when @open_data returns , the space it used on the stack will 
    be used by the stack frame for the next function that is called. But the standard
    I/O library will still be using that portion of memory for its stream buffer. Ch-
    aos is sure to result. To correct this problem, the array@ databuf needs to be a-
    llocated from global memory, either statically (static or extern ) or dynamically 
    (one of the alloc functions).
-----------------------------------------------------------------------------------*/
#if 0
#include <stdio.h>
FILE * open_data(void)
{
FILE *fp;
char databuf[1024]; /* setvbuf makes this the stdio buffer */
if ((fp = fopen("datafile", "r")) == NULL)
return(NULL);
if (setvbuf(fp, databuf, _IOLBF, BUFSIZ) != 0)
return(NULL);
return(fp); /* error */
} 
#endif

