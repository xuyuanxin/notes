#include<stdlib.h>    /*rand()*/
#include<time.h>      /*time()*/
#include<stdio.h>

#include"matrix.h"



matrix_t matrix;
matrix_t matrix_s;/*静态矩阵(维度小于等于9)  static matrix*/


void matr_create(matrix_t matr)
{
    int i,k;

	for(i = 0; i < MatrixDim; i++)
	{
	    for(k = 0; k < MatrixDim; k++)
	    {
	        matr[i][k] = rand() % 7;
	    }
	}
}

void matr_create_s(matrix_t matr)
{
    int i,j;

	if(MatrixDim > 10)
	{
	    printf("Create Static Matrix Error:too big dimension[%d]",MatrixDim);
		return;
	}

	for(i = 0; i < MatrixDim; i++)
	{
	    for(j = 0; j < MatrixDim; j++)
	    {
	        matr[i][j] = 10*i +j;
	    }
	}
}


void matr_show(matrix_t matr)
{  
    int i,j;
	for(i = 0; i < MatrixDim; i++)
	{
	    printf("\r\n");
	    for(j = 0; j < MatrixDim; j++)
	    {
            printf("%d ",matr[i][j]);
	    }
	}

}
void matr_show_s(matrix_t matr)
{  
    int i,j;
	for(i = 0; i < MatrixDim; i++)
	{
	    printf("\r\n");
	    for(j = 0; j < MatrixDim; j++)
	    {
            printf("%02d ",matr[i][j]);
	    }
	}

}


/*整体顺时针旋转九十度
00 01 02 03        30 20 10 00
10 11 12 13        31 21 11 01
20 21 22 23        32 22 12 02
30 31 32 33        33 23 13 03
*/
void matr_rotate(matrix_t matr)
{
    int matr_l[MatrixDim][MatrixDim];
	int i,j,k;

	for(i = 0; i < MatrixDim; i++)
	{
	    for(j = 0; j < MatrixDim; j++)
	    {
	        matr_l[i][j] = matr[i][j] ;
	    }
	}

	for(i = 0; i < MatrixDim; i++)
	{
	    for(j = 0,k = MatrixDim-1; j < MatrixDim; j++,k--)
	    {
	        matr[i][j] = matr_l[k][i] ;
	    }
	}
}

/*边界顺时针旋转九十度
00 01 02 03        30 20 10 00
10 11 12 13        31       01
20 21 22 23        32       02
30 31 32 33        33 23 13 03

是第一行或最后一行: 整体赋值
否则              : 只对第一列和最后一列赋值
*/
void matr_boundary_rotate(matrix_t matr)
{
    int i,j,k;
	int matr_l[MatrixDim][MatrixDim];

	for(i = 0; i < MatrixDim; i++)
	{
	    for(j = 0; j < MatrixDim; j++)
	    {
            matr_l[i][j] = matr[i][j];
	    }
	}

	for(i = 0; i < MatrixDim; i++)
	{
	    for(j = 0,k = MatrixDim-1; j < MatrixDim; j++,k--)
	    {
	        if(0 == i || MatrixDim-1 == i)
	        {
	            matr[i][j] = matr_l[k][i];
	        }
			else
			{
			    if(0 == j || MatrixDim-1 == j)
					matr[i][j] = matr_l[k][i];
			}
	    }
	}
}



/*整体逆时针旋转九十度
00 01 02 03        03 13 23 33
10 11 12 13        02 12 22 32
20 21 22 23        01 11 21 31
30 31 32 33        00 10 20 30
*/
void matr_anti_rotate(matrix_t matr)
{
    int matr_l[MatrixDim][MatrixDim];
	int i,k,j;

	for(i = 0; i < MatrixDim; i++)
	{
	    for(j = 0; j < MatrixDim; j++)
	    {
	        matr_l[i][j] = matr[i][j] ;
	    }
	}

	for(i = 0,k = MatrixDim-1; i < MatrixDim; i++,k--)
	{
	    for(j = 0; j < MatrixDim; j++)
	    {
	        matr[i][j] = matr_l[j][k] ;
	    }
	}
}


/*边界逆时针旋转九十度
00 01 02 03        03 13 23 33
10 11 12 13        02       32
20 21 22 23        01       31
30 31 32 33        00 10 20 30
*/
void matr_boundary_anti_rotate(matrix_t matr)
{
    int i,j,k;
	int matr_l[MatrixDim][MatrixDim];

	for(i = 0; i < MatrixDim; i++)
	{
	    for(j = 0; j < MatrixDim; j++)
	    {
            matr_l[i][j] = matr[i][j];
	    }
	}

	for(i = 0,k = MatrixDim-1; i < MatrixDim; i++,k--)
	{
	    for(j = 0; j < MatrixDim; j++)
	    {
	        if(0 == i || MatrixDim-1 == i)
	        {
	            matr[i][j] = matr_l[j][k];
	        }
			else
			{
			    if(0 == j || MatrixDim-1 == j)
					matr[i][j] = matr_l[j][k];
			}
	    }
	}
}


/*1 整体顺时针旋转九十度   2 边界顺时针旋转九十度
  3 整体逆时针旋转九十度   4 边界逆时针旋转九十度*/
void matr_rotate_test(int flag,char const *string)
{
    printf("\r\n%s",string);
	matr_create(matrix);
	matr_show(matrix);
	
	switch(flag)
	{
	    case 1: matr_rotate(matrix); break;
		case 2: matr_boundary_rotate(matrix); break;
		case 3: matr_anti_rotate(matrix); break;
		case 4: matr_boundary_anti_rotate(matrix); break;
		default : printf("\r\nNot Rotate input flag error!");
	}
	
	printf("\r\nrotate result");
	matr_show(matrix);
	printf("\r\n");
}

void matr_rotate_dynamic_test()
{
	matr_rotate_test(1,"clockwise rotate 90 degrees: whole");
	matr_rotate_test(2,"clockwise rotate 90 degrees: boundary");

	matr_rotate_test(3,"anticlockwise rotate 90 degrees: whole");
	matr_rotate_test(4,"anticlockwise rotate 90 degrees: boundary");  
}



void matr_rotate_static_test()
{
    
}


void main()
{
    matr_create_s(matrix_s);
	matr_show_s(matrix_s);

	printf("\r\n");
	matr_rotate_dynamic_test();
}



/*
dimension: dim
matrix:    matr*/
