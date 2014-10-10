/* 计数排序
   复杂度: thet(n)
   条件: n个输入元素的值都介于0到k之间。
   原理:对于一个输入元素x，确定出小于x的元素的个数，这样就可以把x直接放入最终的数组中。
 */

#include<stddef.h>
#include<stdlib.h>
#define CS_MAX 100 /*0 ~ 100*/

void sort_counting(int array[],int size)
{
    int i,value,location;
    int temp[CS_MAX+1] = {0};
	int *p = NULL;

	p = (int *)malloc(size*sizeof(int));

	for(i = 0; i < size; ++i)
	{
	    *(p+i) = array[i];
	    temp[array[i]]++;               /*此时temp[i]中存放的是i出现的次数*/
	}

	for(i = 1; i <= CS_MAX; ++i)
	{
	    temp[i] = temp[i] + temp[i-1];  /*此时temp[i]是小于等于i的元素的个数*/
	}

	for(i = 0; i < size; ++i)
	{
        value = *(p+i);
		location = temp[value]-1;
		temp[value]--;                  /*数组中重复的值要占据多个地方*/
		array[location] = value;
	}

	free(p);
}
