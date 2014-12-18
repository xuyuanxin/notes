/*******************************************************************************
                   Remove Nth Node From End of List(Easy)
 *******************************************************************************
 Given a linked list, remove the nth node from the end of list and return its head.
 
 For example,
	Given linked list: 1->2->3->4->5, and n = 2.
	After removing the second node from the end, the linked list becomes 1->2->3->5.
 Note:
 Given n will always be valid.
 Try to do this in one pass.
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
	 ListNode *removeNthFromEnd(ListNode *head, int n) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************
 设置两个指针p q，p先走n步，然后p q一起走，p走到尾后，删除q->next
 ******************************************************************************/


 class Solution {
 public:

ListNode *removeNthFromEnd(ListNode *head, int n) 
{
    ListNode *del,*p,*q=NULL;
	int i;

	if(NULL == head) return NULL;
	if(0 == n) return head;

	p = head;

	for(i = 0; i < n-1; ++i)
		p = p->next;

    q = NULL;
	
	while(p->next)
	{
	    p = p->next;

		if(NULL == q)
			q = head;
		else
		    q = q->next;
	}

	if(NULL == q)
	{
	    del = head;
		head = head->next;
	}
	else
	{
	    del = q->next;
	    q->next = q->next->next;
	}
	
	delete del;

	return  head;
}

 };


