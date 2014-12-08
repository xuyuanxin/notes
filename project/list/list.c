#if 0
#define offsetof(TYPE, MEMBER) ((unsigned long) &((TYPE *)0)->MEMBER)


#define container_of(ptr, type, member) ({			\
        const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
        (type *)( (char *)__mptr - offsetof(type,member) );})



#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)



typedef struct list_head_tag 
{
	struct list_head *next;
	struct list_head *prev;
}list_head_t;

void __list_add(list_head_t *new,list_head_t *prev,list_head_t *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

/*把new加入head之前  new -> head -> others*/
void list_add_before_head(list_head_t *new,list_head_t *head)
{
	__list_add(new, head, head->next);
}

/*把new加入head之后 head -> new -> others*/
void list_add_after_head(list_head_t *new, list_head_t *head)
{
	__list_add(new, head->prev, head);
}

void list_add(list_head_t *new, list_head_t *head)
{
    list_add_after_head(new,head);
}

void list_del(list_head_t *entry)
{
    list_head_t *prev = entry->prev;
	list_head_t *next = entry->next;
	
	next->prev = prev;
	prev->next = next;

	if(entry != entry->next){
	    entry->next = 0xffffffff;
	    entry->prev = 0xffffffff;
	}
}

#endif


