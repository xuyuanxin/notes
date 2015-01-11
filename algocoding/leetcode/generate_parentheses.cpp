/*******************************************************************************
                        Generate Parentheses(Medium) 
 *******************************************************************************
 Given n pairs of parentheses, write a function to generate all combinations of 
 well-formed parentheses.
 
 For example, given n = 3, a solution set is:
 
 "((()))", "(()())", "(())()", "()(())", "()()()"

 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 vector<string> generateParenthesis(int n) {
		 
	 }
 };
 ************************************************************************************
                              algo
 ************************************************************************************
 该问题解的个数就是卡特兰数，但是现在不是求个数，而是要将所有合法的括号排列打印出来。
 针对一个长度为2n的合法排列，第1到2n个位置都满足如下规则：左括号的个数大于等于右括号的
 个数。所以，我们就可以按照这个规则去打印括号：假设在位置k我们还剩余left个左括号和right
 个右括号，
 如果left>0，则我们可以直接打印左括号，而不违背规则。
 如果left>=right，则我们不能打印右括号，因为打印会违背合法排列的规则，否则可以打印右括号。
 如果left和right均为零，则说明我们已经完成一个合法排列，可以将其打印出来。
 通过深搜，我们可以很快地解决问题，针对n=2，问题的解空间如下：

 http://blog.csdn.net/yutianzuijin/article/details/13161721
 ***********************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h> /* abs */

using namespace std;
class Solution {
public:
vector<string> generateParenthesis(int n) {
	vector<string> result;
	string s;
    generate(n,n,s,result);
	return result;
}

void generate(int leftNum,int rightNum,string s,vector<string> &result)
{
    if(leftNum==0&&rightNum==0){
        result.push_back(s);
    }
    if(leftNum>0){
        generate(leftNum-1,rightNum,s+'(',result);
    }
    if(rightNum>0&&leftNum<rightNum){
        generate(leftNum,rightNum-1,s+')',result);
    }
}

};


/***********************************************************************************/

void generate_parenthesis_test(int n)
{
    Solution solu;
	vector<string> result;
	vector<string>::iterator it;
	result = solu.generateParenthesis(n);
    cout << "parenthesis: " << n << endl;
    for(it = result.begin(); it != result.end(); it++){
	    cout << *it << endl;
    }
}


int main()
{
	generate_parenthesis_test(0);
	generate_parenthesis_test(1);
	generate_parenthesis_test(2);
	generate_parenthesis_test(3);
	generate_parenthesis_test(4);
	generate_parenthesis_test(5);

	return 0;
}

