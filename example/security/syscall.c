#include <stdlib.h>

/*
 Compile this program using the static option with gcc, this prevents dynamic linkin-
 g, which will preserve our exit syscall. 

 gcc ¨Cstatic ¨Co exit exit.c 

*/
int main()
{
    exit(0);
}

/*-----------------------------------------------------------------------------------
 One way to manipulate the program is to force it to make a system call or syscall. -
 Syscalls are an extremely powerful set of functions that will allow you to access o-
 perating system-specific functions such as getting input, producing output , exiting 
 a process, and executing a binary file.

 There are two common methods of executing a syscall in Linux. You can use either the 
 C library wrapper, libc, which works indirectly,or execute the syscall directly with 
 assembly by loading the appropriate arguments into registers and then calling a sof-
 tware interrupt. 

 System calls in Linux are accomplished via software interrupts and are called with -
 the int 0x80 instruction. When int 0x80 is executed by a user mode program , the CPU 
 switches into kernel mode and executes the syscall function.Linux differs from other 
 Unix syscall calling methods in that it features a fastcall convention for system c-
 alls, which makes use of registers for higher performance. The process works as fol-
 lows:
 1 The specific syscall function is loaded into EAX. 
 2 Arguments to the syscall function are placed in other registers. 
 3 The instruction int 0x80 is executed. 
 4 The CPU switches to kernel mode. 
 5 The syscall function is executed.
 
 A specific integer value is associated with each syscall ; this value must be placed 
 into EAX. Each syscall can have a maximum of six arguments , which are inserted into 
 EBX, ECX, EDX, ESI, EDI, and EPB, respectively. If more than the stock six arguments 
 are required for the syscall, the arguments are passed via a data structure to the -
 first argument.
-----------------------------------------------------------------------------------*/
