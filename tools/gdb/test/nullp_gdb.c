#include <stdio.h>

int null_test(void)
{
    int *null_pionter = NULL;

    *null_pionter = 0;
	
    return 0;
}

int main()
{
    int a = 0;

	a = null_test();

	return a;
}

