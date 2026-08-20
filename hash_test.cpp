/*
## 1. 数组与哈希（6）

1. **LC 1 两数之和**｜Easy｜S｜哈希表
给定一个整数数组 nums 和一个整数目标值 target，
请你在该数组中找出和为目标值 target  的那两个整数，并返回它们的数组下标。

你可以假设每种输入只会对应一个答案，并且你不能使用两次相同的元素。

你可以按任意顺序返回答案。
*/
#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<string>
#include<algorithm>

using namespace std;

std::vector<int> FindTarget(
    const std::vector<int>&nums,
    const int target)
{
    int n=static_cast<int>(nums.size());
    std::vector<int> result;
    for(int i=0;i<n;++i)
    {
        for(int j=i+1;j<n;++j)
        {
            if(nums[i]+nums[j]==target)
            {
                result.push_back(i);
                result.push_back(j);
                break;
            }

        }
        if(!result.empty())
            break;
    }
    return result;
}

// 使用哈希表

std::vector<int> FindTarget1(
    const std::vector<int>& nums,
    const int target
)
{
    int n=static_cast<int>(nums.size());

    std::unordered_map<int,int> indexMap;
    for(int i=0;i<n;++i)
    {
        int complement = target-nums[i];
        auto it=indexMap.find(complement);
        if(it!=indexMap.end())
        {
            return {it->second,i};
        }
        indexMap[nums[i]]=i;
    }
    return {};
}
/*
2. **LC 49 字母异位词分组**｜Medium｜S｜字符串哈希
给你一个字符串数组，请你将 字母异位词 组合在一起。可以按任意顺序返回结果列表。

示例 1:

输入: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]

输出: [["bat"],["nat","tan"],["ate","eat","tea"]]

解释：

在 strs 中没有字符串可以通过重新排列来形成 "bat"。
字符串 "nat" 和 "tan" 是字母异位词，因为它们可以重新排列以形成彼此。
字符串 "ate" ，"eat" 和 "tea" 是字母异位词，因为它们可以重新排列以形成彼此。

*/

vector<vector<string>> groupAnagrams(
    const vector<string>& strs
)
{
    vector<vector<string>> result;
    std::unordered_map<string,vector<string>> maps;
    int n = static_cast<int>(strs.size());

    for(int i=0;i<n;++i)
    {
        string s=strs[i];
        sort(s.begin(),s.end());
        maps[s].push_back(strs[i]);
    }
    for(auto& map:maps)
    {
        result.push_back(map.second);
    }
    return result;
}

/*
3. **LC 128 最长连续序列**｜Medium｜S｜哈希集合
给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。

请你设计并实现时间复杂度为 O(n) 的算法解决此问题。

示例 1：

输入：nums = [100,4,200,1,3,2]
输出：4
解释：最长数字连续序列是 [1, 2, 3, 4]。它的长度为 4。

0 <= nums.length <= 105
-10^9 <= nums[i] <= 10^9

*/

int longestConsecutive(const vector<int>&nums)
{
    unordered_set<int> numbers(nums.begin(), nums.end());
    int longest = 0;

    for (int num : numbers) {
        // 只有序列起点才开始向后查找，保证平均 O(n)。
        if (numbers.find(num - 1) != numbers.end()) {
            continue;
        }

        int length = 1;
        int current = num;
        while (numbers.find(current + 1) != numbers.end()) {
            ++current;
            ++length;
        }

        longest = std::max(longest, length);
        }
    
    return longest;
}

/*
4. **LC 238 除自身以外数组的乘积**｜Medium｜S｜前后缀积
给你一个整数数组 nums，返回 数组 answer ，其中 answer[i] 等于 nums 中除了 nums[i] 之外其余各元素的乘积 。

题目数据 保证 数组 nums之中任意元素的全部前缀元素和后缀的乘积都在  32 位 整数范围内。

请 不要使用除法，且在 O(n) 时间复杂度内完成此题。

示例 1:

输入: nums = [1,2,3,4]
输出: [24,12,8,6]
*/

vector<int> productExceptSelf(const vector<int>&nums)
{
    int n=static_cast<int>(nums.size());
    vector<int> pre_product(n, 1);
    vector<int> post_product(n, 1);
    
    for(int i=1;i<n;i++)
    {
        pre_product[i]=pre_product[i-1]*nums[i-1];
    }
    
    for(int i=n-2;i>=0;--i)
    {
        post_product[i]=post_product[i+1]*nums[i+1];
    }
    vector<int> result;
    
    for(int i=0;i<n;++i)
    {
        result.push_back(pre_product[i]*post_product[i]);
    }
    return result;
}

vector<int> productExceptSelf_2(const vector<int>& nums)
{
    int n = static_cast<int>(nums.size());
    vector<int> result(n, 1);

    int prefix = 1;
    for (int i = 0; i < n; ++i)
    {
        result[i] = prefix;
        prefix *= nums[i];
    }

    int suffix = 1;
    for (int i = n - 1; i >= 0; --i)
    {
        result[i] *= suffix;
        suffix *= nums[i];
    }

    return result;
}

/*
5. **LC 560 和为 K 的子数组**｜Medium｜S｜前缀和 + 哈希
给你一个整数数组 nums 和一个整数 k ，请你统计并返回 该数组中和为 k 的子数组的个数 。

子数组是数组中元素的连续非空序列。

示例 1：

输入：nums = [1,1,1], k = 2
输出：2
*/

int subarraySum(const vector<int>& nums,int k)
{
    unordered_map<int,int> prefix;

    // 前缀和为0出现一次
    prefix[0]=1;

    int sum=0;
    int result=0;


    for(int num:nums)
    {
        sum += num;


        // 找之前有没有 sum-k
        if(prefix.find(sum-k)!=prefix.end())
        {
            result += prefix[sum-k];
        }


        // 当前前缀和次数+1
        prefix[sum]++;
    }


    return result;
}

/*
6. **LC 41 缺失的第一个正数**｜Hard｜A｜原地哈希
给你一个未排序的整数数组 nums ，请你找出其中没有出现的最小的正整数。

请你实现时间复杂度为 O(n) 并且只使用常数级别额外空间的解决方案。
 
示例 1：

输入：nums = [1,2,0]
输出：3
解释：范围 [1,2] 中的数字都在数组中。
*/

int firstMissingPositive(vector<int>& nums)
{
    const int MAX = 100000;

    vector<bool> v1(MAX+1,false);


    for(int num:nums)
    {
        if(num<=0 || num>MAX)
            continue;

        v1[num]=true;
    }


    for(int i=1;i<=MAX;i++)
    {
        if(!v1[i])
            return i;
    }


    return MAX+1;
}
