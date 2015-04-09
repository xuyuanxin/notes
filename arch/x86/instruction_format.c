unsigned long assamble(void) {
   __asm__(
   "movl %esp,%eax\n\t"
   "movl %ebx,260(%ecx,%edx,2)\n\t"
   "movl %eax,0x20(%ebp)\n\t"
   "addl 260(%ecx,%edx,2),%eax\n\t"
   "addl 0x12345678(%ecx,%edx,2),%eax\n\t"
   "addl 0x1234(%ecx,%edx,2),%eax\n\t"
   "addl 0x12345678,%eax\n\t"
   "leal 9(%eax,%ecx,2), %edx");
   return 0;
}

int accum = 0;

int sum(int x, int y)
{
    int t = x + y;
    accum += t;
	accum += 0x11;
    return t;
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




  
03 84 51 78 56 34 12    add    0x12345678(%ecx,%edx,2),%eax
-------------------------------------------------------------------------------------
a) 03 /r    ADD r32, r/m32    Add r/m32 to r32.
   03 是Opcode
   
b) /r 表示存在ModR/M结构，查表 Table 2-2. 32-Bit Addressing Forms with the ModR/M Byte 
   10    000      100     84h  
   mod    10  : 间接寻址
   reg/op 000 : %eax
   r/m    100 : [--][--]+disp32  表示后面还有 SIB
   
c) 首先mod为10，寻址方式为  [scaled index] + disp32 + [EBP]
   01  010  001        52 
   Scale : 01 
   Index : 010 [EDX*2]
   Base  : 001 %ECX
   
d) disp32 因为b)中的mod为10
   
   
   
03 05 78 56 34 12       add    0x12345678,%eax  # %eax = %eax+0x12345678
-------------------------------------------------------------------------------------
a) 03 /r    ADD r32, r/m32    Add r/m32 to r32.
   03 是Opcode

b) /r 表示存在ModR/M结构，查表 Table 2-2. 32-Bit Addressing Forms with the ModR/M Byte 
   00 000 101     05h  
   mod    00  : 间接寻址
   reg/op 000 : %eax
   r/m    101 : disp32   denotes a 32-bit displacement that follows the ModR/M byte

c) 78 56 34 12   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
*/
