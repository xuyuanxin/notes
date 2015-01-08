/*******************************************************************************
                         N-Queens II(Hard) 
 *******************************************************************************
 Follow up for N-Queens problem.
 
 Now, instead outputting board configurations, return the total number of distinct 
 solutions.
 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 int totalNQueens(int n) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************
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
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h> /* abs */

using namespace std;


class Solution {
public:
int total_nums;

bool is_valid_place(vector<int>A,int r){
    for(int i=0;i<r;i++){
        if((A[i]==A[r])||(abs(A[i]-A[r]))==(r-i))
            return false;
    }
    return true;
}

void total_n_queens(vector<int> A,int cur, int n){
    if(cur == n){
        total_nums++;
    }else{
        for(int i=0;i<n;i++){
            A[cur] = i;
            if(is_valid_place(A,cur))
                total_n_queens(A,cur+1,n);
        }
    }
}

int totalNQueens(int n) {
    vector<int> A(n,-1);
	total_nums = 0;
    total_n_queens(A,0,n);
    return total_nums;
}

};

/*---------------------------------------------------------------------------------*/
void total_n_queens_test(int n)
{
    Solution solu;

	cout << n << "*" << n << " queens total solutions: " << solu.totalNQueens(n) << endl;
}

int main()
{
	total_n_queens_test(1);
	total_n_queens_test(2);
	total_n_queens_test(3);	
	total_n_queens_test(4);
	total_n_queens_test(5);

	total_n_queens_test(10);

	return 0;
}
