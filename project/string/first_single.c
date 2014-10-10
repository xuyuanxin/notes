#include<stdio.h>

/* 找出字符串中第一个不重复的字符
   string:全是小写*/
char first_single(char const *string)
{   
	unsigned int index = 0;
	unsigned int min = 0xffffffff;
	unsigned int array[26][2] = {0};
	char single_char = '\0';

	if('\0' == *string)
		return single_char;

	do
	{
	    array[*string - 'a'][0]++;
		array[*string - 'a'][1] = index++;
	}while(*string++ != '\0');

	for(index = 0; index < 26; index++)
	{
	    if(1 == array[index][0] && array[index][1] < min)
	    {
	        single_char = index + 'a';
			min = array[index][0];
	    }
	}

	return single_char;
}

int main()
{
    int i = 0;

	printf("\r\nTest[%d] First Single Char is:%c",i++,first_single("abcdefghijklmnopqrstuvwxyza"));
	printf("\r\nTest[%d] First Single Char is:%c",i++,first_single("abca"));
	printf("\r\nTest[%d] First Single Char is:%c",i++,first_single("ccdd"));
}


















