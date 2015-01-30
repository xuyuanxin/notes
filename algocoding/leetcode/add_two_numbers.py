#!/usr/bin/env python
#coding=utf-8

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution:
    # @return a ListNode
    def addTwoNumbers(self, l1, l2):
        # method 1: 14 Lines
        dummy, flag = ListNode(0), 0
        head = dummy
        while flag or l1 or l2:
            node = ListNode(flag)
            if l1:
                node.val += l1.val
                l1 = l1.next
            if l2:
                node.val += l2.val
                l2 = l2.next
            flag = node.val / 10
            node.val %= 10
            head.next = node  
            head = head.next  # head.next, head = node, node
        return dummy.next
        
#Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
#Output: 7 -> 0 -> 8
a1 = ListNode(2)
a2 = ListNode(4)
a3 = ListNode(3)
b1 = ListNode(5)
b2 = ListNode(6)
b3 = ListNode(4)
a1.next = a2
a2.next = a3
b1.next = b2
b2.next = b3

solu = Solution()
head = ListNode(-1)
head.next = solu.addTwoNumbers(a1,b1)

def show_list(head):
    while head:
	    print head.val
	    head = head.next
		
show_list(head.next)

'''
asdfasdf
asdfasdfdsfasdf
'''
