# class Solution:
#     # @param A, a list of integers
#     # @return a boolean
#     def canJump(self, A):

class Solution:
    # @param A, a list of integers
    # @return a boolean
    def canJump(self, A):
        step = A[0]
        for i in range(1, len(A)):
            if step > 0:
                step -= 1
                step = max(step, A[i])
            else:
                return False
        return True
		
########################### test ###########################		
solu = Solution()
print solu.canJump([0])
print solu.canJump([2,3,1,1,4])
print solu.canJump([2,1,0,0,4])