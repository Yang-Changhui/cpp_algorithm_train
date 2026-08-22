#include<iostream>
#include<vector>
#include<algorithm>
#include <string>
#include <climits>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
7. **手写快速排序 / 快速选择**｜Medium｜S｜分区、随机化、退化分析
*/
void quickSort(vector<int>& nums, int left, int right)
{
    if (left >= right)
    {
        return;
    }
    
    // 随机选择pivot避免退化
    int randomIdx = left + rand() % (right - left + 1);
    swap(nums[left], nums[randomIdx]);
    
    int i = left;
    int j = right;
    int pivot = nums[left];
    
    while (i < j)
    {
        // 从右向左找到第一个小于pivot的数
        while (i < j && nums[j] >= pivot)
            --j;
        // 从左向右找到第一个大于pivot的数
        while (i < j && nums[i] <= pivot)
            ++i;
        if (i < j)
            swap(nums[i], nums[j]);
    }
    // 将基准移动到中心
    swap(nums[i], nums[left]);
    quickSort(nums, left, i - 1);
    quickSort(nums, i + 1, right);
}

/*
8. **手写归并排序**｜Medium｜S｜分治、稳定性
*/
void merge(vector<int>& nums, int left, int mid, int right)
{
    vector<int> temp;
    int i = left;
    int j = mid;
    while (i < mid && j < right)
    {
        if (nums[i] <= nums[j])
        {
            temp.push_back(nums[i]);
            ++i;
        }
        else
        {
            temp.push_back(nums[j]);
            ++j;
        }
    }
    if (i < mid)
    {
        while (i < mid)
        {
            temp.push_back(nums[i]);
            ++i;
        }
    }
    if (j < right)
    {
        while (j < right)
        {
            temp.push_back(nums[j]);
            ++j;
        }
    }
    for (int k = 0; k < temp.size(); ++k)
    {
        nums[k + left] = temp[k];
    }
}

void mergesort(vector<int>& nums, int left, int right)
{
    if (right - left <= 1)
        return;
    int mid = left + (right - left) / 2;
    mergesort(nums, left, mid);
    mergesort(nums, mid, right);
    merge(nums, left, mid, right);
}

/*
9. **LC 33 搜索旋转排序数组**｜Medium｜S｜二分边界
*/
int search(const vector<int>& nums, int target)
{
    int left = 0;
    int right = static_cast<int>(nums.size()) - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target)
            return mid;
        // 左边有序
        if (nums[left] <= nums[mid])
        {
            if (nums[left] <= target && target < nums[mid])
            {
                right = mid - 1;
            }
            else
                left = mid + 1;
        }
        // 右边有序
        else
        {
            if (target > nums[mid] && target <= nums[right])
            {
                left = mid + 1;
            }
            else
                right = mid - 1;
        }
    }
    return -1;
}

/*
10. **LC 34 在排序数组中查找元素的首尾位置**｜Medium｜S｜左右边界
*/
vector<int> searchRange(const vector<int>& nums, int target)
{
    int n = static_cast<int>(nums.size());
    if (n == 0) return {-1, -1};  // 修复：空数组直接返回
    
    int left = 0;
    int right = n - 1;
    int start = -1;
    int end = -1;

    // 查找左边界：二分找第一个 >= target 的位置（lower_bound）
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] >= target)
            right = mid;
        else
            left = mid + 1;
    }
    if (left >= n || nums[left] != target)
        return {-1, -1};
    start = left;
    
    // 查找右边界：二分找第一个 > target 的位置（upper_bound），再减 1
    left = 0;
    right = n;
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] <= target)
            left = mid + 1;
        else
            right = mid;
    }
    end = left - 1;
    return {start, end};
}

/*
11. **LC 153 寻找旋转排序数组中的最小值**｜Medium｜S｜单调区间
*/
int findMin(const vector<int>& nums)
{
    int n = static_cast<int>(nums.size());
    int left = 0;
    int right = n - 1;
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] < nums[right])
        {
            // 右边有序，最小值在左边,包括mid
            right = mid;
        }
        else if (nums[mid] > nums[right])
        {
            // 左边有序，最小值在右边
            left = mid + 1;
        }
        else
        {
            // nums[mid]==nums[right]，无法判断，缩小右边界
            // 注意：题目说元素互不相同，这个分支不会执行
            right--;
        }
    }
    return nums[left];
}

/*
12. **LC 4 寻找两个正序数组的中位数**｜Hard｜A｜第 K 小 / 值域切分
*/
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    // 确保 nums1 是短的
    if (nums1.size() > nums2.size()) {
        return findMedianSortedArrays(nums2, nums1);
    }
    
    int m = nums1.size();
    int n = nums2.size();
    int totalLeft = (m + n + 1) / 2;
    
    int left = 0;
    int right = m;  // 注意：是 m，不是 m-1
    
    while (left <= right) {  // 注意：是 <=
        int i = left + (right - left) / 2;
        int j = totalLeft - i;
        
        // 处理边界
        int nums1LeftMax = (i == 0) ? INT_MIN : nums1[i - 1];
        int nums1RightMin = (i == m) ? INT_MAX : nums1[i];
        int nums2LeftMax = (j == 0) ? INT_MIN : nums2[j - 1];
        int nums2RightMin = (j == n) ? INT_MAX : nums2[j];
        
        // 检查是否找到正确分割
        if (nums1LeftMax <= nums2RightMin && nums2LeftMax <= nums1RightMin) {
            if ((m + n) % 2 == 1) {
                return max(nums1LeftMax, nums2LeftMax);
            } else {
                return (max(nums1LeftMax, nums2LeftMax) + 
                        min(nums1RightMin, nums2RightMin)) / 2.0;
            }
        } else if (nums1LeftMax > nums2RightMin) {
            right = i - 1;  // i 太大，左移
        } else {
            left = i + 1;   // i 太小，右移
        }
    }
    
    return 0.0;
}

/*
========================
       测试辅助函数
========================
*/

void printResult(const string& name, bool ok)
{
    cout << (ok ? "[PASS] " : "[FAIL] ") << name << endl;
}

void printVec(const vector<int>& v)
{
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i)
    {
        cout << v[i];
        if (i + 1 < v.size()) cout << ", ";
    }
    cout << "]";
}

// 判断数组是否非递减有序
bool isSorted(const vector<int>& v)
{
    for (size_t i = 1; i < v.size(); ++i)
        if (v[i - 1] > v[i])
            return false;
    return true;
}

// 随机生成 n 个元素，取值区间 [lo, hi]
void genRandom(vector<int>& v, int n, int lo, int hi)
{
    v.clear();
    for (int i = 0; i < n; ++i)
        v.push_back(lo + rand() % (hi - lo + 1));
}

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "========== 7. quickSort 手写快排 ==========" << endl;
    {
        vector<int> nums = {4, 1, 3, 9, 7, 2, 5, 6, 8, 0};
        quickSort(nums, 0, static_cast<int>(nums.size()) - 1);
        cout << "quickSort([4,1,3,9,7,2,5,6,8,0]) = ";
        printVec(nums); cout << endl;
        printResult("quickSort 乱序", isSorted(nums));
    }
    {
        vector<int> nums = {1, 2, 3, 4, 5};
        quickSort(nums, 0, static_cast<int>(nums.size()) - 1);
        printResult("quickSort 已升序", isSorted(nums));
    }
    {
        vector<int> nums = {5, 4, 3, 2, 1};
        quickSort(nums, 0, static_cast<int>(nums.size()) - 1);
        printResult("quickSort 已降序", isSorted(nums));
    }
    {
        vector<int> nums = {3, 3, 3, 3, 3};
        quickSort(nums, 0, static_cast<int>(nums.size()) - 1);
        printResult("quickSort 全相等", isSorted(nums));
    }
    {
        vector<int> nums = {};
        quickSort(nums, 0, -1); // 空数组：left>=right 直接返回
        printResult("quickSort 空数组", nums.empty());
    }
    {
        // 与 std::sort 对照的随机测试（含大量重复）
        srand(20260822);
        bool allOk = true;
        for (int t = 0; t < 300; ++t)
        {
            int n = rand() % 60;
            vector<int> a, b;
            genRandom(a, n, -5, 5);
            b = a;
            quickSort(a, 0, static_cast<int>(a.size()) - 1);
            sort(b.begin(), b.end());
            if (a != b) { allOk = false; break; }
        }
        printResult("quickSort 随机对照 x300", allOk);
    }

    cout << "\n========== 8. mergesort 手写归并 ==========" << endl;
    {
        vector<int> nums = {4, 1, 3, 9, 7, 2, 5, 6, 8, 0};
        mergesort(nums, 0, static_cast<int>(nums.size()));
        cout << "mergesort([4,1,3,9,7,2,5,6,8,0]) = ";
        printVec(nums); cout << endl;
        printResult("mergesort 乱序", isSorted(nums));
    }
    {
        vector<int> nums = {5, 4, 3, 2, 1};
        mergesort(nums, 0, static_cast<int>(nums.size()));
        printResult("mergesort 已降序", isSorted(nums));
    }
    {
        vector<int> nums = {2, 2, 1, 1, 3, 3};
        mergesort(nums, 0, static_cast<int>(nums.size()));
        printResult("mergesort 含重复", isSorted(nums));
    }
    {
        vector<int> nums = {1};
        mergesort(nums, 0, static_cast<int>(nums.size()));
        printResult("mergesort 单元素", isSorted(nums));
    }
    {
        vector<int> nums = {};
        mergesort(nums, 0, static_cast<int>(nums.size()));
        printResult("mergesort 空数组", nums.empty());
    }

    cout << "\n========== 9. search (LC 33 旋转排序数组) ==========" << endl;
    {
        vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
        int res = search(nums, 0);
        cout << "search([4,5,6,7,0,1,2], 0) = " << res << endl;
        printResult("search 例1(期望4)", res == 4);
    }
    {
        vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
        printResult("search 找不到返回-1", search(nums, 3) == -1);
    }
    {
        vector<int> nums = {1};
        printResult("search 单元素命中(期望0)", search(nums, 1) == 0);
        printResult("search 单元素未命中(期望-1)", search(nums, 2) == -1);
    }
    {
        vector<int> nums = {5, 1, 3};
        printResult("search 右侧有序段(期望2)", search(nums, 3) == 2);
        printResult("search 左侧有序段(期望1)", search(nums, 1) == 1);
    }
    {
        vector<int> nums = {3, 1};
        printResult("search 两元素查找存在", search(nums, 1) == 1);
        printResult("search 两元素查找不存在", search(nums, 2) == -1);
    }

    cout << "\n========== 10. searchRange (LC 34) ==========" << endl;
    {
        vector<int> nums = {5, 7, 7, 8, 8, 10};
        auto res = searchRange(nums, 8);
        cout << "searchRange([5,7,7,8,8,10], 8) = ";
        printVec(res); cout << endl;
        printResult("searchRange 例1(期望[3,4])",
                     res.size()==2 && res[0]==3 && res[1]==4);
    }
    {
        vector<int> nums = {5, 7, 7, 8, 8, 10};
        auto res = searchRange(nums, 6);
        printResult("searchRange 不存在(期望[-1,-1])",
                     res.size()==2 && res[0]==-1 && res[1]==-1);
    }
    {
        vector<int> nums = {8, 8, 8, 8};
        auto res = searchRange(nums, 8);
        cout << "searchRange([8,8,8,8], 8) = ";
        printVec(res); cout << endl;
        printResult("searchRange 全相同(期望[0,3])",
                     res.size()==2 && res[0]==0 && res[1]==3);
    }
    {
        vector<int> nums = {5, 7, 7, 8, 8, 10};
        auto res = searchRange(nums, 7);
        printResult("searchRange 中间段(期望[1,2])",
                     res.size()==2 && res[0]==1 && res[1]==2);
    }
    {
        vector<int> nums = {};
        auto res = searchRange(nums, 0);
        printResult("searchRange 空数组(期望[-1,-1])",
                     res.size()==2 && res[0]==-1 && res[1]==-1);
    }
    {
        vector<int> nums = {1, 2, 3};
        auto res = searchRange(nums, 2);
        printResult("searchRange 单元素目标(期望[1,1])",
                     res.size()==2 && res[0]==1 && res[1]==1);
    }

    cout << "\n========== 11. findMin (LC 153) ==========" << endl;
    {
        vector<int> nums = {3, 4, 5, 1, 2};
        int res = findMin(nums);
        cout << "findMin([3,4,5,1,2]) = " << res << endl;
        printResult("findMin 例1(期望1)", res == 1);
    }
    {
        vector<int> nums = {0, 1, 2, 4, 5, 6, 7};
        printResult("findMin 未旋转(期望0)", findMin(nums) == 0);
    }
    {
        vector<int> nums = {2, 1};
        printResult("findMin 两元素(期望1)", findMin(nums) == 1);
    }
    {
        vector<int> nums = {1};
        printResult("findMin 单元素(期望1)", findMin(nums) == 1);
    }
    {
        vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
        printResult("findMin 例2(期望0)", findMin(nums) == 0);
    }
    {
        vector<int> nums = {2, 3, 4, 5, 1};
        printResult("findMin 最小在末尾(期望1)", findMin(nums) == 1);
    }

    cout << "\n========== 12. findMedianSortedArrays (LC 4) ==========" << endl;
    {
        vector<int> a = {1, 3}, b = {2};
        double med = findMedianSortedArrays(a, b);
        cout << "findMedianSortedArrays([1,3],[2]) = " << med << endl;
        printResult("findMedian 例1(期望2.0)", med == 2.0);
    }
    {
        vector<int> a = {1, 2}, b = {3, 4};
        double med = findMedianSortedArrays(a, b);
        cout << "findMedianSortedArrays([1,2],[3,4]) = " << med << endl;
        printResult("findMedian 例2(期望2.5)", med == 2.5);
    }
    {
        vector<int> a = {}, b = {1};
        printResult("findMedian 一个空(期望1.0)",
                     findMedianSortedArrays(a, b) == 1.0);
    }
    {
        vector<int> a = {0, 0}, b = {0, 0};
        printResult("findMedian 全零(期望0.0)",
                     findMedianSortedArrays(a, b) == 0.0);
    }
    {
        vector<int> a = {1, 3, 5}, b = {2, 4, 6};
        double med = findMedianSortedArrays(a, b);
        cout << "findMedianSortedArrays([1,3,5],[2,4,6]) = " << med << endl;
        printResult("findMedian 奇数总长(期望3.5)", med == 3.5);
    }
    {
        vector<int> a = {1, 2, 3, 4}, b = {5, 6, 7, 8};
        double med = findMedianSortedArrays(a, b);
        cout << "findMedianSortedArrays([1,2,3,4],[5,6,7,8]) = " << med << endl;
        printResult("findMedian 偶数总长(期望4.5)", med == 4.5);
    }

    cout << "\n=== 所有测试完成 ===" << endl;
    return 0;
}