/*******************************************************************************

位段(bit-field)
  是以位为单位来定义结构体(或联合体)中的成员变量所占的空间。含有位段的结构体(联合体)
  称为位段结构。采用位段结构既能够节省空间，又方便于操作。

位段的定义格式为:
  type  [var]: digits

  其中type只能为int，unsigned int，signed int三种类型(int型能不能表示负数视编译器而
  定，比如VC中int就默认是signed int，能够表示负数)。位段名称var是可选参数，即可以省略。
  digits表示该位段所占的二进制位数。

定义一个位段结构可以像下面这段代码去定义：

         struct node
         {
             unsigned int a:4;       //位段a，占4位
             unsigned int  :0;       //无名位段，占0位
             unsigned int b:4;       //位段b，占4位
             int c:32;           //位段c，占32位
             int  :6;               //无名位段，占6位
         };

 一.位段的使用
    1)位段的类型只能是int，unsigned int，signed int三种类型，不能是char型或者浮点型；
      signed char、unsigned char linux内核里可以是char short等，和gcc有关??
    2)位段占的二进制位数不能超过该基本类型所能表示的最大位数，比如在VC中int是占4
    个字节，那么最多只能是32位；
    3)无名位段不能被访问，但是会占据空间；
    4)不能对位段进行取地址操作；
    5)若位段占的二进制位数为0，则这个位段必须是无名位段，下一个位段从下一个位段存
    储单元(这里的位段存储单元经测试在VC环境下是4个字节)开始存放；
    6)若位段出现在表达式中，则会自动进行整型升级，自动转换为int型或者unsigned int。
    7)对位段赋值时，最好不要超过位段所能表示的最大范围，否则可能会造成意想不到的结果。
    8)位段不能出现数组的形式。
 
 二.位段结构在内存中的存储方式
    1)如果一个位段存储单元能够存储得下位段结构中的所有成员，那么位段结构中的所有
    成员只能放在一个位段存储单元中，不能放在两个位段存储单元中；如果一个位段存储
    单元不能容纳下位段结构中的所有成员，那么从剩余的位段从下一个位段存储单元开始
    存放。(在VC中位段存储单元的大小是4字节).
 
    2)如果一个位段结构中只有一个占有0位的无名位段，则只占1或0字节的空间(C语言中
    是占0字节，而C++中占1字节)；否则其他任何情况下，一个位段结构所占的空间至少是
    一个位段存储单元的大小；

 ******************************************************************************/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct node
{
    unsigned int a:1;      /* 存在一个非0位的位段，则至少占4Byte */
}S; 

typedef struct node1      /* 在C++中占1字节的空间 ，在C中占0字节  */
{
    unsigned int :0;
}S1;

typedef struct node2
{
    unsigned int a:1;
    unsigned int  :0;     /* 下一个位段放在一个新的位段存储单元 ，所以占4+4=8Byte  */
    unsigned c:32;         
}S2;

typedef struct node3
{
    unsigned int a:4;
    unsigned int  :0;
    int :6;               /* 这个位段放在一个新的位段存储单元  */
    unsigned c:32;       /* 由于6+32>32，所位段c也放在一个新的位段存储单元，所以占4+4+4=12Byte  */
}S3;

typedef struct node4  
{
    unsigned int a:1;
    char b;               /* 在一个位段存储单元中能够存下所有的成员，所以占4Byte  */
    int c:1;
    int d:2;
    unsigned int e:2;
}S4;

struct _bf1
{
    unsigned char a:1;
    unsigned char b:1;
    unsigned char c:1;
    
};

struct _bf2
{
    unsigned short a:1;
    unsigned short b:1;
    unsigned short c:1;
    
};

struct _bf3
{
    unsigned short a:1;
    unsigned short b:1;
    unsigned short c:1;
    
};

struct _bf4
{
    union
    {
        struct _bf3 bf3;
        int a;
    };
};


void bit_field_test01()
{
    struct _bf1 bf1;
    struct _bf2 bf2;
    
    printf("\r\nsizeof(bf1) :%d",sizeof(bf1));
    printf("\r\nsizeof(bf2) :%d",sizeof(bf2));
    
}

void bit_field_test02()
{
    struct _bf4 bf4 = {0};
    
    bf4.bf3.a = 1;
    printf("\r\nbf3.a :0x%x",bf4.a);

    bf4.a = 0;
    bf4.bf3.b= 1;
    printf("\r\nbf3.a :0x%x",bf4.a);    
}


void dump_native_bits_storage_layout(unsigned char *p, int bytes_num)
{
    union flag_t 
    {
        unsigned char c;
        struct base_flag_t 
        {
            unsigned int p7:1,
                         p6:1,
                         p5:1,
                         p4:1,
                         p3:1,
                         p2:1,
                         p1:1,
                         p0:1;
        } base;
    } f;
    int i;

    for (i = 0; i < bytes_num; i++) 
    {
        f.c = *(p + i);
        printf("%p: %d%d%d%d%d%d%d%d \n",p + i,f.base.p7,f.base.p6,f.base.p5,f.base.p4,
                                         f.base.p3,f.base.p2,f.base.p1,f.base.p0);
    }
    printf("\n");
}

struct short_flag_t2 {
    unsigned short a : 7,
                   b : 10;
};

struct short_flag_t3 {
    unsigned short a : 2,
                   b : 3;
}; 

/*
layout test :
0x22ccd4: 10001110
0x22ccd5: 00000000
0x22ccd6: 10100111
0x22ccd7: 11000000

0x22ccd2: 01001000
0x22ccd3: 00000000
*/
int bits_storage_layout_test()
{
    struct short_flag_t2 s;
    struct short_flag_t3 s3;
    
    memset(&s, 0, sizeof(s));
    s.a = 113; /* 0111 0001 */
    s.b = 997; /* 0011 1110 0101 */
    printf("\nlayout test :\n");
    dump_native_bits_storage_layout((unsigned char*)&s, sizeof(s));

    memset(&s3, 0, sizeof(s3));
    s3.a = 2; /* 10 */
    s3.b = 4; /* 100 */
    dump_native_bits_storage_layout((unsigned char*)&s3, sizeof(s3));
    
    return 0;
}


struct bool_flag_t {
    _Bool a : 1,
          b : 1;
};

struct char_flag_t {
    unsigned char a : 2,
                  b : 3;
};

struct short_flag_t {
    unsigned short a : 2,
                   b : 3;
};

struct int_flag_t {
    int a : 2,
        b : 3;
};

/* output: 1 1 2 4 4 */
int bits_size_test()
{
    printf("bits size test:\n");
    printf("%ld ", sizeof(struct bool_flag_t));
    printf("%ld ", sizeof(struct char_flag_t));
    printf("%ld ", sizeof(struct short_flag_t));
    printf("%ld ", sizeof(struct short_flag_t2));    
    printf("%ld\n", sizeof(struct int_flag_t));

    return 0;
}


int main(int argc, char *argv[])
{
    S4 s4;
    s4.a=1;
    s4.c=1;
    s4.d=2;              
    s4.e=3;
    printf("%d %d %d %d\n",s4.a,s4.c,s4.d,s4.e);
    printf("%d %d %d %d %d\n",sizeof(S),sizeof(S1),sizeof(S2),sizeof(S3),sizeof(S4));

    bit_field_test01();
    bit_field_test02();
    bits_storage_layout_test();
    bits_size_test();
    return 0;
}

