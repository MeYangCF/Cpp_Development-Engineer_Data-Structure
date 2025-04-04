/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-03-25 下午9:27
@description:
*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;
class Solution {
// 数组
public:
    // 53.最大子数组和
    int maxSubArray(vector<int>& nums) {
        if (nums.size() == 0) {
            return 0;
        }
        vector<int> dp(nums.size());
        dp[0] = nums[0];
        int result = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            dp[i] = max(nums[i], dp[i - 1] + nums[i]);
            if (dp[i] > result) {
                result = dp[i];
            }
        }
        return result;
    }

    // 56.合并区间
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> result;
        sort(intervals.begin(), intervals.end(), [](const vector<int> &a, const vector<int> &b){return a[0] < b[0];});
        result.push_back(intervals[0]);
        for (int i = 1; i < intervals.size(); i++) {
            vector<int> tmp = result.back();
            if (tmp[1] < intervals[i][0]) {
                result.push_back(intervals[i]);
            }
            else {
                if (tmp[1] < intervals[i][1]) {
                    tmp[1] = intervals[i][1];
                    result.pop_back();
                    result.push_back(tmp);
                }
                else {
                    continue;
                }
            }
        }
        return result;
    }

    // 189.轮转数组
    void rotate(vector<int>& nums, int k) {
        int loop = k % nums.size();
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin() + loop);
        reverse(nums.begin() + loop, nums.end());
    }

    // 238.除自身以外数组的乘积
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> left(nums.size() + 1, 1);
        vector<int> right(nums.size() + 1, 1);
        vector<int> result(nums.size(), 0);
        for (int i = 0; i < nums.size(); i++) {
            left[i + 1] = nums[i] * left[i];
        }
        for (int i = nums.size() - 1; i >= 0; i--) {
            right[i] = nums[i] * right[i + 1];
        }
        for (int i = 0; i < nums.size(); i++) {
            result[i] = left[i] * right[i + 1];
        }
        return result;
    }

    // 41.缺失的第一个正数
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            while (nums[i] >= 1 && nums[i] <= n && nums[i] - 1 != i && nums[i] != nums[nums[i] - 1]) {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }
        return n + 1;
    }

// 链表
private:

    struct ListNode {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

    class Node {
    public:
        int val;
        Node* next;
        Node* random;

        Node(int _val) {
            val = _val;
            next = nullptr;
            random = nullptr;
        }
    };

public:
    // 160.相交链表
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* ANode = headA;
        int countA = 0;
        while (ANode) {
            countA++;
            ANode = ANode->next;
        }
        ANode = headA;
        ListNode* BNode = headB;
        int countB = 0;
        while (BNode) {
            countB++;
            BNode = BNode->next;
        }
        BNode = headB;
        int n = abs(countA - countB);
        if (countA > countB) {
            while (n--) {
                ANode = ANode->next;
            }
        }
        if (countB > countA) {
            while (n--) {
                BNode = BNode->next;
            }
        }
        while (ANode != BNode) {
            ANode = ANode->next;
            BNode = BNode->next;
        }
        return ANode;
    }

    // 206.反转链表
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr) {
            return nullptr;
        }
        ListNode* pre = nullptr;
        ListNode* p = head;
        ListNode* tmp;
        while (p != nullptr) {
            tmp = p->next;
            p->next = pre;
            pre = p;
            p = tmp;
        }
        return pre;
    }

    // 234.回文链表
    bool isPalindrome(ListNode* head) {
        vector<int> listVec;
        ListNode* p = head;
        bool result = true;
        while (p != nullptr) {
            listVec.push_back(p->val);
            p = p->next;
        }
        for (int i = 0, j = listVec.size() - 1; i <= j; i++, j--) {
            if (listVec[i] != listVec[j]) {
                result = false;
            }
        }
        return result;
    }

    // 141.环形链表
    bool hasCycle(ListNode *head) {
        bool result = false;
        if (head == nullptr) {
            return result;
        }
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                result = true;
                break;
            }
        }
        return result;
    }

    // 142.环形链表Ⅱ
    ListNode *detectCycle(ListNode *head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                fast = head;
                while (slow != fast) {
                    slow = slow->next;
                    fast = fast->next;
                }
                return fast;
            }
        }
        return nullptr;
    }

    // 21.合并两个有序的链表
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* head = new ListNode();
        ListNode* tmp = head;
        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val <= list2->val) {
                tmp->next = list1;
                list1 = list1->next;
            }
            else {
                tmp->next = list2;
                list2 = list2->next;
            }
            tmp = tmp->next;
        }
        if (list1 != nullptr) {
            tmp->next = list1;
        }
        if (list2 != nullptr) {
            tmp->next = list2;
        }
        return head->next;
    }

    // 2.两数相加
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int index = 0;
        ListNode* head = new ListNode();
        ListNode* tmp = head;
        while (l1 != nullptr && l2 != nullptr) {
            int val = l1->val + l2->val + index;
            if (val >= 10) {
                index = val / 10;
                val = val % 10;
            }
            else {
                index = 0;
            }
            tmp->next = new ListNode(val);
            l1 = l1->next;
            l2 = l2->next;
            tmp = tmp->next;
        }
        if (l1 != nullptr) {
            while (l1 != nullptr) {
                int val = l1->val + index;
                if (val >= 10) {
                    index = val / 10;
                    val = val % 10;
                }
                else {
                    index = 0;
                }
                tmp->next = new ListNode(val);
                l1 = l1->next;
                tmp = tmp->next;
            }
        }
        if (l2 != nullptr) {
            while (l2 != nullptr) {
                int val = l2->val + index;
                if (val >= 10) {
                    index = val / 10;
                    val = val % 10;
                }
                else {
                    index = 0;
                }
                tmp->next = new ListNode(val);
                l2 = l2->next;
                tmp = tmp->next;
            }
        }
        if (index == 1) {
            tmp->next = new ListNode(index);
        }
        return head->next;
    }

    // 19.删除链表的倒数第N个节点
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* newHead = new ListNode(0);
        newHead->next = head;
        ListNode* p = newHead;
        ListNode* q = newHead;
        while (n--) {
            q = q->next;
        }
        while (q->next != nullptr) {
            p = p->next;
            q = q->next;
        }
        p->next = p->next->next;
        return newHead->next;
    }

    // 24.两两交换链表中的节点
    ListNode* swapPairs(ListNode* head) {
        ListNode* newHead = new ListNode(0);
        newHead->next = head;
        if (newHead->next == nullptr) {
            return nullptr;
        }
        ListNode* p = newHead;
        ListNode* q = newHead->next;
        while (q != nullptr && q->next != nullptr) {
            p->next = q->next;
            q->next = q->next->next;
            p->next->next = q;
            p = q;
            q = q->next;
        }
        return newHead->next;
    }

    // 25.k个一组的翻转链表
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head || k == 1) return head;

        // 第一步：计算链表的长度
        int length = 0;
        ListNode* temp = head;
        while (temp) {
            length++;
            temp = temp->next;
        }

        // 第二步：创建一个虚拟头节点，简化边界条件
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* prevGroupEnd = dummy;

        // 第三步：反转每个 k 个节点一组
        while (length >= k) {
            ListNode* groupStart = prevGroupEnd->next;
            ListNode* groupEnd = groupStart;
            for (int i = 1; i < k; ++i) {
                groupEnd = groupEnd->next;
            }
            ListNode* nextGroupStart = groupEnd->next;

            // 反转当前的 k 个节点
            ListNode* prev = nextGroupStart;
            ListNode* current = groupStart;
            while (current != nextGroupStart) {
                ListNode* next = current->next;
                current->next = prev;
                prev = current;
                current = next;
            }

            // 连接反转后的节点
            prevGroupEnd->next = groupEnd;
            groupStart->next = nextGroupStart;

            // 移动 prevGroupEnd 到当前反转后的组的末尾
            prevGroupEnd = groupStart;

            // 剩余的节点长度减去 k
            length -= k;
        }

        return dummy->next;
    }

    // 138.随机链表的复制
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;

        // Step 1: 创建新节点并插入到原链表的每个节点后
        Node* current = head;
        while (current) {
            Node* newNode = new Node(current->val);
            newNode->next = current->next;
            current->next = newNode;
            current = newNode->next;
        }

        // Step 2: 复制random指针
        current = head;
        while (current) {
            if (current->random) {
                current->next->random = current->random->next;
            }
            current = current->next->next;
        }

        // Step 3: 拆分链表
        Node* original = head;
        Node* copyHead = head->next;
        Node* copyCurrent = copyHead;
        while (original) {
            original->next = original->next->next;
            if (copyCurrent->next) {
                copyCurrent->next = copyCurrent->next->next;
                copyCurrent = copyCurrent->next;
            }
            original = original->next;
        }

        return copyHead;
    }

    // 148.排序链表
    ListNode* sortList(ListNode* head) {
        if (!head) return nullptr;  // 处理空链表的情况

        // 1. 将链表节点存入vector
        vector<ListNode*> nodeVec;
        ListNode* p = head;
        while (p != nullptr) {
            nodeVec.push_back(p);
            p = p->next;
        }

        // 2. 对节点按值排序
        sort(nodeVec.begin(), nodeVec.end(), [](ListNode* node1, ListNode* node2) {
            return node1->val < node2->val;
        });

        // 3. 重建有序链表
        for (int i = 0; i < nodeVec.size() - 1; ++i) {
            nodeVec[i]->next = nodeVec[i + 1];  // 将节点连接起来
        }
        nodeVec.back()->next = nullptr;  // 最后一个节点的 next 设置为 null

        return nodeVec.front();  // 返回排序后的链表头
    }

    // 23.合并k个升序链表
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, Compare> nodeQue;
        for (int i = 0; i < lists.size(); i++) {
            if (lists[i] != nullptr) {
                nodeQue.push(lists[i]);
            }
        }
        ListNode* dummy = new ListNode();
        ListNode* tail = dummy;
        while (!nodeQue.empty()) {
            ListNode* newNode = nodeQue.top();
            nodeQue.pop();
            tail->next = newNode;
            tail = tail->next;
            if (newNode->next != nullptr) {
                nodeQue.push(newNode->next);
            }
        }
        return dummy->next;
    }

    struct Compare {
        bool operator()(ListNode* l1, ListNode* l2) {
            return l1->val > l2->val;  // 值较小的优先
        }
    };

    // 146.LRU缓存
struct DListNode {
        int key, value;
        DListNode* prev;
        DListNode* next;
        DListNode(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
    };

    class LRUCache {
    public:
        LRUCache(int capacity) {
            this->capacity = capacity;
            head = new DListNode(0, 0);  // 哑头节点
            tail = new DListNode(0, 0);  // 哑尾节点
            head->next = tail;
            tail->prev = head;
        }

        int get(int key) {
            if (cache.find(key) == cache.end()) {
                return -1;  // 键不存在
            }
            // 将该节点移到链表头部（表示最近使用）
            moveToHead(cache[key]);
            return cache[key]->value;
        }

        void put(int key, int value) {
            if (cache.find(key) == cache.end()) {
                // 如果缓存满了，移除链表尾部的节点
                if (cache.size() == capacity) {
                    removeTail();
                }
                // 插入新节点
                DListNode* newNode = new DListNode(key, value);
                cache[key] = newNode;
                addToHead(newNode);
            } else {
                // 更新已有节点的值，并移到链表头部
                cache[key]->value = value;
                moveToHead(cache[key]);
            }
        }

    private:
        int capacity;
        unordered_map<int, DListNode*> cache;  // 哈希表存储键与节点的映射
        DListNode* head;  // 哑头节点
        DListNode* tail;  // 哑尾节点

        // 将节点添加到头部
        void addToHead(DListNode* node) {
            node->next = head->next;
            node->prev = head;
            head->next->prev = node;
            head->next = node;
        }

        // 移动节点到头部
        void moveToHead(DListNode* node) {
            removeNode(node);
            addToHead(node);
        }

        // 删除节点
        void removeNode(DListNode* node) {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }

        // 删除尾部节点
        void removeTail() {
            DListNode* tailNode = tail->prev;
            removeNode(tailNode);
            cache.erase(tailNode->key);
            delete tailNode;
        }
    };

// 栈
public:
    // 20.有效的括号
    bool isValid(string s) {
        stack<char> stc;
        for (auto c : s) {
            if (c == '(' || c == '{' || c == '[') {
                stc.push(c);
            }
            else {
                if (stc.empty()) {
                    return false;
                }
                if ((c == ')' && stc.top() == '(')
                    || (c == '}' && stc.top() == '{')
                    || (c == ']' && stc.top() == '[')){
                    stc.pop();
                }
                else {
                    return false;
                }
            }
        }
        return stc.empty();
    }

    // 155.最小栈
    class MinStack {
    public:
        MinStack() {

        }

        void push(int val) {
            if (minVal.empty() || val <= minVal.top()) {
                minVal.push(val);
            }
            st.push(val);
        }

        void pop() {
            if (!st.empty()) {
                if (minVal.top() == st.top()) {
                    minVal.pop();
                }
                st.pop();
            }
        }

        int top() {
            return st.top();
        }

        int getMin() {
            return minVal.top();
        }
    private:
        stack<int> minVal;
        stack<int> st;
    };

    // 394.字符串解码
    string decodeString(string s) {
        stack<int> numStack;      // 存储重复次数
        stack<string> strStack;   // 存储中间字符串
        string curr;              // 当前处理的字符串
        int num = 0;              // 当前数字

        for (char c : s) {
            if (isdigit(c)) {
                num = num * 10 + (c - '0');  // 处理可能超过一位的数字
            } else if (c == '[') {
                numStack.push(num);
                strStack.push(curr);
                num = 0;
                curr = "";
            } else if (c == ']') {
                int count = numStack.top();
                numStack.pop();
                string temp = curr;
                curr = strStack.top();
                strStack.pop();
                // 将 temp 重复 count 次后接到 curr 上
                for (int i = 0; i < count; i++) {
                    curr += temp;
                }
            } else {
                curr.push_back(c);
            }
        }
        return curr;
    }

    // 739.每日温度
    vector<int> dailyTemperatures(vector<int>& T) {
        // 递增栈
        stack<int> st;
        vector<int> result(T.size(), 0);
        st.push(0);
        for (int i = 1; i < T.size(); i++) {
            if (T[i] < T[st.top()]) {                       // 情况一
                st.push(i);
            } else if (T[i] == T[st.top()]) {               // 情况二
                st.push(i);
            } else {
                while (!st.empty() && T[i] > T[st.top()]) { // 情况三
                    result[st.top()] = i - st.top();
                    st.pop();
                }
                st.push(i);
            }
        }
        return result;
    }

    // 84.柱状图中最大的矩形
    int largestRectangleArea(vector<int>& heights) {
        int result = 0;
        stack<int> st;
        heights.insert(heights.begin(), 0); // 数组头部加入元素0
        heights.push_back(0); // 数组尾部加入元素0
        st.push(0);

        // 第一个元素已经入栈，从下标1开始
        for (int i = 1; i < heights.size(); i++) {
            if (heights[i] > heights[st.top()]) { // 情况一
                st.push(i);
            } else if (heights[i] == heights[st.top()]) { // 情况二
                st.pop(); // 这个可以加，可以不加，效果一样，思路不同
                st.push(i);
            } else { // 情况三
                while (!st.empty() && heights[i] < heights[st.top()]) { // 注意是while
                    int mid = st.top();
                    st.pop();
                    if (!st.empty()) {
                        int left = st.top();
                        int right = i;
                        int w = right - left - 1;
                        int h = heights[mid];
                        result = max(result, w * h);
                    }
                }
                st.push(i);
            }
        }
        return result;
    }
};