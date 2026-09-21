#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
## 14. 字符串与字典树（3）

79. **LC 5 最长回文子串**｜Medium｜S｜中心扩展 / DP
给你一个字符串 s，找到 s 中最长的 回文 子串。

示例 1：

输入：s = "babad"
输出："bab"
解释："aba" 同样是符合题意的答案。
*/

string longestPalindrome(string s)
{

    int n = s.size();

    if (n == 0)
        return "";

    int count = 1;
    int start = 0;

    for (int i = 0; i < n; ++i)
    {
        // -------------------------
        // 奇数长度回文
        // 例如：a b a
        //         ↑
        //         i
        // -------------------------
        int j = i - 1;
        int k = i + 1;

        while (j >= 0 && k < n && s[j] == s[k])
        {
            j--;
            k++;
        }

        // 此时真正的回文区间：
        // [j + 1, k - 1]
        int len = k - j - 1;

        if (len > count)
        {
            count = len;
            start = j + 1;
        }

        // -------------------------
        // 偶数长度回文
        // 例如：a b b a
        //         ↑ ↑
        //         i i+1
        // -------------------------
        j = i;
        k = i + 1;

        while (j >= 0 && k < n && s[j] == s[k])
        {
            j--;
            k++;
        }

        len = k - j - 1;

        if (len > count)
        {
            count = len;
            start = j + 1;
        }
    }

    return s.substr(start, count);
}

string longestPalindrome_dp(string s)
{
    // 使用二维dp算法,dp[i][j] 表示i-j是否是回文子串
    int n = s.size();
    vector<vector<bool>> dp(n, vector<bool>(n, false));
    int start = 0;
    int max_len = 0;
    for (int i = n - 1; i >= 0; --i)
    {
        for (int j = i; j < n; ++j)
        {
            if (s[i] == s[j])
            {
                if (j - i <= 2 || dp[i + 1][j - 1])
                {
                    dp[i][j] = true;
                    int len = j - i + 1;
                    if (len > max_len)
                    {
                        max_len = len;
                        start = i;
                    }
                }
            }
        }
    }
    return s.substr(start, max_len);
}

/*
80. **LC 208 实现 Trie**｜Medium｜S｜前缀树
Trie（发音类似 "try"）或者说 前缀树 是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。
这一数据结构有相当多的应用情景，例如自动补全和拼写检查。

请你实现 Trie 类：

Trie() 初始化前缀树对象。
void insert(String word) 向前缀树中插入字符串 word 。
boolean search(String word) 如果字符串 word 在前缀树中，返回 true（即，在检索之前已经插入）；否则，返回 false 。
boolean startsWith(String prefix) 如果之前已经插入的字符串 word 的前缀之一为 prefix ，返回 true ；否则，返回 false 。

示例：

输入
["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
[[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
输出
[null, null, true, false, true, null, true]
 */

class Trie
{
public:
    struct TrieNode
    {
        TrieNode *children[26];
        bool isEnd;
        string word;

        TrieNode()
        {
            isEnd = false;
            for (int i = 0; i < 26; i++)
            {
                children[i] = nullptr;
            }
        }
    };

private:
    TrieNode *root;

public:
    Trie()
    {
        root = new TrieNode();
    }

    TrieNode* getRoot()
    {
        return root;
    }

    void insert(string word)
    {
        TrieNode *cur = root;

        for (char c : word)
        {
            int index = c - 'a';

            // 当前字符不存在，就创建节点
            if (cur->children[index] == nullptr)
            {
                cur->children[index] = new TrieNode();
            }

            cur = cur->children[index];
        }

        // 标记这里是一个完整单词的结尾
        cur->isEnd = true;
        cur->word = word;
    }

    bool search(string word)
    {
        TrieNode *cur = root;

        for (char c : word)
        {
            int index = c - 'a';

            if (cur->children[index] == nullptr)
            {
                return false;
            }

            cur = cur->children[index];
        }

        // 路径存在还不够，必须确实是某个单词的结尾
        return cur->isEnd;
    }

    bool startsWith(string prefix)
    {
        TrieNode *cur = root;

        for (char c : prefix)
        {
            int index = c - 'a';

            if (cur->children[index] == nullptr)
            {
                return false;
            }

            cur = cur->children[index];
        }

        // 只要整条前缀路径存在即可
        return true;
    }
};

/*
81. **LC 212 单词搜索 II**｜Hard｜A｜Trie + 回溯
给定一个 m x n 二维字符网格 board 和一个单词（字符串）列表 words， 返回所有二维网格上的单词 。

单词必须按照字母顺序，通过 相邻的单元格 内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。
同一个单元格内的字母在一个单词中不允许被重复使用。
输入：board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]],
    words = ["oath","pea","eat","rain"]
输出：["eat","oath"]
*/
void dfs(vector<vector<char>> &board, int i, int j, Trie::TrieNode* node, vector<string>& ans)
{
    int n = board.size();
    int m = board[0].size();
    if (i < 0 || i >= n || j < 0 || j >= m)
        return;
    if (board[i][j]=='#')
        return;
    char c=board[i][j];

    if(node->children[c-'a']==nullptr)
        return;
    // Trie 同步向下走
    node = node->children[c - 'a'];
    if(node->isEnd)
    {
        ans.push_back(node->word);
        // 防止同一个单词被重复加入
        node->isEnd = false;
    }
    board[i][j]='#';
    dfs(board,i-1,j,node,ans);
    dfs(board,i+1,j,node,ans);
    dfs(board,i,j-1,node,ans);
    dfs(board,i,j+1,node,ans);
    board[i][j]=c;
}

vector<string> findWords(vector<vector<char>> &board, vector<string> &words)
{
    if (board.empty() || board[0].empty())
        return {};

    int n = board.size();
    int m = board[0].size();
    Trie tree;
    for(auto word:words)
        tree.insert(word);

    vector<string> ans;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            dfs(board, i, j, tree.getRoot(),ans);
        }
    }
    return ans;
}


int main()
{
    // -------------------------
    // 测试 LC 5：最长回文子串
    // -------------------------
    string s = "babad";
    cout << "longestPalindrome(\"babad\") = " << longestPalindrome(s) << endl;
    cout << "longestPalindrome_dp(\"babad\") = " << longestPalindrome_dp(s) << endl;

    // -------------------------
    // 测试 LC 208：Trie
    // -------------------------
    Trie trie;
    trie.insert("apple");
    cout << boolalpha;
    cout << "search(\"apple\") = " << trie.search("apple") << endl;       // true
    cout << "search(\"app\") = " << trie.search("app") << endl;           // false
    cout << "startsWith(\"app\") = " << trie.startsWith("app") << endl;   // true
    trie.insert("app");
    cout << "search(\"app\") = " << trie.search("app") << endl;           // true

    // -------------------------
    // 测试 LC 212：单词搜索 II
    // -------------------------
    vector<vector<char>> board = {
        {'o', 'a', 'a', 'n'},
        {'e', 't', 'a', 'e'},
        {'i', 'h', 'k', 'r'},
        {'i', 'f', 'l', 'v'}
    };

    vector<string> words = {"oath", "pea", "eat", "rain"};
    vector<string> ans = findWords(board, words);

    cout << "findWords result: ";
    for (const string& word : ans)
    {
        cout << word << " ";
    }
    cout << endl;

    return 0;
}
