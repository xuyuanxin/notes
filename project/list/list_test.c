#include<stdlib.h>
#include<stdio.h>
#include<inttypes.h>
#include<string.h>
#include"inc/lk_list.h"


//struct list_head my_dogs = { &(my_dogs), &(my_dogs) };
LIST_HEAD(my_dogs);
LIST_HEAD(my_cats);


int cat_add(char *name,int age)
{
    struct list_item *newcat = NULL;

	newcat = list_item_create();
    if(NULL == newcat)
    {
        return -1;
    }

	strncpy(newcat->cat.c_name,name,32);

	newcat->cat.c_name[31] = 0;
	
	newcat->cat.c_age = age;

	list_add(&newcat->list,&my_cats);

	return 0;
}


int dog_add(char *name,int age)
{
	struct list_item *newdog = NULL;

	newdog = list_item_create();
	if(NULL == newdog)
	{
		return -1;
	}

	strncpy(newdog->dog.d_name,name,32);

	newdog->dog.d_name[31] = 0;
	newdog->dog.d_age = age;

	list_add_tail(&newdog->list,&my_dogs);

	return 0;
}


int dog_exist(char *name,int age)
{
	struct list_item *dog = NULL;

	list_for_each_entry(dog,&my_dogs,list)
	{
	    if((0 == strcmp(dog->dog.d_name,name)) && (dog->dog.d_age == age))
			return 1;
	}

	return 0;
}


int dog_del(char *name,int age)
{    
    struct list_item *cur = NULL;
    struct list_item *tmp = NULL;

    list_for_each_entry_safe(cur,tmp,&my_dogs,list)
    {
        if((0 == strcmp(cur->dog.d_name,name)) && (cur->dog.d_age == age))
        {
            list_del(&cur->list);
			free(cur);
        }		
    }

	return 0;
}


int dog_free()
{    
    struct list_item *cur = NULL;
    struct list_item *tmp = NULL;

    list_for_each_entry_safe(cur,tmp,&my_dogs,list)
    {
        list_del(&cur->list);
	    free(cur);
    }

	return 0;
}


void dog_show()
{
    int i = 0;
    struct list_item *dog = NULL;

	list_for_each_entry(dog,&my_dogs,list)
	{
        printf("\r\nDog[%d] name:%s age:%u",i++,dog->dog.d_name,dog->dog.d_age);
	}

	return ;
}


/*---------------------------------------------------------------------------------*/

int dog_test_add()
{
    printf("\r\n-------- dog test add -------");

    (void)dog_add("dog1",1);
    (void)dog_add("dog2",2);
    (void)dog_add("dog3",3);

	dog_show();
	dog_free();

	return 0;
}

int dog_test_exist()
{
    printf("\r\n-------- dog test exist -------");
    (void)dog_add("dog1",1);
    (void)dog_add("dog2",2);
    (void)dog_add("dog3",3);

	dog_show();

	printf("\r\ndog2 2 exist:%d",dog_exist("dog2",2));
	printf("\r\ndog0 0 exist:%d",dog_exist("dog0",0));
	
	dog_free();

	return 0;
}

int dog_test_del()
{
    printf("\r\n-------- dog test del -------");

	(void)dog_add("dog1",1);
	(void)dog_add("dog2",2);
	(void)dog_add("dog3",3);

	dog_show();

	(void)dog_del("dog2",2);
	printf("\r\n----del dog2 2");
	dog_show();

	(void)dog_del("dog1",1);
	printf("\r\n----del dog1 1");
	dog_show(); 
	
	(void)dog_del("dog3",3);
	printf("\r\n----del dog3 3");
	dog_show();
	
	dog_free();

	return 0;
}



int dog_test()
{
    (void)dog_test_add();
	(void)dog_test_exist();
    (void)dog_test_del();

	return 0;
}



int list_test()
{
    dog_test();

	return 0;
}


