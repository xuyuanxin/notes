#ifndef __BST_H__
#define __BST_H__

/*binary search tree*/

#define BST_NAMELEN 32 /*包括最后的\0*/

/*二叉查找树节点结构*/
typedef struct bstnode
{
	struct bstnode *bst_parent; /*父节点*/
	struct bstnode *bst_left;   /*左孩子*/
	struct bstnode *bst_right;  /*右孩子*/
	int             bst_key;    /*节点key值*/
}bstnode_t;

typedef struct bstctr
{
    char       bst_name[32];
	int        bst_nodenums;
	bstnode_t *bst_root;
}bst_ctrl;


#endif
