#include <stdint.h>
#include <stdio.h>

#include "sa_queue.h"
#include "sa_mem.h"

struct sa_que *sa_queue_create(que_dfree dfree, uint32_t size)
{
    struct sa_que *q;

	q = sa_malloc(0, sizeof(*q));
	if(NULL == q)
	{
	    printf("error! queue create fail! \r\n");
		return NULL;
	}

	q->q_dfree = dfree;
	q->q_nums  = 0;
	q->q_size  = size;

	INIT_LIST_HEAD(&q->q_head);

	return q;
}

int sa_enqueue(struct sa_que *q, void *data)
{
	struct sa_que_node *qn;

    if(q->q_nums > q->q_size)
    {
		return QUEERR_FULL;
    }

    qn = sa_queue_node_alloc();
	if(NULL == qn)
	{
	    return QUEERR_NOMEM;
	}

	qn->data = data;

	list_add_tail(&qn->q_node, &q->q_head);
	q->q_nums++;

	return 0;
}

void *sa_dequeue(struct sa_que *q)
{
    void *data;
	struct sa_que_node *qn;
	
    if(list_empty(&q->q_head))
		return NULL;

    qn = list_first_entry(&q->q_head, struct sa_que_node, q_node);
	data = qn->data;
	sa_queue_node_free(qn);
	q->q_nums--;
	return data;
}

struct sa_que_node *sa_queue_node_alloc()
{
   return sa_malloc(0,sizeof(struct sa_que_node));
}

void sa_queue_node_free(void *ptr)
{
   sa_mfree(0,ptr);
}

void sa_queue_show(struct sa_que *q, char *name)
{
    struct sa_que_node *qn;

	printf("%s nums %d",name, q->q_nums);
    list_for_each_entry(qn, &q->q_head, q_node)
    {
        if(NULL != q->q_dshow)
			q->q_dshow(qn->data);
    }
}
