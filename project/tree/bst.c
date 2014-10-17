#include<stdio.h>
#include"bst.h"

int nodedepth = 0;
int nodeindex = 0;
int treedepth = 0;

bstnode *bst_search(bstnode *proot, int key)
{
    if(NULL == proot || key == proot->bst_key)
		return proot;

	if(key < proot->bst_key)
		return bst_search(proot->bst_left,key);
	else
		return bst_search(proot->bst_right,key);
}

bstnode *bst_insert(bstnode *root_node,int key)
{
    if(NULL != bst_search(root_node,key))
    {
        printf("\r\nkey %d alread in tree");
		return root_node;
    }
	
    nodedepth++;
	
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
		//root_node->bst_depth = nodedepth - 1;		
		//root_node->bst_index = nodeindex;
	} 
	else if(key < root_node->bst_key)/*插入左子树*/
	{	    
	    nodeindex = nodeindex*2;
		root_node->bst_left = bst_insert(root_node->bst_left,key);
		root_node->bst_left->bst_parent = root_node;
	} 
	else 
	{
	    nodeindex = nodeindex*2 + 1;
		root_node->bst_right = bst_insert(root_node->bst_right,key);
		root_node->bst_right->bst_parent = root_node;
	}

    nodeindex = nodeindex/2;
    nodedepth--;
	
	return root_node;
}

bstnode *bst_delete(bstnode *proot,int key)
{    
	bstnode *pdel;   /*待删除节点*/
	bstnode *pchild; /*待删除节点的子节点*/
	bstnode *pnode = NULL;

    pnode = bst_search(proot,key);
	
	if(NULL == pnode)
    {
        printf("\r\nkey %d not in tree");
		return proot;
    }

    /*确定待删除的节点，pnode或者pnode的后继*/
    if(NULL == pnode->bst_left || NULL == pnode->bst_right)
		pdel = pnode;
	else
		pdel = tree_successor(pnode);/*有两个孩子,一定有后继*/

	/*pdel最多有一个子女，找到非NULL子女，没有子女pchild为空*/
	if(NULL != pdel->bst_left)
		pchild = pdel->bst_left;
	else
		pchild = pdel->bst_right;

    /*pchild非空,说明有且只有一个孩子*/
	if(NULL != pchild)
		pchild->bst_parent = pdel->bst_parent;/*先把要删除节点的子节点的父节点设置好*/

	/*设置要删除节点的父节点的子节点*/

	if(NULL == pdel->bst_parent)
	{
        proot = pchild;/*要删除节点没有父节点,说明它是树根*/
	}
	else
	{
		if(pdel == pdel->bst_parent->bst_left)
			pdel->bst_parent->bst_left = pchild;
		else
			pdel->bst_parent->bst_right = pchild;
	}

	if(pnode != pdel)/*条件成立说明删除的是后继,此时要修改key*/
	{
		pnode->bst_key = pdel->bst_key;
		
	}

	free(pdel);

    bst_set(proot);
	
	return proot;	
}

void bst_inorder(bstnode *root)
{  
    bstnode *parent;

    if(NULL != root)
    {
        parent = root->bst_parent;
		
        bst_inorder(root->bst_left);
		
		printf("\r\nkey:%2d depth:%d index:%d  ",root->bst_key,root->bst_depth,root->bst_index);

		if(NULL != parent)			
		    printf("key:%2d depth:%d index:%d",parent->bst_key,parent->bst_depth,parent->bst_index);
		
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

int bst_depth(bstnode *root)
{ 
    treedepth = 0;
    nodedepth++;
	
    if(NULL != root)
    {
        bst_depth(root->bst_left);		
		bst_depth(root->bst_right);
    }
	
	nodedepth--;
	
	if(nodedepth > treedepth)
		treedepth = nodedepth;

	return treedepth;
}

void bst_set(bstnode *pnode)
{  
    bstnode *parent = NULL;

	nodedepth++;
	nodeindex = nodeindex*2;

    if(NULL != pnode)
    {
        parent = pnode->bst_parent;
		
		if( (NULL != parent) && (pnode == parent->bst_right) )
			nodeindex++;
		
		pnode->bst_depth = nodedepth - 1;
		pnode->bst_index = nodeindex;
		
        bst_set(pnode->bst_left);		
		bst_set(pnode->bst_right);
    }
	
	nodedepth--;
    nodeindex = nodeindex/2;	
}

#if 1/*********************************************************************/
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
	test_tree_root = bst_insert(test_tree_root,18);
	test_tree_root = bst_insert(test_tree_root,19);
	test_tree_root = bst_insert(test_tree_root,20);
	
	printf("\r\ntree depth : %d",bst_depth(test_tree_root));
	bst_inorder(test_tree_root);
	
	bst_set(test_tree_root);
	
	printf("\r\ntree depth : %d",bst_depth(test_tree_root));
	bst_inorder(test_tree_root);

    printf("\r\n");

	tree_struct_after_init();
	tree_show(test_tree_root,bst_depth(test_tree_root)+1);
	
	//printf("\r\ntree depth : %d",bst_depth(test_tree_root));

	bst_destory(test_tree_root);
}

void bst_test_delete()
{
    test_tree_root = bst_insert(test_tree_root,15);
	test_tree_root = bst_insert(test_tree_root,10);
	test_tree_root = bst_insert(test_tree_root,25);

    test_tree_root = bst_delete(test_tree_root,15);
	test_tree_root = bst_delete(test_tree_root,10);

    #if 0
	printf("\r\ntree depth : %d rootkey:%d",bst_depth(test_tree_root),test_tree_root->bst_key);	
	test_tree_root = bst_delete(test_tree_root,15);	
	printf("\r\ntree depth : %d rootkey:%d",bst_depth(test_tree_root),test_tree_root->bst_key);	
	tree_show(test_tree_root,bst_depth(test_tree_root));
	#endif
	
	tree_show(test_tree_root,bst_depth(test_tree_root));

	bst_destory(test_tree_root);

}


void bst_test()
{
    bst_test_insert();
    //bst_test_delete();
}
#endif
