#include <stdio.h>

/*
 
$ ./a.exe
abc
input:{abc
}
char 0 is: 97
char 1 is: 98
char 2 is: 99
char 3 is: 10
\r 13 \n 10
*/
int fgets_eg()
{
    int i = 0;
    char mystring [512];
    char *pstr;

    pstr = fgets(mystring, 512, stdin);
    printf("input:{%s}\n",mystring);

	while('\0' != mystring[i])
	{
	    printf("char %d is: %d \n",i,mystring[i]);
		++i;
	}

	printf("\\r %d",'\r');
	printf("\\n %d",'\n');

	return 0;
}


int main()
{
    fgets_eg();

	return 0;
}
