

#####################################################################################
#最简单直观的想法就是一个一个子串试过去是否为回文。但是这样的时间复杂度很高。而且其实
#有很多不必判断的过程，如i到j之间，如果i-1与j-1已经不相同了，那么判断i,j毫无意义。所
#以很简单的思路是判断每个点扩展的最大串。遇到相同的字母相连的情况可以合在一起判断。这
#种方法在最坏的情况下复杂度会达到O(n^2)。
#有大神给出了O(n)时间复杂度的算法，具体可以看
#http://leetcode.com/2011/11/longest-palindromic-substring-part-ii.html
class Solution:
    # @return a string
    def longestPalindrome(self, s):
        if not s or len(s) == 1:
            return s
        # record the result value
        max_length = 1
        start_index = 0
        end_index = 0
        for i in range(0, len(s)-1):
            count = 1
            # aba
            if s[i] != s[i+1]:
                while i-count >= 0 and i + count < len(s) and s[i-count] == s[i+count]:
                    count += 1
                if (count-1) * 2 + 1 > max_length:
                    max_length = (count-1) * 2 + 1
                    start_index = i - count + 1
                    end_index = i + count - 1
            # xaaaaax
            else:
                count_repeat = 1
                count = 0
                while i+1 < len(s) and s[i] == s[i+1]:
                    i += 1
                    count_repeat += 1
                while i-count_repeat+1-count >= 0 and i + count < len(s) and s[i-count_repeat+1-count] == s[i+count]:
                    count += 1
                if (count-1) * 2 + count_repeat > max_length:
                    max_length = (count-1) * 2 + count_repeat
                    start_index = i - count -count_repeat + 2
                    end_index = i + count - 1
        return s[start_index:end_index+1]
	
	
	
class Solution1:
    # @return a string
    def getlongestpalindrome(self, s, l, r):
        while l >= 0 and r < len(s) and s[l] == s[r]:
            l -= 1; r += 1
        return s[l+1 : r]
    def longestPalindrome(self, s):
        palindrome = ''
        for i in range(len(s)):
            len1 = len(self.getlongestpalindrome(s, i, i))
            if len1 > len(palindrome): palindrome = self.getlongestpalindrome(s, i, i)
            len2 = len(self.getlongestpalindrome(s, i, i + 1))
            if len2 > len(palindrome): palindrome = self.getlongestpalindrome(s, i, i + 1)
        return palindrome
		
#http://blog.sina.com.cn/s/blog_aaf26b820102v9b3.html		
class Solution:
    # @return a string
    def longestPalindrome(self, s):
        if len(s)==1:
            return s
        p=s[0]
        for i in range(1,len(s)):
            if len(self.palin(s,i,i))>len(p):
                p=self.palin(s,i,i)
            if len(self.palin(s,i-1,i))>len(p):
                p=self.palin(s,i-1,i)
        return p
    def palin(self,s,begin,end):
        while (begin>=0)and (end
            begin-=1
            end+=1
        return s[begin+1:end]		
		
#下面是优化的思路及程序：

#优化思路：只要返回最大长度的子串，所以一切小于当前最大长度的子串都无需计算。用参数l 
#标记当前回文数左右两侧应该至少达到的位置。begin和end变成begin-l，end+l。python的求倒
#序字符串方法：[::-1],判断str1=s[begin,end+1] 和 str2=str1[::-1]是否相等
#（s[begin,end+1]是否为回文数）。若相等则继续判断，否则抛弃这种情况。
#附加改进：如果begin-l,end+l超出边界则直接返回

class Solution:
    # @return a string
    def longestPalindrome(self, s):
        if len(s)==1:
            return s
        p=s[0]
        for i in range(1,len(s)):
            l=(len(p)-1)/2
            if len(self.palin(s,i-l,i+l))>len(p):
                p=self.palin(s,i-l,i+l)
            if len(self.palin(s,i-1-l,i+l))>len(p):
                p=self.palin(s,i-1-l,i+l)
        return p
    
    def palin(self,s,begin,end):
        if (begin<0)or (end>=len(s)):
            return ''
        else:
            str1=s[begin:end+1]
            str2=str1[::-1]
            if (str1==str2):
                while (begin>=0)and (end
                  begin-=1
                  end+=1
            else:
                return ''
        return s[begin+1:end] 

   		
