/*基于数组的队列实现*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"queue.h"

queue_s *queue_create(char *name,int size)
{
    queue_s *queue = NULL;
	int memsize = sizeof(queue_s) + sizeof(queue_node)*size;
	
    queue = (queue_s *)malloc(memsize);
		
	if(NULL == queue)
	{
	    printf("\r\nError queue create fail!");
		return NULL;
	}

	memset(queue,0,memsize);

	queue->q_w_idx = 0;
	queue->q_r_idx = 0;
	queue->q_count = 0;
    queue->q_size  = size;

	return queue;
}

void queue_destory(queue_s *queue)
{
    (void)free(queue);
}

int queue_full(queue_s *queue)
{
}

int queue_empty(queue_s *queue)
{
}


/*写队列 成功返回1 失败返回0*/
int enqueue(queue_s *queue,int key,void *data)
{
    int i;

	if(NULL==queue)
	{
        printf("\r\nError enqueue; input para error");
		return 0;	    
	}	
	
    if(queue->q_count >= queue->q_size)
    {
        printf("\r\nError enqueue; queue full count:%d size:%d",queue->q_count,queue->q_size);
		return 0;
    }
	
	i = queue->q_w_idx%queue->q_size;
	queue->q_node[i].qn_key = key;	
	queue->q_node[i].qn_data = data;

	queue->q_count++;
	queue->q_w_idx++;

	return 1;
}

/*读队列(fifo) 成功返回1 失败返回0*/
int dequeue(queue_s *queue,int *key,void **data)
{
    int i = 0;

	if(NULL == queue)
	{
        printf("\r\nError dequeue; input para error 0x%x 0x%x",queue,key);
		return 0;	    
	}
	
    if(queue->q_count <= 0)
    {
        printf("\r\nError dequeue; queue empty count:%d",queue->q_count);
		return 0;
    }

	i = queue->q_r_idx%queue->q_size;

    if(NULL != key)
	    *key = queue->q_node[i].qn_key;

	if((NULL != data) &&(NULL != *data))
		*data = queue->q_node[i].qn_data;

    queue->q_count--;
	queue->q_r_idx++;

	return 1;
}

void queue_show(queue_s *queue)
{
	if(NULL == queue)
	{
        printf("\r\nError queue show; input para error");
		return ;	    
	}

	printf("\r\nqueue %s info",queue->q_name);	
	printf("\r\nw_idx:%d",queue->q_w_idx);
	printf("\r\nr_idx:%d",queue->q_r_idx);
	printf("\r\nsize:%d",queue->q_size);
	printf("\r\ncount:%d",queue->q_count);
}
