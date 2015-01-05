/*******************************************************************************
                         Unique Paths(Medium) 
 *******************************************************************************
 A robot is located at the top-left corner of a m x n grid (marked 'Start' in the 
 diagram below).
 
 The robot can only move either down or right at any point in time. The robot is 
 trying to reach 
 the bottom-right corner of the grid (marked 'Finish' in the diagram below).
 
 How many possible unique paths are there?
 
 
 Above is a 3 x 7 grid. How many possible unique paths are there?
 
 Note: m and n will be at most 100.
 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 int uniquePaths(int m, int n) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************
 
 ******************************************************************************/
class Solution {
public:
int uniquePaths(int m, int n) {

}

/* timeout */
int uniquePaths2(int m, int n) {
    if (m < 1 || n < 1) return 0;
    if (m == 1 && n == 1) return 1;
    return uniquePaths2(m - 1, n) + uniquePaths2(m, n - 1);
}

int uniquePaths3(int m, int n) {
    vector<vector<int>> v(m, vector<int>(n, 1));
	
    for(int i=1; i<m; ++i){
        for(int j=1; j<n; ++j){
            v[i][j] = v[i-1][j] + v[i][j-1];
        }
    }
	
    return v[m-1][n-1];
}



/*
 Éè×´Ì¬Îª f[i][j]£¬±íÊ¾´ÓÆðµã (1; 1) µ½´ï (i; j) µÄÂ·ÏßÌõÊý£¬Ôò×´Ì¬×ªÒÆ·½³ÌÎª£º
 f[i][j]=f[i-1][j]+f[i][j-1]
 
 ×ó±ßµÄ f[j]£¬±íÊ¾¸üÐÂºóµÄ f[j]£¬Óë¹«Ê½ÖÐµÄ f[i[[j] ¶ÔÓ¦
 ÓÒ±ßµÄ f[j]£¬±íÊ¾ÀÏµÄ f[j]£¬Óë¹«Ê½ÖÐµÄ f[i-1][j] ¶ÔÓ¦
*/
int uniquePaths4(int m, int n) {
	vector<int> f(n,0);
	f[0] = 1;
	
	for (int i = 0; i < m; i++) {
	    for (int j = 1; j < n; j++) {
            f[j] = f[j - 1] + f[j];
	    }
    }
	
    return f[n - 1];
}




};




/*******************************************************************************
                         Unique Paths II (Medium) 
 *******************************************************************************
 Follow up for "Unique Paths":
 
 Now consider if some obstacles are added to the grids. How many unique paths would 
 there be?
 
 An obstacle and empty space is marked as 1 and 0 respectively in the grid.
 
 For example,
 There is one obstacle in the middle of a 3x3 grid as illustrated below.
 
 [
   [0,0,0],
   [0,1,0],
   [0,0,0]
 ]
 The total number of unique paths is 2.
 
 Note: m and n will be at most 100.

 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************
 
 ******************************************************************************/



class Solution2 {
public:
int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
 
}

int uniquePathsWithObstacles2(vector<vector<int> > &obstacleGrid) {
	const int m = obstacleGrid.size();
	const int n = obstacleGrid[0].size();
	
    if(m == 0 || n == 0){
        return 0;
    }

    vector<vector<int> > f(m,n);
			
	f[0][0] = obstacleGrid[0][0] == 1 ? 0 : 1;
	for(int i = 1; i < m; i++)
		f[i][0] = obstacleGrid[i][0] == 1 ? 0 : f[i-1][0];
		 
	for(int i = 1; i < n; i++)
		f[0][i] = obstacleGrid[0][i] == 1 ? 0 : f[0][i-1];
		 
	for(int i = 1; i < m; i++)
		for(int j = 1; j < n; j++)
			f[i][j] = obstacleGrid[i][j] == 1 ? 0 : f[i-1][j] + f[i][j-1];
			 
	return f[f.size()-1][f[0].size()-1];
}

};


int main()
{
}
