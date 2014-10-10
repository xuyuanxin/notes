#include<stdio.h>
#include "binary_search_tree.h"

#define TREE_STACK_SIZE  50  /*栈的大小*/

tree_node_t *tree_stack[TREE_STACK_SIZE];
int tree_stack_top = -1;

int tree_stack_empty()
{
    if(-1 == tree_stack_top)
		return 1;

	return 0;
}

int tree_stack_full()
{
    if(TREE_STACK_SIZE-1 == tree_stack_top)
		return 1;

	return 0;
}

int tree_stack_push(tree_node_t *node)
{
    if(tree_stack_full())
    {
        printf("\r\npush error stack full");
		return 0;
    }

	tree_stack_top++;

	tree_stack[tree_stack_top] = node;

	return 1;
}

tree_node_t *tree_stack_pop()
{
    if(tree_stack_empty())
    {        
        printf("\r\npop error stack empty");
	    return (tree_node_t *)0xffffffff;
    }

	return tree_stack[tree_stack_top--];
}

/*获得最近一次压栈的值*/
tree_node_t *tree_stack_gettop()
{
    if(tree_stack_empty())
    {        
        printf("\r\nget top error stack empty");
	    return (tree_node_t *)0xffffffff;
    }

	return tree_stack[tree_stack_top];
}

