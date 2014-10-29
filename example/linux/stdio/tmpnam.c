#include<stdio.h>
#include<stdlib.h>

int main(void)
{
	char name[L_tmpnam], line[4096];
	FILE *fp;
	
	printf("%s\n", tmpnam(NULL)); /* first temp name */
	tmpnam(name); /* second temp name */
	printf("%s\n", name);
	
	if ((fp = tmpfile()) == NULL) /* create temp file */
	{
	    printf("tmpfile error");
		return 1;
	}
	
	fputs("one line of output\n", fp); /* write to temp file */
	rewind(fp); /* then read it back */
	
	if (fgets(line, sizeof(line), fp) == NULL)
	{
	    printf("fgets error");
        return 1;
	}
	
	fputs(line, stdout); /* print the line we wrote */
	
	exit(0);
}

