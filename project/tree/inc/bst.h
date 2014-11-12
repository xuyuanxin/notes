/********************************************************************
                  二叉查找树 binary search tree
********************************************************************
 1 左子树的关键字 <= 父节点的关键字，右子树的关键字 >= 父节点的关键字
 2 中序遍历(先左后右)按key从小到大输出
 3 规定每个节点都是它自己的祖先

 参考
 1 算法导论
 2 http://www.cnblogs.com/dolphin0520/archive/2011/08/25/2153720.html
 ********************************************************************/

/*
              A
         /          \
        B           C
    /       \    /      \
   D        E   F        G
*/


#ifndef __BST_H__
#define __BST_H__

#define BST_NAMELEN 32 /*包括最后的\0*/

/*二叉查找树节点结构*/
typedef struct _bstnode
{
	struct _bstnode *bst_parent; /*父节点*/
	struct _bstnode *bst_left;   /*左孩子*/
	struct _bstnode *bst_right;  /*右孩子*/
	int              bst_key;    /*节点key值*/
	int              bst_depth;  /*节点高度，根节点是0*/
	int              bst_index;  /*节点在本层的索引 第一个是0 第二个是1*/
}bstnode;

/*******************************************************************************
广度优先遍历二叉树。广度优先周游二叉树(层序遍历)是用队列来实现的，
从二叉树的第一层（根结点）开始，自上至下逐层遍历；
在同一层中，按照从左到右的顺序对结点逐一访问。
按照从根结点至叶结点、从左子树至右子树的次序访问二叉树的结点。
算法：
1初始化一个队列，并把根结点入列队；
2当队列为非空时，循环执行步骤3到步骤5，否则执行6；
3出队列取得一个结点，访问该结点；
4若该结点的左子树为非空，则将该结点的左子树入队列；
5若该结点的右子树为非空，则将该结点的右子树入队列；
6结束。
*******************************************************************************/
extern void bst_levelorder(bstnode *root);


/*******************************************************************************
 对于任一结点P：
 1)访问结点P，并将结点P入栈;
 2)结点P的左孩子若为空，则取栈顶结点并进行出栈操作，并将栈顶结点的右孩子置为当前
   的结点P，循环至1);若不为空，则将P的左孩子置为当前的结点P;
 3)直到P为NULL并且栈为空，则遍历结束。

 就是一路访问左孩子，然后入栈。没有左孩子了原路返回，也就是逐个出栈，出栈的过程
 中遇到右子树非空的，就再重复上述动作。
 ******************************************************************************/
extern void bst_preorder_v2(bstnode *root);



/*树的中序遍历(递归实现):按key的从小到大输出*/
extern void bst_inorder(bstnode *root);

/********************************************************************************
 树的中序遍历(非递归实现):按key的从小到大输出
 一路向左，左入栈，直到没有左。
 然后原路返回，即逐个出栈，每出来一个先访问它，
 如果它的右子树为空，弹出下一个
 若果它的右子树非空，重复上述过程
 ******************************************************************************/
extern void bst_inorder_v2(bstnode *root);

/*后续遍历递归实现*/
extern void bst_postorder(bstnode *root);

/*******************************************************************************
  后序遍历按照“左孩子-右孩子-根结点”的顺序进行访问。
  要保证根结点在左孩子和右孩子访问之后才能访问，因此对于任一结点P，先将其入栈。
  1 P不存在左孩子和右孩子，则可以直接访问它；
  2 其左孩子和右孩子都已被访问过了，则同样可以直接访问该结点。
  若非上述两种情况:
  则将P的右孩子和左孩子依次入栈
  这样就保证了每次取栈顶元素的时候，左孩子在右孩子前面被访问，左孩子和右孩子都
  在根结点前面被访问。
  
  如何判断:左孩子和右孩子都已被访问过了
  首先注意入栈的方式一定是父节点最先，右子树次之，左子树最后
  如果发现上一个弹出的节点是栈顶节点的左孩子或者右孩子，那么栈顶节点的左孩子和
  右孩子都被访问过了。
   
  例如
              A
         /          \
        B           C
    /       \    /      \
   D        E   F        G
   1 A入栈，发现A不满足访问条件，然后右子树入栈，左子树入栈 此时栈的内容是:A C B
   2 查看栈顶(注意不是弹出)是B，重复1的方法，之后栈的内容是 A C B E D
   3 查看栈顶(注意不是弹出)是D，满足访问条件，然后弹出并输出:D
   4 查看栈顶(注意不是弹出)是E，满足访问条件，然后弹出并输出:E
   5 查看栈顶(注意不是弹出)是B，满足访问条件，然后弹出并输出:B
   6 查看栈顶(注意不是弹出)是C，不满足访问条件，重复1的方法，栈的内容是 A C G F
   7 查看栈顶(注意不是弹出)是F，满足访问条件，然后弹出并输出:F
   8 查看栈顶(注意不是弹出)是G，满足访问条件，然后弹出并输出:G
   9 查看栈顶(注意不是弹出)是C，满足访问条件，然后弹出并输出:C
  10 查看栈顶(注意不是弹出)是C，满足访问条件，然后弹出并输出:A
  11 栈空结束
*******************************************************************************/
extern void bst_postorder_v2(bstnode *root);


/*查找@key是否在树@proot中*/
extern bstnode *bst_search(bstnode *proot, int key);


/*
@root_node:树的根节点
@key      :待插入的关键字  
return    :插入@key后,树的根节点(除了首次插入,根节点无变化)*/
extern bstnode *bst_insert(bstnode *root_node,int key);

/*插入的非递归实现*/
extern bstnode *bst_insert_v2(bstnode *proot,int key);



/*********************************************************************************************************
  node无子女    : 直接删除。把node父节点的孩子节点置NULL.
  node有一个子女: 直接删除，把node父节点的孩子置为node节点的孩子.
  node有两个子女: 删除node的后继(肯定没有左子女)，然后把node的key值置为其后继的key值.
                  即此时node节点位置不变,删除后继后,把node节点的key值修改一下就可以了.
                  比如中序遍历是: 3 6 9,删除6(6的孩子是3 9),那么只要把6的后继9替代6就可以了,中序遍历顺序不变

  1 根据pnode找到真正要删除的节点pdel,可能就是pnode，也可能使pnode的后继
  2 pchild_del置为pdel的非空子节点，找不到则置空
  3 pchild_del非空,且无父节点，说明pchild_del是根节点，好办让pchild_del的娃当根节点。
  4 删除pdel，首先判断pdel是其父亲的左孩子还是右孩子，是左孩子就把自己的孩子pchild_del置为自己父亲的左孩子。
  5 最后如果发现pdel不是入参pnode，说明pnode有两个孩子，把pnode的key值置为其后继的key值
  **********************************************************************************************************
   功能  : 把key值为@key的节点从树中删除，树的根节点是@proot
   返回值: 树的根节点(可能变化)
  **********************************************************************************************************/
extern bstnode *bst_delete(bstnode *proot,int key);


/*销毁树@root_node,释放节点*/
extern void bst_destory(bstnode **root_node);


/*以节点@pnode为根的树的最小节点,也就是最左的节点*/
extern bstnode *tree_min (bstnode *pnode);

/*以节点@pnode为根的树的最大节点,也就是最右的节点*/
extern bstnode *tree_max (bstnode *pnode);


/***********************************************************************************
  中序遍历的后继节点:按中序遍历输出，在其后输出的那个节点。
  1 p右子树非空,后继为其右子树的最左节点即key值最小那个
    (因为中序遍历是先左后右,既然右子树非空,后继肯定在其中).
  2 p右子树为空，则寻找其父节点。如果p是其父节点的右孩子，那么其父节点已经输出过了。
    以父节点为当前节点继续寻父，直到找到一个节点，这个节点是其父节点的左孩子。
    可能最终也没有找到这样的节点，那么p就是树中最后一个输出节点，没有后继
************************************************************************************
  功能  :返回@pnode节点的后继节点
  返回值:后继节点,没有后继返回NULL
************************************************************************************/
extern bstnode *tree_successor (bstnode *pnode);


/****************************************************************************
  找节点node的前驱
  中序前驱:按中序遍历输出，在节点node前输出的那个节点。 
  左孩子不为空:前驱是node左子树的最大节点
  左孩子为空  :前驱是node祖先，且这个祖先的右孩子也是node的祖先
               找node父节点，如果这个父节点是通过左孩子找到的，则继续向上寻找
*****************************************************************************
功能  :返回@pnode节点的前驱节点
返回值:前驱节点,没有后继返回NULL
****************************************************************************/
extern bstnode *tree_predecessor(bstnode *pnode);

/*******************************************************************************
 计算树的高度: The maximum depth is the number of nodes along the longest path 
 from the root node down to the farthest leaf node.
 ******************************************************************************/
int bst_depth(bstnode *root);

/********************************************************************************
 The minimum depth is the number of nodes along the shortest path from the root 
 node down to the nearest leaf node.it is indeed arguable whether the Minimum depth 
 of binary tree {1,2} is 1 or 2, It depends on the way one define the depth, if you 
 want the shortest distance to a null node, then the answer would be 1 else if you 
 want the shortest distance to a null node whose sibling is also a null node, in 
 which case the answer to Binary tree{1,2} would be 2.
 ******************************************************************************/
int bst_depth_min(bstnode *root);

/*判断两颗树是否相同(关键字key和结构都相同)*/
int bst_issame(bstnode *p,bstnode *q);


/*设置树中每个节点的坐标*/
extern void bst_set(bstnode *pnode);

/*清除树中每个节点的坐标*/
extern void bst_clear(bstnode *pnode);


/*dbg printf*/
#define bst_dbgp(fmt, args...)  \
    do \
	{\
	    if(1 == bstdbg_flag)\
		{\
		    printf(fmt,##args);\
		}\
	}while(0)


#endif
