#include <stdio.h>
#include "foo.h"

void foo ()
{
    #ifdef Debug
    printf ("%s,This is foo ()! Debug\n",HELLO);
	#else
	printf ("%s,This is foo ()! Release\n",HELLO);
	#endif
}
