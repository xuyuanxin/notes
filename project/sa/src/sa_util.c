#include <assert.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <sys/stat.h>

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

/* todo */
void *sa_re_alloc(void *old, size_t new_size)
{
    void *new_mem = NULL;

	new_mem = malloc(new_size);
	if(NULL == new_mem)
		return NULL;

    return new_mem;
}

int mkdirs(const char *pPath)
{
    char tmpPath[128];
    int pos=0;
    const char* pCur = pPath;

    if(-1 != access(pPath,0)) 
	{
         return -1;
    }

    if(strlen(pPath) > 128) 
	{
        return -1;
    }

    memset(tmpPath,0,sizeof(tmpPath));
	
    while('\0' != *pCur++)
    {
        tmpPath[pos++] = *(pCur-1);

         if(*pCur=='/' || *pCur=='\0')
         {
             if(0!=access(tmpPath,0) && strlen(tmpPath)>0)
             {
                 if (-1 == mkdir(tmpPath,0777))
				 {
				     return -1;
				 }
             }
         }
    }

	return 0;
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

