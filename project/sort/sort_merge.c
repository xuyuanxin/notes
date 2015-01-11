/**************************************************************************
 1 复杂度 nlgn  
 **************************************************************************/

#include <stdio.h>
#include <stdbool.h>

/*******************************************************************************  
  1 把已经排好序的array[first...middle]和array[middle+1 ... end]合并成一个有序数组
  2 first <= middle < end

  array[first...middle]称为左数组，array[middle+1 ... end]称为右数组。
  a 把左数组的元素拷贝到临时数组ArrayL，右数组拷贝到ArrayR。
  b 左右数组都是从小到大排好序的，怎么合并成一个有序数组呢，现在用扑克牌的例子说明:
    假设左右两个数组是两堆扑克牌，正面朝上且最小的在最上面。我始终拿取两堆中最小的
    那个，等我把牌起完最后我手里的牌就是从小到大排序的。

  代码中要注意:
  1 左右数组的元素个数也许不一样
  2 也许左堆的扑克牌一直是小牌，这样会一直从左堆取牌。
  3 也许右堆的牌已经取完，无需判断直接从左堆取牌。
 *******************************************************************************/
void merge(int array[],int first, int middle, int end)
{
    int IndexL,IndexR,i;
	bool EmptyFlagL,EmptyFlagR;
	int LengthL = middle - first + 1;
	int LengthR = end - middle;
    int ArrayL[LengthL],ArrayR[LengthR];

	for(i = 0; i < LengthL; i++)
	{
	    ArrayL[i] = array[first + i];
	}

	for(i = 0; i < LengthR; i++)
	{
	    ArrayR[i] = array[middle + 1 + i];
	}

	IndexL  = 0; IndexR  = 0; EmptyFlagL = false; EmptyFlagR = false;

    for(i = first; i <= end; i++)
    {
        if( ((ArrayL[IndexL] <= ArrayR[IndexR]) && !EmptyFlagL) || EmptyFlagR)
        {
			array[i] = ArrayL[IndexL];
		    IndexL++;
			
			if(LengthL == IndexL) 
				EmptyFlagL = true;
        }
		else
		{
			array[i] = ArrayR[IndexR];
		    IndexR++;
			
			if(LengthR == IndexR) 
				EmptyFlagR = true;
		}	
    }	
}

/*1 把数组array[first]到array[end]的元素从小到大排序
  2 end > first*/
void sort_merge(int array[], int first, int end)
{
    int middle;

    if(first < end)
    {
	    middle = (first + end)/2;
	
	    sort_merge(array,first,middle);
	    sort_merge(array,middle + 1 ,end);

	    merge(array,first,middle,end);
    }
}

#if 0
int main()
{
    int i;
    int array[8] = {8,1,5,7,4,2,3,9};

	//merge(array,0,3,7);
	sort_merge(array,0,7);

    for(i = 0; i < 8; i++)
	    printf("\r\narray[%d] = %d",i,array[i]);
}
#endif
