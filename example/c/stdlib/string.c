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

/*
string ",", tokens ","
no split

string ",,", tokens ","
no split

string "a,", tokens ","
split 0, "a"

string "a,a", tokens ","
split 0, "a"
split 1, "a"

string "a,,a", tokens ","
split 0, "a"
split 1, "a"

string "a,a,", tokens ","
split 0, "a"
split 1, "a"

string "a", tokens ","
split 0, "a"

string "", tokens ","
no split
*/
int __strtok_eg(char *str, char *tk)
{
  char *pch;
  int i = 0;
  printf ("string \"%s\", tokens \"%s\"\n",str,tk);
  pch = strtok(str,tk);
  while (pch != NULL)
  {
	printf ("split %d, \"%s\" \n", i++, pch);
	pch = strtok (NULL, tk);
  }

  if(0 == i)
  {
    printf("no split\n");
  }

  printf("\n");
  
  return 0;
}



int strtok_eg()
{
  char str1[] =",";  
  char str2[] =",,";
  char str3[] ="a,";
  char str4[] ="a,a";
  char str5[] ="a,,a"; 
  char str6[] ="a,a,";
  char str7[] ="a";
  char str8[] ="";

  char *tk = ",";

  __strtok_eg(str1,tk);
  __strtok_eg(str2,tk);  
  __strtok_eg(str3,tk); 
  __strtok_eg(str4,tk);
  __strtok_eg(str5,tk);
  __strtok_eg(str6,tk);
  __strtok_eg(str7,tk);
  __strtok_eg(str8,tk);

  return 0;
}


int main(void)
{
    //strtok_eg("a");
    //strtok_eg(",");
    //strtok_eg(",,");
    //strtok_eg(",a");
    strtok_eg();


}

