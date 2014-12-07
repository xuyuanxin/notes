
struct dog
{
    char             d_name[32];
	int              d_age;
	struct list_head d_list;
};


//struct list_head my_dogs = { &(my_dogs), &(my_dogs) };
LIST_HEAD(my_dogs);


int dog_add(char *name,int age)
{
    struct dog *newdog = NULL;

	newdog = (struct dog *)malloc(sizeof(*newdog));

	if(NULL == newdog)
	{
	    printf("dog-add fail!\r\n");
		return 1;
	}

	list_add(&newdog->d_list,&my_dogs);

	return 0;
}

int dog_isexist(char *name,int age)
{
    struct dog *dog = NULL;

	list_for_each_entry(dog,&my_dogs,d_list)
	{
	    if((0 == strcmp(dog->d_name,name)) && (dog->d_age == age))
			return 1;
	}

	return 0;
}