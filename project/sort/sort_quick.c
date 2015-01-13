/************************************************************************************
                            ==== 快速排序 ====
*************************************************************************************    
 1 复杂度 最坏运行时间: thet(n^2)  平均运行时间: thet(nlgn) 
 2 Quicksort is a sorting algorithm whose worst-case running time is Θ(n^2) on an 
   input array of n numbers. In spite of this slow worst-case running time, quicksort 
   is often the best practical choice for sorting because it is remarkably efficient 
   on the average: its expected running time is Θ(n lg n), and the constant factors 
   hidden in the Θ(n lg n) notation are quite small. It also has the advantage of 
   sorting in place (see page 16), and it works well even in virtual memory environments.
************************************************************************************/

/*-----------------------------------------------------------------------------------
  把array[first]~aray[end]分成两部分，array[first]~aray[q]和array[q+1]~aray[end]
  前一部分小于等于array[q]，后一部分大于array[q]
  其中q是返回值，它是根据一定的方法计算出来的。
-----------------------------------------------------------------------------------*/
int partition(int array[],int first,int end)
{
  int pivot,s_i,j,temp;

  s_i = first - 1;
  pivot = array[end];/*可以在数组中任选，选取的元素决定q的值*/

  for(j = first; j < end; ++j){
      if(array[j] <= pivot){
          s_i++;
		  temp = array[j];
		  array[j] = array[s_i];
		  array[s_i] = temp;
      }
  }

  s_i++;
  temp = array[end];
  array[end] = array[s_i];
  array[s_i] = temp;

  return (s_i);
}

/*-----------------------------------------------------------------------------------
 @array: array[first] ~ array[end] 排序
 @first: 第一个元素索引   一般为零
 @end  : 最后一个元素索引 一般为数组元素个数减1
-----------------------------------------------------------------------------------*/
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

/*-----------------------------------------------------------------------------------
**                       sort_quick过程示例
**-----------------------------------------------------------------------------------
 0 1 2 3 4 5 6 7   <---- 索引
 ---------------
 2 8 7 1 3 5 6 4   <---- 初始，选取最后一个元素作为分界点,s_i = -1
 
 2 8 7 1 3 5 6 4   <---- j=0; s_i =-1->0 swap(a[0],a[0]) 
 2 8 7 1 3 5 6 4   <---- j=1; s_i = 0->0  
 2 8 7 1 3 5 6 4   <---- j=2; s_i = 0->0  
 2 1 7 8 3 5 6 4   <---- j=3; s_i = 0->1 swap(a[3],a[1])
 2 1 3 8 7 5 6 4   <---- j=4; s_i = 1->2 swap(a[4],a[2])
 2 1 3 8 7 5 6 4   <---- j=5; s_i = 2->2 
 2 1 3 8 7 5 6 4   <---- j=6; s_i = 2->2  
 2 1 3 4 7 5 6 8   <---- j=7; s_i = 2->3 swap(a[7),a[3])，无条件交换，return 3;

 2 1 3   4 7 5 6 8   按照上面的方法分被划分这两个子数组

 2 1 3  ----> 
 
*/
