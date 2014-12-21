/*******************************************************************************
当多个数据需要共享内存或者多个数据每次只取其一时，可以利用联合体(union)。
1)联合体是一个结构；
2)它的所有成员相对于基地址的偏移量都为0；
3)此结构空间要大到足够容纳最"宽"的成员；
4)其对齐方式要适合其中所有的成员；
下面解释这四条描述：
由于联合体中的所有成员是共享一段内存的，因此每个成员的存放首地址相对于于联合体变
量的基地址的偏移量为0，即所有成员的首地址都是一样的。为了使得所有成员能够共享一段
内存，因此该空间必须足够容纳这些成员中最宽的成员。对于这句“对齐方式要适合其中所
有的成员”是指其必须符合所有成员的自身对齐方式。
*******************************************************************************/

#include<stdlib.h>
#include<stdio.h>

struct _cat
{
    int c_age;
	int c_weight;
};

struct _dog
{
    int d_age;
	int d_weight;
	int d_colour;
};

struct peta
{
    union
    {
    struct _cat p_cat;
    struct _dog p_dog;
    };
	int p_type;
};

struct petb
{
    union
    {
    struct _cat p_cat;
    struct _dog p_dog;
    }u;
	int p_type;
};

int main()
{
    struct peta peta;
	struct petb petb;

	printf("\r\nsizeof(struct peta) :%d",sizeof(struct petb));	
	printf("\r\nsizeof(petb.u)      :%d",sizeof(petb.u));
	printf("\r\nsizeof(petb.u.p_cat):%d",sizeof(petb.u.p_cat));
	printf("\r\nsizeof(petb.u.p_dog):%d",sizeof(petb.u.p_dog));

	printf("\r\nsizeof(peta.p_cat):%d",sizeof(peta.p_cat));
	printf("\r\nsizeof(peta.p_dog):%d",sizeof(peta.p_dog));
	
	printf("\r\nAddr peta       :%p",&peta);
	printf("\r\nAddr peta.p_cat :%p",&peta.p_cat);
	printf("\r\nAddr peta.p_dog :%p",&peta.p_dog);

	return 0;	
}

