#include<stdio.h>
#include<string.h>
#include "binary_search_tree.h"

#define TREE_DEPTH 15
#define TREE_LINE  160
#define NODE_INFO_LEN 3

char tree_str_info[TREE_DEPTH][TREE_LINE+1] = {0};

int g_tree_depth = 0;


/*ÐÞ¸Ä*/
int tree_struct_init()
{
    int i,j,k,f;
	char *pstring=NULL;

	g_tree_depth = 0;

	for(i = 0;i < TREE_DEPTH;++i)
		for(j = 0;j <= TREE_LINE;++j)
	        tree_str_info[i][j] = ' ';
    
    pstring = "                                |------------------------------..------------------------------|";
	strcpy(tree_str_info[0],pstring);

	pstring = "                                |                                                              |";
	strcpy(tree_str_info[1],pstring);

	pstring = "                |--------------..--------------|                                |--------------..--------------|";
	strcpy(tree_str_info[2],pstring);
	
	pstring = "                |                              |                                |                              |";
	strcpy(tree_str_info[3],pstring);

	pstring = "        |------..------|                |------..------|                |------..------|                |------..------|";
	strcpy(tree_str_info[4],pstring);
	
	pstring = "        |              |                |              |                |              |                |              |";
	strcpy(tree_str_info[5],pstring);

	pstring = "    |--..--|        |--..--|        |--..--|        |--..--|        |--..--|        |--..--|        |--..--|        |--..--|";
	strcpy(tree_str_info[6],pstring);

	pstring = "    |      |        |      |        |      |        |      |        |      |        |      |        |      |        |      |";
	strcpy(tree_str_info[7],pstring);

	pstring = "   ..      ..      ..      ..      ..      ..      ..      ..      ..      ..      ..      ..      ..      ..      ..      ..";
	strcpy(tree_str_info[8],pstring);

	pstring = "  |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |";
	strcpy(tree_str_info[9],pstring);

	pstring = " ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..";
	strcpy(tree_str_info[10],pstring);

	pstring = " ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||";
	strcpy(tree_str_info[11],pstring);

	pstring = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	pstring = "................................................................................................................................";
	strcpy(tree_str_info[12],pstring);
}

void __tree_struct_set(int depth,int index,int key)
{
    int base_index;
	int real_index;

	base_index = 128/(1 << (depth+1));
	real_index = base_index + base_index*2*index;

	//printf("\r\nbase_index:%d,real_index:%d",base_index,real_index);

	tree_str_info[depth*2][real_index - 1] = '0' + key/10;
	tree_str_info[depth*2][real_index] = '0' + key%10;
}

void tree_struct_set(tree_node_t *pnode)
{
    if(NULL != pnode)
    {
        tree_struct_set(pnode->left);
		__tree_struct_set(pnode->depth,pnode->index,pnode->key);
		tree_struct_set(pnode->right);
    }
}

int tree_struct_printf()
{
    int i,max;
	
	if(0 == g_tree_depth)
		max = 0;
	else
		max = g_tree_depth*2 - 1;
	
    for(i = 0;i < max;++i)	
	    printf("\r\n%s",tree_str_info[i]);
}

int tree_struct_after_init()
{  
    int i;

    tree_struct_init();
	for(i = 0;i < TREE_DEPTH;++i)	
	    printf("\r\n%s",tree_str_info[i]);
}

int tree_show(tree_node_t *pnode,int depth)
{
    tree_struct_init();
	tree_struct_set(pnode);
	
	g_tree_depth = depth;
	tree_struct_printf();
}

