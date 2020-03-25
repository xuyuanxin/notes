II Sorting and Order Statistics  

# Heapsort 

heapsort’s running time is $O(nlgn)$  

heapsort sorts in place: only a constant number of array elements are stored outside the input array at any time.  

## 6.1 Heaps  

The (binary) heap data structure is an array object that we can view as a nearly complete binary tree (see Section B.5.3), as shown in Figure 6.1. Each node of the tree corresponds to an element of the array. The tree is completely filled on all levels except possibly the lowest, which is filled from the left up to a point.  

 ![sort_01](.\images\sort_01.png)

Figure 6.1 A max-heap viewed as (a) a binary tree and (b) an array. The number within the circle at each node in the tree is the value stored at that node. The number above a node is the corresponding index in the array. Above and below the array are lines showing parent-child relationships; parents are always to the left of their children. The tree has height three; the node at index 4 (with value 8) has height one.  

The root of the tree is A[1], (index from 1) and given the index i of a node, we can easily compute the indices of its parent, left child, and right child:  

```python
PARENT(i)
1    return 下取整(i/2)
LEFT(i)
1    return 2i
RIGHT(i)
1    return 2i + 1
```

$\lfloor x \rfloor$

There are two kinds of binary heaps: max-heaps and min-heaps. In both kinds, the values in the nodes satisfy a heap property. In a max-heap, the max-heap property is that for every node i other than the root,  

```python
A[PARENT(i)] >= A[i]
```

that is, the value of a node is at most the value of its parent. Thus, the largest element in a max-heap is stored at the root. A min-heap is organized in the opposite way; the min-heap property is that for every node i other than the root,  

```python
A[PARENT(i)] <= A[i]
```

The smallest element in a min-heap is at the root.  

Viewing a heap as a tree, we define the **height** of a node in a heap to be the number of edges on the longest simple downward path from the node to a leaf, and we define the height of the heap to be the height of its root.  Since a heap of n elements is based on a complete binary tree, its height is $\Theta(lgn)$ (see Exercise 6.1-2). We shall see that the basic operations on heaps run in time at most proportional to the height of the tree and thus take $O(lgn)$ time.   













