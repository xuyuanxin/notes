/*******************************************************************************
                         Sort List(Medium) 
 *******************************************************************************
 Sort a linked list in O(n log n) time using constant space complexity.
 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 ListNode *sortList(ListNode *head) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************
 ³£Êý¿Õ¼äÇÒ O(nlogn)£¬µ¥Á´±íÊÊºÏÓÃ¹é²¢ÅÅÐò£¬Ë«ÏòÁ´±íÊÊºÏÓÃ¿ìËÙÅÅÐò¡£±¾Ìâ¿ÉÒÔ¸´
 ÓÃ¡±Merge Two Sorted Lists¡±µÄ´úÂë¡£
 ******************************************************************************/
/**
* Definition for singly-linked list.
* struct ListNode {
* 	int val;
* 	ListNode *next;
* 	ListNode(int x) : val(x), next(NULL) {}
* };
*/
class Solution {
public:
ListNode *sortList(ListNode *head) {
	if (head == NULL || head->next == NULL)return head;

	ListNode *fast = head, *slow = head;
	
	while (fast->next != NULL && fast->next->next != NULL) {
	    fast = fast->next->next;
	    slow = slow->next;
	}

	fast = slow;
	slow = slow->next;
	fast->next = NULL;
	
	ListNode *l1 = sortList(head);
	ListNode *l2 = sortList(slow);
	
	return mergeTwoLists(l1, l2);
}

// Merge Two Sorted Lists
ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
	ListNode dummy(-1);
	
	for (ListNode* p = &dummy; l1 != nullptr || l2 != nullptr; p = p->next) {
	    int val1 = l1 == nullptr ? INT_MAX : l1->val;
	    int val2 = l2 == nullptr ? INT_MAX : l2->val;
		
	    if (val1 <= val2) {
	        p->next = l1;
	        l1 = l1->next;
	    } else {
	        p->next = l2;
	        l2 = l2->next;
	    }
	}
	
	return dummy.next;
}

};
