#include<stdio.h>
#include"bst.h"

int treedepth = 0;
int treeindex = 0;

bstnode *bst_insert(bstnode *root_node,int key)
{
    treedepth++;
	
	if(root_node == NULL) 
	{
		root_node = (bstnode *)malloc(sizeof(bstnode));
		if(NULL == root_node)
		{
			return NULL;
		}
		
		root_node->bst_left  = NULL;
		root_node->bst_right = NULL;
		root_node->bst_key   = key;
		root_node->bst_depth = treedepth - 1;		
		root_node->bst_index = treeindex;
	} 
	else if(key < root_node->bst_key)/*插入左子树*/
	{	    
	    treeindex = treeindex*2;
		root_node->bst_left = bst_insert(root_node->bst_left,key);
		root_node->bst_left->bst_parent = root_node;
	} 
	else 
	{
	    treeindex = treeindex*2 + 1;
		root_node->bst_right = bst_insert(root_node->bst_right,key);
		root_node->bst_right->bst_parent = root_node;
	}

    treeindex = treeindex/2;
    treedepth--;
	
	return root_node;
}

bstnode *bst_delete(bstnode *proot,bstnode *pnode)
{    
	bstnode *pdel;      /*待删除节点，可能就是pnode(pnode最多有一个孩子)，也可能使pnode的后继(pnode有两个孩子)*/
	bstnode *pchild_del;/*待删除节点的子节点*/

    /*确定待删除的节点，pnode或者pnode的后继*/
    if(NULL == pnode->bst_left || NULL == pnode->bst_right)
		pdel = pnode;
	else
		pdel = tree_successor(pnode);

	/*pdel最多有一个子女，找到非NULL子女，没有子女pchild_del为空*/
	if(NULL != pdel->bst_left)
		pchild_del = pdel->bst_left;
	else
		pchild_del = pdel->bst_right;

    /*pchild_del非空,说明有且只有一个孩子*/
	if(NULL != pchild_del)
		pchild_del->bst_parent = pdel->bst_parent;

	if(NULL == pdel->bst_parent)
	{
        proot = pchild_del;
	}
	else
	{
		if(pdel == pdel->bst_parent->bst_left)
			pdel->parent->bst_left = pchild_del;
		else
			pdel->parent->bst_right = pchild_del;
	}

	if(pnode != pdel)
		pnode->bst_key = pdel->bst_key;

	return proot;	
}

void bst_inorder(bstnode *root)
{  
    if(NULL != root)
    {
        bst_inorder(root->bst_left);
		
		printf("\r\nkey:%d depth:%d index:%d",root->bst_key,root->bst_depth,root->bst_index);

		if(NULL != root->bst_parent)
			printf(" pkey:%d",root->bst_parent->bst_key);
		
		bst_inorder(root->bst_right);
    }
}

void bst_destory(bstnode *root_node)
{
	if( NULL == root_node)
		return;
	
	bst_destory(root_node->bst_left);
	bst_destory(root_node->bst_right);
	
	free(root_node);
	
	root_node = NULL;
}

bstnode *bst_min (bstnode *pnode)
{
    if(NULL == pnode){
		return NULL;
    }
	
    while(NULL != pnode->bst_left){
        pnode = pnode->bst_left;
    }

	return pnode;
}

bstnode *bst_max (bstnode *pnode)
{
    if(NULL == pnode){
		return NULL;
    }

    while(NULL != pnode->bst_right){
        pnode = pnode->bst_right;
    }

	return pnode;
}

bstnode *bst_successor (bstnode *pnode)
{
    bstnode *pparent;

    if(NULL != pnode->bst_right)
		return tree_min(pnode->bst_right);

	pparent = pnode->bst_parent;

	while(NULL != pparent && pnode == pparent->bst_right)
	{
	    pnode   = pparent;
		pparent = pparent->bst_parent;
	}

	return pparent;
}

bstnode *bst_predecessor(bstnode *pnode)
{
    bstnode *pparent;

    if(NULL != pnode->bst_left)
		return tree_max(pnode->bst_left);

	pparent = pnode->bst_parent;

	while(NULL != pparent && pnode == pparent->bst_left)
	{
	    pnode   = pparent;
		pparent = pparent->bst_parent;
	}

	return pparent;
}


/*********************************************************************/
bstnode *test_tree_root = NULL;

void bst_test_insert()
{
    test_tree_root = bst_insert(test_tree_root,10);
	test_tree_root = bst_insert(test_tree_root,9);
	test_tree_root = bst_insert(test_tree_root,7);
	test_tree_root = bst_insert(test_tree_root,8);
	test_tree_root = bst_insert(test_tree_root,11);
	test_tree_root = bst_insert(test_tree_root,15);
	test_tree_root = bst_insert(test_tree_root,17);
	test_tree_root = bst_insert(test_tree_root,16);

	bst_inorder(test_tree_root);
	
	tree_show(test_tree_root);

	bst_destory(test_tree_root);

}

void bst_test()
{
    bst_test_insert();
}

