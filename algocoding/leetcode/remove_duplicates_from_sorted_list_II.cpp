/*******************************************************************************
                Remove Duplicates from Sorted List II(Medium)
 *******************************************************************************
 Given a sorted linked list, delete all nodes that have duplicate numbers, leaving 
 only distinct numbers from the original list.
 
 For example,
 Given 1->2->3->3->4->4->5, return 1->2->5.
 Given 1->1->1->2->3, return 2->3.
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
    ListNode *single, *del,*prev,*cur,*next,lhead(-1);
   
    if (head == nullptr) return nullptr;
    
	lhead.next = head;
	prev = head;
	cur = head->next;
	del = nullptr;
	single = &lhead;

	while(nullptr != cur)
	{
	    next = cur->next;
		
	    if(prev->val == cur->val)
	    {
	        del = prev;
			prev->next = cur->next;
			delete cur;	
	    }
		else
		{		    
			if(del == prev)
			{
			    single->next = prev->next;
			    delete del;
				del = nullptr;
			}
			else
			{
			    single = prev;
			}

			prev = cur;
		}

		cur = next;
	}
	
	if(nullptr != del)
	{
	    single->next = prev->next;
		delete del;
	}

	return lhead->next;   
}

};

