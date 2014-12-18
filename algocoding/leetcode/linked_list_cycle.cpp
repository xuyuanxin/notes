/*******************************************************************************
                           Linked List Cycle(Medium)
 *******************************************************************************
 Given a linked list, determine if it has a cycle in it.
 
 Follow up:
 Can you solve it without using extra space?
 *******************************************************************************
                             interface
 *******************************************************************************
 struct ListNode 
 {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
 };
 
 class Solution {
 public:
	 bool hasCycle(ListNode *head) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************

 ******************************************************************************/


class Solution {
public:

bool hasCycle(ListNode *head) 
{
    ListNode *fast,*slow;

	if(NULL == head) return false;

	fast = head;
	slow = head;

	while(fast && fast->next)
	{
	    slow = slow->next;
		fast = fast->next->next;

		if(slow == slow) return true;
	}

    return false;
}


};



