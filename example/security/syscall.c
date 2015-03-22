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
