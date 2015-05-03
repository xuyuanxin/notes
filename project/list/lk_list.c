#include<stdlib.h>
#include<stdio.h>
#include<inttypes.h>
#include<string.h>
#include"inc/lk_list.h"


struct list_head *list_create()
{
    struct list_head *lroot = NULL;

	lroot = malloc(sizeof(*lroot));
	if(NULL == lroot)
	{
	    printf("list create fail!\n");
		return NULL;
	}

	INIT_LIST_HEAD(lroot);
	
	return lroot;
}

struct list_item *list_item_create()
{
    struct list_item *item = NULL;

	item = (struct list_item *)malloc(sizeof(*item));

	if(NULL == item)
	{
	    printf("list item create fail!\r\n");
		return NULL;
	}

	memset(item,0,sizeof(*item)); 
	return item;
}

