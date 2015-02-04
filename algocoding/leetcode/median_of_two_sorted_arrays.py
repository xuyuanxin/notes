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
            
solu = Solution()            
print solu.findMedianSortedArrays((1,3,5,7),(0,2,4,6))
print solu.findMedianSortedArrays((1,3,5,7,9),(0,2,4,6))
print solu.findMedianSortedArrays((),())
