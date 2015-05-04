							 
/* internal pointer magic utilities */				 
/* static inline */ emu_hashtable_bucket_item *emu_hashtable_bucket_items__head2elem(emu_hashtable_bucket_item_root *root) {		 
	return(list__magic(root, emu_hashtable_bucket_item_root, head, emu_hashtable_bucket_item, link));	 
}								 
/* static inline */ emu_hashtable_bucket_item *emu_hashtable_bucket_items__tail2elem(emu_hashtable_bucket_item_root *root) {		 
	return(list__magic(root, emu_hashtable_bucket_item_root, tail, emu_hashtable_bucket_item, link));	 
}								 
/* static inline */ emu_hashtable_bucket_item_root *emu_hashtable_bucket_items__elem2head(emu_hashtable_bucket_item *elem) {		 
	return(list__magic(elem, emu_hashtable_bucket_item, link, emu_hashtable_bucket_item_root, head));	 
}								 
/* static inline */ emu_hashtable_bucket_item_root *emu_hashtable_bucket_items__elem2tail(emu_hashtable_bucket_item *elem) {		 
	return(list__magic(elem, emu_hashtable_bucket_item, link, emu_hashtable_bucket_item_root, tail));	 
}								 
								 
/* initializers */						 
/* static inline */ void emu_hashtable_bucket_items_init(emu_hashtable_bucket_item_root *root) {			 
	root->head.next = emu_hashtable_bucket_items__tail2elem(root);		 
	root->head.prev = root->tail.next = NULL;		 
	root->tail.prev = emu_hashtable_bucket_items__head2elem(root);		 
}								 
/* static inline */ void emu_hashtable_bucket_items_init_link(emu_hashtable_bucket_item *elem) {		 
	elem->link.next = elem->link.prev = NULL;		 
}								 
								 
/* accessor functions */					 
/* static inline */ emu_hashtable_bucket_item *emu_hashtable_bucket_items_first(emu_hashtable_bucket_item_root *root) {		 
	return(root->head.next);				 
}								 
/* static inline */ emu_hashtable_bucket_item *emu_hashtable_bucket_items_last(emu_hashtable_bucket_item_root *root) {		 
	return(root->tail.prev);				 
}								 
/* static inline */ emu_hashtable_bucket_item *emu_hashtable_bucket_items_next(emu_hashtable_bucket_item *elem) {		 
	return(elem->link.next);				 
}								 
/* static inline */ emu_hashtable_bucket_item *emu_hashtable_bucket_items_prev(emu_hashtable_bucket_item *elem) {		 
	return(elem->link.prev);				 
}								 
								 
/* predicates */						 
/* static inline */ bool emu_hashtable_bucket_items_empty(emu_hashtable_bucket_item_root *root) {			 
	return(root->head.next->link.next == NULL);		 
}								 
/* static inline */ bool emu_hashtable_bucket_items_iselem(emu_hashtable_bucket_item *elem) {		 
	return(elem->link.next != NULL && elem->link.prev != NULL); 
}								 
/* static inline */ bool emu_hashtable_bucket_items_ishead(emu_hashtable_bucket_item *elem) {		 
	return(elem->link.next != NULL && elem->link.prev == NULL); 
}								 
/* static inline */ bool emu_hashtable_bucket_items_istail(emu_hashtable_bucket_item *elem) {		 
	return(elem->link.next == NULL && elem->link.prev != NULL); 
}								 
/* static inline */ bool emu_hashtable_bucket_items_isunlinked(emu_hashtable_bucket_item *elem) {		 
	return(elem->link.next == NULL && elem->link.prev == NULL); 
}								 
/* faster but less safe predicates for looping */		 
/* static inline */ bool emu_hashtable_bucket_items_athead(emu_hashtable_bucket_item *elem) {		 
	return(elem->link.prev == NULL);			 
}								 
/* static inline */ bool emu_hashtable_bucket_items_attail(emu_hashtable_bucket_item *elem) {		 
	return(elem->link.next == NULL);			 
}								 
/* slightly more complicated predicates */			 
/* static inline */ bool emu_hashtable_bucket_items_isfirst(emu_hashtable_bucket_item *elem) {		 
	return(emu_hashtable_bucket_items_athead(emu_hashtable_bucket_items_prev(elem)));		 
}								 
/* static inline */ bool emu_hashtable_bucket_items_islast(emu_hashtable_bucket_item *elem) {		 
	return(emu_hashtable_bucket_items_attail(emu_hashtable_bucket_items_next(elem)));		 
}								 
								 
/* internal list manipulation */				 
/* static inline */ void emu_hashtable_bucket_items__splice_before			 
		(emu_hashtable_bucket_item *elem, emu_hashtable_bucket_item *newX0, emu_hashtable_bucket_item *newXN) {	 
	newX0->link.prev = elem->link.prev;			 
	newXN->link.next = elem;					 
	elem->link.prev->link.next = newX0;			 
	elem->link.prev = newXN;					 
}								 
/* static inline */ void emu_hashtable_bucket_items__splice_after				 
		(emu_hashtable_bucket_item *elem, emu_hashtable_bucket_item *newX0, emu_hashtable_bucket_item *newXN) {	 
	newXN->link.next = elem->link.next;			 
	newX0->link.prev = elem;					 
	elem->link.next->link.prev = newXN;			 
	elem->link.next = newX0;					 
}								 
/* static inline */ void emu_hashtable_bucket_items__unsplice(emu_hashtable_bucket_item *old0, emu_hashtable_bucket_item *oldN) { 
	old0->link.prev->link.next = oldN->link.next;		 
	oldN->link.next->link.prev = old0->link.prev;		 
}								 
								 
/* single element manipulation */				 
/* static inline */ void emu_hashtable_bucket_items_insert_before(emu_hashtable_bucket_item *elem, emu_hashtable_bucket_item *newX) { 
	emu_hashtable_bucket_items__splice_before(elem, newX, newX);			 
}								 
/* static inline */ void emu_hashtable_bucket_items_insert_after(emu_hashtable_bucket_item *elem, emu_hashtable_bucket_item *newX) { 
	emu_hashtable_bucket_items__splice_after(elem, newX, newX);			 
}								 
/* static inline */ void emu_hashtable_bucket_items_insert_first(emu_hashtable_bucket_item_root *root, emu_hashtable_bucket_item *newX) { 
	emu_hashtable_bucket_items_insert_before(root->head.next, newX);		 
	/* or emu_hashtable_bucket_items_insert_after(emu_hashtable_bucket_items__head2elem(root), newX); */ 
}								 
/* static inline */ void emu_hashtable_bucket_items_insert_last(emu_hashtable_bucket_item_root *root, emu_hashtable_bucket_item *newX) { 
	emu_hashtable_bucket_items_insert_after(root->tail.prev, newX);		 
	/* or emu_hashtable_bucket_items_insert_before(emu_hashtable_bucket_items__tail2elem(root), newX); */ 
}								 
/* static inline */ void emu_hashtable_bucket_items_remove(emu_hashtable_bucket_item *elem) {		 
	emu_hashtable_bucket_items__unsplice(elem, elem);				 
	emu_hashtable_bucket_items_init_link(elem);					 
}								 
/* static inline */ emu_hashtable_bucket_item *emu_hashtable_bucket_items_remove_first(emu_hashtable_bucket_item_root *root) {	 
	emu_hashtable_bucket_item *elem = emu_hashtable_bucket_items_first(root);			 
	if(emu_hashtable_bucket_items_attail(elem)) return(NULL);			 
	emu_hashtable_bucket_items_remove(elem);					 
	return(elem);						 
}								 
/* static inline */ emu_hashtable_bucket_item *emu_hashtable_bucket_items_remove_last(emu_hashtable_bucket_item_root *root) {	 
	emu_hashtable_bucket_item *elem = emu_hashtable_bucket_items_last(root);			 
	if(emu_hashtable_bucket_items_athead(elem)) return(NULL);			 
	emu_hashtable_bucket_items_remove(elem);					 
	return(elem);						 
}								 
/* static inline */ void emu_hashtable_bucket_items_remove_next(emu_hashtable_bucket_item *elem) {		 
	elem = emu_hashtable_bucket_items_next(elem);				 
	if(!emu_hashtable_bucket_items_attail(elem)) emu_hashtable_bucket_items_remove(elem);		 
}								 
/* static inline */ void emu_hashtable_bucket_items_remove_prev(emu_hashtable_bucket_item *elem) {		 
	elem = emu_hashtable_bucket_items_prev(elem);				 
	if(!emu_hashtable_bucket_items_athead(elem)) emu_hashtable_bucket_items_remove(elem);		 
}								 
								 
/* concatenation etc. */					 
/* static inline */ void emu_hashtable_bucket_items_concat(emu_hashtable_bucket_item_root *dst, emu_hashtable_bucket_item_root *src) {	 
	emu_hashtable_bucket_item *elem0 = emu_hashtable_bucket_items_first(src);			 
	emu_hashtable_bucket_item *elemN = emu_hashtable_bucket_items_last(src);			 
	if(emu_hashtable_bucket_items_attail(elem0)) return;			 
	emu_hashtable_bucket_items__unsplice(elem0, elemN);				 
	emu_hashtable_bucket_items__splice_after(dst->tail.prev, elem0, elemN);	 
}								 
								 
/* safe magic for the user */					 
/* static inline */ emu_hashtable_bucket_item_root *emu_hashtable_bucket_items_getroot(emu_hashtable_bucket_item *elem) {		 
	if(emu_hashtable_bucket_items_ishead(elem))	return(emu_hashtable_bucket_items__elem2head(elem)); 
	if(emu_hashtable_bucket_items_istail(elem))	return(emu_hashtable_bucket_items__elem2tail(elem)); 
	return(NULL);						 
}								 
								 
/* looping operations */					 
/* static inline */ emu_hashtable_bucket_item_root *emu_hashtable_bucket_items_findroot_fwd(emu_hashtable_bucket_item *elem) {	 
	while(!emu_hashtable_bucket_items_attail(elem))				 
		elem = emu_hashtable_bucket_items_next(elem);			 
	return(emu_hashtable_bucket_items__elem2tail(elem));			 
}								 
/* static inline */ emu_hashtable_bucket_item_root *emu_hashtable_bucket_items_findroot_rev(emu_hashtable_bucket_item *elem) {	 
	while(!emu_hashtable_bucket_items_athead(elem))				 
		elem = emu_hashtable_bucket_items_prev(elem);			 
	return(emu_hashtable_bucket_items__elem2head(elem));			 
}								 
/* static inline */ int emu_hashtable_bucket_items_length(emu_hashtable_bucket_item_root *root) {			 
	emu_hashtable_bucket_item *elem; int i;					 
	for(elem = emu_hashtable_bucket_items_first(root), i = 0;			 
	    !emu_hashtable_bucket_items_attail(elem);				 
	    elem = emu_hashtable_bucket_items_next(elem), i++);			 
	return(i);						 
}								 
/* static */ void emu_hashtable_bucket_items_qsort_r(emu_hashtable_bucket_item_root *root, void *arg,		 
		int (*cmp)(void *, emu_hashtable_bucket_item *, emu_hashtable_bucket_item *)) {	 
	emu_hashtable_bucket_item *pivot, *elem;					 
	emu_hashtable_bucket_item_root one, two, three;					 
	int c;							 
								 
	emu_hashtable_bucket_items_init(&one);					 
	emu_hashtable_bucket_items_init(&two);					 
	emu_hashtable_bucket_items_init(&three);					 
								 
	pivot = emu_hashtable_bucket_items_remove_first(root);			 
	if(pivot == NULL) return;				 
	emu_hashtable_bucket_items_insert_last(&two, pivot);			 
								 
	while(elem = emu_hashtable_bucket_items_remove_first(root), elem != NULL) {	 
		c = cmp(arg, pivot, elem);			 
		if(c > 0)					 
			emu_hashtable_bucket_items_insert_last(&one, elem);		 
		else						 
		if(c < 0)					 
			emu_hashtable_bucket_items_insert_last(&three, elem);	 
		else						 
			emu_hashtable_bucket_items_insert_last(&two, elem);		 
	}							 
	emu_hashtable_bucket_items_qsort_r(&one, arg, cmp);				 
	emu_hashtable_bucket_items_qsort_r(&three, arg, cmp);			 
	emu_hashtable_bucket_items_concat(root, &one);				 
	emu_hashtable_bucket_items_concat(root, &two);				 
	emu_hashtable_bucket_items_concat(root, &three);				 
}								 
/* static */ int emu_hashtable_bucket_items_qsort_cmp(void *a, emu_hashtable_bucket_item *e1, emu_hashtable_bucket_item *e2) {	 
	/* function pointers can't be portably cast to void pointers */ 
	int (**arg)(emu_hashtable_bucket_item *, emu_hashtable_bucket_item *) = a;			 
	int (*cmp)(emu_hashtable_bucket_item *, emu_hashtable_bucket_item *) = *arg;			 
	return(cmp(e1,e2));					 
}								 
/* static inline */ void emu_hashtable_bucket_items_qsort					 
		(emu_hashtable_bucket_item_root *root, int (*cmp)(emu_hashtable_bucket_item *, emu_hashtable_bucket_item *)) { 
	emu_hashtable_bucket_items_qsort_r(root, &cmp, emu_hashtable_bucket_items_qsort_cmp);		 
}								 
								 
/* memory handling */						 
/* static inline */ emu_hashtable_bucket_item_root *emu_hashtable_bucket_items_create(void) {			 
	emu_hashtable_bucket_item_root *root = xalloc(sizeof(*root));			 
	emu_hashtable_bucket_items_init(root);					 
	return(root);						 
}								 
/* static inline */ void emu_hashtable_bucket_items_destroy(emu_hashtable_bucket_item_root *root) {		 
	emu_hashtable_bucket_item *elem;						 
	if(root == NULL) return;				 
	while(elem = emu_hashtable_bucket_items_remove_first(root), elem != NULL)	 
		xfree(elem, sizeof(*elem));			 
	xfree(root, sizeof(*root));				 
}								 

/*----------------------------------------------------------------------------------*/

