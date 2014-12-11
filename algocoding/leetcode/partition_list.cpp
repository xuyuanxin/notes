/*******************************************************************************
                           Partition List(Medium)
********************************************************************************
Given a linked list and a value x, partition it such that all nodes less than x 
come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two 
partitions.

For example,
Given 1->4->3->2->5->2 and x = 3,
return 1->2->2->4->3->5.
********************************************************************************
                             interface
********************************************************************************
struct ListNode 
{
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
};
 
class Solution {
public:
    ListNode *partition(ListNode *head, int x) {
        
    }
};
********************************************************************************
                              algo
********************************************************************************
设定两个链表头a b，遍历所给的链表，小于x的节点挂在a上，否则挂到b，最后把a b合并
*******************************************************************************/



// LeetCode, Partition List
//time O(n),space O(1)
class Solution {
public:
ListNode* partition(ListNode* head, int x)
{
    ListNode left_dummy(-1); 
    ListNode right_dummy(-1);
	
    ListNode *left_cur = &left_dummy;
    ListNode *right_cur = &right_dummy;
	
    for (ListNode *cur = head; cur; cur = cur->next) 
	{
        if (cur->val < x) 
		{
            left_cur->next = cur;
            left_cur = cur;
        } 
		else 
		{
            right_cur->next = cur;
            right_cur = cur;
        }
    }
	
    left_cur->next = right_dummy.next;
    right_cur->next = NULL;
	
    return left_dummy.next;
}

};


