#include<stdio.h>
#include<string.h>
#include "binary_search_tree.h"

#define TREE_DEPTH 15
#define TREE_LINE  160
#define NODE_INFO_LEN 3

char tree_str_info[TREE_DEPTH][TREE_LINE+1] = {0};

int g_node_depth = 0;
int g_node_index = 0;
int g_tree_depth = 0;

void tree_node_coordinate_get(int *depth,int *index)
{
    *depth = g_node_depth - 1;
	*index = g_node_index;
}

void tree_node_coordinate_adjust(tree_node_t * pnode,int flag)
{
    tree_node_t *pparent;
	
    if(0 == flag)	
	    g_node_depth++;
    else if(1 == flag)
		g_node_depth--;

	if(NULL != pnode)
		pparent = pnode->parent;

	if(NULL != pnode && NULL != pparent)
	{
		if(0 == flag && pnode == pparent->left) 
			g_node_index = g_node_index*2;
	    else if(0 == flag && pnode == pparent->right)
			g_node_index = g_node_index*2 + 1;
        else if(1 == flag && pnode == pparent->right) 
			g_node_index = g_node_index/2;	
	}

    if( (g_node_depth > g_tree_depth) && (1 == flag) )
		g_tree_depth = g_node_depth;
}

/*设置树中每个节点的坐标*/
void tree_node_coordinate_set(tree_node_t *pnode)
{   
	tree_node_coordinate_adjust(pnode,0);

    if(NULL != pnode)
    {
        tree_node_coordinate_set(pnode->left);
		pnode->depth = g_node_depth - 1;
		pnode->index = g_node_index;
		tree_node_coordinate_set(pnode->right);
    }
	
	tree_node_coordinate_adjust(pnode,1);
}

void tree_node_coordinate_clear(tree_node_t *pnode)
{
    if(NULL != pnode)
    {
        tree_node_coordinate_clear(pnode->left);
		pnode->depth = 0;
		pnode->index = 0;
		tree_node_coordinate_clear(pnode->right);
    }
}

int tree_struct_init()
{
    int i,j,k,f;
	char *pstring=NULL;

	g_tree_depth = 0;

	for(i = 0;i < TREE_DEPTH;++i)
		for(j = 0;j <= TREE_LINE;++j)
	        tree_str_info[i][j] = ' ';
    
    pstring = "                                |------------------------------NN------------------------------|";
	strcpy(tree_str_info[0],pstring);

	pstring = "                                |                                                              |";
	strcpy(tree_str_info[1],pstring);

	pstring = "                |--------------NN--------------|                                |--------------NN--------------|";
	strcpy(tree_str_info[2],pstring);
	
	pstring = "                |                              |                                |                              |";
	strcpy(tree_str_info[3],pstring);

	pstring = "        |------NN------|                |------NN------|                |------NN------|                |------NN------|";
	strcpy(tree_str_info[4],pstring);
	
	pstring = "        |              |                |              |                |              |                |              |";
	strcpy(tree_str_info[5],pstring);

	pstring = "    |--NN--|        |--NN--|        |--NN--|        |--NN--|        |--NN--|        |--NN--|        |--NN--|        |--NN--|";
	strcpy(tree_str_info[6],pstring);

	pstring = "    |      |        |      |        |      |        |      |        |      |        |      |        |      |        |      |";
	strcpy(tree_str_info[7],pstring);

	pstring = "   NN      NN      NN      NN      NN      NN      NN      NN      NN      NN      NN      NN      NN      NN      NN      NN";
	strcpy(tree_str_info[8],pstring);

	pstring = "  |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |";
	strcpy(tree_str_info[9],pstring);

	pstring = " NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN";
	strcpy(tree_str_info[10],pstring);

	pstring = " ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||";
	strcpy(tree_str_info[11],pstring);

	pstring = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	pstring = "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN";
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

int tree_struct_show(tree_node_t *pnode)
{
    tree_struct_init();
	tree_node_coordinate_set(pnode);
	tree_struct_set(pnode);
	tree_struct_printf();
}

int tree_show(tree_node_t *pnode,int depth)
{
    tree_struct_init();
	tree_struct_set(pnode);
	
	g_tree_depth = depth;
	tree_struct_printf();
}


int main_t()
{
	tree_struct_after_init();

	return 0;
}




/*

                                |------------------------------NN------------------------------|
                                |                                                              |
                |--------------NN--------------|                                |--------------NN--------------|
                |                              |                                |                              |
        |------NN------|                |------NN------|                |------NN------|                |------NN------|
        |              |                |              |                |              |                |              |
    |--NN--|        |--NN--|        |--NN--|        |--NN--|        |--NN--|        |--NN--|        |--NN--|        |--NN--|
    |      |        |      |        |      |        |      |        |      |        |      |        |      |        |      |
   NN      NN      NN      NN      NN      NN      NN      NN      NN      NN      NN      NN      NN      NN      NN      NN
  |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |
 NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN
 ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||
NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN

                                                               64
                               32                                                              96
               16                              48                              80                              112
*/
