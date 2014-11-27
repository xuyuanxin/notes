/*******************************************************************************
You are given two linked lists representing two non-negative numbers. The digits 
are stored in reverse order and each of their nodes contain a single digit. Add 
the two numbers and return it as a linked list.

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 *//*
class Solution {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        
    }
};

*******************************************************************************/





#include <cstddef>

struct ListNode 
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) 
{
    ListNode lhead(-1);
    int rem = 0,a=0,b=0;
    ListNode *ltail = &lhead;	
    ListNode *la = l1;
    ListNode *lb = l2;

	while(NULL != la || NULL != lb)
	{
	    a = (NULL==la ? 0:la->val);
	    b = (NULL==lb ? 0:lb->val);
		ltail->next = new ListNode((a + b + rem) % 10);
		rem = (a + b + rem) / 10;
		ltail = ltail->next;
		la = (NULL==la ? NULL:la->next);
		lb = (NULL==lb ? NULL:lb->next);
	}
		
    if (rem > 0)
        ltail->next = new ListNode(rem);
	
    return lhead.next;
}

};

int main()
{
    return 0;
}
