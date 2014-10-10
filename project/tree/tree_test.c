#include<stdio.h>
#include<string.h>
#include "binary_search_tree.h"

tree_node_t node01 = {NULL,NULL,NULL,0};
tree_node_t node02 = {NULL,NULL,NULL,0};
tree_node_t node03 = {NULL,NULL,NULL,0};
tree_node_t node04 = {NULL,NULL,NULL,0};
tree_node_t node05 = {NULL,NULL,NULL,0};
tree_node_t node06 = {NULL,NULL,NULL,0};
tree_node_t node07 = {NULL,NULL,NULL,0};
tree_node_t node08 = {NULL,NULL,NULL,0};
tree_node_t node09 = {NULL,NULL,NULL,0};
tree_node_t node10 = {NULL,NULL,NULL,0};

tree_node_t root = {NULL,NULL,NULL,0} ;


void tree_node_clear()
{
	node01.parent = NULL; node01.left = NULL; node01.right = NULL; node01.key = 0;
	node02.parent = NULL; node02.left = NULL; node02.right = NULL; node02.key = 0;
	node03.parent = NULL; node03.left = NULL; node03.right = NULL; node03.key = 0;
	node04.parent = NULL; node04.left = NULL; node04.right = NULL; node04.key = 0;
	node05.parent = NULL; node05.left = NULL; node05.right = NULL; node05.key = 0;
	
    root.parent = NULL; root.left = NULL; root.right = NULL; root.key = 0;
	
	node06.parent = NULL; node06.left = NULL; node06.right = NULL; node06.key = 0;
	node07.parent = NULL; node07.left = NULL; node07.right = NULL; node07.key = 0;
	node08.parent = NULL; node08.left = NULL; node08.right = NULL; node08.key = 0;
	node09.parent = NULL; node09.left = NULL; node09.right = NULL; node09.key = 0;
	node10.parent = NULL; node10.left = NULL; node10.right = NULL; node10.key = 0;
}

void tree_node_name_show(tree_node_t *pnode)
{
    if(NULL == pnode)  printf("%-7s","NULL");
    
    if(&root == pnode) printf("%-7s","ROOT");
	
    if(&node01 == pnode) printf("%-7s","node01");
	if(&node02 == pnode) printf("%-7s","node02");
	if(&node03 == pnode) printf("%-7s","node03");
	if(&node04 == pnode) printf("%-7s","node04");
	if(&node05 == pnode) printf("%-7s","node05");

	if(&node06 == pnode) printf("%-7s","node06");
	if(&node07 == pnode) printf("%-7s","node07");
	if(&node08 == pnode) printf("%-7s","node08");
	if(&node09 == pnode) printf("%-7s","node09");
	if(&node10 == pnode) printf("%-7s","node10");
}


/*
                                       root(5)[0,0]    
                           /                                 \
                    node01(3)[1,0]                       node02(7)[1,1]
                 /                  \                 /                      \
          node03(2)[2,0]       node04(5)[2,1]      NULL[2,2]           node05(8)[2,3]
               
inorder: 2 3 5 5 7 8
*/
void tree_init()
{
    tree_node_clear();
	
    root.parent = NULL; root.left = &node01; root.right = &node02; root.key = 5;

	node01.parent = &root;    node01.left = &node03;  node01.right = &node04;  node01.key = 3;
	node02.parent = &root;    node02.left = NULL;     node02.right = &node05;  node02.key = 7;
	node03.parent = &node01;  node03.left = NULL;     node03.right = NULL;     node03.key = 2;
	node04.parent = &node01;  node04.left = NULL;     node04.right = NULL;     node04.key = 5;
	node05.parent = &node02;  node05.left = NULL;     node05.right = NULL;     node05.key = 8;

	return ;
}

int tree_test_traverse()
{
    tree_init();
	
	tree_struct_show(&root);

	printf("\r\npreorder recursion: \r\n");
	tree_traverse_preorder_recursion(&root);
	
    printf("\r\npreorder iterative: \r\n");
	tree_traverse_preorder_iterative(&root);

    printf("\r\nInorder recursion: \r\n");
	tree_traverse_inorder_recursion(&root);
	
    printf("\r\nInorder iterative: \r\n");
	tree_traverse_inorder_iterative(&root);


    printf("\r\npostorder recursion: \r\n");
	tree_traverse_postorder_recursion(&root);
	
    printf("\r\npostorder iterative: \r\n");
	tree_traverse_postorder_iterative(&root);	

	return 0;
}
int tree_test_max_min()
{ 
    tree_node_t *pnode_max = NULL;
    tree_node_t *pnode_min = NULL;
	
    tree_init();
	
    pnode_max = tree_max(&root);
    pnode_min = tree_min(&root);

	if(NULL == pnode_max || NULL == pnode_min){
		printf("\r\nmax min test fail!");
		return 1;
	}

	printf("\r\nKey max: %d in ",pnode_max->key);
	tree_node_name_show(pnode_max);
	printf("\r\nKey min: %d in ",pnode_min->key);
	tree_node_name_show(pnode_min);

	return 0;
}

int __tree_test_pre_suc(tree_node_t *pnode)
{ 
    tree_node_t *pnode_pre = NULL;
    tree_node_t *pnode_suc = NULL;
	
    tree_init();
	
    pnode_pre = tree_predecessor(pnode);
    pnode_suc = tree_successor(pnode);

	printf("\r\n| ");
	tree_node_name_show(pnode);
	printf("  ");
	tree_node_name_show(pnode_pre);
	printf("     ");
	tree_node_name_show(pnode_suc);
	printf("  |");
}

int tree_test_pre_suc()
{
    printf("\r\n");
	printf("\r\n+-------------------------------+");
	printf("\r\n|    tree   pre&suc   test      |");
	printf("\r\n|-------------------------------|");	
	printf("\r\n| node   predecessor  successor |");
	printf("\r\n|-------------------------------|");

	__tree_test_pre_suc(&root);
	__tree_test_pre_suc(&node01);
	__tree_test_pre_suc(&node02);
	__tree_test_pre_suc(&node03);	
	__tree_test_pre_suc(&node04);
	__tree_test_pre_suc(&node05);
	
	printf("\r\n+-------------------------------+\r\n");
}


int __tree_test_search(int key)
{   
    tree_node_t *pnode1 = NULL;
	tree_node_t *pnode2 = NULL;
	
    tree_init();

    printf("\r\n| %02d   ",key);
	pnode1 = tree_search(&root,key);
	pnode2 = tree_search_iterative(&root,key);
	tree_node_name_show(pnode1);
	printf(" ");
	tree_node_name_show(pnode2);
	printf("  |");
}

int tree_test_search()
{  
    int key;
	
    printf("\r\n");
	printf("\r\n+-----------------------+");
	printf("\r\n|   tree search test    |");
	printf("\r\n|-----------------------|");	
	printf("\r\n| Key  Result1  Result2 |");
	printf("\r\n|-----------------------|");
	for(key = 0; key < 11; ++key){
        __tree_test_search(key);
	}
	printf("\r\n+-----------------------+\r\n");
}

int tree_test_del()
{ 
    tree_init();
	tree_struct_show(&root);

	printf("\r\n\r\ndel node03 key:%d",node03.key);
	tree_delete(tree,&node03);
	tree_struct_show(tree);
	
	printf("\r\n\r\ndel root key:%d",root.key);
    tree_delete(tree,&root);
	tree_struct_show(tree);

	printf("\r\n\r\ndel node02 key:%d",node02.key);
    tree_delete(tree,&node02);
	tree_struct_show(tree);
}

int tree_test()
{
    tree_test_traverse();
	//tree_test_max_min();
	//tree_test_pre_suc();
	//tree_test_search();
	tree_test_del();
}



