/*******************************************************************************
                           reorder list(Medium)
 *******************************************************************************
 Given a singly linked list L: L0->L1->...Ln-1->Ln,
 reorder it to: L0->Ln->L1->Ln-1->L2->Ln-2->...
 
 You must do this in-place without altering the nodes' values.
 
 For example,
 Given {1,2,3,4}, reorder it to {1,4,2,3}.

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
	 void reorderList(ListNode *head) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************
 1 找到中间节点，慢指针一次走一步，快指针一次走两步，快指针走完，慢指针到中间
 2 从中间断开，把后面一个链表翻转，然后合并两个子链。 Time Limit Exceeded
 ******************************************************************************/


 class Solution {
public:

ListNode *reverse(ListNode *head)
{
    ListNode *head_s,*curr,*next;
	
    if(NULL == head || NULL == head->next) return head;

	head_s = head;
	curr = head->next;
	next = curr->next;

	while(curr->next)
	{
	    curr->next = next->next;
		head_s = next;
		next->next = curr;
	}

    return head_s;
}

/* Time Limit Exceeded */
void reorderList(ListNode *head) 
{
    ListNode *slow,*fast,*prev,*curr,*next1,*next2;

    if(NULL == head || NULL == head->next) return;
	
	slow = head;
	fast = head;

	while(fast && fast->next)
	{
	    prev = slow;
	    slow = slow->next;
		fast = fast->next->next;
	}

	prev->next = NULL;

	/* 后面的链比前面的链多一个节点，或者相同 */

	slow = reverse(slow);

	curr = head;

	while(curr->next)
	{
	    next1 = curr->next;		
		next2 = slow->next;
		
	    curr->next = slow;
		slow->next = next1;

		curr = next1;
		slow = next2;
	}

	curr->next = slow;	
}




};

