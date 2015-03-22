#include <stdio.h>

void return_input (void)
{ 
    char array[30]; 
    gets (array); 
    printf("%s\n", array); 
}

void showname()
{
    printf("hahaha\n");
}

int main() 
{
	int i=0;
	
	char stuffing[44];
	
	 
	
	for (i=0; i<=40; i+=4)
	
	*(long *) &stuffing[i] = 0x80484bb;
	
	puts(stuffing);

    return_input(); 
    return 0; 
}

