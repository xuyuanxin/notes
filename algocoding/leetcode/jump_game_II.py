# class Solution:
#     # @param A, a list of integers
#     # @return an integer
#     def jump(self, A):

class Solution:
# We use "last" to keep track of the maximum distance that has been reached
# by using the minimum steps "ret", whereas "curr" is the maximum distance
# that can be reached by using "ret+1" steps. Thus,curr = max(i+A[i]) where 0 <= i <= last.
    def jump(self, A):    
        ret = 0
        last = 0
        curr = 0
        for i in range(len(A)):
            if i > last:
                last = curr
                ret += 1
            curr = max(curr, i+A[i])
        return ret
		
########################### test ###########################		
solu = Solution()
print solu.jump([0])
print solu.jump([2,3,1,1,4])
print solu.jump([2,1,0,0,4])