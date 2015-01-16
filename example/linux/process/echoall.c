#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;

int main1(void)
{   
	int i; 
    printf("hello pid=%d/n", getpid());    
   
    for (i=0; environ[i]!=NULL; ++i) {        
        printf("%s/n", environ[i]);    
    }    
    return 0;
}


int main(int argc, char *argv[])
{
    int i;
    char **ptr;
    for (i = 0; i < argc; i++) { /* echo all command-line args */
        printf("argv[%d]: %s\n", i, argv[i]);
    }
    for (ptr = environ; *ptr != 0; ptr++) { /* and all env strings */
        printf("%s\n", *ptr);
    }
    exit(0);
}
