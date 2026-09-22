#include<iostream>
#include<vector>
#include<utility>
#include <algorithm>
#include<queue>
using namespace std;

/*
82. **LC 48 旋转图像**｜Medium｜S｜矩阵原地变换
给定一个 n × n 的二维矩阵 matrix 表示一个图像。请你将图像顺时针旋转 90 度。

你必须在 原地 旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要 使用另一个矩阵来旋转图像。
输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[[7,4,1],[8,5,2],[9,6,3]]
*/

void rotate(vector<vector<int>>& matrix) {
    // 先对角线交换
    int n=matrix.size();
    int m=matrix[0].size();
    for(int i=0;i<n;++i)
    {
        for(int j=i+1;j<m;++j)
        {
            swap(matrix[i][j],matrix[j][i]);
        }
    }
    //左右交换
    // for(int i=0;i<n;++i)
    // {
    //     for(int j=0;j<m/2;++j)
    //     {
    //         swap(matrix[i][j],matrix[i][m-j-1]);
    //     }
    // }
    for(int i=0;i<n;++i)
        reverse(matrix[i].begin(),matrix[i].end());
}

/*
83. **LC 54 螺旋矩阵**｜Medium｜S｜边界模拟
给你一个 m 行 n 列的矩阵 matrix ，请按照 顺时针螺旋顺序 ，返回矩阵中的所有元素。

输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[1,2,3,6,9,8,7,4,5]
*/
vector<int> spiralOrder(vector<vector<int>>& matrix)
{
    vector<int> ans;

    int m = matrix.size();
    int n = matrix[0].size();

    int top = 0;
    int bottom = m - 1;
    int left = 0;
    int right = n - 1;

    while (top <= bottom && left <= right)
    {
        // 1. 上边：左 -> 右
        for (int j = left; j <= right; j++)
        {
            ans.push_back(matrix[top][j]);
        }
        top++;

        // 2. 右边：上 -> 下
        for (int i = top; i <= bottom; i++)
        {
            ans.push_back(matrix[i][right]);
        }
        right--;

        // 防止只剩一行时重复遍历
        if (top <= bottom)
        {
            // 3. 下边：右 -> 左
            for (int j = right; j >= left; j--)
            {
                ans.push_back(matrix[bottom][j]);
            }
            bottom--;
        }

        // 防止只剩一列时重复遍历
        if (left <= right)
        {
            // 4. 左边：下 -> 上
            for (int i = bottom; i >= top; i--)
            {
                ans.push_back(matrix[i][left]);
            }
            left++;
        }
    }

    return ans;
}

/*
84. **LC 136 只出现一次的数字**｜Easy｜S｜异或
给你一个 非空 整数数组 nums ，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。

你必须设计并实现线性时间复杂度的算法来解决此问题，且该算法只使用常量额外空间。


示例 1 ：

输入：nums = [2,2,1]

输出：1
*/

int singleNumber(vector<int>& nums) {
    int ans=0;
    for(int num:nums)
        ans=ans^num;
    return ans;
}

/*
85. **LC 973 最接近原点的 K 个点**｜Medium｜S｜距离 + 堆 / 快选
给定一个数组 points ，其中 points[i] = [xi, yi] 表示 X-Y 平面上的一个点，
并且是一个整数 k ，返回离原点 (0,0) 最近的 k 个点。

这里，平面上两点之间的距离是 欧几里德距离（ √(x1 - x2)2 + (y1 - y2)2 ）。

你可以按 任何顺序 返回答案。除了点坐标的顺序之外，答案 确保 是 唯一 的。
输入：points = [[1,3],[-2,2]], k = 1
输出：[[-2,2]]
解释： 
(1, 3) 和原点之间的距离为 sqrt(10)，
(-2, 2) 和原点之间的距离为 sqrt(8)，
由于 sqrt(8) < sqrt(10)，(-2, 2) 离原点更近。
我们只需要距离原点最近的 K = 1 个点，所以答案就是 [[-2,2]]。

*/

vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
    int n=points.size();

    priority_queue<pair<int,int>> pq; //大根堆
    for(int i=0;i<n;++i)
    {
        int dis=points[i][0]*points[i][0]+points[i][1]*points[i][1];
        pq.push({dis,i});
        if(pq.size()>k)
            pq.pop();
    }
    vector<vector<int>> result;
    while(!pq.empty())
    {
        auto [dis,loc]=pq.top();
        pq.pop();
        result.push_back(points[loc]);
    }
    return result;
}


int main()
{
    // LC 48 测试
    vector<vector<int>> matrix1 = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };

    rotate(matrix1);

    cout << "LC 48:" << endl;
    for(const auto& row : matrix1)
    {
        for(int num : row)
            cout << num << " ";
        cout << endl;
    }


    // LC 54 测试
    vector<vector<int>> matrix2 = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };

    vector<int> spiral = spiralOrder(matrix2);

    cout << "LC 54:" << endl;
    for(int num : spiral)
        cout << num << " ";
    cout << endl;


    // LC 136 测试
    vector<int> nums = {4,1,2,1,2};

    cout << "LC 136:" << endl;
    cout << singleNumber(nums) << endl;


    // LC 973 测试
    vector<vector<int>> points = {
        {1,3},
        {-2,2}
    };

    int k = 1;

    vector<vector<int>> closest = kClosest(points,k);

    cout << "LC 973:" << endl;
    for(const auto& point : closest)
    {
        cout << "[" << point[0] << "," << point[1] << "]" << endl;
    }

    return 0;
}