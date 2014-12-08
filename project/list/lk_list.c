#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"inc/lk_list.h"

struct _dog
{
    char             d_name[32];
	int              d_age;
	struct list_head d_list;
};


//struct list_head my_dogs = { &(my_dogs), &(my_dogs) };
LIST_HEAD(my_dogs);

/* buy a dog  ^_^ */
int dog_add(char *name,int age)
{
    struct _dog *newdog = NULL;

	newdog = (struct _dog *)malloc(sizeof(*newdog));

	if(NULL == newdog)
	{
	    printf("dog-add fail!\r\n");
		return 1;
	}

	memset(newdog,0,sizeof(sizeof(*newdog)));

	strncpy(newdog->d_name,name,32);

	newdog->d_name[31] = 0;
	
	newdog->d_age = age;

	list_add(&newdog->d_list,&my_dogs);

	return 0;
}

/* this dog exist in the list,exist return 1 */
int dog_isexist(char *name,int age)
{
    struct _dog *dog = NULL;

	list_for_each_entry(dog,&my_dogs,d_list)
	{
	    if((0 == strcmp(dog->d_name,name)) && (dog->d_age == age))
			return 1;
	}

	return 0;
}

/* sale a dog */
int dog_del(char *name,int age)
{    
    struct _dog *cur = NULL;
    struct _dog *tmp = NULL;

    list_for_each_entry_safe(cur,tmp,&my_dogs,d_list)
    {
        if((0 == strcmp(cur->d_name,name)) && (cur->d_age == age))
        {
            list_del(&cur->d_list);
			free(cur);
        }		
    }

	return 0;
}

/* clean dog */
int dog_clean(struct list_head *head)
{    
    struct _dog *cur = NULL;
    struct _dog *tmp = NULL;

    list_for_each_entry_safe(cur,tmp,head,d_list)
    {
        list_del(&cur->d_list);
	    free(cur);
    }

	return 0;
}


void dog_show()
{
    int i = 0;
    struct _dog *dog = NULL;

	list_for_each_entry(dog,&my_dogs,d_list)
	{
        printf("\r\nDog %d name:%s age:%u",i++,dog->d_name,dog->d_age);
	}

	return ;
}


int dog_test_add()
{
    printf("\r\n-------- dog test add -------");

    (void)dog_add("dog1",1);
    (void)dog_add("dog2",2);
    (void)dog_add("dog3",3);

	dog_show();

	dog_clean(&my_dogs);

	return 0;
}

int dog_test_exist()
{
    printf("\r\n-------- dog test exist -------");
    (void)dog_add("dog1",1);
    (void)dog_add("dog2",2);
    (void)dog_add("dog3",3);

	dog_show();

	printf("\r\ndog2 2 exist:%d",dog_isexist("dog2",2));
	printf("\r\ndog0 0 exist:%d",dog_isexist("dog0",0));
	
	dog_clean(&my_dogs);

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
	
	dog_clean(&my_dogs);

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
