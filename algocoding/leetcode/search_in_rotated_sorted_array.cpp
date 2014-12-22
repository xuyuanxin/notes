/*******************************************************************************
                   Search in Rotated Sorted Array (Hard)
 *******************************************************************************
 Suppose a sorted array is rotated at some pivot unknown to you beforehand. 
 (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
 You are given a target value to search. If found in the array return its index, 
 otherwise return -1.

 You may assume no duplicate exists in the array.
 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 int search(int A[], int n, int target) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************
 ���м������ֿ�������һ����Խ��"��ת��",����һ��û��Խ��û�п�Խ"��ת��"����һ
 ��Ԫ�ذ������еģ�ʼ������һ����Ϊ����first last�����ݡ�

 �������Ӧ��Ĭ���Ǵ�С���������
 ******************************************************************************/

 class Solution {
public:

int search(int A[], int n, int target) 
{
    int first=0,last=n-1,mid;

	while (first <= last) 
	{
        mid = (first + last) / 2;
		
        if (A[mid] == target) return mid;

        if (A[first] < A[mid])
		{
            if (A[first] <= target && target < A[mid])
                last = mid-1;
            else
                first = mid + 1;
        }
		else
		{
            if (A[mid+1] <= target && target <= A[last])
                first = mid + 1;
            else
                last = mid-1;
        }

    }
	
    return -1;        
}

/* ����ʵ�� */
int search2(int A[], int n, int target) 
{
    int first = 0, last = n;

	while (first != last) 
	{
        const int mid = (first + last) / 2;
		
        if (A[mid] == target)
            return mid;

        if (A[first] <= A[mid]) 
		{
            if (A[first] <= target && target < A[mid])
                last = mid;
            else
                first = mid + 1;
        } 
		else 
		{
            if (A[mid] < target && target <= A[last-1])
                first = mid + 1;
            else
                last = mid;
        }
    }
    return -1;        
}




};
