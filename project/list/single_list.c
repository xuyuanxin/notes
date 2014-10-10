/*singly linked list*/
#include<stdio.h>  /*printf*/
#include<stdlib.h> /*malloc free*/



typedef struct sll_node_tag
{
    struct sll_node_tag *next;
	int key;
}sll_node;


typedef struct sll_ctrl_tag
{
    struct sll_node_tag *head;
	struct sll_node_tag *tail;
	int nums;
}sll_ctrl;


sll_ctrl *sll_create()
{
    sll_ctrl *sll_list;

	sll_list = (sll_ctrl *)malloc(sizeof(sll_ctrl));

	if(NULL != sll_list)
	{
	    sll_list->head = NULL;
		sll_list->tail = NULL;
		sll_list->nums = 0;
	}

	return sll_list;
}

void sll_destory(sll_ctrl *list,int free_ctrl)
{
	sll_node *cur;
	sll_node *f;

	if(NULL == list)
		return;
	
	cur = list->head;

	while(NULL != cur)
	{
	    f   = cur;
		cur = cur->next;
	    free(f);
	}

	if(free_ctrl)
	    free(list);
}


void sll_init(sll_ctrl *list)
{
    list->head = NULL;
	list->tail = NULL;
	list->nums = 0;
}

/*在链表@list中查找关键字@key,找到返回@key所在节点，没找到返回NULL。
  @pre是@key所在节点的前一个节点(有返回，没有返回NULL) @pre参数可以
  传NULL，表示不需要返回前一节点。*/
sll_node *sll_search(sll_ctrl *list,int key,sll_node **prenode)
{
    sll_node *cur;	
    sll_node *pre;

	cur = list->head;
	pre = NULL;

	while(NULL != cur)
	{
	    if(cur->key == key)
			break;

		pre = cur;
		cur = cur->next;
	}

	if(NULL == cur)
		pre = NULL;

	if(NULL != prenode)
	    *prenode = pre;
		
	return cur;
}

/*把关键字@key加入链表@list的头部 return 0:0k -1:error*/
int sll_insert(sll_ctrl *list,int key)
{
    sll_node *list_head;
	sll_node *newnode = NULL;

	if(NULL != sll_search(list,key,NULL))
	{
	    printf("\r\nsll insert info key %d already in list",key);
		return 0;
	}

	newnode = (sll_node *)malloc(sizeof(sll_node));

    newnode->key  = key;
	newnode->next = NULL;
	
	if(NULL == newnode)
	{
	    printf("\r\nsll insert error malloc memory fail");
		return -1;
	}
	
    if(NULL==list->head || NULL==list->tail || 0==list->nums)
    {
        if(NULL!=list->head || NULL!=list->tail || 0!=list->nums)
        {
            printf("\r\nsll insert error head:0x%x tail:0x%x nums:%d",list->head,list->tail,list->nums);
			return -1;
        }

		list->head = newnode;
		list->tail = newnode;
    }
	else
	{
	    list_head = list->head;
		list->head = newnode;
		newnode->next = list_head;
	}
	
	list->nums++;

	return 0;
}

/*把@key所在节点从@list中删除。return 0:0k -1:error*/
int sll_del(sll_ctrl *list,int key)
{
	sll_node *delnode = NULL;
	sll_node *pre = NULL;

	delnode = sll_search(list,key,&pre);

	if(NULL == delnode)
	{
	    printf("\r\nsll del info key %d not in the list",key);
		return 0;
	}

	if(NULL == pre)/*pre为NULL，说明要删除头*/
	{
	    printf("\r\ndel head addr:0x%x key: %d",delnode,delnode->key);
	    if(1 == list->nums)
	    {
	        list->head = NULL;
		    list->tail = NULL;
	    }
		else
		{
		    list->head = delnode->next;
		}
	}
	else
	{
	    if(list->tail == delnode)
			list->tail = pre;
		
	    pre->next = delnode->next;
	}

	free(delnode);
	list->nums--;

	return 0;
}

void sll_reverse(sll_ctrl *list)
{
    sll_node *head;
	sll_node *tail;
	sll_node *cur;
	sll_node *cur_save;
	sll_node *next;
	sll_node *nnext = NULL;

	head = list->head;
	tail = list->tail;

	if(NULL == list || NULL == head)
		return ;

    cur   = list->head;
	next  = cur->next;
	nnext = NULL;

	if(NULL == next)
		return;
	
	while(NULL != cur)
	{
		if(NULL != next)
			nnext = next->next;
		
		next->next = cur;

		cur  = next;
		next = nnext;

		if(NULL == next)
			break;
	}

	list->head = tail;
	list->tail = head;

	head->next = NULL;
}

void sll_show(sll_ctrl *list)
{
    sll_node *cur;
	int i = 0;

	if(NULL == list)
	{
	    printf("\r\nError input para error at sll_show");
		return;
	}
	
	cur = list->head;

	printf("\r\n+-------------------------+");
	printf("\r\n| list 0x%08x  nums %d |",list,list->nums);	
	printf("\r\n+-------------------------+");

    if(0 == list->nums)
	    return;
	
	printf("\r\n| index     addr     key  |");	
	printf("\r\n+-------------------------+");
	printf("\r\n| head   0x%08x  %d    |",list->head,list->head->key);
	printf("\r\n| tail   0x%08x  %d    |",list->tail,list->tail->key);
	printf("\r\n+-------------------------+");

	while(NULL != cur)
	{
	    printf("\r\n| %04d   0x%08x  %d    |",i++,cur,cur->key);
		cur = cur->next;
	}
	
	printf("\r\n+-------------------------+");
}

/*=============================================================================================================*/
sll_ctrl my_sll;


void sll_test_insert()
{
    sll_init(&my_sll);

	sll_insert(&my_sll,1);
	sll_insert(&my_sll,2);	
	sll_insert(&my_sll,2);
	sll_insert(&my_sll,3);
	sll_insert(&my_sll,4);
	sll_insert(&my_sll,5);
	sll_insert(&my_sll,6);
	sll_show(&my_sll);
	sll_destory(&my_sll,0);
}

void sll_test_reverse()
{
    sll_init(&my_sll);	
	printf("\r\nsll show");
	sll_show(&my_sll);
	printf("\r\nsll reverse");
	sll_reverse(&my_sll);
	sll_show(&my_sll);
	sll_destory(&my_sll,0);

	sll_init(&my_sll);
	sll_insert(&my_sll,1);
	printf("\r\nsll show");
	sll_show(&my_sll);
	printf("\r\nsll reverse");
	sll_reverse(&my_sll);
	sll_show(&my_sll);
	sll_destory(&my_sll,0);
	
	sll_init(&my_sll);
	sll_insert(&my_sll,1);	
	sll_insert(&my_sll,2);
	printf("\r\nsll show");
	sll_show(&my_sll);
	printf("\r\nsll reverse");
	sll_reverse(&my_sll);
	sll_show(&my_sll);
	sll_destory(&my_sll,0);

	sll_init(&my_sll);
	sll_insert(&my_sll,1);	
	sll_insert(&my_sll,2);	
	sll_insert(&my_sll,3);
	printf("\r\nsll show");
	sll_show(&my_sll);
	printf("\r\nsll reverse");
	sll_reverse(&my_sll);
	sll_show(&my_sll);
	sll_destory(&my_sll,0);


	sll_init(&my_sll);
	sll_insert(&my_sll,1);	
	sll_insert(&my_sll,2);	
	sll_insert(&my_sll,3);
	sll_insert(&my_sll,4);
	sll_insert(&my_sll,5);
	sll_insert(&my_sll,6);
	sll_insert(&my_sll,7);
	printf("\r\nsll show");
	sll_show(&my_sll);
	printf("\r\nsll reverse");
	sll_reverse(&my_sll);
	sll_show(&my_sll);
	sll_destory(&my_sll,0);

}

void sll_test_del()
{
    sll_init(&my_sll);

	sll_insert(&my_sll,1);
	sll_insert(&my_sll,2);	
	sll_insert(&my_sll,3);
	sll_insert(&my_sll,4);
	sll_insert(&my_sll,5);
	sll_insert(&my_sll,6);

	sll_show(&my_sll);

    printf("\r\n---->del key 2");
	sll_del(&my_sll,2);
	sll_show(&my_sll);

    printf("\r\n---->del key 1");
    sll_del(&my_sll,1);
	sll_show(&my_sll);
	
    printf("\r\n---->del key 5");
    sll_del(&my_sll,5);
	sll_show(&my_sll);	

    printf("\r\n---->del key 9");
    sll_del(&my_sll,9);
	sll_show(&my_sll);	
	
	sll_destory(&my_sll,0);
}

void sll_test_search_result(sll_node *cur,sll_node *pre)
{
	if(NULL != cur)
		printf("\r\ncurnode:0x%x,key:%d",cur,cur->key);
	else
		printf("\r\ncurnode NULL");

	if(NULL != pre)
		printf("\r\nprenode:0x%x,key:%d",pre,pre->key);
	else
		printf("\r\nprenode NULL");

}

void sll_test_search()
{
    sll_node *cur;
	sll_node *pre;
	
    sll_init(&my_sll);
	
    cur = sll_search(&my_sll,1,&pre);
	sll_test_search_result(cur,pre);

	sll_destory(&my_sll,0);
}

int main()
{
    //sll_test_insert();
	//sll_test_reverse();
	//sll_test_del();	
	sll_test_search();
}
