/*
## 3. 双指针（5）

13. **LC 15 三数之和**｜Medium｜S｜排序 + 左右指针
给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]] 
满足 i != j、i != k 且 j != k ，同时还满足 nums[i] + nums[j] + nums[k] == 0 。
请你返回所有和为 0 且不重复的三元组。

注意：答案中不可以包含重复的三元组。

示例 1：
输入：nums = [-1,0,1,2,-1,-4]
输出：[[-1,-1,2],[-1,0,1]]
解释：
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0 。
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0 。
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0 。
不同的三元组是 [-1,0,1] 和 [-1,-1,2] 。
注意，输出的顺序和三元组的顺序并不重要。
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>

using namespace std;
vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> result;
    int n = nums.size();
    if (n < 3) return result;
    
    sort(nums.begin(), nums.end());
    
    for (int i = 0; i < n - 2; ++i) {
        // 跳过重复的 i
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        
        // 优化：如果最小的数都大于0，后面的数更大，不可能和为0
        if (nums[i] > 0) break;
        
        int left = i + 1;
        int right = n - 1;
        int target = -nums[i];
        
        while (left < right) {
            int sum = nums[left] + nums[right];
            
            if (sum == target) {
                result.push_back({nums[i], nums[left], nums[right]});
                
                // 跳过重复的 left
                while (left < right && nums[left] == nums[left + 1]) left++;
                // 跳过重复的 right
                while (left < right && nums[right] == nums[right - 1]) right--;
                
                left++;
                right--;
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
    }
    
    return result;
}

/*
14. **LC 11 盛最多水的容器**｜Medium｜S｜贪心移动指针
给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i]) 。

找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。

返回容器可以储存的最大水量。

说明：你不能倾斜容器。
输入：[1,8,6,2,5,4,8,3,7]
输出：49 
解释：图中垂直线代表输入数组 [1,8,6,2,5,4,8,3,7]。
*/

int maxArea(vector<int>& height) {
    int result=0;
    int n=height.size();
    int left=0;
    int right=n-1;
    while(left<right)
    {
        int area=min(height[left],height[right])*(right-left);
        result=max(result,area);
        if(height[left]<=height[right])
        {
            int currentLeft=height[left];
            while(left<right && height[left]<=currentLeft)
                left++;
        }
        else
        {
            int currentRight=height[right];
            while(left<right&&height[right]<=currentRight)
                right--;
        }

    }
    return result;
}

/*
15. **LC 42 接雨水**｜Hard｜S｜双指针 / 单调栈
给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
输出：6
解释：上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）
*/

int trap(vector<int>& height) {
    if (height.size() < 3)
        return 0;
    int result=0;
    int left=0;
    int right=static_cast<int>(height.size())-1;
    int leftMax=0;
    int rightMax=0;
    while(left<right)
    {
        if(height[left]<=height[right])
        {
            if(height[left]>leftMax)
            {
                leftMax=height[left];
            }
            else
            {
                result+=(leftMax-height[left]);
            }
            left++;
        }
        else
        {
            if(height[right]>rightMax)
            {
                rightMax=height[right];
            }
            else
            {
                result+=(rightMax-height[right]);
            }
            right--;
        }      
    }
    return result;
}


/*
16. **LC 88 合并两个有序数组**｜Easy｜S｜逆向双指针
给你两个按 非递减顺序 排列的整数数组 nums1 和 nums2，另有两个整数 m 和 n ，分别表示 nums1 和 nums2 中的元素数目。

请你 合并 nums2 到 nums1 中，使合并后的数组同样按 非递减顺序 排列。

注意：最终，合并后数组不应由函数返回，而是存储在数组 nums1 中。
为了应对这种情况，nums1 的初始长度为 m + n，其中前 m 个元素表示应合并的元素，后 n 个元素为 0 ，应忽略。
nums2 的长度为 n 。

示例 1：

输入：nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
输出：[1,2,2,3,5,6]
解释：需要合并 [1,2,3] 和 [2,5,6] 。
合并结果是 [1,2,2,3,5,6] ，其中斜体加粗标注的为 nums1 中的元素。
*/

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i=m-1;
    int j=n-1;
    int k=m+n-1;
    while(j>=0)
    {
        if(i>=0 && nums1[i]>=nums2[j])
        {
            nums1[k]=nums1[i--];
        }
        else
        {
            nums1[k]=nums2[j--];
        }
        k--;
    }
}

/*
17. **LC 283 移动零**｜Easy｜A｜快慢指针
给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。

请注意 ，必须在不复制数组的情况下原地对数组进行操作。

示例 1:

输入: nums = [0,1,0,3,12]
输出: [1,3,12,0,0]
*/
void moveZeroes(vector<int>& nums) {
    int n = static_cast<int>(nums.size());
    int slow=0;
    for(int fast=0;fast<n;fast++)
    {
        if(nums[fast]!=0)
            nums[slow++]=nums[fast];
    }
    while(slow<n)
        nums[slow++]=0;
}


int main()
{
    // 1. LC 15 三数之和
    {
        vector<int> nums = {-1, 0, 1, 2, -1, -4};
        vector<vector<int>> result = threeSum(nums);
        vector<vector<int>> expected = {{-1, -1, 2}, {-1, 0, 1}};
        assert(result == expected);
        cout << "threeSum passed!" << endl;
    }

    // 2. LC 11 盛最多水的容器
    {
        vector<int> height = {1, 8, 6, 2, 5, 4, 8, 3, 7};
        assert(maxArea(height) == 49);
        cout << "maxArea passed!" << endl;
    }

    // 3. LC 42 接雨水
    {
        vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
        assert(trap(height) == 6);
        cout << "trap passed!" << endl;
    }

    // 4. LC 88 合并两个有序数组
    {
        vector<int> nums1 = {1, 2, 3, 0, 0, 0};
        vector<int> nums2 = {2, 5, 6};
        merge(nums1, 3, nums2, 3);
        vector<int> expected = {1, 2, 2, 3, 5, 6};
        assert(nums1 == expected);
        cout << "merge passed!" << endl;
    }

    // 5. LC 283 移动零
    {
        vector<int> nums = {0, 1, 0, 3, 12};
        moveZeroes(nums);
        vector<int> expected = {1, 3, 12, 0, 0};
        assert(nums == expected);
        cout << "moveZeroes passed!" << endl;
    }

    // 边界测试：全 0 / 无 0 / 单元素
    {
        vector<int> nums = {0, 0, 0};
        moveZeroes(nums);
        assert((nums == vector<int>{0, 0, 0}));

        vector<int> nums2 = {1, 2, 3};
        moveZeroes(nums2);
        assert((nums2 == vector<int>{1, 2, 3}));

        vector<int> nums3 = {0};
        moveZeroes(nums3);
        assert((nums3 == vector<int>{0}));
        cout << "boundary tests passed!" << endl;
    }

    cout << "\nAll tests passed!" << endl;
    return 0;
}
