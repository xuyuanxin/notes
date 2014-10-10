#include<stdio.h>
//#include<stddef.h>
#include "binary_search_tree.h"
#include "tree_stack.h"


tree_node_t *tree = &root;

/*广度优先遍历二叉树。广度优先周游二叉树(层序遍历)是用队列来实现的，
从二叉树的第一层（根结点）开始，自上至下逐层遍历；
在同一层中，按照从左到右的顺序对结点逐一访问。
按照从根结点至叶结点、从左子树至右子树的次序访问二叉树的结点。
算法：
1初始化一个队列，并把根结点入列队；
2当队列为非空时，循环执行步骤3到步骤5，否则执行6；
3出队列取得一个结点，访问该结点；
4若该结点的左子树为非空，则将该结点的左子树入队列；
5若该结点的右子树为非空，则将该结点的右子树入队列；
6结束。*/
void tree_traverse_cengci_recursion(tree_node_t *root)
{
}

void tree_traverse_cengci_iterative(tree_node_t *root)
{
}


/*深度优先遍历:包括前序遍历、中序遍历、后序遍历*/
void tree_traverse_preorder_recursion(tree_node_t *root)
{  
    if(NULL != root)
    {
    	tree_node_name_show(root);
		printf("key:%d  depth:%d  index: %d\r\n",root->key,root->depth,root->index);
		
        tree_traverse_preorder_recursion(root->left);
		tree_traverse_preorder_recursion(root->right);
    }
}

void tree_traverse_preorder_iterative(tree_node_t *root)
{
	tree_node_t *node = NULL;
	
	node = root;

	while(node!=NULL||!tree_stack_empty())
	{
		while(NULL != node)
		{
			tree_node_name_show(node);
			printf("key:%d	depth:%d  index: %d\r\n",node->key,node->depth,node->index);
			
			tree_stack_push(node);
			node = node->left;
		}

		if(!tree_stack_empty())
		{
			node = tree_stack_gettop();
			(void)tree_stack_pop();
			node = node->right;
		}
	}
}

void tree_traverse_inorder_recursion(tree_node_t *root)
{  
    if(NULL != root)
    {
        tree_traverse_inorder_recursion(root->left);
		
		tree_node_name_show(root);
		printf("key:%d  depth:%d  index: %d\r\n",root->key,root->depth,root->index);
		
		tree_traverse_inorder_recursion(root->right);
    }
}

void tree_traverse_inorder_iterative(tree_node_t *root)
{
    tree_node_t *node = NULL;
	
	node = root;

    while(node!=NULL||!tree_stack_empty())
    {
	    while(NULL != node)
	    {
	        tree_stack_push(node);
			node = node->left;
	    }

		if(!tree_stack_empty())
		{
		    node = tree_stack_gettop();
			
			tree_node_name_show(node);
			printf("key:%d  depth:%d  index: %d\r\n",node->key,node->depth,node->index);
			
			(void)tree_stack_pop();
			node = node->right;
		}
    }
}


void tree_traverse_postorder_recursion(tree_node_t *root)
{  
    if(NULL != root)
    {
        tree_traverse_postorder_recursion(root->left);
		tree_traverse_postorder_recursion(root->right);

		tree_node_name_show(root);
		printf("key:%d  depth:%d  index: %d\r\n",root->key,root->depth,root->index);
    }
}

/*后序遍历按照“左孩子-右孩子-根结点”的顺序进行访问。
  要保证根结点在左孩子和右孩子访问之后才能访问，因此对于任一结点P，先将其入栈。
  如果P不存在左孩子和右孩子，则可以直接访问它；或者P存在左孩子或者右孩子，但是
  其左孩子和右孩子都已被访问过了，则同样可以直接访问该结点。若非上述两种情况，
  则将P的右孩子和左孩子依次入栈，这样就保证了每次取栈顶元素的时候，左孩子在右
  孩子前面被访问，左孩子和右孩子都在根结点前面被访问。*/
void tree_traverse_postorder_iterative(tree_node_t *root)
{
    tree_node_t *pre = NULL;
	tree_node_t *cur = NULL;

    if(NULL == root)
		return;
	
	(void)tree_stack_push(root);

	while(!tree_stack_empty())
	{
	    cur = tree_stack_gettop();

		if(((NULL == cur->right) && (NULL == cur->left)) || 
		   ((NULL != pre) && (pre==cur->right||pre==cur->left)))
		{
		    /*如果当前结点没有孩子结点或者孩子节点都已被访问过*/
			tree_node_name_show(cur);
			printf("key:%d  depth:%d  index: %d\r\n",cur->key,cur->depth,cur->index);

			(void)tree_stack_pop();
			pre=cur; 
		}
		else
		{
		    if(cur->right!=NULL)
                tree_stack_push(cur->right);
            if(cur->left!=NULL)    
                tree_stack_push(cur->left);
		}
	}
}


tree_node_t *tree_search(tree_node_t *pnode, int key)
{
    if(NULL == pnode || key == pnode->key)
		return pnode;

	if(key < pnode->key)
		return tree_search(pnode->left,key);
	else
		return tree_search(pnode->right,key);
}
tree_node_t *tree_search_iterative (tree_node_t *pnode, int key)
{
    while(NULL != pnode && key != pnode->key)
    {
        if(key < pnode->key)
			pnode = pnode->left;
		else
			pnode = pnode->right;
    }

	return pnode;
}
tree_node_t *tree_min (tree_node_t *pnode)
{
    if(NULL == pnode){
		return NULL;
    }
	
    while(NULL != pnode->left){
        pnode = pnode->left;
    }

	return pnode;
}
tree_node_t *tree_max (tree_node_t *pnode)
{
    if(NULL == pnode){
		return NULL;
    }

    while(NULL != pnode->right){
        pnode = pnode->right;
    }

	return pnode;
}
tree_node_t *tree_successor (tree_node_t *pnode)
{
    tree_node_t *pparent;

    if(NULL != pnode->right)
		return tree_min(pnode->right);

	pparent = pnode->parent;

	while(NULL != pparent && pnode == pparent->right)
	{
	    pnode   = pparent;
		pparent = pparent->parent;
	}

	return pparent;
}
tree_node_t *tree_predecessor(tree_node_t *pnode)
{
    tree_node_t *pparent;

    if(NULL != pnode->left)
		return tree_max(pnode->left);

	pparent = pnode->parent;

	while(NULL != pparent && pnode == pparent->left)
	{
	    pnode   = pparent;
		pparent = pparent->parent;
	}

	return pparent;
}

void tree_insert(tree_node_t *proot,tree_node_t *pnode)
{
    tree_node_t *pfather = NULL;
	tree_node_t *ptree_node = proot;

	while(NULL != ptree_node)
	{
	    pfather = ptree_node;

		if(pnode->key < ptree_node->key)
			ptree_node = ptree_node->left;
		else
			ptree_node = ptree_node->right;
	}

	pnode->parent = pfather;

	if(NULL == pfather)
	{
		tree = pnode;/*树为空，node作为根节点*/
	}
	else
	{
	    if(pnode->key < pfather->key)
			pfather->left = pnode;
		else
			pfather->right = pnode;
	}
}

tree_node_t *tree_delete(tree_node_t *proot,tree_node_t *pnode)
{    
	tree_node_t *pdel;      /*待删除节点，可能就是pnode(pnode最多有一个孩子)，也可能使pnode的后继(pnode有两个孩子)*/
	tree_node_t *pchild_del;/*待删除节点的子节点*/

    /*确定待删除的节点，pnode或者pnode的后继*/
    if(NULL == pnode->left || NULL == pnode->right)
		pdel = pnode;
	else
		pdel = tree_successor(pnode);

	/*pdel最多有一个子女，找到非NULL子女，没有子女pchild_del为空*/
	if(NULL != pdel->left)
		pchild_del = pdel->left;
	else
		pchild_del = pdel->right;

	if(NULL != pchild_del)
		pchild_del->parent = pdel->parent;

	if(NULL == pdel->parent)
	{
        tree = pchild_del;
	}
	else
	{
		if(pdel == pdel->parent->left)
			pdel->parent->left = pchild_del;
		else
			pdel->parent->right = pchild_del;
	}

	if(pnode != pdel)
		pnode->key = pdel->key;

	return pdel;/*返回实际上删除的节点*/	
}
