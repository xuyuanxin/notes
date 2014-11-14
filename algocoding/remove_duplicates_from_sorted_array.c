/*******************************************************************************
 Given a sorted array, remove the duplicates in place such that each element appear 
 only once and return the new length.

 Do not allocate extra space for another array, you must do this in place with 
 constant memory.

 For example,
 Given input array A = [1,1,2],

 Your function should return length = 2, and A is now [1,2].
 ******************************************************************************/

 int removeDuplicates(int A[], int n)
 {
     int i,nums=0;

	 if(0 == n)
	 	return 0;

	 for(i = 1; i < n; i++)
	 {
	     if(A[nums] != A[i])
	     {
	         nums++;
			 A[nums] = A[i];
	     }
	 }

	 return nums+1;
 }

 int main()
 {
     int i,nums = 0;
     int a[10] = {1,1,2};
     int b[10] = {1,1,1}; 
     int c[10] = {1}; 
     int d[10] = {1,2,3};
	 
	 nums = removeDuplicates(a,3);
     printf("\r\narray a nums:%d  ",nums);
	 for(i = 0; i < nums; ++i) printf("%d ",a[i]);

	 nums = removeDuplicates(b,3);
     printf("\r\narray b nums:%d  ",nums);
     for(i = 0; i < nums; ++i) printf("%d ",b[i]);
	 
	 nums = removeDuplicates(c,1);	 
     printf("\r\narray c nums:%d  ",nums);
	 for(i = 0; i < nums; ++i) printf("%d ",c[i]);

	 nums = removeDuplicates(d,3);
	 printf("\r\narray d nums:%d  ",nums);
	 for(i = 0; i < nums; ++i) printf("%d ",d[i]);

 }
 
