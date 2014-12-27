/*******************************************************************************
                         Add Binary(Easy)
 *******************************************************************************
 Given two binary strings, return their sum (also a binary string).
 
 For example,
 a = "11"
 b = "1"
 Return "100".
 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 string addBinary(string a, string b) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************
 
 ******************************************************************************/
#include <iostream>	 
#include <string>
#include <algorithm>  /* reverse */
using namespace std;


class Solution {
public:

string addBinary(string a, string b) 
{
    string result;	
    int carry = 0;
	
    const size_t n = a.size() > b.size() ? a.size() : b.size();
	
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
	
    for (size_t i = 0; i < n; i++) {
        const int ai = i < a.size() ? a[i] - '0' : 0;
        const int bi = i < b.size() ? b[i] - '0' : 0;
        const int val = (ai + bi + carry) % 2;
        carry = (ai + bi + carry) / 2;
        result.insert(result.begin(), val + '0');
    }
	
    if (carry == 1) {
        result.insert(result.begin(), '1');
    }
	
    return result;		 
}


};



void add_binary_test(string a, string b)
{
    Solution solu;
	
    cout << a << "+" << b << "=" << solu.addBinary(a,b) << endl;
}


int main()
{    
    add_binary_test("","");
    add_binary_test("","1");
    add_binary_test("1","1");
	
    add_binary_test("11","1");

	return 0;
}

