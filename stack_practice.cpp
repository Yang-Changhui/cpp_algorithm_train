#include<iostream>
#include <queue>
#include <vector>
#include <functional>
#include <map>

using namespace std;

/*
## 13. 堆与 Top-K（4）

75. **LC 215 数组中的第 K 个最大元素**｜Medium｜S｜堆 / 快选
给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。

请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。

你必须设计并实现时间复杂度为 O(n) 的算法解决此问题。

示例 1:

输入: [3,2,1,5,6,4], k = 2
输出: 5
*/
void top_down(vector<int>& heap, int i)
{
    int n = heap.size();

    while (true)
    {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && heap[left] < heap[smallest])
            smallest = left;

        if (right < n && heap[right] < heap[smallest])
            smallest = right;

        // 当前节点已经满足小根堆
        if (smallest == i)
            break;

        swap(heap[i], heap[smallest]);
        i = smallest;
    }
}

void build_heap(vector<int>& heap)
{
    for (int i = heap.size() / 2 - 1; i >= 0; --i)
        top_down(heap, i);
}

int findKthLargest(vector<int>& nums, int k)
{
    // 维护大小为 k 的小根堆
    vector<int> heap(nums.begin(), nums.begin() + k);

    build_heap(heap);

    for (int i = k; i < nums.size(); ++i)
    {
        // 比第 k 大候选值还小，不需要处理
        if (nums[i] <= heap[0])
            continue;

        // 替换堆顶
        heap[0] = nums[i];

        // 恢复小根堆
        top_down(heap, 0);
    }

    return heap[0];
}

int findKthLargest_2(vector<int>& nums, int k)
{
    // 小根堆
    priority_queue<int, vector<int>, greater<int>> pq;

    for (int num : nums)
    {
        pq.push(num);

        // 始终只保留最大的 k 个元素
        if (pq.size() > k)
            pq.pop();
    }

    // 最大的 k 个元素中，最小的就是第 k 大
    return pq.top();
}


/*
76. **LC 347 前 K 个高频元素**｜Medium｜S｜桶 / 堆
给你一个整数数组 nums 和一个整数 k ，请你返回其中出现频率前 k 高的元素。你可以按 任意顺序 返回答案。

示例 1：

输入：nums = [1,1,1,2,2,3], k = 2

输出：[1,2]
*/

vector<int> topKFrequent(vector<int>& nums, int k) {
    // 字典，堆频率建立最小堆
    map<int,int> m;
    int n=nums.size();
    for(int i=0;i<n;++i)
        m[nums[i]]++;
    priority_queue<
    pair<int,int>,
    vector<pair<int,int>>,
    greater<pair<int,int>>
    > pq;
    for(const auto &pair:m)
    {
        pq.push({pair.second,pair.first});
        if(pq.size()>k)
            pq.pop();
    }
    vector<int> result;
    while (!pq.empty()) {
        result.push_back(pq.top().second);
        pq.pop();
    }
    return result;
}

/*
77. **LC 23 合并 K 个升序链表**｜Hard｜S｜小根堆
给你一个链表数组，每个链表都已经按升序排列。

请你将所有链表合并到一个升序链表中，返回合并后的链表。

示例 1：

输入：lists = [[1,4,5],[1,3,4],[2,6]]
输出：[1,1,2,3,4,4,5,6]
解释：链表数组如下：
[
  1->4->5,
  1->3->4,
  2->6
]
将它们合并到一个有序链表中得到。
1->1->2->3->4->4->5->6
*/

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
struct cmp{
    bool operator()(ListNode* a,ListNode* b)
    {
        return a->val>b->val;
    }
};
ListNode* mergeKLists(vector<ListNode*>& lists) {
    priority_queue<
    ListNode*,
    vector<ListNode*>,
    cmp
    > pq;
    int n=lists.size();
    // 每个链表的头节点入堆
    for (ListNode* node : lists) {
        if (node != nullptr)
            pq.push(node);
    }

    ListNode dummy(0);
    ListNode* first=&dummy;
    while(!pq.empty())
    {
        ListNode* node=pq.top();
        pq.pop();
        first->next=node;
        first=first->next;
        if(node->next!=nullptr)
            pq.push(node->next);
    }
    return dummy.next;
}

/*
78. **LC 295 数据流的中位数**｜Hard｜A｜双堆
中位数是有序整数列表中的中间值。如果列表的大小是偶数，则没有中间值，中位数是两个中间值的平均值。

例如 arr = [2,3,4] 的中位数是 3 。
例如 arr = [2,3] 的中位数是 (2 + 3) / 2 = 2.5 。
实现 MedianFinder 类:

MedianFinder() 初始化 MedianFinder 对象。

void addNum(int num) 将数据流中的整数 num 添加到数据结构中。

double findMedian() 返回到目前为止所有元素的中位数。与实际答案相差 10-5 以内的答案将被接受。

示例 1：

输入
["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
[[], [1], [2], [], [3], []]
输出
[null, null, null, 1.5, null, 2.0]
*/

class MedianFinder {
public:
    priority_queue<int,vector<int>> pq_large; //大根堆，保存前半部分数组
    priority_queue<int,vector<int>,greater<int>> pq_small; //小根堆，保存后半部分数组

    MedianFinder() {
    }
    
    void addNum(int num) {
        //先放入左边
        pq_large.push(num);

        //将左边最大的移动到右边
        pq_small.push(pq_large.top());
        pq_large.pop();
        while (pq_large.size()<pq_small.size())
        {
            pq_large.push(pq_small.top());
            pq_small.pop();
        }
        
    }
    
    double findMedian() {
        if (pq_large.size() == pq_small.size()) {
            return ((double)pq_large.top() + pq_small.top()) / 2.0;
        }
        else {
            return pq_large.top();
        }
    }
};