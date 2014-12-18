/*******************************************************************************
                        Swap Nodes in Pairs (Medium)
 *******************************************************************************
 Given a linked list, swap every two adjacent nodes and return its head.
 
 For example,
 Given 1->2->3->4, you should return the list as 2->1->4->3.
 Your algorithm should use only constant space. You may not modify the values in 
 the list, only nodes itself can be changed.
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
	 ListNode *swapPairs(ListNode *head) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************

 ******************************************************************************/

 class Solution {
 public:

ListNode *swapPairs(ListNode *head) 
{
    ListNode *prev,*curr,*next,lhead(-1);

	if(NULL == head) return NULL;

    lhead.next = head;
	
	prev = &lhead;
	curr = prev->next;
	next = (NULL == curr? NULL:curr->next);

	while(curr->next)
	{
	    curr->next = next->next;
		next->next = curr;
		prev->next = next;

        prev = curr;
		curr = curr->next;
		next = (NULL == curr? NULL:curr->next);

		if(NULL == curr) break;
	}

	return lhead.next;
}



 };


