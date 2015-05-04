/* http://blog.csdn.net/hs794502825/article/details/24597773 */
/* pidhash_init */

struct hlist_head 
{
	struct hlist_node *first;
};

struct hlist_node 
{
	struct hlist_node *next;
	struct hlist_node **pprev;
};

#define INIT_HLIST_HEAD(ptr) ((ptr)->first = NULL)

/*-----------------------------------------------------------------------------------
+-------+
| first |----> NULL
+-------+
                  n1
+-------+     +-------+
| first |---->| next  |---->NULL
+-------+     |-------+
 &h.first<----| pprev |
              +-------+

                  n2           n1           
+-------+     +-------+     +-------+
| first |---->| next  |---->| next  |
+-------+     |-------+     |-------|
 &h.first<----| pprev |<----| pprev |
              +-------+     +-------+

                  n3           n2           n1
+-------+     +-------+     +-------+     +-------+
| first |---->| next  |---->| next  |---->| next  |
+-------+     |-------+     |-------|     |-------|
 &h.first<----| pprev |<----| pprev |<----| pprev |
              +-------+     +-------+     +-------+

-----------------------------------------------------------------------------------*/
static inline void hlist_add_head(struct hlist_node *n, struct hlist_head *h)
{
	struct hlist_node *first = h->first;
	n->next = first;
	if (first)
		first->pprev = &n->next;
	h->first = n;
	n->pprev = &h->first;
}

