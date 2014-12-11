/*******************************************************************************
                 Remove Duplicates from Sorted List(Easy)
 *******************************************************************************
 Given a sorted linked list, delete all duplicates such that each element appear 
 only once.

 For example,
 Given 1->1->2, return 1->2.
 Given 1->1->2->3->3, return 1->2->3.
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
	 ListNode *deleteDuplicates(ListNode *head) {
		 
	 }
 };

 *******************************************************************************
                              algo
 *******************************************************************************
 ******************************************************************************/


 class Solution {
 public:

ListNode *deleteDuplicates(ListNode *head) 
{
    ListNode *prev,*cur, *next;
	
    if (head == nullptr) return nullptr;

	prev = head;
	cur  = prev->next;

	while(nullptr != cur)
	{
	    next = cur->next;
		
	    if(prev->val == cur->next)
	    {
	        prev->next = cur->next;
			delete cur;
	    }
		else
		{
		    prev = cur;
		}

		cur = next;
	}
	
    return head;		 
}

};

