#include<iostream>
#include<vector>
#include<string>

using namespace std;

/*
## 6. 链表与设计（6）

28. **LC 206 反转链表**｜Easy｜S｜迭代与递归
给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。
输入：head = [1,2,3,4,5]
输出：[5,4,3,2,1]
*/

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* reverseList(ListNode* head) {
    ListNode* prev=nullptr;
    ListNode* cur=head;
    while(cur!=nullptr)
    {
        ListNode* next=cur.next;
        cur->next=prev;
        prev=cur;
        cur=next;
    }
    return prev;
}

/*
29. **LC 21 合并两个有序链表**｜Easy｜S｜虚拟头结点
将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 

输入：l1 = [1,2,4], l2 = [1,3,4]
输出：[1,1,2,3,4,4]
*/

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode dummy(0);
    ListNode* cur=&dummy;

    
    while(list1!=nullptr && list2!=nullptr)
    {
        if(list1->val<=list2->val)
        {
            cur->next=list1;
            list1=list1->next;
        }
        else
        {
            cur->next=list2;
            list2 = list2->next;
        }
        cur=cur->next;
    }
    cur->next = (list1 != nullptr) ? list1 : list2;

    return dummy.next;
}

/*
30. **LC 141 环形链表**｜Easy｜S｜快慢指针
给你一个链表的头节点 head ，判断链表中是否有环。

如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。 为了表示给定链表中的环，评测系统内部使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。注意：pos 不作为参数进行传递 。仅仅是为了标识链表的实际情况。

如果链表中存在环 ，则返回 true 。 否则，返回 false 。
*/
bool hasCycle(ListNode *head) {
    ListNode* slow=head;
    ListNode* fast=head;
    while(fast!=nullptr && fast->next!=nullptr)
    {
        slow=slow->next;
        fast=fast->next->next;
        if(slow==fast)
            return true;
    }
    return false;
}

/*
31. **LC 92 反转链表 II**｜Medium｜S｜局部反转
给你单链表的头指针 head 和两个整数 left 和 right ，其中 left <= right 。
请你反转从位置 left 到位置 right 的链表节点，返回 反转后的链表 。
输入：head = [1,2,3,4,5], left = 2, right = 4
输出：[1,4,3,2,5]
*/

ListNode* reverseBetween(ListNode* head, int left, int right) {
    ListNode dummy(0);
    dummy.next = head;

    ListNode* prev = &dummy;

    // 1. prev 移动到 left 前一个节点
    for (int i = 1; i < left; ++i) {
        prev = prev->next;
    }

    // 2. cur 指向 left 节点
    ListNode* cur = prev->next;

    // 3. 不断把 cur 后面的节点插到 prev 后面
    for (int i = 0; i < right - left; ++i) {
        ListNode* next = cur->next;

        cur->next = next->next;
        next->next = prev->next;
        prev->next = next;
    }

    return dummy.next;
}
