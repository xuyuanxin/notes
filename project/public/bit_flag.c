#include<stdio.h>


#define BF_00 0x0001
#define BF_01 0x0002
#define BF_02 0x4
#define BF_03 0x8
#define BF_04 0x10
#define BF_05 0x20
#define BF_06 0x40
#define BF_07 0x80

#define BF_08 0x100
#define BF_09 0x200
#define BF_10 0x400
#define BF_11 0x800
#define BF_12 0x1000
#define BF_13 0x2000
#define BF_14 0x4000
#define BF_15 0x8000

#define BF_16 0x10000
#define BF_17 0x20000
#define BF_18 0x40000
#define BF_19 0x80000
#define BF_20 0x100000
#define BF_21 0x200000
#define BF_22 0x400000
#define BF_23 0x800000

#define BF_24 0x1000000
#define BF_25 0x2000000
#define BF_26 0x4000000
#define BF_27 0x8000000
#define BF_28 0x10000000
#define BF_29 0x20000000
#define BF_30 0x40000000
#define BF_31 0x80000000


unsigned int bitflag = 0;
unsigned short bitflag2 = 0;



int test1()
{
    bitflag |= BF_01;
	printf("bitflag:0x%x\r\n",bitflag);
	
    bitflag |= BF_00;	
	printf("bitflag:0x%x\r\n",bitflag);
	
    bitflag |= BF_31;	
	printf("bitflag:0x%x\r\n",bitflag);

    bitflag &= ~BF_31;	
	printf("bitflag:0x%x\r\n",bitflag);


	if(bitflag&BF_31) printf("bit 31 set");



    bitflag2 |= BF_00;
	printf("bitflag2:0x%x\r\n",bitflag2);
	
    bitflag2 |= BF_01;	
	printf("bitflag2:0x%x\r\n",bitflag2);
	
    bitflag2 |= BF_15;	
	printf("bitflag2:0x%x\r\n",bitflag2);

    bitflag2 |= BF_31;	
	printf("bitflag2:0x%x\r\n",bitflag2);

	return 0;
}


int test2()
{
    bitflag |= BF_01;
	printf("bitflag:0x%x\r\n",bitflag);

	if(bitflag&BF_01) printf("bit 1 set");

	return 0;
}

int main()
{
    test2();
    return 0;
}

