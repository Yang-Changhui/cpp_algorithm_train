#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

/*
67. **LC 70 爬楼梯**｜Easy｜S｜线性 DP
假设你正在爬楼梯。需要 n 阶你才能到达楼顶。

每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？

示例 1：

输入：n = 2
输出：2
解释：有两种方法可以爬到楼顶。
1. 1 阶 + 1 阶
2. 2 阶
*/

int climbStairs(int n) {
    if(n<=0)
        return 0;
    if(n==2)
        return n;

    vector<int> dp(n+1);
    dp[1]=1;
    dp[2]=2;
    for(int i=3;i<=n;++i)
    {
        dp[i]=dp[i-1]+dp[i-2];
    }
    return dp[n];
}

/*
68. **LC 198 打家劫舍**｜Medium｜S｜状态压缩
你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，
影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。

给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。

示例 1：

输入：[1,2,3,1]
输出：4
解释：偷窃 1 号房屋 (金额 = 1) ，然后偷窃 3 号房屋 (金额 = 3)。
     偷窃到的最高金额 = 1 + 3 = 4 。
*/

int rob(vector<int>& nums) {
    int n=nums.size();
    if (n == 0)
        return 0;
    if (n == 1)
        return nums[0];

    int pre1=nums[0];
    int pre2=max(nums[0],nums[1]);
    for(int i=2;i<n;++i)
    {
        int cur=max(pre1+nums[i],pre2);
        pre1=pre2;
        pre2=cur;
    }
    return pre2;
}

/*
69. **LC 322 零钱兑换**｜Medium｜S｜完全背包
给你一个整数数组 coins ，表示不同面额的硬币；以及一个整数 amount ，表示总金额。

计算并返回可以凑成总金额所需的 最少的硬币个数 。如果没有任何一种硬币组合能组成总金额，返回 -1 。

你可以认为每种硬币的数量是无限的。

示例 1：

输入：coins = [1, 2, 5], amount = 11
输出：3 
解释：11 = 5 + 5 + 1
*/

int coinChange(vector<int>& coins, int amount) {
    // dp[i] = 凑出金额 i 所需要的最少硬币数量,amount+1作为无穷,表示不可达
    vector<int> dp(amount+1,amount+1); 
    dp[0]=0;
    for(int i=1;i<=amount;++i)
    {
        for(int coin:coins)
        {
            if(i>=coin)
                dp[i]=min(dp[i],d[i-coin]+1);
        }
    }
    return dp[amount]==amount+1?-1:dp[amount];
}

/*
70. **LC 300 最长递增子序列**｜Medium｜S｜DP + 二分优化
给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。

子序列 是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。
例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列。

示例 1：

输入：nums = [10,9,2,5,3,7,101,18]
输出：4
解释：最长递增子序列是 [2,3,7,101]，因此长度为 4 。
*/

int lengthOfLIS(vector<int>& nums) {
    // dp[i]表示以第i个元素结尾的最大递增子序列的长度
    int n=nums.size();
    if(n==0)   
        return 0;
    vector<int> dp(n,1);
    int result;
    for(int i=1;i<n;++i)
    {
        for(int j=0;j<i;++j)
        {
            if(nums[i]>nums[j])
                dp[i]=max(dp[i],dp[j]+1);
        }
        result=max(result,dp[i]);
    }   
    return result;
}

int lengthOfLIS_greedy(vector<int>& nums) {
    // 贪心加二分
    vector<int> tails;

    for (int x : nums) {

        auto it = lower_bound(tails.begin(), tails.end(), x);

        if (it == tails.end()) {
            tails.push_back(x);
        } else {
            *it = x;
        }
    }

    return tails.size();
}

/*
71. **LC 1143 最长公共子序列**｜Medium｜S｜二维 DP
给定两个字符串 text1 和 text2，返回这两个字符串的最长 公共子序列 的长度。如果不存在 公共子序列 ，返回 0 。

一个字符串的 子序列 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符
（也可以不删除任何字符）后组成的新字符串。

例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。
两个字符串的 公共子序列 是这两个字符串所共同拥有的子序列。

示例 1：

输入：text1 = "abcde", text2 = "ace" 
输出：3  
解释：最长公共子序列是 "ace" ，它的长度为 3 。
*/

int longestCommonSubsequence(string text1, string text2) {
    //dp[i][j] 表示text1前i个元素，和text2前j个元素，拥有的最长公共子序列
    int n = text1.size();
    int m = text2.size();

    // dp[i][j]：
    // text1 前 i 个字符和 text2 前 j 个字符的 LCS 长度
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            f(text1[i-1]==text2[j-1])
            {
                dp[i][j]=dp[i-1][j-1]+1;
            }
            else
                dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
        }
    }
    return dp[n][m];
}

/*
72. **LC 72 编辑距离**｜Medium｜S｜二维 DP 状态设计
给你两个单词 word1 和 word2， 请返回将 word1 转换成 word2 所使用的最少操作数  。

你可以对一个单词进行如下三种操作：

插入一个字符
删除一个字符
替换一个字符
 
示例 1：

输入：word1 = "horse", word2 = "ros"
输出：3
解释：
horse -> rorse (将 'h' 替换为 'r')
rorse -> rose (删除 'r')
rose -> ros (删除 'e')
*/
int minDistance(string word1, string word2) {
    // dp[i][j]：
    // word1 前 i 个字符和 word2 前 j 个字符的 LCS 长度
    if(word1==word2)
        return 0;
    int n=word1.size();
    int m=word2.size();
    vector<vector<int>> dp(n+1,vector<int>(m+1,0));
    for(int i=1;i<=n;++i)
        dp[i][0]=i;   //相当于删除
    for(int j=1;j<=m;++j)
        dp[0][j]=j;   //相当于插入

    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            if(word1[i-1]==word2[j-1])
                dp[i][j]=dp[i-1][j-1];
            else
                dp[i][j]=min(dp[i-1][j],dp[i][j-1],dp[i-1][j-1])+1;
        }
    }
    return dp[n][m];

}
