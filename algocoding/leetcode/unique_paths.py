# class Solution:
#     # @return an integer
#     def uniquePaths(self, m, n):

class Solution:
    # @return an integer
    def uniquePaths(self, m, n):
        paths = [[1] for i in range(m)]  # initialize the 1st column to be 1 [[1], [1], [1]] 
        
        for i in range(n - 1):           # initialize the 1st row to be 1  [[1, 1, 1], [1], [1]]
            paths[0].append(1) 
        
        for i in range(m - 1):
            for j in range(n - 1):
                paths[i + 1].append(paths[i][j + 1] + paths[i + 1][j])
        
        return paths[m - 1][n - 1]

class Solution2:
    # @return an integer
    def uniquePaths(self, m, n):
        if m == 1 and n == 1:
            list = [[1]]
        elif m == 1 and n > 1:
            list = [[1 for i in range(n)]]
        elif m > 1 and n == 1:
            list = [[1] for i in range(m)]
        else:
            list = [[0 for i in range(n)] for i in range(m)]
            for i in range(0, n):
                list[0][i] = 1
            for i in range(0, m):
                list[i][0] = 1
            for i in range(1, m):
                for j in range(1, n):
                    list[i][j] = list[i-1][j] + list[i][j-1]
        return list[m-1][n-1]
		
class Solution3:
    # @return an integer
    def uniquePaths(self, m, n):
        list = [[1 for i in range(n)] for i in range(m)]
        for i in range(1, m):
            for j in range(1, n):
                list[i][j] = list[i-1][j] + list[i][j-1]
        return list[m-1][n-1]			
#----------------------------- test -------------------------------#    
solu = Solution3()
print 'unique paths:',solu.uniquePaths(1,1)
print 'unique paths:',solu.uniquePaths(2,2)
print 'unique paths:',solu.uniquePaths(3,3)
print 'unique paths:',solu.uniquePaths(4,4)
