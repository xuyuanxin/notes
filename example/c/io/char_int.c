/*
** Convert a series of digits from the standard input to an integer.
   ¡∑œ∞ π”√:getchar ungetc
*/

#include <stdio.h>
#include <ctype.h>

int read_int()
{
	int	value;
	int	ch;

	value = 0;
	
	while( ( ch = getchar() ) != EOF && isdigit( ch ) ){
		value *= 10;
		value += ch - '0';
	}
	ungetc( ch, stdin );/* Push back the nondigit so we don't lose it.*/
	return value;
}

int main(int argc,char **argv)
{
	int	value;
    int ch;

	value = read_int();
	ch = getchar();
	printf("\r\nvalue:%d ch:%c",value,ch);

	return 0;
}
