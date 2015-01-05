/*******************************************************************************
                         Merge k Sorted Lists(Hard) 
 *******************************************************************************
 Merge k sorted linked lists and return it as one sorted list. Analyze and describe 
 its complexity.
 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************
 
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
ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
    ListNode dummy(-1);
    if (l1 == nullptr) return l2;
    if (l2 == nullptr) return l1;
	
    ListNode *p = &dummy;
	
    for (; l1 != nullptr && l2 != nullptr; p = p->next) {
        if (l1->val > l2->val){ 
			p->next = l2; 
			l2 = l2->next; 
		} else { 
		    p->next = l1; 
			l1 = l1->next; 
		}
    }
	
    p->next = (l1 != nullptr? l1 : l2);
	
    return dummy.next;
} 

ListNode *mergeKLists(vector<ListNode *> &lists) {
    ListNode *p = nullptr;
	
	if (lists.size() == 0) return nullptr;

	p = lists[0];
	
    for (int i = 1; i < lists.size(); i++) {
        p = mergeTwoLists(p, lists[i]);
    }
	
    return p;
}




};

