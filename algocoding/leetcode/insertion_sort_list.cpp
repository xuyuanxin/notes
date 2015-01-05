/*******************************************************************************
                         Insertion Sort List(Medium) 
 *******************************************************************************
 Sort a linked list using insertion sort.
 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
 ListNode *insertionSortList(ListNode *head) {
 
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
ListNode *insertionSortList(ListNode *head) {
    ListNode dummy(INT_MIN);
    //dummy.next = head;
    for (ListNode *cur = head; cur != nullptr;) {
        auto pos = findInsertPos(&dummy, cur->val);
        ListNode *tmp = cur->next;
        cur->next = pos->next;
        pos->next = cur;
        cur = tmp;
    }
	
    return dummy.next;
}


/* curÊÇ¿Õ£¬»òÕßÊÇµÚÒ»¸ö´óÓÚxµÄ½Úµã¡£
   keyÖµÎªxµÄ½Úµã£¬²åÈëµ½preµÄºóÃæ*/
ListNode* findInsertPos(ListNode *head, int x) {
    ListNode *pre = nullptr;
	
    for (ListNode *cur = head; cur != nullptr && cur->val <= x;pre = cur, cur = cur->next)
        ;
	
    return pre;
}


};
