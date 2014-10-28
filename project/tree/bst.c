#include<stdio.h>
#include<stdlib.h>
#include"bst.h"
#include"queue.h"

int nodedepth = 0;
int nodeindex = 0;
int treedepth = 0;
char bstdbg_flag = 0;
queue_s *bstqueue = NULL;

void bst_levelorder(bstnode *root)
{
	bstnode *bstnode;
	int cnt = 0;
	
	if(NULL == root)
	{
		return;
	}

	enqueue(bstqueue,0,root);

	while(0 == queue_empty(bstqueue))
	{	
		dequeue(bstqueue,NULL,&bstnode);
		
		if(NULL != bstnode)
		{
		    printf("%02d  ",bstnode->bst_key);
			//printf("\r\nkey:%d	depth:%d  index: %d",bstnode->bst_key,bstnode->bst_depth,bstnode->bst_index);
		}

		if(NULL != bstnode->bst_left)
			enqueue(bstqueue,0,bstnode->bst_left);

		if(NULL != bstnode->bst_right)
			enqueue(bstqueue,0,bstnode->bst_right);
	}
}

void bst_levelorder_v2(bstnode *root)
{
    return;
}

void bst_preorder(bstnode *root)
{
    return;
}

void bst_preorder_v2(bstnode *root)
{
	bstnode *node = NULL;
	
	node = root;

	while(node!=NULL||!stack_empty())
	{
		while(NULL != node)
		{
			if(NULL != node)
			{
				printf("%02d  ",node->bst_key);
			}
			
			stack_push(node);
			node = node->bst_left;
		}

		if(!stack_empty())
		{
			node = stack_pop();
			node = node->bst_right;
		}
	}
}

void bst_inorder(bstnode *root)
{  
    bstnode *parent;

    if(NULL != root)
    {
        parent = root->bst_parent;
		
        bst_inorder(root->bst_left);
		
		printf("\r\nkey:%02d depth:%d index:%d  ",root->bst_key,root->bst_depth,root->bst_index);

		if(NULL != parent)			
		    printf("key:%02d depth:%d index:%d",parent->bst_key,parent->bst_depth,parent->bst_index);
		
		bst_inorder(root->bst_right);
    }
}

void bst_inorder_v2(bstnode *root)
{
	bstnode *node = NULL;
	
	node = root;

	while(node!=NULL||!stack_empty())
	{
		while(NULL != node)
		{
			stack_push(node);
			node = node->bst_left;
		}

		if(!stack_empty())
		{
			node = stack_pop();
			
			if(NULL != node)
			{
				printf("%02d  ",node->bst_key);
			}
			
			node = node->bst_right;
		}
	}
}

void bst_postorder(bstnode *root)
{  
	if(NULL != root)
	{		
		bst_postorder(root->bst_left); 
		bst_postorder(root->bst_right);
		printf("\r\n%02d  ",root->bst_key);
	}
}

void bst_postorder_v2(bstnode *root)
{
	bstnode *pre = NULL;
	bstnode *cur = NULL;

	if(NULL == root)
		return;
	
	(void)stack_push(root);

	while(!stack_empty())
	{
		cur = stack_pop();
		(void)stack_push(cur);/*只想看栈顶元素，并不想弹出*/

		if(((NULL == cur->bst_right) && (NULL == cur->bst_left)) || 
		   ((NULL != pre) && (pre==cur->bst_right||pre==cur->bst_left)))
		{
			/*如果当前结点没有孩子结点或者孩子节点都已被访问过*/
			if(NULL != cur)
			{
				printf("%02d  ",cur->bst_key);
			}

			(void)stack_pop();
			pre=cur; 
		}
		else
		{
			if(cur->bst_right!=NULL)/*注意先右后左入栈(这样才能左先出栈)*/
				stack_push(cur->bst_right);
			if(cur->bst_left!=NULL)    
				stack_push(cur->bst_left);
		}
	}
}

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
		bst_dbgp("\r\nnew node:%p key:%d insert tree",root_node,root_node->bst_key);
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

bstnode *bst_insert_v2(bstnode *proot,int key)
{
    bstnode *pfather = NULL;
	bstnode *pnode = NULL;
	bstnode *tmp     = proot;

	while(NULL != tmp)
	{
	    pfather = tmp;

		if(key < tmp->bst_key)
			tmp = tmp->bst_left;
		else
			tmp = tmp->bst_right;
	}

	pnode = (bstnode *)malloc(sizeof(bstnode));
	if(NULL == pnode)
	{
	    printf("\r\ninsert error malloc fail!");
		return proot;
	}
	
	pnode->bst_left   = NULL;
	pnode->bst_right  = NULL;
	pnode->bst_key    = key;	
	pnode->bst_parent = pfather;
	
	bst_dbgp("\r\nnew node:%p key:%d insert tree",pnode,pnode->bst_key);

	if(NULL == pfather)
	{
		return pnode;/*树为空，node作为根节点*/
	}
	else
	{
	    if(pnode->bst_key < pfather->bst_key)
			pfather->bst_left = pnode;
		else
			pfather->bst_right = pnode;
	}
	
	return proot;
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

void bst_destory(bstnode **root)
{
	bstnode *node = *root;

	if( NULL == node)
		return;
	
	bst_destory(&node->bst_left);
	bst_destory(&node->bst_right);
	
	bst_dbgp("\r\nfree node:%p key:%d ",node,node->bst_key);
	
	free(node);
	*root = NULL;
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

void bst_clear(bstnode *pnode)
{
	if(NULL != pnode)
	{
		bst_clear(pnode->bst_left);
		pnode->bst_depth = 0;
		pnode->bst_index = 0;
		bst_clear(pnode->bst_right);
	}
}


#if 1/*********************************************************************/
bstnode *test_tree_root = NULL;

void bst_test_order()
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
	
	bst_set(test_tree_root);
	
	printf("\r\ntree depth  : %d",bst_depth(test_tree_root));
	tree_show(test_tree_root,bst_depth(test_tree_root)+1);
	
	printf("\r\nlevel order : ");
	bst_levelorder(test_tree_root);

	printf("\r\npreorder v2 : ");
	bst_preorder_v2(test_tree_root);	

	printf("\r\ninorder v2  : ");
	bst_inorder_v2(test_tree_root);	

	printf("\r\npostorder v2: ");
	bst_postorder_v2(test_tree_root);
	
	bst_destory(&test_tree_root);
}

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
		
	bst_set(test_tree_root);

	tree_show(test_tree_root,bst_depth(test_tree_root)+1);
	
	bst_destory(&test_tree_root);

	printf("\r\ninsert v2 root:%p",test_tree_root);

    test_tree_root = bst_insert_v2(test_tree_root,10);
	test_tree_root = bst_insert_v2(test_tree_root,9);
	test_tree_root = bst_insert_v2(test_tree_root,7);
	test_tree_root = bst_insert_v2(test_tree_root,8);
	test_tree_root = bst_insert_v2(test_tree_root,11);
	test_tree_root = bst_insert_v2(test_tree_root,15);
	test_tree_root = bst_insert_v2(test_tree_root,17);
	test_tree_root = bst_insert_v2(test_tree_root,16);
	test_tree_root = bst_insert_v2(test_tree_root,18);
	test_tree_root = bst_insert_v2(test_tree_root,19);
	test_tree_root = bst_insert_v2(test_tree_root,20);
		
	bst_set(test_tree_root);
	tree_show(test_tree_root,bst_depth(test_tree_root)+1);
	
	bst_destory(&test_tree_root);	
}

void bst_test_delete()
{
    test_tree_root = bst_insert(test_tree_root,15);
	test_tree_root = bst_insert(test_tree_root,10);
	test_tree_root = bst_insert(test_tree_root,25);
	
	bst_set(test_tree_root);
	tree_show(test_tree_root,bst_depth(test_tree_root)+1);

    test_tree_root = bst_delete(test_tree_root,15);
	test_tree_root = bst_delete(test_tree_root,10);

	printf("\r\ndelete ");
	bst_set(test_tree_root);
	tree_show(test_tree_root,bst_depth(test_tree_root)+1);
	
	bst_destory(&test_tree_root);

}

void bst_test_destory()
{
    bstdbg_flag = 1;
    printf("\r\ntree root 1: %p",test_tree_root);
    test_tree_root = bst_insert(test_tree_root,15);
	test_tree_root = bst_insert(test_tree_root,10);
	test_tree_root = bst_insert(test_tree_root,25);	
	test_tree_root = bst_insert(test_tree_root,30);	
	test_tree_root = bst_insert(test_tree_root,5);	
	
    printf("\r\ntree root 2: %p",test_tree_root);
	
	bst_destory(&test_tree_root);
	
    printf("\r\ntree root 3: %p",test_tree_root);
	
    bstdbg_flag = 0;
}

void bst_test()
{
    bstqueue = queue_create("bst queue",100);
	
    if(NULL == bstqueue)
    {
        printf("\r\ncreate bst queue fail!!!");
	  	return;
    }
	
	//bst_test_order();
    bst_test_insert();
    //bst_test_delete();
    //bst_test_destory();

	queue_destory(bstqueue);
}
#endif

