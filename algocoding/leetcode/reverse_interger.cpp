
#include <iostream>	 
#include <string>
#include <algorithm>  /* reverse */
#include <stdlib.h>
#include <stdio.h>
using namespace std;


class Solution {
public:
int reverse(int x) 
{
	int sign = x > 0 ? 1 : -1;
	unsigned int tmp = (unsigned int)abs(x);
	unsigned long long result = 0;
          
    while (tmp) {  
        result = result*10 + tmp%10;
        tmp /= 10;  
    }
	if(result > 0xffffffff) return 0;
	if(-1 == sign && result>0x80000000) return 0;
	if(1 == sign && result>0x7fffffff) return 0;
	return (int)result*sign;	
}


};


/*---------------------------------------------------------------------------------*/

void reverse_interger_test(int a)
{
    Solution solu;
	printf("%d -> %d \n",a,solu.reverse(a));
}

int main()
{    
    int a;
	unsigned int b,c,d;	
	reverse_interger_test(0);
	reverse_interger_test(1);
	reverse_interger_test(-1);
	reverse_interger_test(100);
	reverse_interger_test(-100);
	reverse_interger_test(-123);
	reverse_interger_test(123);
	reverse_interger_test(1534236469);
	reverse_interger_test(-1563847412);
	
	
	reverse_interger_test(0x7fffffff);
	reverse_interger_test(-0x7fffffff);
	reverse_interger_test(-1463847418);

    a = -2;
	printf("%d\n",abs(a));

	if((unsigned int)abs(a)>(unsigned int)(1<<31)) printf("big\n");
	else printf("small\n");

    b = 1<<31;
	c = (unsigned int)1<<31;
	d = 0x80000000;
	printf("b:%u(0x%x) c:%u(0x%x) d:%u(0x%x) const:%d(0x%x) %u(0x%x) %u(0x%x)\n",
		   b,b,c,c,d,d,1<<31,1<<31,1<<31,1<<31,0x80000000,0x80000000);
	
	return 0;
}

