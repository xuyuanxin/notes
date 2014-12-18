/*******************************************************************************
                      Reverse Nodes in k-Group(Hard)
 *******************************************************************************
 Given a linked list, reverse the nodes of a linked list k at a time and return 
 its modified list.
 If the number of nodes is not a multiple of k then left-out nodes in the end 
 should remain as it is.
 You may not alter the values in the nodes, only nodes itself may be changed.
 Only constant memory is allowed.
 
 For example,
 Given this linked list: 1->2->3->4->5 
 For k = 2, you should return: 2->1->4->3->5 
 For k = 3, you should return: 3->2->1->4->5
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
	 ListNode *reverseKGroup(ListNode *head, int k) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************
 翻转的过程中更新头节点(翻转k个更新一次)，代码中用khead表示头

 1 先定义1个表头，让khead指向它
 2 取出链表前k个节点，然后翻转，之后让khead指向这k个节点中的最后一个(翻转后的)
 3 重复步骤2，同时注意不足k的情况。
 ******************************************************************************/

 class Solution {
 public:

ListNode *reverseKGroup(ListNode *head, int k)
{
    ListNode lhead(-1),*curr,*khead,*kbeg,*temp,*next;
	int i;

	if(NULL == head) return NULL;
	if(k < 2) return head;

	lhead.next = head;
	khead = &lhead;
	curr = head;

	while(curr)
	{
	    kbeg = curr;
		
	    for(i = 1; i < k && curr; i++)
			curr = curr->next;
		
		if(NULL == curr) break; /* 不足k个 */
		
		temp = curr->next;
	
        /* 翻转从kbeg到curr的节点 */
		next = kbeg->next;
		while(kbeg->next != curr)
		{
			kbeg->next = next->next;
			next->next = khead->next;
			khead->next = next;
			next = kbeg->next;
		}

		kbeg->next = next->next;
		next->next = khead->next;
		khead->next = next;
		khead = kbeg;

		if(NULL == temp)
			break;

		curr = temp;
	}
    
	return lhead.next;
}


/*
Time Limit Exceeded
Last executed input:	{1,2,3}, 4
*/
ListNode *reverseKGroup2(ListNode *head, int k)
{
    ListNode lhead(-1),*curr,*next,*khead;
	int i;

	if(NULL == head) return NULL;
	if(1 == k) return head;

	lhead.next = head;
	khead = &lhead;
	curr = lhead.next;
	next = curr->next;

	i = 1;
	
	while(curr->next)
	{
        curr->next = next->next;
		next->next = khead->next;
		khead->next = next;

		i++;
		
        if(i == k)
        {
           khead = curr;
		   curr = curr->next;
		   i = 1;
        }

		next = (curr == NULL? NULL:curr->next);
		if(NULL == curr) break;
	}

	/* 节点个数是k的整数倍 此时curr==NULL i==1(nodenums/k余数为1，此时i也是1)*/

	if( NULL != curr )
	{
	    curr = khead->next;
		next = curr->next;
		
		while(curr->next)
		{
			curr->next = next->next;
			next->next = khead->next;
			khead->next = next;
		}
	}

	return lhead.next;
}



 };


/*
Input:	{1,2}, 3
Output:	{2,1}
Expected:	{1,2}

Runtime Error
{1,2}, 2

Time Limit Exceeded
Last executed input:	{1,2,3}, 4

*/

