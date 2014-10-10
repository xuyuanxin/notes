//#include "apue.h"
#include <fcntl.h>
#include <sys/mman.h>
#include<stdio.h>
#include<stdlib.h>
#define COPYINCR (1024*1024*1024) /* 1 GB */

int main(int argc, char *argv[])
{
	int  fdin, fdout;
	void  *src, *dst;
	size_t  copysz;
	struct stat sbuf;
	off_t  fsz=0;
	
	if (argc != 3)
	{
	    printf("usage: %s <fromfile> <tofile>", argv[0]);
		return 1;
	}
	
	if ((fdin = open(argv[1], O_RDONLY)) < 0)
	{
	    printf("can¡¯t open %s for reading", argv[1]);
		return 1;
	}
	
	if ((fdout = open(argv[2], O_RDWR | O_CREAT | O_TRUNC,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
	    printf("can¡¯t creat %s for writing", argv[2]);
	
	if (fstat(fdin, &sbuf) < 0) /* need size of input file */
	    printf("fstat error");
	
	if (ftruncate(fdout, sbuf.st_size) < 0) /* set output file size */
	    printf("ftruncate error");
	
	while (fsz < sbuf.st_size) 
	{
	    if ((sbuf.st_size - fsz) > COPYINCR)
	        copysz = COPYINCR;
	    else
	        copysz = sbuf.st_size - fsz;
		
	    if ((src = mmap(0, copysz, PROT_READ, MAP_SHARED,fdin, fsz)) == MAP_FAILED)
	        printf("mmap error for input");
		
	    if ((dst = mmap(0, copysz, PROT_READ | PROT_WRITE,MAP_SHARED, fdout, fsz)) == MAP_FAILED)
	        printf("mmap error for output");
		
	    memcpy(dst,src,copysz); /* does the file copy */
		
	    munmap(src, copysz);
	    munmap(dst, copysz);
	    fsz += copysz;
	}
	
	exit(0);
}

