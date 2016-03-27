#include <string.h>
#include <stdio.h>


int strchr_eg()
{
    char string[17];
    char *ptr;
    strcpy(string,"This^is^a^string");
    ptr=strchr(string,'^');
	
	printf("index:%d  %s----%s\n",ptr-string,string,ptr);
	ptr[0] = '\0';
	printf("len %d %s",strlen(string),string);
    return 0;	
}

int strtok_eg ()
{
  char str[] ="This^a#sample$string.";
  char * pch;
  printf ("Splitting string \"%s\" into tokens:\n",str);
  pch = strtok(str,"^#");
  while (pch != NULL)
  {
    printf ("%s <--> %s \n",pch,str);
    pch = strtok (NULL, "^#");
  }
  return 0;
}
int main(void)
{
    strtok_eg();
}

