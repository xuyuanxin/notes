/*******************************************************************************
                         Path Sum(Easy)
 *******************************************************************************
 Given a binary tree and a sum, determine if the tree has a root-to-leaf path such 
 that adding up all the values along the path equals the given sum.

 For example:
 Given the below binary tree and sum = 22,
              5
             / \
            4   8
           /   / \
          11  13  4
         /  \      \
        7    2      1
 return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
     bool hasPathSum(TreeNode *root, int sum) {
        
     }
 }; 
 *******************************************************************************
                              algo
 *******************************************************************************
 
 ******************************************************************************/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:

bool hasPathSum(TreeNode *root, int sum) {
    if (root == nullptr) return false;
    if (root->left == nullptr && root->right == nullptr)
        return sum == root->val;
    return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
}

bool hasPathSum2(TreeNode *root, int sum) {
    return dfs(root, sum, 0);
}

bool dfs(TreeNode *node, int sum, int curSum)
{
    if (node == NULL)
        return false;
    
    if (node->left == NULL && node->right == NULL)
        return curSum + node->val == sum;
           
    return dfs(node->left, sum, curSum + node->val) || dfs(node->right, sum, curSum + node->val);
}


}; 
