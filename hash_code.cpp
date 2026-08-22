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
#include<utility>

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
    const int n = static_cast<int>(nums.size());

    vector<bool> v1(n+1,false);


    for(int num:nums)
    {
        if(num<=0 || num>n)
            continue;

        v1[num]=true;
    }

    for(int i=1;i<=n;i++)
    {
        if(!v1[i])
            return i;
    }

    return n+1;
}

int firstMissingPositive_1(vector<int>& nums)
{
    //原地哈希
    int n =static_cast<int>(nums.size());
    for(int i=0;i<n;++i)
    {
        while(nums[i]>=1 && nums[i]<=n && nums[i]!=nums[nums[i]-1])
            swap(nums[i],nums[nums[i]-1]);
    }
    for(int i=0;i<n;++i)
    {
        if(nums[i]!=i+1)
            return i+1;
    }
    return n+1;
}

/*
========================
       测试
========================
*/

void printResult(const string& name, bool ok)
{
    cout << (ok ? "[PASS] " : "[FAIL] ") << name << endl;
}

void printVec(const vector<int>& v)
{
    cout << "[";
    for(size_t i=0;i<v.size();++i)
    {
        cout << v[i];
        if(i+1<v.size()) cout << ", ";
    }
    cout << "]";
}

void printVecStr(const vector<vector<string>>& vv)
{
    cout << "[";
    for(size_t i=0;i<vv.size();++i)
    {
        cout << "[";
        for(size_t j=0;j<vv[i].size();++j)
        {
            cout << "\"" << vv[i][j] << "\"";
            if(j+1<vv[i].size()) cout << ", ";
        }
        cout << "]";
        if(i+1<vv.size()) cout << ", ";
    }
    cout << "]";
}

int main()
{
    // 1. FindTarget —— Two Sum (暴力)
    {
        vector<int> nums = {2, 7, 11, 15};
        int target = 9;
        auto res = FindTarget(nums, target);
        cout << "FindTarget([2,7,11,15], 9) = ";
        printVec(res);
        cout << endl;
        printResult("FindTarget", res.size()==2 && nums[res[0]]+nums[res[1]]==target);
    }
    {
        vector<int> nums = {3, 2, 4};
        int target = 6;
        auto res = FindTarget(nums, target);
        cout << "FindTarget([3,2,4], 6) = ";
        printVec(res);
        cout << endl;
        printResult("FindTarget", res.size()==2 && nums[res[0]]+nums[res[1]]==target);
    }

    // 2. FindTarget1 —— Two Sum (哈希)
    {
        vector<int> nums = {2, 7, 11, 15};
        int target = 9;
        auto res = FindTarget1(nums, target);
        cout << "FindTarget1([2,7,11,15], 9) = ";
        printVec(res);
        cout << endl;
        printResult("FindTarget1", res.size()==2 && nums[res[0]]+nums[res[1]]==target);
    }
    {
        vector<int> nums = {3, 2, 4};
        int target = 6;
        auto res = FindTarget1(nums, target);
        cout << "FindTarget1([3,2,4], 6) = ";
        printVec(res);
        cout << endl;
        printResult("FindTarget1", res.size()==2 && nums[res[0]]+nums[res[1]]==target);
    }

    // 3. groupAnagrams
    {
        vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
        auto res = groupAnagrams(strs);
        cout << "groupAnagrams([eat,tea,tan,ate,nat,bat]) = ";
        printVecStr(res);
        cout << endl;
        printResult("groupAnagrams", res.size()==3);
    }

    // 4. longestConsecutive
    {
        vector<int> nums = {100, 4, 200, 1, 3, 2};
        int res = longestConsecutive(nums);
        cout << "longestConsecutive([100,4,200,1,3,2]) = " << res << endl;
        printResult("longestConsecutive", res==4);
    }
    {
        vector<int> nums = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
        int res = longestConsecutive(nums);
        cout << "longestConsecutive([0,3,7,2,5,8,4,6,0,1]) = " << res << endl;
        printResult("longestConsecutive", res==9);
    }

    // 5. productExceptSelf
    {
        vector<int> nums = {1, 2, 3, 4};
        auto res = productExceptSelf(nums);
        cout << "productExceptSelf([1,2,3,4]) = ";
        printVec(res);
        cout << endl;
        printResult("productExceptSelf", res==vector<int>{24,12,8,6});
    }

    // 6. productExceptSelf_2
    {
        vector<int> nums = {1, 2, 3, 4};
        auto res = productExceptSelf_2(nums);
        cout << "productExceptSelf_2([1,2,3,4]) = ";
        printVec(res);
        cout << endl;
        printResult("productExceptSelf_2", res==vector<int>{24,12,8,6});
    }

    // 7. subarraySum
    {
        vector<int> nums = {1, 1, 1};
        int k = 2;
        int res = subarraySum(nums, k);
        cout << "subarraySum([1,1,1], 2) = " << res << endl;
        printResult("subarraySum", res==2);
    }
    {
        vector<int> nums = {1, 2, 3};
        int k = 3;
        int res = subarraySum(nums, k);
        cout << "subarraySum([1,2,3], 3) = " << res << endl;
        printResult("subarraySum", res==2);
    }

    // 8. firstMissingPositive (vector<bool> 版本)
    {
        vector<int> nums = {1, 2, 0};
        int res = firstMissingPositive(nums);
        cout << "firstMissingPositive([1,2,0]) = " << res << endl;
        printResult("firstMissingPositive v1", res==3);
    }
    {
        vector<int> nums = {3, 4, -1, 1};
        int res = firstMissingPositive(nums);
        cout << "firstMissingPositive([3,4,-1,1]) = " << res << endl;
        printResult("firstMissingPositive v1", res==2);
    }
    {
        vector<int> nums = {7, 8, 9, 11, 12};
        int res = firstMissingPositive(nums);
        cout << "firstMissingPositive([7,8,9,11,12]) = " << res << endl;
        printResult("firstMissingPositive v1", res==1);
    }

    // 9. firstMissingPositive_1 (原地哈希版本)
    {
        vector<int> nums = {1, 2, 0};
        int res = firstMissingPositive_1(nums);
        cout << "firstMissingPositive_1([1,2,0]) = " << res << endl;
        printResult("firstMissingPositive_1", res==3);
    }
    {
        vector<int> nums = {3, 4, -1, 1};
        int res = firstMissingPositive_1(nums);
        cout << "firstMissingPositive_1([3,4,-1,1]) = " << res << endl;
        printResult("firstMissingPositive_1", res==2);
    }
    {
        vector<int> nums = {7, 8, 9, 11, 12};
        int res = firstMissingPositive_1(nums);
        cout << "firstMissingPositive_1([7,8,9,11,12]) = " << res << endl;
        printResult("firstMissingPositive_1", res==1);
    }
    {
        // 额外测试：所有元素 1~n 都存在 → 返回 n+1
        vector<int> nums = {3, 4, 2, 1};
        int res = firstMissingPositive_1(nums);
        cout << "firstMissingPositive_1([3,4,2,1]) = " << res << endl;
        printResult("firstMissingPositive_1", res==5);
    }
    {
        // 额外测试：空数组
        vector<int> nums = {};
        int res = firstMissingPositive_1(nums);
        cout << "firstMissingPositive_1([]) = " << res << endl;
        printResult("firstMissingPositive_1", res==1);
    }

    cout << "\n=== 所有测试完成 ===" << endl;
    return 0;
}