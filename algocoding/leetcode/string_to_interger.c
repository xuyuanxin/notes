#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int myAtoi(char *str) 
{
	int ret = 0;
    int digit,sign;

	if(NULL == str) return 0;
 
	while(isspace(*str)) str++;
	
	sign= (*str == '-') ? -1 : 1;
	 
	if (*str == '-' || *str == '+') {
		str++;
	}
	 
	while(isdigit(*str)) {
		digit = *str - '0';
	 
		if (INT_MAX / 10 >= ret) {
			ret *= 10;
		} else {
			return sign == -1 ? INT_MIN : INT_MAX;
		}
		 
		if (INT_MAX - digit >= ret) {
			ret += digit;
		} else {
			return sign == -1 ? INT_MIN : INT_MAX;
		}
		 
		str++;
	}
 
	return ret * sign;
}



/*---------------------------------------------------------------------------------*/
int atoi_test(char *str)
{
    printf("%s -> %d\n",str,myAtoi(str));
}

int main()
{
    printf("INT_MAX:%d INT_MIN:%d\n",INT_MAX,INT_MIN);
	atoi_test("1");
	atoi_test("  -123  asdfasdf1234");	
	return 0;
}
