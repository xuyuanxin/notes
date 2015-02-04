#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int  globvar = 6;
char  buf[]  = "a write to stdout\n";

/*-----------------------------------------------------------------------------------
 write:²»´ø»º³å
 printf:±ê×¼I/O¿â´ø»º³å£¬Èç¹û±ê×¼Êä³öÁ¬½Óµ½ÖÕ¶ËÉè±¸£¬ÔòËüÊÇÐÐ»º³åµÄ£¬·ñÔòËüÊÇÈ«»º³åµÄ¡£

 printf("before fork\n");
 1 Êä³öµ½ÖÕ¶ËÊ±(´ËÊ±printfÊÇÐÐ»º³åµÄ)
   µ÷ÓÃÇ°ÒÑ¾­Ë¢ÐÂ»º³åÇø£¬ËùÒÔ×Ó½ø³Ì²»»áÊä³ö"before fork"
 2 Êä³öµ½ÎÄ¼þ(´ËÊ±printfÊÇÈ«»º³åµÄ)
   ËäÈ»ÓÐ\n£¬ÓÉÓÚ´ËÊ±ÊÇÈ«»º³åµÄ£¬ËùÒÔ×Ó½ø³ÌÒ²»áÊä³ö¡£

output:
a write to stdout                                                                                                                   
print with newline                                                                                                                  
print no newline                                                                                                                    
child: pid: 2148 glob: 7 var: 89                                                                                                    
                                                                                                                                    
print no newline                                                                                                                    
parent: pid: 2147 glob: 6 var: 88


$ ./a.exe >out.txt
$ cat out.txt
a write to stdout                                                                                                                   
print with newline                                                                                                                  
print no newline                                                                                                                    
child: pid: 2198 glob: 7 var: 89                                                                                                    
                                                                                                                                    
print with newline                                                                                                                  
print no newline                                                                                                                    
parent: pid: 2197 glob: 6 var: 88

-----------------------------------------------------------------------------------*/
int fork_eg01(void)
{
    int  var; 
    pid_t  pid;
    var = 88;
	
    if (write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1) {
        printf("write error\n");
    }
	
    printf("print with newline\n");
    printf("print no newline"); 
	
    if ((pid = fork()) < 0) {
        printf("fork error \n");
		return 0;
    } else if (pid == 0) { /* child */
        printf("\n");
        globvar++;
        var++;
		printf("child: pid: %d glob: %d var: %d\n\n", (long)getpid(),globvar,var);
    } else {  /* parent */
        sleep(1);
		printf("\n");
        printf("parent: pid: %d glob: %d var: %d\n\n", (long)getpid(),globvar,var);
    }	
    exit(0);
}

int main()
{
    fork_eg01();
	return 0;
}
