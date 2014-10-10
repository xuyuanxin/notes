/********************************************************************

                         二叉查找树
 1 左子树的关键字 <= 父节点的关键字，右子树的关键字 >= 父节点的关键字
 2 中序遍历(先左后右)按key从小到大输出
 3 规定每个节点都是它自己的祖先
 
 ********************************************************************/
 
typedef struct tree_node_struct
{
	struct tree_node_struct *parent;
	struct tree_node_struct *left;
	struct tree_node_struct *right;
		 
	int key;
	 
	int depth;/*节点高度，根节点是0*/
	int index;/*节点在本层的索引 第一个是0 第二个是1*/
}tree_node_t;

extern tree_node_t node01;
extern tree_node_t node02;
extern tree_node_t node03;
extern tree_node_t node04;
extern tree_node_t node05;
extern tree_node_t node06;
extern tree_node_t node07;
extern tree_node_t node08;
extern tree_node_t node09;
extern tree_node_t node10;
extern tree_node_t root;
extern tree_node_t *tree;

/*最左的节点*/
extern tree_node_t *tree_min (tree_node_t *pnode);


/*最右的节点*/
extern tree_node_t *tree_max (tree_node_t *pnode);


/*中序遍历的后继节点:按中序遍历输出，在其后输出的那个节点。当前节点是@pnode
  1 p右子树非空，后继为其右子树的最左节点(key值最小)
  2 p右子树为空，则寻找其父节点。如果p是其父节点的右孩子，那么其父节点已经输出过了。
    以父节点为当前节点继续寻父，直到找到一个节点，这个节点是其父节点的左孩子。
    可能最终也没有找到这样的节点，那么p就是树中最后一个输出节点，没有后继*/
extern tree_node_t *tree_successor (tree_node_t *pnode);


/*找节点node的前驱
  中序前驱:按中序遍历输出，在节点node前输出的那个节点。 
  左孩子不为空:前驱是node左子树的最大节点
  左孩子为空  :前驱是node祖先，且这个祖先的右孩子也是node的祖先
               找node父节点，如果这个父节点是通过左孩子找到的，则继续向上寻找*/
extern tree_node_t *tree_predecessor(tree_node_t *pnode);

/*查找 递归版本*/
extern tree_node_t *tree_search(tree_node_t *pnode, int key);

/*查找 迭代版本*/
extern tree_node_t *tree_search_iterative (tree_node_t *pnode, int key);

/*中序遍历，先左后右*/
extern void tree_traverse_inorder_recursion(tree_node_t *root);


/**********************************************************************
          函数功能:把节点pnode插入到树中，树的根节点是proot
 ----------------------------------------------------------------------
 1 根据key的大小找到一个为NULL的位置，这个地方就是pnode要插入的地方。
 2 如果proot为空，pnode就作为这颗树的根节点
 **********************************************************************/
extern void tree_insert(tree_node_t *proot,tree_node_t *pnode);


/**********************************************************************
		   函数功能:把节点pnode从树中删除，树的根节点是proot
  ---------------------------------------------------------------------
  node无子女    :直接删除，要判断node是其父节点的左孩子还是右孩子，然后把父节点的左孩子或右孩子置NULL
  node有一个子女:直接删除，要判断node是其父节点的左孩子还是右孩子，然后把父节点的左孩子或右孩子置为node节点的不为空的孩子
  node有两个子女:删除node的后继(没有左子女)，然后把node的key值置为其后继的key值.自己删除了让谁替代自己?当然是后继了。

  1 根据pnode找到真正要删除的节点pdel,可能就是pnode，也可能使pnode的后继
  2 pchild_del置为pdel的非空子节点，找不到则置空
  3 pchild_del非空就给pchild_del找个父亲，如果发现你没有父亲，说明你是根节点啊，好办让你的娃当根节点吧。
  4 删除pdel，首先判断pdel是其父亲的左孩子还是右孩子，是左孩子就把自己的孩子pchild_del置为自己父亲的左孩子。
  5 最后如果发现pdel不是入参pnode，说明pnode有两个孩子，把pnode的key值置为其后继的key值
  ***********************************************************************/
extern tree_node_t *tree_delete(tree_node_t *proot,tree_node_t *pnode);
