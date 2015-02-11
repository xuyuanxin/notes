#!/usr/bin/env python
#coding=utf-8

#####################################################################################
#reference http://chaoren.is-programmer.com/posts/42744.html
#两个指针从左往右扫描, 当头指针遇到重复字母时, 用尾指针找到上一次出现的重复字母，用此
#时所得子串的长度于更新max, 以尾指针的index+1作为新的搜索起始位置。头指针要扫描到最后
#一个字母, 别忘了最后得到的子串长度也要更新max。
# example : "abcdbefchijk"
#---------------------------
# rear
#  |
#  a b c d b e f c h i j k      ----> len = 4
#          |
#          front
#---------------------------
#    rear
#      |
#  a b c d b e f c h i j k
#          |
#          front
#---------------------------
#    rear
#      |
#  a b c d b e f c h i j k      ----> len = 5
#                |
#              front
#---------------------------
#      rear
#        |
#  a b c d b e f c h i j k
#                |
#              front
#---------------------------
#      rear
#        |
#  a b c d b e f c h i j k      ----> len = 9 (max)
#                        |
#                       front
#---------------------------
class Solution:
    # @return an integer
    def lengthOfLongestSubstring(self, s):
        maxLen = 0
        subStr = ''
        rear = 0
        for front in xrange(len(s)):
            if s[front] not in subStr:
                subStr += s[front]
            else:
                maxLen = max(maxLen, len(subStr))
                while s[rear] != s[front]: rear += 1
                rear += 1
                subStr = s[rear : front+1] #[rear,front+1)
        return max(maxLen, len(subStr))
		
solu=Solution()

print solu.lengthOfLongestSubstring('abcdbefchijk')
