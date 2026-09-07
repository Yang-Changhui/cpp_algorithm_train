#include<iostream>
#include<vector>
#include<deque>
#include<queue>
#include<unordered_map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
/*
34. **LC 102 二叉树的层序遍历**｜Medium｜S｜BFS
给你二叉树的根节点 root ，返回其节点值的 层序遍历 。 （即逐层地，从左到右访问所有节点）。

输入：root = [3,9,20,null,null,15,7]
输出：[[3],[9,20],[15,7]]
*/

vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if(root==nullptr)
        return result;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty())
    {
        vector<int> level;
        int size = q.size();  // 固定当前层节点数量
        for(int i=0;i<size();++i)
        {
            TreeNode* node=q.front();
            q.pop();
            level.push_back(node->val);
            if(node->left!=nullptr)
            {
                q.push(node->left);
            }
            if(node->right!=nullptr)
            {
                q.push(node->right);
            }
        }
        result.push_back(level);
    }
    return result;
}

/*
35. **LC 104 二叉树的最大深度**｜Easy｜S｜DFS
给定一个二叉树 root ，返回其最大深度。

二叉树的 最大深度 是指从根节点到最远叶子节点的最长路径上的节点数。
输入：root = [3,9,20,null,null,15,7]
输出：3
*/
int maxDepth(TreeNode* root)
{
    if (root == nullptr)
        return 0;

    int left = maxDepth(root->left);
    int right = maxDepth(root->right);

    return max(left, right) + 1;
}

/*
36. **LC 236 二叉树的最近公共祖先**｜Medium｜S｜后序递归
给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

百度百科中最近公共祖先的定义为：
“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，
满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
输出：3
解释：节点 5 和节点 1 的最近公共祖先是节点 3 。
*/

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(root==nullptr || root==p || root==q)
        return root;
    TreeNode* left=lowestCommonAncestor(root->left, p, q);
    TreeNode* right=lowestCommonAncestor(root->right,p,q);
    if(left!=nullptr && right!=nullptr)
        return root;
    if(left!=nullptr)
        return left;
    return right;
}

/*
37. **LC 105 从前序与中序遍历序列构造二叉树**｜Medium｜S｜分治
给定两个整数数组 preorder 和 inorder ，其中 preorder 是二叉树的先序遍历， 
inorder 是同一棵树的中序遍历，请构造二叉树并返回其根节点。

输入: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
输出: [3,9,20,null,null,15,7]
*/

unordered_map<int,int> indexMap;
int preindex=0;

TreeNode* build(vector<int>& preorder,int left, int right)
{
    if (left > right)
        return nullptr;

    int rootVal=preorder[preindex++];
    //建立根节点
    TreeNode* root=new TreeNode(rootVal);

    //找出中序遍历中根节点的位置索引
    int index=indexMap[rootVal];
    root->left=build(preorder,left,index-1);
    root->right=build(preorder,index+1,right);

    return root;
}
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    indexMap.clear();
    preindex = 0;
    for(int i=0;i<inorder.size();i++)
        indexMap[inorder[i]]=i;

    return build(preorder,0,inorder.size()-1);
}

/*
38. **LC 98 验证二叉搜索树**｜Medium｜S｜上下界 / 中序
给你一个二叉树的根节点 root ，判断其是否是一个有效的二叉搜索树。

有效 二叉搜索树定义如下：

节点的左子树只包含 严格小于 当前节点的数。
节点的右子树只包含 严格大于 当前节点的数。
所有左子树和右子树自身必须也是二叉搜索树。
输入：root = [2,1,3]
输出：true
*/
long long prev=LLong_MIN;
bool isValidBST(TreeNode* root) {
    if(root==nullptr)
        return true;
    if(!isValidBST(root->left))
        return false;
    if(root->val<=prev)
        return false;
    prev=root->val;
    return isValidBST(root->right);
}

/*
39. **LC 124 二叉树中的最大路径和**｜Hard｜S｜树形 DP
二叉树中的 路径 被定义为一条节点序列，序列中每对相邻节点之间都存在一条边。
同一个节点在一条路径序列中 至多出现一次 。该路径 至少包含一个 节点，且不一定经过根节点。

路径和 是路径中各节点值的总和。

给你一个二叉树的根节点 root ，返回其 最大路径和 。
输入：root = [1,2,3]
输出：6
解释：最优路径是 2 -> 1 -> 3 ，路径和为 2 + 1 + 3 = 6
*/

int result = INT_MIN;

int maxGain(TreeNode* root)
{
    if (root == nullptr)
        return 0;

    // 左右子树能给当前节点提供的最大贡献
    // 如果贡献为负，直接不要
    int left = max(0, maxGain(root->left));
    int right = max(0, maxGain(root->right));

    // 当前节点作为路径最高点
    int currentPath = root->val + left + right;

    // 更新全局最大路径和
    result = max(result, currentPath);

    // 返回给父节点时不能左右都要，只能选择一边
    return root->val + max(left, right);
}

int maxPathSum(TreeNode* root)
{
    result = INT_MIN;
    maxGain(root);

    return result;
}

