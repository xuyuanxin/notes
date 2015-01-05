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
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
	const int m = obstacleGrid.size();
	const int n = obstacleGrid[0].size();
    vector< vector<int> > f(m, vector<int>(n,1));	
	
    if(m == 0 || n == 0){
        return 0;
    }
			
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
	Solution solu;

	vector_constructor();

	return 0;
}
