#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#include "sa_mid.h"

uint32_t mem_stat[MID_MAX];

void *sa_malloc (uint32_t mid, size_t size)
{
    void *mem;

	mem = malloc(size);

	if(NULL != mem)
	{
	    mem_stat[MID_ALL]++;
		mem_stat[mid]++;
	}

	return mem;
}


void sa_mfree (uint32_t mid, void* ptr)
{
    if(NULL == ptr)
		return;
	
    free(ptr);
	
	mem_stat[MID_ALL]++;
	mem_stat[mid]++;	
}

