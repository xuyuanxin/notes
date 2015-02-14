#coding=utf-8



class Solution:
    # @return a string
    def longestPalindrome_v1(self, s):
        if len(s)==1:
            return s
        p=s[0]
        for i in range(1,len(s)):
            if len(self.palin(s,i,i))>len(p):
                p=self.palin(s,i,i)
            if len(self.palin(s,i-1,i))>len(p):
                p=self.palin(s,i-1,i)
        return p
        
    def palin(self,s,beg,end):
        while (beg>=0) and (end < len(s)) and (s[beg]==s[end]):
            beg-=1
            end+=1
        return s[beg+1:end]               
#http://blog.sina.com.cn/s/blog_aaf26b820102v9b3.html          
#下面是优化的思路及程序：
#优化思路：只要返回最大长度的子串，所以一切小于当前最大长度的子串都无需计算。用参数l 
#标记当前回文数左右两侧应该至少达到的位置。begin和end变成begin-l，end+l。python的求倒
#序字符串方法：[::-1],判断str1=s[begin,end+1] 和 str2=str1[::-1]是否相等
#（s[begin,end+1]是否为回文数）。若相等则继续判断，否则抛弃这种情况。
#附加改进：如果begin-l,end+l超出边界则直接返回
    # @return a string
    def longestPalindrome_v2(self, s):
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
                while (begin>=0) and (end < len(s)) and (s[begin]==s[end]):
                  begin-=1
                  end+=1
            else:
                return ''
        return s[begin+1:end] 
        
def longest_pali_test(s):           
    solu=Solution()
    print 'string:', s
    print 'v1    :',solu.longestPalindrome_v1(s)
    print 'v2    :',solu.longestPalindrome_v1(s)
    
longest_pali_test('aabbaa')
longest_pali_test('aa')
longest_pali_test('aabccbaa')
longest_pali_test('caabccbaa')
