# Tree

# Binary Search Trees

Basic operations on a binary search tree take time proportional to the height of the tree. For a complete binary tree with n nodes, such operations run in $\Theta(lgn)$ worst-case time. If the tree is a linear chain of n nodes, however, the same operations take $\Theta(n)$ worst-case time. We shall see in Section 12.4 that the expected height of a randomly built binary search tree is $O(lgn)$, so that basic dynamic-set operations on such a tree take $\Theta(lgn)$ time on average.  

## What is a binary search tree  

A binary search tree is organized, as the name suggests, in a binary tree, as shown in Figure 12.1.  In addition to a key and satellite data, each node contains attributes left, right, and p that point to the nodes corresponding to its left child, its right child, and its parent, respectively. If a child or the parent is missing, the appropriate attribute contains the value NIL. The root node is the only node in the tree whose parent is NIL.     

![](.\images\binary_search_tree_01.png)

Figure 12.1 (a) A binary search tree on 6 nodes with height 2. (b) A less efficient binary search tree with height 4 that contains the same keys.  

- binary-search-tree property: Let x be a node in a binary search tree. If y is a node in the left subtree
  of x, then $y.key \le x.key$. If y is a node in the right subtree of x, then $y.key \ge x.key$.  
- inorder tree walk: prints the key of the root of a subtree between printing the values in its left subtree and printing those in its right subtree.  
- preorder tree walk: prints the root before the values in either subtree  
- postorder tree walk: prints the root after the values in its subtrees  

```python
INORDER-TREE-WALK(x)
1 if x != NIL
2     INORDER-TREE-WALK(x.left)
3     print x.key
4     INORDER-TREE-WALK(x.right)
```

As an example, the inorder tree walk prints the keys in each of the two binary search trees from Figure 12.1 in the order 2,5,5,6,7,8.    

- Theorem 12.1: If x is the root of an n-node subtree, then the call INORDER-TREE-WALK(x) takes $\Theta(n)$ time.  