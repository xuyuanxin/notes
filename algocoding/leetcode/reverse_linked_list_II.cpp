/*******************************************************************************
                           reverse_linked_list_II 
********************************************************************************
Reverse a linked list from position m to n. Do it in-place and in one-pass.

For example:
Given 1->2->3->4->5->NULL, m = 2 and n = 4,

return 1->4->3->2->5->NULL.

Note:
Given m, n satisfy the following condition:
1 <= m =<= n <= length of list.
********************************************************************************
                    Definition for singly-linked list.
********************************************************************************
struct ListNode 
{
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
};
 
class Solution {
public:
    ListNode *reverseBetween(ListNode *head, int m, int n) {
        
    }
};
********************************************************************************
                            algo
********************************************************************************
header->1->2->3->4->5->NULL
为了反转这个单链表，我们先让头结点的next域指向结点2，再让结点1的next域指向结点3，
最后将结点2的next域指向结点1，就完成了第一次交换，顺序就变成了
        Header-结点2-结点1-结点3-结点4-NULL，
然后进行相同的交换将结点3移动到结点2的前面，然后再将结点4移动到结点3的前面就完成
了反转

形象的解释:现在一队人手拉手的站成一排，张一是队长
老大对张一说: 张一把你的下一个兄弟张二叫来，你拉住张二的下一个兄弟
老大对张二说: 张二现在你是小队长了，拉住张一的手
老大对张一说: 再把你的下一个兄弟张三叫来，你拉住张三的下一个兄对
老大对张三说: 张三现在你是小队长了，拉住张一的手
...
*******************************************************************************/

struct ListNode 
{
	  int val;
	  ListNode *next;
	  ListNode(int x) : val(x), next(NULL) {}
};


// LeetCode, Reverse Linked List II
//  time O(n), mem O(1)
class Solution {
public:
ListNode *reverseBetween(ListNode *head, int m, int n) 
{
    ListNode dummy(-1);
    dummy.next = head;
    ListNode *prev = &dummy;
	
    for (int i = 0; i < m-1; ++i)
        prev = prev->next; 
	
    ListNode* const head2 = prev;
    prev = head2->next;
    ListNode *cur = prev->next;

/* 此时
   head2 指向 m 的前一个节点，此后head2一直不变，但节点位置会变
   prev  指向 m 节点
   cur   指向 m 的下一个节点
*/
    for (int i = m; i < n; ++i) 
	{
        prev->next = cur->next;
        cur->next = head2->next;
        head2->next = cur; 
        cur = prev->next;
    }
	
    return dummy.next;
}

ListNode *reverseBetween2(ListNode *head, int m, int n)
{
	int i;
	ListNode  lhead(-1);
	ListNode *rhead = NULL;
	ListNode *cur	= NULL;
	ListNode *pre	= NULL;

	if(NULL == head)
	{
		return NULL;
	}
	
	lhead.next = head;
	pre = &lhead;
	
	for(i = 0; i < m-1; ++i)
	{
		pre = pre->next;
	}

	rhead = pre;	 /* rhead 指向 m 的前一个节点(有可能是lhead) */
	pre = pre->next; /* pre   指向 m 节点(不为空)*/
	cur = pre->next; /* cur   指向 m 的下一个节点 */

	for(i = m; i < n; ++i)
	{
		if(NULL == cur)
			break;
		
		pre->next = cur->next;
		cur->next = rhead->next;
		rhead->next = cur;
		cur = pre->next;
	}

	return lhead.next;
}



};

