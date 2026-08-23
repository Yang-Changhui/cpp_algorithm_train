#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
#include<string>
#include<deque>
#include<climits>
#include<cassert>
using namespace std;

/*
## 4. 滑动窗口（5）
18. **LC 3 无重复字符的最长子串**｜Medium｜S｜变长窗口
给定一个字符串 s ，请你找出其中不含有重复字符的 最长 子串 的长度。

示例 1:

输入: s = "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。注意 "bca" 和 "cab" 也是正确答案。
*/
int lengthOfLongestSubstring(string s) {
    int result=0;
    unordered_set<char> set;
    int left=0;
    for(int right=0;right<static_cast<int>(s.size());++right)
    {
        while(set.find(s[right])!=set.end())
        {
            set.erase(s[left]);
            left++;
        }
        set.insert(s[right]);
        result=max(result, right-left+1);
    }
    return result;
}

/*
19. **LC 76 最小覆盖子串**｜Hard｜S｜计数窗口
给定两个字符串 s 和 t，长度分别是 m 和 n，返回 s 中的 最短窗口 子串，使得该子串包含 t 中的每一个字符（包括重复字符）。如果没有这样的子串，返回空字符串 ""。

测试用例保证答案唯一。

示例 1：

输入：s = "ADOBECODEBANC", t = "ABC"
输出："BANC"
解释：最小覆盖子串 "BANC" 包含来自字符串 t 的 'A'、'B' 和 'C'。
*/

string minWindow(string s, string t)
{
    if(t.empty() || s.empty() || t.size() > s.size())
        return "";

    unordered_map<char, int> need;
    unordered_map<char, int> window;

    for(char c : t)
    {
        need[c]++;
    }

    int left = 0;
    int valid = 0;

    int start = 0;
    int minLen = INT_MAX;

    for(int right = 0; right < static_cast<int>(s.size()); ++right)
    {
        char c = s[right];

        // c 是需要的字符
        if(need.find(c) != need.end())
        {
            window[c]++;

            if(window[c] == need[c])
            {
                valid++;
            }
        }

        // 当前窗口已经覆盖 t
        while(valid == static_cast<int>(need.size()))
        {
            // 更新最小窗口
            if(right - left + 1 < minLen)
            {
                minLen = right - left + 1;
                start = left;
            }

            char d = s[left];

            // 移除左边字符
            if(need.find(d) != need.end())
            {
                if(window[d] == need[d])
                {
                    valid--;
                }

                window[d]--;
            }

            ++left;
        }
    }

    if(minLen == INT_MAX)
        return "";

    return s.substr(start, minLen);
}

/*
20. **LC 239 滑动窗口最大值**｜Hard｜S｜单调队列
给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。

返回 滑动窗口中的最大值 。

示例 1：

输入：nums = [1,3,-1,-3,5,3,6,7], k = 3
输出：[3,3,5,5,6,7]
*/

vector<int> maxSlidingWindow(vector<int>& nums, int k)
{
    vector<int> result;
    if(nums.empty() || k <= 0 || k > static_cast<int>(nums.size()))
        return result;
    deque<int> window;   // 保存下标

    for(int i = 0; i < static_cast<int>(nums.size()); ++i)
    {
        // 1. 删除已经离开窗口的元素
        while(!window.empty() && window.front() <= i - k)
        {
            window.pop_front();
        }

        // 2. 维护单调递减队列
        while(!window.empty() &&
              nums[window.back()] <= nums[i])
        {
            window.pop_back();
        }

        // 3. 当前下标进入队列
        window.push_back(i);

        // 4. 窗口长度达到 k 后记录最大值
        if(i >= k - 1)
        {
            result.push_back(nums[window.front()]);
        }
    }

    return result;
}

/*
21. **LC 438 找到字符串中所有字母异位词**｜Medium｜A｜定长窗口
给定两个字符串 s 和 p，找到 s 中所有 p 的 异位词 的子串，返回这些子串的起始索引。不考虑答案输出的顺序。

示例 1:

输入: s = "cbaebabacd", p = "abc"
输出: [0,6]
解释:
起始索引等于 0 的子串是 "cba", 它是 "abc" 的异位词。
起始索引等于 6 的子串是 "bac", 它是 "abc" 的异位词。
*/
vector<int> findAnagrams_1(string s, string p)
{
    //暴力方法
    vector<int> result;

    if(p.empty() || p.size() > s.size())
        return result;

    sort(p.begin(), p.end());

    int n = static_cast<int>(s.size());
    int m = static_cast<int>(p.size());

    for(int i = 0; i <= n - m; ++i)
    {
        string s1 = s.substr(i, m);

        sort(s1.begin(), s1.end());

        if(s1 == p)
        {
            result.push_back(i);
        }
    }

    return result;
}


vector<int> findAnagrams_2(string s, string p)
{
    vector<int> result;

    if(p.empty() || p.size() > s.size())
        return result;

    unordered_map<char, int> need;
    unordered_map<char, int> window;

    for(char ch : p)
    {
        need[ch]++;
    }

    int valid = 0;
    int left = 0;
    int k = static_cast<int>(p.size());

    for(int right = 0;
        right < static_cast<int>(s.size());
        ++right)
    {
        char ch1 = s[right];

        // 右边字符进入窗口
        if(need.find(ch1) != need.end())
        {
            window[ch1]++;

            if(window[ch1] == need[ch1])
            {
                ++valid;
            }
        }

        // 窗口长度达到 k
        if(right - left + 1 == k)
        {
            // 所有字符数量都满足
            if(valid == static_cast<int>(need.size()))
            {
                result.push_back(left);
            }

            // 最左侧字符离开窗口
            char ch2 = s[left];

            if(need.find(ch2) != need.end())
            {
                if(window[ch2] == need[ch2])
                {
                    --valid;
                }

                window[ch2]--;
            }

            ++left;
        }
    }

    return result;
}

vector<int> findAnagrams(string s, string p)
{
    vector<int> result;

    if(p.empty() || p.size() > s.size())
        return result;

    vector<int> need(26, 0);
    vector<int> window(26, 0);

    for(char ch : p)
    {
        need[ch - 'a']++;
    }

    int left = 0;
    int k = static_cast<int>(p.size());

    for(int right = 0;
        right < static_cast<int>(s.size());
        ++right)
    {
        // 右边字符进入窗口
        window[s[right] - 'a']++;

        // 窗口长度达到 k
        if(right - left + 1 == k)
        {
            // 当前窗口与 p 的字符频次完全相同
            if(window == need)
            {
                result.push_back(left);
            }

            // 左边字符离开窗口
            window[s[left] - 'a']--;
            ++left;
        }
    }

    return result;
}

/*
22. **LC 424 替换后的最长重复字符**｜Medium｜A｜窗口合法性
给你一个字符串 s 和一个整数 k 。你可以选择字符串中的任一字符，并将其更改为任何其他大写英文字符。该操作最多可执行 k 次。

在执行上述操作后，返回 包含相同字母的最长子字符串的长度。

示例 1：

输入：s = "ABAB", k = 2
输出：4
解释：用两个'A'替换为两个'B',反之亦然。
*/

int characterReplacement(string s, int k) {
    vector<int> window(26,0);
    int result=0;
    int left=0;
    int maxFreq=0;
    for(int right=0;right<static_cast<int>(s.size());++right)
    {
        window[s[right]-'A']++;
        maxFreq=max(window[s[right]-'A'],maxFreq);
        while(right-left+1-maxFreq>k)
        {
            window[s[left]-'A']--;
            ++left;
        }
        result=max(result,right-left+1);
    }
    return result;

}


void printVector(const vector<int>& values)
{
    cout << "[";
    for(size_t i = 0; i < values.size(); ++i)
    {
        if(i > 0) cout << ",";
        cout << values[i];
    }
    cout << "]";
}

int main()
{
    // LC 3
    assert(lengthOfLongestSubstring("abcabcbb") == 3);
    assert(lengthOfLongestSubstring("bbbbb") == 1);
    assert(lengthOfLongestSubstring("pwwkew") == 3);
    assert(lengthOfLongestSubstring("") == 0);
    cout << "LC3 passed" << endl;

    // LC 76
    assert(minWindow("ADOBECODEBANC", "ABC") == "BANC");
    assert(minWindow("a", "a") == "a");
    assert(minWindow("a", "aa") == "");
    assert(minWindow("", "A") == "");
    assert(minWindow("ABC", "") == "");
    cout << "LC76 passed" << endl;

    // LC 239
    {
        vector<int> nums = {1,3,-1,-3,5,3,6,7};
        vector<int> expected = {3,3,5,5,6,7};
        assert(maxSlidingWindow(nums, 3) == expected);
    }
    {
        vector<int> nums = {1};
        vector<int> expected = {1};
        assert(maxSlidingWindow(nums, 1) == expected);
    }
    cout << "LC239 passed" << endl;

    // LC 438: 三种实现都测试
    {
        string s = "cbaebabacd";
        string p = "abc";
        vector<int> expected = {0,6};
        assert(findAnagrams_1(s, p) == expected);
        assert(findAnagrams_2(s, p) == expected);
        assert(findAnagrams(s, p) == expected);
    }
    {
        string s = "abab";
        string p = "ab";
        vector<int> expected = {0,1,2};
        assert(findAnagrams_1(s, p) == expected);
        assert(findAnagrams_2(s, p) == expected);
        assert(findAnagrams(s, p) == expected);
    }
    cout << "LC438 passed" << endl;

    // LC 424
    assert(characterReplacement("ABAB", 2) == 4);
    assert(characterReplacement("AABABBA", 1) == 4);
    assert(characterReplacement("AAAA", 0) == 4);
    assert(characterReplacement("", 2) == 0);
    cout << "LC424 passed" << endl;

    cout << "All sliding-window tests passed!" << endl;
    return 0;
}
