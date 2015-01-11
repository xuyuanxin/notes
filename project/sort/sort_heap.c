/************************************************************************************
二叉堆: 是一种特殊的堆，二叉堆是"完全二叉树"或者是"近似完全二叉树"。
堆特性：父节点的键值总是保持固定的序关系于任何一个子节点的键值，且每个节点的左子树和右
        子树都是一个二叉堆。
最大堆: 当父节点的键值总是大于或等于任何一个子节点的键值时为最大堆。 
最小堆: 当父节点的键值总是小于或等于任何一个子节点的键值时为最小堆。

二叉堆一般用数组来表示。如果存储数组的下标基于0，那么下标为i的节点的子节点是2i + 1与
2i + 2；其父节点的下标是(i - 1)/2(取下整)。

如下图的两个堆：

			  1 			       11
			/	\			/	\
		   2	     3		   9       10
		  / \	/ \ 	        / \	 / \
		 4	 5	6  7	      5	 6	7	8
		/ \ / \ 		     / \ / \
	   8  9 10 11	        1  2 3  4 

将这两个堆保存在以0开始的数组中
位置:  0   1   2   3   4   5   6   7   8   9   10   11
左图:  1   2   3   4   5   6   7   8   9   10  11
右图:  11  9   10  5   6   7   8   1   2   3   4

 ==== 堆排序 ====
 1 复杂度 O(nlgn)
 2 原地排序算法
*/

/*
  @array: 数组首地址
  @i    : 数组元素索引，从0开始计数
  @max  : max小于等于数组的个数
  功能  : array[i]的左右子树都满足最大堆性质,调用此函数让以array[i]为根的树也满足最大堆性质*/
void adjust_heap(int array[], int i, int max)
{
    int left,right,largest,temp;

	left  = 2*i + 1;
	right = 2*i + 2;

	if(left < max && array[left] > array[i])
	{
	    largest = left;
	}
	else
	{
	    largest = i;
	}

	if(right < max && array[right] > array[largest])
	    largest = right;

	if(i != largest)
	{
	    temp = array[i];
		array[i] = array[largest];
		array[largest] = temp;

		adjust_heap(array,largest,max);
	}
}

/*@size: 数组元素的个数 大于等于2
  功能 : 建立最大堆
  实现 : */
void build_heap(int array[],int size)
{
    int i;

	for(i = size/2 - 1; i >= 0; --i)
		adjust_heap(array,i,size);
}

/*堆排序(从小到大)
  @size: 数组元素的个数 大于等于2
  方法 : 1 首先在整个数组上建立最大堆，此时最大的元素是array[0]。
         2 交换array[0]和array[size-1]的值。
         3 在array[0]到array[size-2]上建立最大堆，此时最大的元素是array[0]。
         4 交换array[0]和array[size-2]的值。
         5 在array[0]到array[size-3]上建立最大堆，此时最大的元素是array[0]。
         6 ...*/
void sort_heap(int array[],int size)
{
    int i,temp;
	
    build_heap(array,size); /*堆建立后树的根即array[0]是健值最大的节点。*/

	for(i = size - 1; i > 0; --i)
	{
	    temp = array[i];
		array[i] = array[0];
		array[0] = temp;

		adjust_heap(array,0,i);
	}
}

