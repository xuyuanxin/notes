/*******************************************************************************
                             Rotate List(Medium)
 *******************************************************************************
 Given a list, rotate the list to the right by k places, where k is non-negative.
 
 For example:
 Given 1->2->3->4->5->NULL and k = 2,
 return 4->5->1->2->3->NULL.
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
	 ListNode *rotateRight(ListNode *head, int k) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************
 首先遍历链表得出节点个数能n，把尾节点指向头形成一个环，再接着往后走n-k步，断开
 链表，返回新的头节点。
 ******************************************************************************/


 class Solution {
 public:

ListNode *rotateRight(ListNode *head, int k)
{
    ListNode *cur = NULL;
    int nums = 0,i;

	if(NULL == head)
		return NULL;

	cur  = head;
	nums = 1;

	while(cur->next)
	{
	    nums++;
		cur = cur->next;
	}

	cur->next = head;

	k = nums - (k%nums);

	for(i = 0; i < k; ++i)
	{
	    cur = cur->next;
	}

	head = cur->next; /* new header */
	cur->next = NULL;

	return head;	
}

};

