#ifndef __SA_MEM_H__
#define __SA_MEM_H__


void* sa_malloc (uint32_t mid, size_t size);
void sa_mfree (uint32_t mid, void* ptr);

#endif

