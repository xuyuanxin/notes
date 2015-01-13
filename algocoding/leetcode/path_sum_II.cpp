/*******************************************************************************
                         Path Sum II (Medium)
 *******************************************************************************
 Given a binary tree and a sum, find all root-to-leaf paths where each path's sum 
 equals the given sum.

 For example:
 Given the below binary tree and sum = 22,
              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1
 return
 [
    [5,4,11,2],
    [5,8,4,5]
 ]
 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
     vector<vector<int> > pathSum(TreeNode *root, int sum) {
        
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
vector<vector<int> > pathSum(TreeNode *root, int sum) {
    vector<vector<int> > result;
    vector<int> cur;
    path_sum(root, sum, cur, result);
    return result;
}

private:
void path_sum(TreeNode *root, int gap, vector<int> &cur,vector<vector<int> > &result) {
    if (root == nullptr){ 
		return;
    }	
    cur.push_back(root->val);
    if (root->left == nullptr && root->right == nullptr) {
        if (gap == root->val)
            result.push_back(cur);
    }
    pathSum(root->left, gap - root->val, cur, result);
    pathSum(root->right, gap - root->val, cur, result);
    cur.pop_back();
}


};

class Solution2 {
public:
void dfs(TreeNode *node, int sum, int curSum, vector<int> a)
{
    if (node == NULL){
        return;
    }	
    
    if (node->left == NULL && node->right == NULL){
        if (curSum + node->val == sum){
            a.push_back(node->val);
            ret.push_back(a);
        }
        return;
    }
    
    a.push_back(node->val);
    dfs(node->left, sum, curSum + node->val, a);
    dfs(node->right, sum, curSum + node->val, a);
}
    
vector<vector<int> > pathSum(TreeNode *root, int sum) {
    ret.clear();
    vector<int> a; 
    dfs(root, sum, 0, a);
    return ret;
}

private:
    vector<vector<int> > ret;
};
