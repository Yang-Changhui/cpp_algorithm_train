#include<iostream>
#include<vector>
#include<deque>
#include<queue>
#include<unordered_map>
#include<string>
#include<sstream>
#include<climits>
#include<algorithm>

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
        for(int i=0;i<size;++i)
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
    if(preorder.empty() || inorder.empty() || preorder.size()!=inorder.size())
        return nullptr;

    indexMap.clear();
    preindex = 0;
    for(size_t i=0;i<inorder.size();i++)
        indexMap[inorder[i]]=static_cast<int>(i);

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
long long prevVal=LLONG_MIN;

bool isValidBSTHelper(TreeNode* root) {
    if(root==nullptr)
        return true;
    if(!isValidBSTHelper(root->left))
        return false;
    if(root->val<=prevVal)
        return false;
    prevVal=root->val;
    return isValidBSTHelper(root->right);
}

bool isValidBST(TreeNode* root) {
    prevVal=LLONG_MIN;
    return isValidBSTHelper(root);
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

/*
40. **LC 297 二叉树的序列化与反序列化**｜Hard｜A｜编码设计
序列化是将一个数据结构或者对象转换为连续的比特位的操作，进而可以将转换后的数据存储在一个文件或者内存中，
同时也可以通过网络传输到另一个计算机环境，采取相反方式重构得到原数据。

请设计一个算法来实现二叉树的序列化与反序列化。这里不限定你的序列 / 反序列化算法执行逻辑，
你只需要保证一个二叉树可以被序列化为一个字符串并且将这个字符串反序列化为原始的树结构。

提示: 输入输出格式与 LeetCode 目前使用的方式一致，详情请参阅 LeetCode 序列化二叉树的格式。
你并非必须采取这种方式，你也可以采用其他的方法解决这个问题。
输入：root = [1,2,3,null,null,4,5]
输出：[1,2,3,null,null,4,5]
*/

class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (root == nullptr) {
            return "";
        }

        //使用层序遍历
        queue<TreeNode*> q;
        string result;
        q.push(root);

        while(!q.empty())
        {
            TreeNode* node=q.front();
            q.pop();
            if(node==nullptr)
            {
                result+="#,";
                continue;
            }

            result+=to_string(node->val) + ",";

            q.push(node->left);
            q.push(node->right);
            
        }
        return result;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.empty()) {
            return nullptr;
        }

        vector<string> values;
        string token;
        stringstream ss(data);  //包装字符串流

        while (getline(ss, token, ',')) {
            values.push_back(token);
        }
        
        TreeNode* root = new TreeNode(stoi(values[0]));

        queue<TreeNode*> q;
        q.push(root);

        size_t i = 1;

        while (!q.empty() && i < values.size()) {
            TreeNode* node = q.front();
            q.pop();

            if (values[i] != "#") {
                node->left = new TreeNode(stoi(values[i]));
                q.push(node->left);
            }
            ++i;

            if (i < values.size() && values[i] != "#") {
                node->right = new TreeNode(stoi(values[i]));
                q.push(node->right);
            }
            ++i;
        }

        return root;
    }
};

/*
41. **LC 543 二叉树的直径**｜Easy｜A｜后序状态合并
给你一棵二叉树的根节点，返回该树的 直径 。

二叉树的 直径 是指树中任意两个节点之间最长路径的长度 。这条路径可能经过也可能不经过根节点 root 。

两节点之间路径的 长度 由它们之间边数表示。
输入：root = [1,2,3,4,5]
输出：3
解释：3 ，取路径 [4,2,1,3] 或 [5,2,1,3] 的长度。
*/

int diameterDepth(TreeNode* root)
{
    if (root == nullptr)
        return 0;

    // 左右子树能给当前节点提供的最大贡献
    // 如果贡献为负，直接不要
    int left = diameterDepth(root->left);
    int right = diameterDepth(root->right);

    // 当前节点作为路径最高点
    int currentPath = left + right;

    // 以当前节点为最高点时的直径
    result = max(result, currentPath);

    // 返回当前节点向下的最大深度
    return max(left, right)+1;
}

int diameterOfBinaryTree(TreeNode* root)
{
    result = 0;
    diameterDepth(root);

    return result;
}

// ==================== main 测试 ====================
void deleteTree(TreeNode* root)
{
    if(root==nullptr)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void printLevelOrder(const vector<vector<int>>& levels)
{
    cout << "[";
    for(size_t i=0;i<levels.size();++i)
    {
        cout << "[";
        for(size_t j=0;j<levels[i].size();++j)
        {
            cout << levels[i][j];
            if(j+1<levels[i].size())
                cout << ",";
        }
        cout << "]";
        if(i+1<levels.size())
            cout << ",";
    }
    cout << "]";
}

int main()
{
    // LC 102 / LC 104 测试：root = [3,9,20,null,null,15,7]
    TreeNode* root1 = new TreeNode(3);
    root1->left = new TreeNode(9);
    root1->right = new TreeNode(20);
    root1->right->left = new TreeNode(15);
    root1->right->right = new TreeNode(7);

    cout << "LC102 levelOrder: ";
    printLevelOrder(levelOrder(root1));
    cout << endl;
    cout << "LC104 maxDepth: " << maxDepth(root1) << endl;

    // LC 236 测试：15 和 7 的最近公共祖先应为 20
    TreeNode* lca = lowestCommonAncestor(root1, root1->right->left, root1->right->right);
    cout << "LC236 LCA(15,7): " << (lca ? lca->val : -1) << endl;

    // LC 105 测试
    vector<int> preorder = {3,9,20,15,7};
    vector<int> inorder = {9,3,15,20,7};
    TreeNode* root2 = buildTree(preorder, inorder);
    cout << "LC105 buildTree: ";
    printLevelOrder(levelOrder(root2));
    cout << endl;

    // LC 98 测试：有效 BST [2,1,3]
    TreeNode* bst = new TreeNode(2);
    bst->left = new TreeNode(1);
    bst->right = new TreeNode(3);
    cout << "LC98 valid BST: " << boolalpha << isValidBST(bst) << endl;

    // LC 98 测试：无效 BST [5,1,4,null,null,3,6]
    TreeNode* invalidBst = new TreeNode(5);
    invalidBst->left = new TreeNode(1);
    invalidBst->right = new TreeNode(4);
    invalidBst->right->left = new TreeNode(3);
    invalidBst->right->right = new TreeNode(6);
    cout << "LC98 invalid BST: " << boolalpha << isValidBST(invalidBst) << endl;

    // LC 124 测试：[-10,9,20,null,null,15,7]，答案应为 42
    TreeNode* root3 = new TreeNode(-10);
    root3->left = new TreeNode(9);
    root3->right = new TreeNode(20);
    root3->right->left = new TreeNode(15);
    root3->right->right = new TreeNode(7);
    cout << "LC124 maxPathSum: " << maxPathSum(root3) << endl;

    // LC 297 测试：序列化与反序列化
    TreeNode* root4 = new TreeNode(1);
    root4->left = new TreeNode(2);
    root4->right = new TreeNode(3);
    root4->right->left = new TreeNode(4);
    root4->right->right = new TreeNode(5);

    Codec codec;
    string data = codec.serialize(root4);
    cout << "LC297 serialize: " << data << endl;
    TreeNode* decoded = codec.deserialize(data);
    cout << "LC297 decoded: ";
    printLevelOrder(levelOrder(decoded));
    cout << endl;

    // LC 543 测试：[1,2,3,4,5]，直径应为 3
    TreeNode* root5 = new TreeNode(1);
    root5->left = new TreeNode(2);
    root5->right = new TreeNode(3);
    root5->left->left = new TreeNode(4);
    root5->left->right = new TreeNode(5);
    cout << "LC543 diameter: " << diameterOfBinaryTree(root5) << endl;

    // 空树测试
    cout << "Empty tree maxDepth: " << maxDepth(nullptr) << endl;
    cout << "Empty tree diameter: " << diameterOfBinaryTree(nullptr) << endl;
    cout << "Empty tree serialize: \"" << codec.serialize(nullptr) << "\"" << endl;

    deleteTree(root1);
    deleteTree(root2);
    deleteTree(bst);
    deleteTree(invalidBst);
    deleteTree(root3);
    deleteTree(root4);
    deleteTree(decoded);
    deleteTree(root5);

    return 0;
}
