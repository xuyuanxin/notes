
#if 0
unsigned long assamble(void) {
   __asm__(
   "movl %esp,%eax\n\t"
   "movl %ebx,260(%ecx,%edx,2)\n\t"
   "movl %eax,0x20(%ebp)\n\t"
   "addl 260(%ecx,%edx,2),%eax\n\t"
   "addl 0x12345678(%ecx,%edx,2),%eax\n\t"
   "addl 0x1234(%ecx,%edx,2),%eax\n\t"
   "addl 0x12345678,%eax\n\t"
   "addl %eax,1\n\t"
   "leal 9(%eax,%ecx,2), %edx");
   return 0;
}
#else
//".set noreorder\n\t"

unsigned long assamble(void) {
   __asm__(
   "add %eax,1\n\t"
   "add %eax,0x11223344\n\t"
   ".byte 0x83\n\t" // 0x83c001
   ".byte 0xc0\n\t"
   ".byte 0x01\n\t"
   //".word 0x100c\n\t"
   );
   return 0;
}

#endif

int accum = 0;

int sum(int x, int y)
{
    int t = x + y;
    accum += t;
	accum += 0x11;
    return t;
}

int main()
{
    return 0;
}

/*
gcc -O1 -S -masm=intel code.c

gcc -O1 -S instruction_format.c
gcc -O1 -c instruction_format.c
objdump -d instruction_format.o

00000000 <_assamble>:
   0:   55                      push   %ebp
   1:   89 e5                   mov    %esp,%ebp
   3:   89 e0                   mov    %esp,%eax
   5:   89 9c 51 04 01 00 00    mov    %ebx,0x104(%ecx,%edx,2)
   c:   89 45 20                mov    %eax,0x20(%ebp)
   f:   03 84 51 04 01 00 00    add    0x104(%ecx,%edx,2),%eax
  16:   03 84 51 78 56 34 12    add    0x12345678(%ecx,%edx,2),%eax
  1d:   03 05 78 56 34 12       add    0x12345678,%eax
  23:   8d 54 48 09             lea    0x9(%eax,%ecx,2),%edx
  27:   b8 00 00 00 00          mov    $0x0,%eax
  2c:   5d                      pop    %ebp
  2d:   c3                      ret




   
   
   
   
   
   
   
   
*/

