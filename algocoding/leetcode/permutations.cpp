/*******************************************************************************
                         Permutations(Medium) 
 *******************************************************************************
 Given a collection of numbers, return all possible permutations.
 
 For example,
 [1,2,3] have the following permutations:
 [1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1].
 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 vector<vector<int> > permute(vector<int> &num) {
		 
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
vector<vector<int> > permute(vector<int> &num) {
        
}

vector<vector<int> > permute2(vector<int> &num) {
	vector<vector<int> > result;
	permute_dfs(0,num,result);
    return result;
}

void permute_dfs(int pos, vector<int> &num, vector<vector<int> > &result){
    if(pos == num.size()){
        result.push_back(num);
    } else {
        for(int i=pos; i<num.size(); i++){
            swap(num[i], num[pos]);
            permute_dfs(pos+1, num, result);
            swap(num[i], num[pos]);
        }
    }
}

};

/*---------------------------------------------------------------------------------*/
void permute_test_show(vector<vector<int> > &result)
{
    vector<int> tmp;
    vector<vector<int> >::iterator it;	
    vector<int>::iterator it2;	
	
	for (it = result.begin(); it != result.end(); ++it){
		tmp = *it;
		for (it2 = tmp.begin(); it2 != tmp.end(); ++it2){
            cout << ' ' << *it2;
		}
		cout << endl;
	}	
}

void permute_test(int nums)
{
    Solution solu;
	vector<int> tmp;
	vector<vector<int> > result;
    vector<int>::iterator it2;	
	
	for(int i = 1; i <= nums; ++i){
		tmp.push_back(i);
	}

    cout << "permute:";
	for (it2 = tmp.begin(); it2 != tmp.end(); ++it2){
	    cout << ' ' << *it2;
	}

    cout << endl;
	
	result = solu.permute2(tmp);
    permute_test_show(result);
	
}

int main()
{
	permute_test(2);
	permute_test(3);

	return 0;
}
