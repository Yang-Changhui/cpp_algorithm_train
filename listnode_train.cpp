#include<iostream>
#include<vector>
#include<string>
#include <unordered_map>

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
        ListNode* next=cur->next;
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


/*
32. **LC 25 K 个一组翻转链表**｜Hard｜S｜分段操作
给你链表的头节点 head ，每 k 个节点一组进行翻转，请你返回修改后的链表。

k 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 k 的整数倍，
那么请将最后剩余的节点保持原有顺序。

你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。

输入：head = [1,2,3,4,5], k = 2
输出：[2,1,4,3,5]
*/

ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode dummy(0);
    dummy.next = head;
    ListNode* prev = &dummy;

    while(true)
    {
        // 首先判断是否够k个
        ListNode* kth = prev;
        for(int i=0;i<k;++i)
        {
            kth=kth->next;
            if(kth==nullptr)
            {
                return dummy.next;
            }
        }

        ListNode* cur = prev->next;

        for(int i=1;i<k;++i)
        {
            ListNode* next = cur->next;
            cur->next=next->next;
            next->next=prev->next;
            prev->next=next;
        }
        prev=cur;
    }
}

/*
33. **LC 146 LRU 缓存**｜Medium｜S｜哈希 + 双向链表
请你设计并实现一个满足  LRU (最近最少使用) 缓存 约束的数据结构。
实现 LRUCache 类：
LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存
int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value ；
如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过 capacity ，则应该 逐出 最久未使用的关键字。
函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。

示例：

输入
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
输出
[null, null, null, 1, null, -1, null, -1, 3, 4]
*/

class LRUCache {
private:
    struct Node {
        int key;
        int value;
        Node* prev;
        Node* next;

        Node(int k, int v)
            : key(k), value(v), prev(nullptr), next(nullptr) {}
    };

    int capacity;
    unordered_map<int, Node*> cache;
    Node* head;
    Node* tail;

    void addToHead(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void moveToHead(Node* node) {
        removeNode(node);
        addToHead(node);
    }

    Node* removeTail() {
        Node* node = tail->prev;
        removeNode(node);
        return node;
    }

public:
    explicit LRUCache(int capacity) : capacity(capacity) {
        head = new Node(0, 0);
        tail = new Node(0, 0);
        head->next = tail;
        tail->prev = head;
    }

    ~LRUCache() {
        Node* cur = head;
        while (cur != nullptr) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
    }

    int get(int key) {
        auto it = cache.find(key);
        if (it == cache.end()) {
            return -1;
        }

        Node* node = it->second;
        moveToHead(node);
        return node->value;
    }

    void put(int key, int value) {
        auto it = cache.find(key);
        if (it != cache.end()) {
            Node* node = it->second;
            node->value = value;
            moveToHead(node);
            return;
        }

        Node* node = new Node(key, value);
        cache[key] = node;
        addToHead(node);

        if (static_cast<int>(cache.size()) > capacity) {
            Node* removed = removeTail();
            cache.erase(removed->key);
            delete removed;
        }
    }
};



ListNode* buildList(const vector<int>& nums) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    for (int x : nums) {
        tail->next = new ListNode(x);
        tail = tail->next;
    }
    return dummy.next;
}

vector<int> listToVector(ListNode* head) {
    vector<int> result;
    while (head != nullptr) {
        result.push_back(head->val);
        head = head->next;
    }
    return result;
}

void freeList(ListNode* head) {
    while (head != nullptr) {
        ListNode* next = head->next;
        delete head;
        head = next;
    }
}

void printVector(const vector<int>& nums) {
    cout << "[";
    for (size_t i = 0; i < nums.size(); ++i) {
        if (i > 0) cout << ",";
        cout << nums[i];
    }
    cout << "]";
}

void checkListTest(const string& name, ListNode* head, const vector<int>& expected) {
    vector<int> actual = listToVector(head);
    cout << name << ": ";
    printVector(actual);
    cout << "  expected=";
    printVector(expected);
    cout << (actual == expected ? "  PASS\n" : "  FAIL\n");
}

int main() {
    cout << "===== Linked List Tests =====\n";

    {
        ListNode* head = buildList({1, 2, 3, 4, 5});
        head = reverseList(head);
        checkListTest("reverseList", head, {5, 4, 3, 2, 1});
        freeList(head);
    }

    {
        ListNode* list1 = buildList({1, 2, 4});
        ListNode* list2 = buildList({1, 3, 4});
        ListNode* head = mergeTwoLists(list1, list2);
        checkListTest("mergeTwoLists", head, {1, 1, 2, 3, 4, 4});
        freeList(head);
    }

    {
        ListNode* head = buildList({3, 2, 0, -4});
        ListNode* second = head->next;
        ListNode* tail = head;
        while (tail->next != nullptr) tail = tail->next;
        tail->next = second;
        cout << "hasCycle(true): " << (hasCycle(head) ? "PASS" : "FAIL") << "\n";
        tail->next = nullptr;
        freeList(head);

        head = buildList({1, 2, 3});
        cout << "hasCycle(false): " << (!hasCycle(head) ? "PASS" : "FAIL") << "\n";
        freeList(head);
    }

    {
        ListNode* head = buildList({1, 2, 3, 4, 5});
        head = reverseBetween(head, 2, 4);
        checkListTest("reverseBetween", head, {1, 4, 3, 2, 5});
        freeList(head);
    }

    {
        ListNode* head = buildList({1, 2, 3, 4, 5});
        head = reverseKGroup(head, 2);
        checkListTest("reverseKGroup(k=2)", head, {2, 1, 4, 3, 5});
        freeList(head);

        head = buildList({1, 2, 3, 4, 5});
        head = reverseKGroup(head, 3);
        checkListTest("reverseKGroup(k=3)", head, {3, 2, 1, 4, 5});
        freeList(head);
    }

    cout << "\n===== LRU Cache Tests =====\n";
    {
        LRUCache cache(2);
        cache.put(1, 1);
        cache.put(2, 2);
        cout << "get(1) = " << cache.get(1) << " expected=1 " << (cache.get(1) == 1 ? "PASS" : "FAIL") << "\n";
        cache.put(3, 3);
        cout << "get(2) = " << cache.get(2) << " expected=-1 " << (cache.get(2) == -1 ? "PASS" : "FAIL") << "\n";
        cache.put(4, 4);
        cout << "get(1) = " << cache.get(1) << " expected=-1 " << (cache.get(1) == -1 ? "PASS" : "FAIL") << "\n";
        cout << "get(3) = " << cache.get(3) << " expected=3 " << (cache.get(3) == 3 ? "PASS" : "FAIL") << "\n";
        cout << "get(4) = " << cache.get(4) << " expected=4 " << (cache.get(4) == 4 ? "PASS" : "FAIL") << "\n";
    }

    return 0;
}
