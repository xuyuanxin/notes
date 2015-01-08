/*******************************************************************************
                      Valid Parentheses(Easy)
 *******************************************************************************
 Given a string containing just the characters '(', ')', '{', '}', '[' and ']', 
 determine if the input string is valid.
 
 The brackets must close in the correct order, "()" and "()[]{}" are all valid 
 but "(]" and "([)]" are not.
 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 bool isValid(string s) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************
 字符串S中的每一个字符C
 if C是左括号 ( ([{ ) 
     就压入栈stack中。
 if C是右括号，判断stack是不是空的
     空则说明没有左括号，直接返回not valid，
     非空就取出栈顶的字符来对比，
         如果是匹配的，就弹出栈顶的字符，继续取S中的下一个字符；
         如果不匹配，说明不是valid的，直接返回。

 当遍历了一次字符串S后，如果此时stack不是空的，这时说明S不是valid的，因为只要
 valid，一定全都可以得到匹配使左括号弹出。
 ******************************************************************************/
#include <iostream>
#include <string>
#include <stack>
 using namespace std;
 
 class Solution {
 public:
 bool isValid(string s)
 {
	 string left = "([{";
	 string right = ")]}";
	 
	 stack<char> stk;
	 
	 for (auto c : s) {
		 if (left.find(c) != string::npos) {
			 stk.push (c);
		 } else {
			 if (stk.empty () || stk.top () != left[right.find(c)])
				 return false;
			 else
				 stk.pop ();
		 }
	 }
	 
	 return stk.empty();
 }
 
 
 };

 int vaild_parentheses_test(string s,int expect)
 {
	 Solution solu;
 
	 cout << s << " : " << solu.isValid(s) << " (" << expect << ")" << endl;
 
	 return 0;
 }
 
 int main()
 {
	 vaild_parentheses_test("()[]",1);
	 vaild_parentheses_test("()[{]",0);
	 vaild_parentheses_test("(",0); 
	 vaild_parentheses_test("([{}])",1);
	 return 0;
 }
	 

