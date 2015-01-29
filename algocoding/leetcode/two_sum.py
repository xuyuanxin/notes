class Solution:
    # @return a tuple, (index1, index2)
    def twoSum(self, num, target):
        dict = {} #value:index
        for i in xrange(len(num)):
            x = num[i]
            if target-x in dict:
                return (dict[target-x]+1, i+1)
            dict[x] = i
			
solu = Solution()
print solu.twoSum([2, 7, 11, 15],9)	
