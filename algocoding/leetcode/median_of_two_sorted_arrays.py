#coding=utf-8
#####################################################################################
#解题思路：这道题要求两个已经排好序的数列的中位数。中位数的定义：如果数列有偶数个数，
#那么中位数为中间两个数的平均值；如果数列有奇数个数，那么中位数为中间的那个数。
#比如{1，2，3，4，5}的中位数为3。{1，2，3，4，5，6}的中位数为（3+4）/ 2 = 3.5。
#那么这题最直接的思路就是将两个数列合并在一起，然后排序，然后找到中位数就行了。可是这
#样最快也要O((m+n)log(m+n))的时间复杂度，而题目要求O(log(m+n))的时间复杂度。这道题其
#实考察的是二分查找，是《算法导论》的一道课后习题，难度还是比较大的。

#首先我们来看如何找到两个数列的第k小个数，即程序中getKth(A, B , k)函数的实现。用一个
#例子来说明这个问题：A = {1，3，5，7}；B = {2，4，6，8，9，10}；如果要求第7个小的数，
#A数列的元素个数为4，B数列的元素个数为6；k/2 = 7/2 = 3，而A中的第3个数A[2]=5；B中的
#第3个数B[2]=6；而A[2]<B[2]；则A[0]，A[1]，A[2]中必然不可能有第7个小的数。
#因为A[2]<B[2]，所以比A[2]小的数最多可能为A[0], A[1], B[0], B[1]这四个数，也就是说
#A[2]最多可能是第5个大的数，由于我们要求的是getKth(A, B, 7)；现在就变成了求
#getKth(A', B, 4)；即A' = {7}；B不变，求这两个数列的第4个小的数，因为A[0]，A[1]，A[2]
#中没有解，所以我们直接删掉它们就可以了。这个可以使用递归来实现。

#第k小：例如 (3 4 5) ，3是第1小，4是第2小，5是第3小。
#A B 是两个已经排序的数组，找到A和B中第k小的元素
#方法1：把这两个数组合并(merge)，根据索引就可以找到第k小元素
#方法2：逐半丢弃，类似二分查找
#为了方便假设A有m个元素，B有n个元素。m>k,n>k,k>2;
#把A和B都分成两份 A1=A[0,k/2), A2=A[k/2,m); B1=B[0,k/2), B2=B[k/2,n);
#如果A[k/2-1] < B[k/2-1]; 说明A1是这4份中最小的一份，第k小元素一定不在A1中，丢弃A1。
#在剩下的A2,B1,B2中找第k/2小元素。
#例如A=[1,3,5,7],B=[2,4,6,8],找A和B中第4小元素(4)
#A1=[1,3],A2=[5,7]; 4/2=2
#B1=[2,4],B2=[6,8];
#丢弃A1，在A2=[5,7];B=[2,4,6,8];中找第2小元素。
class Solution:
    # @return a float
    def getKth(self, A, B, k):
        lenA = len(A); lenB = len(B)
        if lenA > lenB:  #always assume that B is equal or smaller than A
            return self.getKth(B, A, k)
        if lenA == 0 and lenB == 0: return 0xffffffff
        if lenA == 0: return B[k - 1] # A smaller
        if k == 1: return min(A[0], B[0])
        pa = min(k/2, lenA); pb = k - pa #divide k into two parts  
        if A[pa - 1] <= B[pb - 1]:
            return self.getKth(A[pa:], B, pb)
        else:
            return self.getKth(A, B[pb:], pa)
    
    def findMedianSortedArrays(self, A, B):
        lenA = len(A); lenB = len(B)
        if (lenA + lenB) % 2 == 1: 
            return self.getKth(A, B, (lenA + lenB)/2 + 1)
        else:
            return (self.getKth(A, B, (lenA + lenB)/2) + self.getKth(A, B, (lenA + lenB)/2 + 1)) * 0.5

    #len(B)>=len(A)
    def getKth_v2(self, A, B, k):
        lenA = len(A); lenB = len(B)
        if lenA > lenB:  #always assume that B is equal or smaller than A
            return self.getKth_v2(B, A, k)
        if lenA == 0 and lenB == 0: return 0xffffffff #inpara error
        if lenA == 0: return B[k - 1]     #  return case1/2
        if k == 1: return min(A[0], B[0]) #  return case2/2
        
        nums = min(k/2, lenA); 
        if A[nums - 1] <= B[nums - 1]:
            return self.getKth_v2(A[nums:], B, k-nums)
        else:
            return self.getKth_v2(A, B[nums:], k-nums)
    
    def findMedianSortedArrays_v2(self, A, B):
        lenA = len(A); lenB = len(B)
        if lenA == 0 and lenB == 0: return 0xffffffff
        if (lenA + lenB) % 2 == 1: 
            return self.getKth_v2(A, B, (lenA + lenB)/2 + 1)
        else:
            value1 = self.getKth_v2(A, B, (lenA + lenB)/2)
            value2 = self.getKth_v2(A, B, (lenA + lenB)/2 + 1)
            return (value1+value2) * 0.5

#################################################################
def median_two_array_test(A, B):               
    solu = Solution()
    print 'median of',A,B	
    print solu.findMedianSortedArrays(A,B)
    print solu.findMedianSortedArrays_v2(A,B)

print median_two_array_test((1,3,5,7,9),(0,2,4,6))
print median_two_array_test((1,),(0,2,4,6))
print median_two_array_test((1,2),(0,2,4,6))
print median_two_array_test((1,),(2,))
print median_two_array_test((1,2,2),(2,3))

'''
题目是这样的：给定两个已经排序好的数组（可能为空），找到两者所有元素中第k大的元
素。另外一种更加具体的形式是，找到所有元素的中位数。本篇文章我们只讨论更加一般性
的问题：如何找到两个数组中第k大的元素？不过，测试是用的两个数组的中位数的题目，
Leetcode第4题 Median of Two Sorted Arrays
 
方案1：假设两个数组总共有n个元素，那么显然我们有用O(n)时间和O(n)空间的方法：用
merge sort的思路排序，排序好的数组取出下标为k-1的元素就是我们需要的答案。这个方
法比较容易想到，但是有没有更好的方法呢？
方案2：我们可以发现，现在我们是不需要“排序”这么复杂的操作的，因为我们仅仅需要
第k大的元素。我们可以用一个计数器，记录当前已经找到第m大的元素了。同时我们使用两
个指针pA和pB，分别指向A和B数组的第一个元素。使用类似于merge sort的原理，如果数组
A当前元素小，那么pA++，同时m++。如果数组B当前元素小，那么pB++，同时m++。最终当m
等于k的时候，就得到了我们的答案——O(k)时间，O(1)空间。
但是，当k很接近于n的时候，这个方法还是很费时间的。当然，我们可以判断一下，如果k

 比n/2大的话，我们可以从最大的元素开始找。但是如果我们要找所有元素的中位数呢？时
 间还是O(n/2)=O(n)的。有没有更好的方案呢？
 我们可以考虑从k入手。如果我们每次都能够剔除一个一定在第k大元素之前的元素，那么我
 们需要进行k次。但是如果每次我们都剔除一半呢？所以用这种类似于二分的思想，我们可以
 这样考虑：
 
 Assume that the number of elements in A and B are both larger than k/2, and if 
 we compare the k/2-th smallest element in A(i.e. A[k/2-1]) and the k-th smallest 
 element in B(i.e. B[k/2 - 1]), there are three results:(Becasue k can be odd or 
 even number, so we assume k is even number here for simplicy. The following is 
 also true when k is an odd number.)
     A[k/2-1] = B[k/2-1]
     A[k/2-1] > B[k/2-1]
     A[k/2-1] < B[k/2-1]
     
 if A[k/2-1] < B[k/2-1], that means all the elements from A[0] to A[k/2-1](i.e. 
 the k/2 smallest elements in A) are in the range of k smallest elements in the 
 union of A and B. Or, in the other word, A[k/2 - 1] can never be larger than the 
 k-th smalleset element in the union of A and B.
 
  Why?
  We can use a proof by contradiction. Since A[k/2 - 1] is larger than the k-th 
  smallest element in the union of A and B, then we assume it is the (k+1)-th 
  smallest one. Since it is smaller than B[k/2 - 1], then B[k/2 - 1] should be 
  at least the (k+2)-th smallest one. So there are at most (k/2-1) elements 
  smaller than A[k/2-1] in A, and at most (k/2 - 1) elements smaller than 
  A[k/2-1] in B.So the total number is k/2+k/2-2, which, no matter when k is odd 
  or even, is surly smaller than k(since A[k/2-1] is the (k+1)-th smallest element). 
  So A[k/2-1] can never larger than the k-th smallest element in the union of A 
  and B if A[k/2-1]<B[k/2-1];
  Since there is such an important conclusion, we can safely drop the first k/2 
  element in A, which are definitaly smaller than k-th element in the union of 
  A and B. This is also true for the A[k/2-1] > B[k/2-1] condition, which we 
  should drop the elements in B.
  When A[k/2-1] = B[k/2-1], then we have found the k-th smallest element, that 
  is the equal element, we can call it m. There are each (k/2-1) numbers smaller 
  than m in A and B, so m must be the k-th smallest number. So we can call a 
  function recursively, when A[k/2-1] < B[k/2-1], we drop the elements in A, 
  else we drop the elements in B.
 
  We should also consider the edge case, that is, when should we stop?
  1. When A or B is empty, we return B[k-1]( or A[k-1]), respectively;
  2. When k is 1(when A and B are both not empty), we return the smaller one of A[0] and B[0]
  3. When A[k/2-1] = B[k/2-1], we should return one of them
 
  In the code, we check if m is larger than n to garentee that the we always 
  know the smaller array, for coding simplicy.
 分析
 这是一道非常经典的题。这题更通用的形式是，给定两个已经排序好的数组，找到两者所
 有元素中第 k 大的元素。O(m + n) 的解法比较直观，直接merge两个数组，然后求第k大
 的元素。不过我们仅仅需要第 k 大的元素，是不需要“排序”这么复杂的操作的。可以用
 一个计数器，记录当前已经找到第 m 大的元素了。同时我们使用两个指针 pA 和 pB，分
 别指向 A 和 B 数组的第一个元素，使用类似于merge sort的原理，如果数组A当前元素小，
 那么 pA++，同时 m++；如果数组B当前元素小，那么 pB++，同时 m++。最终当m等于k 的
 时候，就得到了我们的答案，O(k)时间，O(1) 空间。但是，当 k 很接近 m + n的时候，
 这个方法还是O(m + n) 的。
 
 有没有更好的方案呢？我们可以考虑从 k 入手。如果我们每次都能够删除一个一定在第 k 
 大元素之前的元素，那么我们需要进行 k 次。但是如果每次我们都删除一半呢？由于 A 
 和 B 都是有序的，我们应该充分利用这里面的信息，类似于二分查找，也是充分利用了
 “有序”。
 假设 A 和 B 的元素个数都大于 k/2，我们将 A 的第 k/2 个元素（即 A[k/2-1]）和 B 
 的第 k/2个元素（即 B[k/2-1]）进行比较，有以下三种情况（为了简化这里先假设k 为偶
 数，所得到的结论对于k 是奇数也是成立的）：
 1 A[k/2-1] == B[k/2-1]
 2 A[k/2-1] > B[k/2-1]
 3 A[k/2-1] < B[k/2-1]
 如果 A[k/2-1] < B[k/2-1]，意味着 A[0] 到 A[k/2-1 的肯定在 A 和 B 的 top k 元素
 的范围内，换句话说，A[k/2-1]不可能大于 A 和 B 的第k 大元素。留给读者证明。
 因此，我们可以放心的删除 A 数组的这 k/2 个元素。同理，当 A[k/2-1] > B[k/2-1] 
 时，可以删除 B数组的 k/2 个元素。
 当 A[k/2-1] == B[k/2-1] 时，说明找到了第 k 大的元素，直接返回 A[k/2-1] 或 B[k/2-1]
 即可。
 因此，我们可以写一个递归函数。那么函数什么时候应该终止呢？
 1 当 A 或 B是空时，直接返回 B[k-1]或 A[k-1]；
 2 当 k=1是，返回 min(A[0], B[0])；
 3 当 A[k/2-1] == B[k/2-1] 时，返回 A[k/2-1] 或 B[k/2-1]
'''
