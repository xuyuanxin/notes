#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"queue.h"


queue_s *test_queue;


void queue_test_01()
{
    int key = 0xffffffff;
	
    test_queue = queue_create(NULL,5);

    if(NULL == test_queue)
		return;	
	
    enqueue(test_queue,1,NULL);
    enqueue(test_queue,2,NULL);
    enqueue(test_queue,3,NULL);
    enqueue(test_queue,4,NULL);
    enqueue(test_queue,5,NULL);
    enqueue(test_queue,6,NULL);

	queue_show(test_queue);

	dequeue(test_queue,&key,NULL);
	printf("\r\nread queue key:%d",key);

	dequeue(test_queue,&key,NULL);
	printf("\r\nread queue key:%d",key);
	
	dequeue(test_queue,&key,NULL);
	printf("\r\nread queue key:%d",key);
	
	dequeue(test_queue,&key,NULL);
	printf("\r\nread queue key:%d",key);
	
	dequeue(test_queue,&key,NULL);
	printf("\r\nread queue key:%d",key);

	dequeue(test_queue,&key,NULL);
	printf("\r\nread queue key:%d",key);
	
	queue_show(test_queue);

	queue_destory(test_queue);
}


void queue_test()
{

	queue_test_01();
}

#if 0
int main()
{
    queue_test_main();
}
#endif
