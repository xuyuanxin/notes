/*-----------------------------------------------------------------------------------
                            ==== Quicksort ====
 ------------------------------------------------------------------------------------    
 Quicksort is a sorting algorithm whose worst-case running time is thet(n^2) on an i-
 nput array of n numbers. In spite of this slow worst-case running time, quicksort is 
 often the best practical choice for sorting because it is remarkably efficient on t-
 he average: its expected running time is thet(nlgn), and the constant factors hidden 
 in the thet(nlgn) notation are quite small . It also has the advantage of sorting in 
 place, and it works well even in virtual memory environments.

 Here is the three-step divide-and-conquer process for sorting a typical subarray   -
 A[p...r].
 Divide: Partition (rearrange) the array A[p...r] into two (possibly empty) subarrays 
 A[p ... q - 1] and A[q + 1 ... r] such that each element of A[p ... q - 1] is less -
 than or equal to A[q], which is, in turn, less than or equal to each element of    -
 A[q + 1 ... r]. Compute the index q as part of this partitioning procedure.
 Conquer: Sort the two subarrays A[p ... q -1] and A[q +1 ... r] by recursive calls -
 to quicksort.
 Combine: Since the subarrays are sorted in place, no work is needed to combine them: 
 the entire array A[p ... r] is now sorted.
 -----------------------------------------------------------------------------------*/

#include <stdio.h>
 
void array_show(int array[], int nums,int p)
{
    int i = 0;
	printf("\n%d: ",p);
	for(i = 0; i < nums; ++i)
		printf("%d ",array[i]);

	printf("\n");
}


/*-----------------------------------------------------------------------------------
 Partition (rearrange) the array A[p ... r] into two (possibly empty) subarrays 
 A[p ... q - 1] and A[q + 1 ... r] such that each element of A[p ... q - 1] is less -
 than or equal to A[q], which is, in turn, less than or equal to each element of    -
 A[q + 1 ... r]. Compute the index q as part of this partitioning procedure.
-----------------------------------------------------------------------------------*/
int partition(int array[],int first,int end)
{
  int pivot,s_i,j,temp;

  s_i = first - 1;
  pivot = array[end]; /*可以在数组中任选，选取的元素决定q的值*/

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
 @array: array[first] ~ array[end] 
 @first: 第一个元素索引   一般为零
 @end  : 最后一个元素索引 一般为数组元素个数减1
-----------------------------------------------------------------------------------*/
void sort_quick(int array[],int first,int end)
{
    int q;

    if(first < end)
    {
        q = partition(array,first,end);
		//array_show(array,10,q);
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
                   --------------------- for循环结束,注意此时j==6
 2 1 3 4 7 5 6 8   <---- j=7; s_i = 2->3 swap(a[7),a[3])，无条件交换，return 3;

 2 1 3   4   7 5 6 8   按照上面的方法分被划分这两个子数组

 2 1 3   ----> 
 
 7 5 6 8 ----> 
*/
