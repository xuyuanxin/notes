#include<stdio.h>
#include"cube.h"

cube_t cube;

void cube_face_create(face_t cube_face)
{
    int i,k;

	for(i = 0; i < MatrixDim; i++)
	{
	    for(k = 0; k < MatrixDim; k++)
	    {
	        cube_face[i][k] = rand() % 6;
	    }
	}
}

void cube_create()
{
    int i;

	for(i = 0; i < FaceNum; i++)
	{
	   cube_face_create(cube[i]);
	}
}

void cube_show_face(face_t cube_face)
{
    int i,k;

	for(i = 0; i < MatrixDim; i++)
	{
	    printf("\r\n");
		printf("      ");
	    for(k = 0; k < MatrixDim; k++)
	    {
	        printf("%d ",cube_face[i][k]);
	    }
	}
}
void cube_show()
{
    int i;

	for(i = 0; i < FaceNum; i++)
	{
	   printf("\r\nFace%d ",i);
	   cube_show_face(cube[i]);
	}

}

/*逆时针旋转九十度 绕x轴旋转某层
  第一层和最后一层影响五个面，以三阶魔方为例
  layer 0: 20         20         22         00         20
           21         10         21         10         21
           22         00         20         20         22
           f5 move to f3 move to f4 move to f1 move to f5*/
void cube_rotate_x_layer(int layers)
{
    int i,j,k;
	cube_t cube_l;

    for(i = 0; i < MatrixDim; i++)
    {
        for(i = 0; i < MatrixDim; i++)
        {
            for(i = 0; i < MatrixDim; i++)
            {
                cube_l[i][j][k] = cube[i][j][k]; 
            }
        }
    }

    for(i = 0; i < MatrixDim; i++)
    {
        cube[5][MatrixDim - 1 - layers][i] = cube_l[1][i][layers];
    }
}
void main()
{
    cube_create();
	cube_show();
	
}


