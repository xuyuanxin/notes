

# Tree

# Binary Search Trees

Basic operations on a binary search tree take time proportional to the height of the tree. For a complete binary tree with n nodes, such operations run in $\Theta(lgn)$ worst-case time. If the tree is a linear chain of n nodes, however, the same operations take $\Theta(n)$ worst-case time. We shall see in Section 12.4 that the expected height of a randomly built binary search tree is $O(lgn)$, so that basic dynamic-set operations on such a tree take $\Theta(lgn)$ time on average.  

## What is a binary search tree  

A binary search tree is organized, as the name suggests, in a binary tree, as shown in Figure 12.1.  In addition to a key and satellite data, each node contains attributes left, right, and p that point to the nodes corresponding to its left child, its right child, and its parent, respectively. If a child or the parent is missing, the appropriate attribute contains the value NIL. The root node is the only node in the tree whose parent is NIL.     

![](.\images\binary_search_tree_01.png)

> Figure 12.1 (a) A binary search tree on 6 nodes with height 2. (b) A less efficient binary search tree with height 4 that contains the same keys.  
>

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

## Querying a binary search tree  

We often need to search for a key stored in a binary search tree. Besides the SEARCH operation, binary search trees can support such queries as MINIMUM, MAXIMUM, SUCCESSOR, and PREDECESSOR.   

### Searching  

![binary_search_tree_02](.\images\binary_search_tree_02.png)

> Figure 12.2 Queries on a binary search tree. To search for the key 13 in the tree, we follow the path 15->6->7->13 from the root. The minimum key in the tree is 2, which is found by following left pointers from the root. The maximum key 20 is found by following right pointers from the root. The successor of the node with key 15 is the node with key 17, since it is the minimum key in the right subtree of 15. The node with key 13 has no right subtree, and thus its successor is its lowest ancestor whose left child is also an ancestor. In this case, the node with key 15 is its successor.  

Given a pointer to the root of the tree and a key k, TREE-SEARCH returns a pointer to a node with key k if one exists; otherwise, it returns NIL.  

```python
TREE-SEARCH(x,k)
1 if x == NIL or k == x.key
2      return x
3 if k < x.key
4      return TREE-SEARCH(x.left,k)
5 else return TREE-SEARCH(x.right,k)
```

The nodes encountered during the recursion form a simple path downward from the root of the tree, and thus the running time of TREE-SEARCH is  $O(h)$, where h is the height of the tree.  

We can rewrite this procedure in an iterative fashion by “unrolling” the recursion into a while loop. On most computers, the iterative version is more efficient.  

```python
ITERATIVE-TREE-SEARCH(x,k)
1 while x != NIL and k != x.key
2     if k < x.key
3         x = x.left
4     else x = x.right
5 return x
```

### Minimum and maximum  

If a node x has no left subtree, then since every key in the right subtree of x is at least as large as x.key, the minimum key in the subtree rooted at x is x.key. If node x has a left subtree, then since no key in the right subtree is smaller than x.key and every key in the left subtree is not larger than x.key, the minimum key in the subtree rooted at x resides in the subtree rooted at x.left. The pseudocode for TREE-MAXIMUM is symmetric.

```python
TREE-MINIMUM(x)
1 while x.left != NIL
2     x = x.left
3 return x

TREE-MAXIMUM(x)
1 while x.right != NIL
2     x = x.right
3 return x
```

Both of these procedures run in $O(h)$ time on a tree of height h since, as in TREESEARCH, the sequence of nodes encountered forms a simple path downward from the root.  

### Successor and predecessor  

Given a node in a binary search tree, sometimes we need to find its successor in the sorted order determined by an inorder tree walk. If all keys are distinct, the successor of a node x is the node with the smallest key greater than x.key. The following procedure returns the successor of a node x in a binary search tree if it exists, and NIL if x has the largest key in the tree:    

```python
TREE-SUCCESSOR(x)
1 if x.right != NIL
2     return TREE-MINIMUM(x.right)
3 y = x.p
4 while y != NIL and x == y.right
5     x = y
6     y = y.p
7 return y
```

We break the code for TREE-SUCCESSOR into two cases. 

- If the right subtree of node x is nonempty, then the successor of x is just the leftmost node in x’s right subtree, which we find in line 2 by calling TREE-MINIMUM(x.right). For example, the successor of the node with key 15 in Figure 12.2 is the node with key 17.  
- On the other hand, as Exercise 12.2-6 asks you to show, if the right subtree of node x is empty and x has a successor y, then y is the lowest ancestor of x whose left child is also an ancestor of x. In Figure 12.2, the successor of the node with key 13 is the node with key 15. To find y, we simply go up the tree from x until we encounter a node that is the left child of its parent; lines 3–7 of TREE-SUCCESSOR handle this case.  

The running time of TREE-SUCCESSOR on a tree of height h is $O(h)$, since we either follow a simple path up the tree or follow a simple path down the tree. The procedure TREE-PREDECESSOR, which is symmetric to TREE-SUCCESSOR, also runs in time $O(h)$.  

