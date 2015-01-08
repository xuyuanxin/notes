/*******************************************************************************
                         Permutations II(Hard) 
 *******************************************************************************
 Given a collection of numbers that might contain duplicates, return all possible 
 unique permutations.
 
 For example,
 [1,1,2] have the following unique permutations:
 [1,1,2], [1,2,1], and [2,1,1].
 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 vector<vector<int> > permuteUnique(vector<int> &num) {
		 
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
vector<vector<int> > permuteUnique(vector<int> &num) {
        
}

vector<vector<int> > permuteUnique2(vector<int> &num) {
	vector<vector<int> > result;
	permute_unique_dfs(0,num,result);
    return result;
}


/*
  pos
   |
  \|/
   1    1    2    2    2
       /|\ 
        |
       cur( 相同的元素不交换 1和1不交换 )
----------------------------------------------------------------
pos                j
 |                 |
\|/               \|/
 1     1     2     2     2
	       /|\ 
	        |
	       cur( a和b不同，如果有多个b，a只和最后一个b交换。1和最后一个2交换,
	            发现cur后面还有2就不交换，等最后的2再交换)
*/
int permute_is_vaild(int pos,int cur,vector<int> &num)
{
    int j;

    if(pos == cur) {
		return 1;
    }
	
	if(num[cur] == num[pos]){            /* 相同的元素不交换 */
		return 0;
	}	
	
	for(j = cur+1; j < num.size(); ++j){ /* a和b不同，如果有多个b，a只和最后一个b交换 */
		if(num[cur] == num[j]) return 0;
	}	

    return 1;
}

void permute_unique_dfs(int pos, vector<int> &num, vector<vector<int> > &result){
    if(pos == num.size()){
        result.push_back(num);
    } else {
        for(int i=pos; i<num.size(); i++){

            if(!permute_is_vaild(pos,i,num)) continue;
			
            swap(num[i], num[pos]);
            permute_unique_dfs(pos+1, num, result);
            swap(num[i], num[pos]);
        }
    }
}


};

/*---------------------------------------------------------------------------------*/
void permute_test_show(vector<int> &nums,vector<vector<int> > &result)
{
    vector<int> tmp;
    vector<vector<int> >::iterator it;	
    vector<int>::iterator it2;	

    cout << "permute:";
	for (it2 = nums.begin(); it2 != nums.end(); ++it2){
	    cout << ' ' << *it2;
	}
	
	cout << endl;	
	
	for (it = result.begin(); it != result.end(); ++it){
		tmp = *it;
		for (it2 = tmp.begin(); it2 != tmp.end(); ++it2){
            cout << ' ' << *it2;
		}
		cout << endl;
	}
	cout << endl;	
}

void permute_test01()
{
    Solution solu;
	vector<int> tmp;
	vector<vector<int> > result;

	tmp.push_back(1);
	
	result = solu.permuteUnique2(tmp);
    permute_test_show(tmp,result);
}

void permute_test02()
{
    Solution solu;
	vector<int> tmp;
	vector<vector<int> > result;

	tmp.push_back(1);tmp.push_back(1);
	
	result = solu.permuteUnique2(tmp);
    permute_test_show(tmp,result);
}

void permute_test03()
{
    Solution solu;
	vector<int> tmp;
	vector<vector<int> > result;

	tmp.push_back(1);tmp.push_back(1);
    tmp.push_back(2);	
	result = solu.permuteUnique2(tmp);
    permute_test_show(tmp,result);
}

void permute_test04()
{
    Solution solu;
	vector<int> tmp;
	vector<vector<int> > result;

	tmp.push_back(1);tmp.push_back(2);
    tmp.push_back(3);	
	result = solu.permuteUnique2(tmp);
    permute_test_show(tmp,result);
}


void permute_test05()
{
    Solution solu;
	vector<int> tmp;
	vector<vector<int> > result;

	tmp.push_back(1);tmp.push_back(1);
	tmp.push_back(2);tmp.push_back(2);
	tmp.push_back(2);
	
	result = solu.permuteUnique2(tmp);
    permute_test_show(tmp,result);
}



int main()
{
	permute_test01();
	permute_test02();
	permute_test03();
	permute_test04();
	permute_test05();

	return 0;
}
