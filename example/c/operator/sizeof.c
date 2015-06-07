/*-----------------------------------------------------------------------------------
 sizeof是C/C++中的一个操作符（operator）, 其作用就是返回一个对象或者类型所占的内存字
 节数. 其返回值类型为size_t, 在头文件stddef.h中定义. 这是一个依赖于编译系统的值, 一般
 定义为:
     typedef unsigned int size_t;
        
 sizeof有三种语法形式，如下：
 1) sizeof( object );    // sizeof( 对象 );
 2) sizeof( type_name ); // sizeof( 类型 );
 3) sizeof object;       // sizeof 对象; 一般不用，知道就行
 ----------------------------------------------------------------------------------*/
#include <stdio.h>

struct _tag{
    int a;
	int b;
	int c;
};

/* 数组做型参时, 数组名称当作指针使用!! */
void sizeof_test01(int tmp[3])
{
    int a;
	int *p;
	int array[3];
	char *string = "abcde";

	printf("sizeof(int)     :%d %d\r\n",sizeof(int),sizeof(a));	
	printf("sizeof(void *)  :%d %d\r\n",sizeof(void *),sizeof(p));
	printf("sizeof(array[3]):%d \r\n",sizeof(array));
	printf("sizeof(tmp[3])  :%d \r\n",sizeof(tmp));
	printf("sizeof(string)  :%d %d %d\r\n",sizeof(string),sizeof(*string),sizeof("abcde"));
}

void sizeof_test02(struct _tag s,struct _tag *sp)
{
    int temp[3];
	printf("sizeof(s)       :%d %d\r\n",sizeof(s),sizeof(struct _tag));
	printf("sizeof(sp/*sp)  :%d %d\r\n",sizeof(sp),sizeof(*sp));	
	
	sizeof_test01(temp);
}

void sizeof_test03()
{
    struct _tag ss;

	sizeof_test02(ss,&ss);
}

/*-----------------------------------------------------------------------------------
 $ ./a.exe
 sizeof(s)       :12 12
 sizeof(sp/*sp)  :8 12
 sizeof(int)     :4 4
 sizeof(void *)  :8 8
 sizeof(array[3]):12
 sizeof(tmp[3])  :8
 sizeof(string)  :8 1 6
 ----------------------------------------------------------------------------------*/
int main()
{
   sizeof_test03();
}
