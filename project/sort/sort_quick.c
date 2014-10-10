/*
       ==== 快速排序 ====
 1 复杂度 最坏运行时间: thet(n^2)  平均运行时间: thet(nlgn) 
*/

/*
  把array[first]~aray[end]分成两部分，array[first]~aray[q]和array[q+1]~aray[end]
  前一部分小于等于array[q]，后一部分大于array[q]
  其中q是返回值，它是根据一定的方法计算出来的。*/
int partition(int array[],int first,int end)
{
  int pivot,s_i,j,temp;

  s_i = first - 1;
  pivot = array[end];/*可以在数组中任选*/

  for(j = first; j < end; ++j)
  {
      if(array[j] <= pivot)
      {
          s_i++;
		  temp = array[j];
		  array[j] = array[s_i];
		  array[s_i] = temp;
      }
  }
  
  temp = array[end];
  array[end] = array[s_i+1];
  array[s_i+1] = temp;

  return (s_i + 1);
}

/* 
 @array: array[first] ~ array[end] 排序
 @first: 第一个元素索引   一般为零
 @end  : 最后一个元素索引 一般为数组元素个数减1
*/
void sort_quick(int array[],int first,int end)
{
    int q;
	
    if(first < end)
    {
        q = partition(array,first,end);
		sort_quick(array,first,q-1);
		sort_quick(array,q+1,end);
    }
}
