/*******************************************************************************
                      Length of Last Word(Easy)
 *******************************************************************************
 Given a string s consists of upper/lower-case alphabets and empty space characters 
 ' ', return the length of last word in the string.
 
 If the last word does not exist, return 0.
 
 Note: A word is defined as a character sequence consists of non-space characters 
 only.
 
 For example, 
 Given s = "Hello World",
 return 5.
 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 int lengthOfLastWord(const char *s) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************

 ******************************************************************************/
#include <iostream>	 
#include <string>
using namespace std;

class Solution {
public:
int lengthOfLastWord(const char *s) 
{
	int len = 0;
	
	while (*s) {
	    if (*s++ != ' ')
	        ++len;
	    else if (*s && *s != ' ')
	        len = 0;
	}
	
	return len;
}



};


int length_last_word_test(char *s,int expect)
{
    Solution solu;

	cout << "last word len: " << solu.lengthOfLastWord(s);
	cout << " (" << expect << ")" << endl;
}

int main()
{
    length_last_word_test((char *)"Hello World",5);
    length_last_word_test((char *)"Hello            ",5);
    length_last_word_test((char *)"             ",0);

    length_last_word_test((char *)"Hello World ",5);
	return 0;
}
