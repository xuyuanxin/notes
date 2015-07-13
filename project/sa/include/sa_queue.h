#ifndef __SA_QUEUE_H__
#define __SA_QUEUE_H__

#include "sa_list.h"

#define QUEERR_FULL  1
#define QUEERR_NOMEM 2

typedef void (*que_dfree)(void *data); 
typedef void (*que_dshow)(void *data); 


struct sa_que
{
    uint32_t q_nums;
	uint32_t q_size;
	que_dfree q_dfree;
	que_dshow q_dshow;
	struct list_head q_head;
};


struct sa_que_node
{
    void *data;
	struct list_head q_node;
};


struct sa_que *sa_queue_create(que_dfree dfree, uint32_t size);

int sa_enqueue(struct sa_que *q, void *data);

void *sa_dequeue(struct sa_que *q);

struct sa_que_node *sa_queue_node_alloc();

void sa_queue_node_free(void *ptr);

void sa_queue_show(struct sa_que *q, char *name);


#endif
