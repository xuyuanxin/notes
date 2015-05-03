#ifndef __lk_list_h__
#define __lk_list_h__

#include <inttypes.h>

#include "list_test.h"


struct list_head 
{
    struct list_head *next; 
    struct list_head *prev;
};

struct list_item
{
	union 
	{
		struct _dog dog;
		struct _cat cat;
	};

	union
	{
		void 		*data;
		uint32_t 	uint32;
		int32_t 	int32;
		char 		*str;
	};

	struct list_head list;
};


#define x_offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)


/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr   : the pointer to the member.
 * @type  : the type of the container struct this is embedded in.
 * @member: the name of the member within the struct.
 * line 2 : make compile warning when type conflict
 */
#define container_of(ptr, type, member) ({            \
    const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
    (type *)( (char *)__mptr - x_offsetof(type,member) );})


#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
    struct list_head name = LIST_HEAD_INIT(name)

static inline void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list;
    list->prev = list;
}


/*-----------------------------------------------------------------------------------
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!

    +----------------+
    |      head      |
    |    +------+    |
    +--->| next |----+
         +------+ 
    +----| prev |<---+
    |    +------+    |
    +----------------+
-----------------------------------------------------list_add(new,head,head->next)
    +----------------------------+
    |     new1         head      |
    |   +------+     +------+    |
    +-->| next |---->| next |----+
        +------+     +------+ 
    +---| prev |<----| prev |<---+
    |   +------+     +------+    |
    +----------------------------+ 
-----------------------------------------------------list_add(new,head,head->next)
    +----------------------------------------+
    |     new2        new1         head      |
    |   +------+    +------+     +------+    |
    +-->| next |--->| next |---->| next |----+
        +------+    +------+     +------+ 
    +---| prev |<---| prev |<----| prev |<---+
    |   +------+    +------+     +------+    |
    +----------------------------------------+ 
-------------------------------------------------------------------------------------
    +----------------+
    |      head      |
    |    +------+    |
    +--->| next |----+
         +------+ 
    +----| prev |<---+
    |    +------+    |
    +----------------+
--------------------------------------------------list_add_tail(new,head->prev,head)
    +----------------------------+
    |     head         new1      |
    |   +------+     +------+    |
    +-->| next |---->| next |----+
        +------+     +------+ 
    +---| prev |<----| prev |<---+
    |   +------+     +------+    |
    +----------------------------+ 
--------------------------------------------------list_add_tail(new,head->prev,head)
    +----------------------------------------+
    |     head        new1         new2      |
    |   +------+    +------+     +------+    |
    +-->| next |--->| next |---->| next |----+
        +------+    +------+     +------+ 
    +---| prev |<---| prev |<----| prev |<---+
    |   +------+    +------+     +------+    |
    +----------------------------------------+     
-----------------------------------------------------------------------------------*/
static inline void __list_add(struct list_head *new,
                  struct list_head *prev, struct list_head *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}


/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __list_del(struct list_head * prev, struct list_head * next)
{
    next->prev = prev;
    prev->next = next;
}

/**----------------------------------------------------------------------------------
 * list_add - add a new entry
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
**---------------------------------------------------------------------------------*/
static inline void list_add(struct list_head *new, struct list_head *head)
{
    __list_add(new, head, head->next);
}

/*-----------------------------------------------------------------------------------
list_add_tail - add a new entry
@new: new entry to be added
@head: list head to add it before
@func: Insert a new entry before the specified head. This is useful for implementing 
       queues.
-----------------------------------------------------------------------------------*/
static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
	__list_add(new, head->prev, head);
}

/*----------------------------------------------------------------------------------- 
This function removes the element entry from the list. Note that it does not free any
memory belonging to entry or the data structure in which it is embedded;this function
merely removes the element from the list.
-----------------------------------------------------------------------------------*/
static inline void list_del(struct list_head *entry)
{
    __list_del(entry->prev, entry->next);
    entry->next = NULL/*LIST_POISON1*/;
    entry->prev = NULL/*LIST_POISON2*/;
}

static inline void __list_del_entry(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
}

/*----------------------------------------------------------------------------------- 
 * list_del_init - deletes entry from list and reinitialize it.
 * @entry: the element to delete from the list.

This function behaves the same as list_del() , except it also reinitializes the given
list_head with the rationale that you no longer want the entry in the list, but you -
can reuse the data structure itself.
----------------------------------------------------------------------------------- */
static inline void list_del_init(struct list_head *entry)
{
	__list_del_entry(entry);
	INIT_LIST_HEAD(entry);
}

/*-----------------------------------------------------------------------------------
 * list_empty - tests whether a list is empty
 * @head: the list to test.
 This returns nonzero if the given list is empty; otherwise, it returns zero.
----------------------------------------------------------------------------------- */
static inline int list_empty(const struct list_head *head)
{
	return head->next == head;
}



/**
 * list_entry - get the struct for this entry
 * @ptr:    the &struct list_head pointer.
 * @type:    the type of the struct this is embedded in.
 * @member:    the name of the list_struct within the struct.
 */
#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)



/**
 * list_first_entry - get the first element from a list
 * @ptr:    the list head to take the element from.
 * @type:    the type of the struct this is embedded in.
 * @member:    the name of the list_struct within the struct.
 *
 * Note, that list is expected to be not empty.
 */
#define list_first_entry(ptr, type, member) \
    list_entry((ptr)->next, type, member)

/**
 * list_next_entry - get the next element in list
 * @pos:    the type * to cursor
 * @member:    the name of the list_struct within the struct.
 */
#define list_next_entry(pos, member) \
    list_entry((pos)->member.next, typeof(*(pos)), member)


/**
 * list_last_entry - get the last element from a list
 * @ptr:	the list head to take the element from.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_head within the struct.
 *
 * Note, that list is expected to be not empty.
 */
#define list_last_entry(ptr, type, member) \
	list_entry((ptr)->prev, type, member)
	
/**
 * list_prev_entry - get the prev element in list
 * @pos:	the type * to cursor
 * @member: the name of the list_head within the struct.
 */
#define list_prev_entry(pos, member) \
		list_entry((pos)->member.prev, typeof(*(pos)), member)


/*-----------------------------------------------------------------------------------
 * list_for_each_entry    -    iterate over list of given type
 * @pos:    the type * to use as a loop cursor.
 * @head:    the head for your list.
 * @member:    the name of the list_struct within the struct.

Here, @pos is a pointer to the object containing the list_head nodes. @head is a poi-
nter to the list_head head node from which you want to start iterating. @member is t-
he variable name of the list_head structure in @pos.
-----------------------------------------------------------------------------------*/
#define list_for_each_entry(pos, head, member)                \
    for (pos = list_first_entry(head, typeof(*pos), member);    \
         &pos->member != (head);                    \
         pos = list_next_entry(pos, member))

/*-----------------------------------------------------------------------------------
 * @pos:	   the type * to use as a loop cursor.
 * @head:   the head for your list.
 * @member: the name of the list_head within the struct.
 * @func:   iterate backwards over list of given type. That is , instead of following 
            the next pointers forward through the list , it follows the prev pointers 
            backward. 
-----------------------------------------------------------------------------------*/
#define list_for_each_entry_reverse(pos, head, member)			\
		for (pos = list_last_entry(head, typeof(*pos), member); 	\
			 &pos->member != (head);					\
			 pos = list_prev_entry(pos, member))

/*-----------------------------------------------------------------------------------
 @pos:    the type * to use as a loop cursor.
 @n:      another type * to use as temporary storage
 @head:   the head for your list.
 @member: the name of the list_struct within the struct.
 @func:   iterate over list of given type safe against removal of list entry 
-----------------------------------------------------------------------------------*/
#define list_for_each_entry_safe(pos, n, head, member)            \
        for (pos = list_first_entry(head, typeof(*pos), member),    \
            n = list_next_entry(pos, member);            \
             &pos->member != (head);                    \
             pos = n, n = list_next_entry(n, member))





struct list_item *list_item_create();



#endif
