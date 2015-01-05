/*******************************************************************************
                         N-Queens(Hard) 
 *******************************************************************************
 The n-queens puzzle is the problem of placing n queens on an n¡Án chessboard such 
 that no two queens attack each other.
 
 Given an integer n, return all distinct solutions to the n-queens puzzle.
 
 Each solution contains a distinct board configuration of the n-queens' placement, 
 where 'Q' and '.' both indicate a queen and an empty space respectively.
 
 For example,
 There exist two distinct solutions to the 4-queens puzzle:
 
 [
  [".Q..",	// Solution 1
   "...Q",
   "Q...",
   "..Q."],
 
  ["..Q.",	// Solution 2
   "Q...",
   "...Q",
   ".Q.."]
 ]
 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 vector<vector<string> > solveNQueens(int n) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************
 
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h> /* abs */

using namespace std;

class Solution {
public:

void printQueen(vector<int> &A,int n,vector< vector<string> > &result){
    vector<string> r;
	
    for(int i=0;i<n;i++){
        string str(n,'.');
        str[A[i]] = 'Q';
        r.push_back(str);
    }
	
    result.push_back(r);
}

bool isValidQueens(vector<int>A,int r){
    for(int i=0;i<r;i++){
        if((A[i]==A[r])||(abs(A[i]-A[r]))==(r-i))
            return false;
    }
    return true;
}

void nqueens(vector<int> A,int cur, int n,vector<vector<string> > &result){
    if(cur == n){
        printQueen(A,n,result);
    }else{
        for(int i=0;i<n;i++){
            A[cur] = i;
            if(isValidQueens(A,cur))
                nqueens(A,cur+1,n,result);
        }
    }
}

/************************************************************************************
 Analysis:
 The classic recursive problem.
 1 Use a int vector to store the current state,  A[i]=j refers that the ith row and 
   jth column is placed a queen.
 2 Valid state:  not in the same column, which is A[i]!=A[current], not in the same 
   diagonal direction: abs(A[i]-A[current]) != r-i
 3 Recursion: 
       Start:   placeQueen(0,n)
        if current ==n then print result
        else
            for each place less than n,
                 place queen
                if current state is valid, then place next queen   place Queen(cur+1,n)
           end for
        end i
************************************************************************************/
vector< vector<string> > solveNQueens(int n) {
    vector<vector<string> > result;
    result.clear();
    vector<int> A(n,-1);
    nqueens(A,0,n,result);
    return result;
}

void show_result(vector<vector<string> > &result)
{
    vector<string> vs;
	string s;
	
    for(int i=0;i<result.size();i++){
		vs = result[i];
		for(int j=0;j<vs.size();j++){
			s = vs[j];
            cout << s << endl;
		}	
		cout << endl;
    }
}



};


void n_queens_test(int n)
{
    Solution solu;
	vector<vector<string> > result;

	result = solu.solveNQueens(n);

	solu.show_result(result);
	cout << endl;

}

int main()
{
	n_queens_test(5);

	return 0;
}








#if 0
vector<vector<string> > solveNQueens2(int n) {
	this->columns = vector<int>(n, 0);
	this->main_diag = vector<int>(2 * n, 0);
	this->anti_diag = vector<int>(2 * n, 0);
	vector<vector<string> > result;
	
	vector<int> C(n, 0); /*C[i] ±íÊ¾µÚ i ÐÐ»ÊºóËùÔÚµÄÁÐ±àºÅ */
	
	dfs(C, result, 0);
	
	return result;
}

private:
vector<int> columns; /*±íÊ¾ÒÑ¾­·ÅÖÃµÄ»ÊºóÕ¼¾ÝÁËÄÄÐ©ÁÐ*/
vector<int> main_diag; /* Õ¼¾ÝÁËÄÄÐ©Ö÷¶Ô½ÇÏß */
vector<int> anti_diag; /* Õ¼¾ÝÁËÄÄÐ©¸±¶Ô½ÇÏß */

void dfs(vector<int> &C, vector<vector<string> > &result, int row) {
	const int N = C.size();
	
	if (row == N) { /* ÖÕÖ¹Ìõ¼þ£¬Ò²ÊÇÊÕÁ²Ìõ¼þ£¬ÒâÎ¶×ÅÕÒµ½ÁËÒ»¸ö¿ÉÐÐ½â */
		vector<string> solution;
		for (int i = 0; i < N; ++i) {
			string s(N, '.');
			
			for (int j = 0; j < N; ++j) {
				if (j == C[i]) s[j] = 'Q';
			}
			
			solution.push_back(s);
		}
		result.push_back(solution);
		return;
	}
	
	for (int j = 0; j < N; ++j) { 
		const bool ok = columns[j] == 0 && main_diag[row + j] == 0 && anti_diag[row - j + N] == 0;
		if (!ok) continue;
		C[row] = j;
		columns[j] = main_diag[row + j] = anti_diag[row - j + N] = 1;
		dfs(C, result, row + 1);

		columns[j] = main_diag[row + j] = anti_diag[row - j + N] = 0;
	}
}
#endif
