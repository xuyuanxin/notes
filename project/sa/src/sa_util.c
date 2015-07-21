#include <assert.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <malloc.h>
 
#define sizeMalloc(p) (*(((unsigned int *)p)-1) & ~(0x01|0x02))

int sa_rand32(int wait)
{ 
    int rfd = -1;
	int num = 0;
	
    if (1 == wait)
	{ 
        rfd = open("/dev/random", O_RDONLY);
	}
	else
	{
	    rfd = open("/dev/urandom", O_RDONLY);
	}

    (void)read(rfd, &num, 4); 
	
    return num; 
}

void *sa_re_alloc(void *old, size_t new_size)
{
    void *new_mem = NULL;

	new_mem = malloc(new_size);
	if(NULL == new_mem)
		return NULL;

    //memcpy
}


int main_t(void)
{
   int i=0;
   
   printf("rand num 0: %d\r\n",sa_rand32(0));
   printf("rand num 1: %d\r\n",sa_rand32(0));
   
   for(i = 0; i < 30; i++) 
   {
      void *p = malloc(i);
      printf("malloc %d-%d bytes!\n", i, sizeMalloc(p));
      free(p);
   }
   return 0;
}

