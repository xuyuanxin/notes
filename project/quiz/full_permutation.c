/*
功能: 输出n个字符的全排列 例如
  输入: "abc" 
  输出: abc; acb; bac; bca; cab; cba;
  输入: "aab"
  输出: aab; aba; baa;

方法: 


公式:
  a1,a1,...a1, a2,a2,...a2,.......,an,an,...an
  其中，a1的个数为N1, a2的个数为N2,以此类推，总个数为M。
  则可以得到不重复的排列种类的数目,为(不知是否已有证明):
  M!/(N1!*N2!*...*Nn!)
*/

#include<stdio.h>
#include<string.h>

int count = 0;

static void permutation(char *string,int first,int end)
{
    int i,temp,j;
	
    if(first == end){
	    printf("\r\n%s        %d",string,++count);
		return;
    }

    for(i = first; i <= end; ++i){
        
        if((string[i] == string[first]) && (i != first))       /*相同的元素不交换*/
			continue;
      
		for(j = i+1; j <= end; ++j)                            /*a和b不同，如果有多个b，a只和最后一个b交换*/
		    if((string[i] == string[j]) && (i != first))
				break;

		if(j <= end)
			continue;
		
        temp = string[i];string[i] = string[first];string[first] = temp;
	    permutation(string,first+1,end);
        temp = string[i];string[i] = string[first];string[first] = temp;
    }
}


void full_permutation(char *string)
{
	if(NULL == string)
	{
		printf("\r\nIn Para Error");
		return;
	}

    permutation(string,0,strlen(string)-1);
}





/********************** 以下是测试函数 **********************/

int factorial(int n)
{
    if((1 == n) || (0 == n))
		return 1;

	return n*factorial(n-1);
}

int permutation_num(char *string)
{
    int num = 1;
	int i,len;
    int count[256] = {0};

	if(NULL == string || '\0' == *string)
		return;

	len = strlen(string);

    do
    {
        count[*string]++;
    }while(*string++ != '\0');

	for(i = 0; i < 256; ++i)
	{			
	    if(0 != count[i])
	        num = num*factorial(count[i]);
	}

	return factorial(len)/num;
}



int main(int argc,char **argv)
{
    if(NULL == argv[1])
    {
    	printf("\r\nIn Para Error %d",argc);
		return;
    }
	printf("\r\nTotal:%d",permutation_num(argv[1]));
	full_permutation(argv[1]);
}

