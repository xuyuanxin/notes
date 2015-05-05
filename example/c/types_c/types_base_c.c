#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define ID_STR_LEN   12
#define NAME_STR_LEN 10

typedef struct student
{
    char id[ID_STR_LEN];
    char name[NAME_STR_LEN];
    uint8_t age;
}student;

student * create_student()
{
    student *stu = (student *)malloc(sizeof(student));
    if (stu == NULL)
    return NULL;
    memset(stu, 0, sizeof(student));
    return stu;
}

void *free_student(student *stu)
{
    if (stu)
    free(stu);
}

static void init_student(student * stu)
{
    assert(stu);
	
    assert(0);
    const char *id = "2013112210";
    const char *name = "Anker";
    uint8_t age = 21;
    memcpy(stu->id, id, strlen(id));
    memcpy(stu->name, name, strlen(name));
    stu->age = age;
}

static int handle_student(intptr_t handle)
{
    if (handle == 0)
    {
        return -1;
    }
    student *stu = (student*)handle;
    printf("id: %s\n", stu->id);
    printf("name: %s\n", stu->name);
    printf("age: %u\n", stu->age);
    return 0;
}

int main()
{
    student *stu;
    stu = create_student();
    init_student(stu);
    
    intptr_t handle = (intptr_t)stu; /*将指针转换为intptr_t类型*/
    handle_student(handle);
    free_student(stu);
    return 0;
}

