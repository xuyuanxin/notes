/****************************************************************************************************
 g_array[0]                                                      g_array[array_length + 2]

   |                                                                    |
  \|/                                                                  \|/
   +------------------------------------------------------------------------------------------------+
   |  max_value  |  max_value  |  random  |  random  |  ...  |  random  |  max_value  |  max_value  |
   +------------------------------------------------------------------------------------------------+
                              /|\                           /|\  
                               |                             |
                           array[0]                 array[array_length - 1]
*****************************************************************************************************/    

#include<stdio.h>     /*printf()*/
#include<stdlib.h>    /*rand()*/
#include<time.h>      /*time()*/
#include <stdbool.h>  /*bool*/

extern void sort_merge(int array[], int first, int end);
extern void sort_insertion(int array[],int ele_num);
extern void sort_bubble(int array[],int ele_num);
extern void sort_heap(int array[],int ele_num);
extern void sort_quick(int array[],int first,int end);


#define array_length 10               /*数组的个数*/
#define length_all   array_length + 4 /*数组前后各有2个魔数(max_value)*/
#define max_value    100      

int g_array[array_length + 4] = {0};
int *p_array = NULL;
int g_printflag = 0;

void show_array()
{
    int i;
	
    for(i = 0; i < array_length + 4; i++)
	{	
	    if(1 == g_printflag)
		    printf("\r\ng_array[%02d] = %d",i,g_array[i]);
	}
}

void array_init()
{  
    int i ;
	
    srand((int)time(0));
	
	for(i = 0; i < array_length + 4; i++)
	{
	    if( (0 == i) || (1 == i) || (array_length + 2 == i) || (array_length + 3 == i))
			g_array[i] = max_value;
		else
	        g_array[i] = (rand() % max_value*2) - max_value;/*确认rand产生的值都大于零*/
	}
	p_array = g_array + 2;

	if(1 == g_printflag)
	    printf("\r\n******** Array Elements After Init ********");
	
	show_array();
}

void array_init1()
{  
    int i ;
	
    srand((int)time(0));
	
	for(i = 0; i < array_length + 4; i++)
	{
	    if( (0 == i) || (1 == i) || (array_length + 2 == i) || (array_length + 3 == i))
			g_array[i] = max_value;
		else
	        g_array[i] = rand()%100;/*CS_MAX*/
	}
	p_array = g_array + 2;

	if(1 == g_printflag)
	    printf("\r\n******** Array Elements After Init ********");
	
	show_array();
}


void sort_check(char *name)
{
    int i,j,k;
	bool sort_success = true;
	int array1[4],array2[array_length];
		
    j = 0; k = 0;
	
	for(i = 0; i < array_length + 4; i++)
	{
		if( (0 == i) || (1 == i) || (array_length + 2 == i) || (array_length + 3 == i))
	    {
            array1[j++] = g_array[i];
	    }
		else
		{
		    array2[k++] = g_array[i];
		}
	}

	for(i = 0; i < 4; i++)
	{		
		if(max_value != array1[i]) 
		{
			sort_success = false;
		}
	}
	
	for(i = 0; i < array_length - 1; i++)
	{
		if(array2[i] > array2[i + 1] )
		{
			sort_success = false;
		}	
	}
	
	if(1 == g_printflag)
	    printf("\r\n\r\n******** Array Elements After Sort ********");	

	if(true == sort_success)
	{
	    show_array();
		printf("\r\n%-15s Sort Success!",name);
	}
    else
    {	
		show_array();
		printf("\r\n%-15s Sort Fail!",name);
    }
}

void sort_test_insertion()
{
	array_init();
	sort_insertion(g_array + 2,array_length);
	sort_check("insertion");

    array_init();
    sort_insertion_v2(g_array + 2,array_length);
    sort_check("insertion_v2");
}

void sort_test_shell()
{
	array_init();
	sort_shell(g_array + 2,array_length);
	sort_check("shell");
	
	array_init();
	sort_shell_v2(g_array + 2,array_length);
	sort_check("shell_v2");	
}


void sort_test_merge()
{
    array_init();
	sort_merge(g_array + 2,0,array_length - 1);
    sort_check("merge");
}

void sort_test_bubble()
{
	array_init();
	sort_bubble(g_array + 2,array_length);
	sort_check("bubble");
}

void sort_test_heap()
{
	array_init();
	sort_heap(g_array + 2,array_length);
	sort_check("heap");
}

void sort_test_quick()
{
    array_init();
	//g_array[2]=2; g_array[3]=1;g_array[4]=3; g_array[5]=1;
	//g_array[6]=3; g_array[7]=5;g_array[8]=6; g_array[9]=4;
	sort_quick(g_array + 2,0,array_length - 1);
    sort_check("quick");
}

void sort_test_counting()
{
    array_init1();
	sort_counting(g_array + 2,array_length);
    sort_check("counting");
}

int main()
{
    g_printflag = 0;
	
    sort_test_insertion();
    sort_test_shell();
	sort_test_merge();
	sort_test_bubble();
    sort_test_heap();
	sort_test_quick();
	//g_printflag =1;
	sort_test_counting();

	return 0;
}
