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
#include <unordered_map>
#include <unordered_set>
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

// 哈希
public:
    // 1.两数之和
    vector<int> twoSum(vector<int>& nums, int target) {
        std::unordered_map <int,int> map;
        for(int i = 0; i < nums.size(); i++) {
            // 遍历当前元素，并在map中寻找是否有匹配的key
            auto iter = map.find(target - nums[i]);
            if(iter != map.end()) {
                return {iter->second, i};
            }
            // 如果没找到匹配对，就把访问过的元素和下标加入到map中
            map.insert(pair<int, int>(nums[i], i));
        }
        return {};
    }

    // 49.字母异位词分组
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> anagramMap;
        for (const string& str : strs) {
            string sortedStr = str;
            sort(sortedStr.begin(), sortedStr.end()); // 对字符串排序
            anagramMap[sortedStr].push_back(str);    // 使用排序后的字符串作为键
        }

        vector<vector<string>> ans;
        for (const auto& pair : anagramMap) {
            ans.push_back(pair.second); // 将每组异位词加入结果
        }
        return ans;
    }

    // 128.最长连续序列
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> mySet;
        for(int i = 0; i < nums.size(); i++) {
            mySet.insert(nums[i]);
        }
        int length = 0;

        for (const int& num : mySet) {
            if(!mySet.count(num - 1)) {
                int currentNum = num;
                int currentStreak = 1;

                while(mySet.count(currentNum + 1)) {
                    currentNum++;
                    currentStreak++;
                }
                length= max(length, currentStreak);
            }
        }
        return length;
    }

// 滑动窗口
public:
    // 3.无重复字符的最长子串
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> charSet;
        int maxLength = 0;
        for (int i = 0; i < s.size(); i++) {
            int currentLength = 0;
            charSet.clear();
            int j = i;
            while (charSet.find(s[j]) == charSet.end() && j < s.size()) {
                charSet.insert(s[j]);
                currentLength++;
                j++;
            }
            maxLength = max(maxLength, currentLength);
        }
        return maxLength;
    }

    // 438.找到字符串中所有字母异位词
    vector<int> findAnagrams(string s, string p) {
        int sLen = s.size(), pLen = p.size();  // 获取 s 和 p 的长度

        // 如果 s 的长度小于 p 的长度，无法找到异位词，直接返回空的结果
        if (sLen < pLen) {
            return vector<int>();
        }

        // 创建一个结果 vector，用于存储所有的异位词起始位置
        vector<int> ans;

        // 创建两个大小为 26 的 vector，分别用于存储 s 和 p 中每个字符的出现次数
        vector<int> sCount(26, 0);  // sCount 存储当前窗口中字符的频次
        vector<int> pCount(26, 0);  // pCount 存储 p 中字符的频次

        // 遍历 p 的每个字符，更新 pCount 和 sCount
        for (int i = 0; i < pLen; ++i) {
            ++sCount[s[i] - 'a'];  // 更新 s 中当前窗口的字符频次
            ++pCount[p[i] - 'a'];  // 更新 p 中的字符频次
        }

        // 如果 s 和 p 在最开始的窗口是异位词，则记录下起始位置 0
        if (sCount == pCount) {
            ans.emplace_back(0);  // 如果当前窗口中的字符频次与 p 的频次相等，说明是异位词
        }

        // 遍历 s 中的其他字符，维护一个滑动窗口
        // 窗口大小始终保持为 pLen
        for (int i = 0; i < sLen - pLen; ++i) {
            // 滑动窗口：减少 sCount 中窗口左侧字符的频次，增加右侧字符的频次
            --sCount[s[i] - 'a'];  // 移除窗口左端的字符
            ++sCount[s[i + pLen] - 'a'];  // 加入窗口右端的字符

            // 如果滑动后的窗口与 pCount 相等，说明该窗口是一个异位词
            if (sCount == pCount) {
                ans.emplace_back(i + 1);  // 记录该窗口的起始位置
            }
        }

        return ans;  // 返回所有找到的异位词的起始位置
    }

// 子串
public:
    // 560.和为 K 的子数组
    int subarraySum(vector<int>& nums, int k) {
        int result = 0;
        int sum = 0;
        unordered_map<int, int> prefixSumCount;
        prefixSumCount[0] = 1;  // 初始化前缀和为 0 的情况，确保从头开始的子数组符合条件

        for (int num : nums) {
            sum += num;  // 累加当前数
            if (prefixSumCount.find(sum - k) != prefixSumCount.end()) {
                result += prefixSumCount[sum - k];  // 如果找到 sum - k，就说明有符合条件的子数组
            }
            prefixSumCount[sum]++;  // 更新当前前缀和的出现次数
        }

        return result;
    }

    // 239.滑动窗口最大值
private:
    class MyQueue { //单调队列（从大到小）
    public:
        deque<int> que; // 使用deque来实现单调队列
        // 每次弹出的时候，比较当前要弹出的数值是否等于队列出口元素的数值，如果相等则弹出。
        // 同时pop之前判断队列当前是否为空。
        void pop(int value) {
            if (!que.empty() && value == que.front()) {
                que.pop_front();
            }
        }
        // 如果push的数值大于入口元素的数值，那么就将队列后端的数值弹出，直到push的数值小于等于队列入口元素的数值为止。
        // 这样就保持了队列里的数值是单调从大到小的了。
        void push(int value) {
            while (!que.empty() && value > que.back()) {
                que.pop_back();
            }
            que.push_back(value);

        }
        // 查询当前队列里的最大值 直接返回队列前端也就是front就可以了。
        int front() {
            return que.front();
        }
    };
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        MyQueue que;
        vector<int> result;
        for (int i = 0; i < k; i++) { // 先将前k的元素放进队列
            que.push(nums[i]);
        }
        result.push_back(que.front()); // result 记录前k的元素的最大值
        for (int i = k; i < nums.size(); i++) {
            que.pop(nums[i - k]); // 滑动窗口移除最前面元素
            que.push(nums[i]); // 滑动窗口前加入最后面的元素
            result.push_back(que.front()); // 记录对应的最大值
        }
        return result;
    }

    // 76.最小覆盖子串
    string minWindow(string s, string t) {
        unordered_map<char, int> need;
        for(auto c : t) ++need[c];
        int left = 0, right = 0;
        int count = 0;
        int start = 0; //用于记录符合要求的最小子串的开头
        int len = INT_MAX; //用于记录最小长度
        while(right < s.size()){
            auto c = s[right];
            ++right;
            if(need.count(c)){
                --need[c];
                if(need[c] == 0)    ++count;
            }

            while(count == need.size()){
                if(right - left < len){
                    start = left;
                    len = right  - left;
                }
                auto c = s[left];
                ++left;
                if(need.count(c)){
                    if(need[c] == 0)
                        --count;
                    ++need[c];
                }
            }
        }
        return len == INT_MAX ? "" : s.substr(start, len);
    }

// 二叉树
public:
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    // 94.二叉树的中序遍历
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> inVec;
        inorder(root, inVec);
        return inVec;
    }

    void inorder(TreeNode* node, vector<int>& inVec) {
        if(node != nullptr) {
            inorder(node->left, inVec);
            inVec.push_back(node->val);
            inorder(node->right, inVec);
        }
    }

    // 104.二叉树的最大深度
    int maxDepth(TreeNode* root) {
        return high(root);
    }

    int high(TreeNode* node) {
        if(node == nullptr) {
            return 0;
        }
        int left = high(node->left);
        int right = high(node->right);
        return left > right ? left + 1 : right + 1;
    }

    // 226. 翻转二叉树
    TreeNode* invertTree(TreeNode* root) {
        if(root == nullptr) {
            return nullptr;
        }

        TreeNode* tmp = root->left;
        root->left = root->right;
        root->right = tmp;

        root->left = invertTree(root->left);
        root->right = invertTree(root->right);
        return root;
    }

    // 101.对称二叉树
    bool isSymmetric(TreeNode* root) {
        return mirror02(root->left, root->right);
    }

    bool mirror02(TreeNode* node1, TreeNode* node2) {
        if (node1 == nullptr && node2 == nullptr) {
            return true;
        }
        if (node1 == nullptr || node2 == nullptr) {
            return false;
        }
        if (node1->val != node2->val) {
            return false;
        }
        return mirror02(node1->left, node2->right)
            && mirror02(node1->right, node2->left);
    }

    // 543.二叉树的直径
    int ans;
    int depth(TreeNode* rt){
        if (rt == NULL) {
            return 0; // 访问到空节点了，返回0
        }
        int L = depth(rt->left); // 左儿子为根的子树的深度
        int R = depth(rt->right); // 右儿子为根的子树的深度
        ans = max(ans, L + R + 1); // 计算d_node即L+R+1 并更新ans
        return max(L, R) + 1; // 返回该节点为根的子树的深度
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        ans = 1;
        depth(root);
        return ans - 1;
    }

    // 102.二叉树的层序遍历
    vector<vector<int>> levelOrder(TreeNode* root) {
        if(root == nullptr) {
            return {};
        }
        vector<vector<int>> res;
        queue<TreeNode*> que;
        que.push(root);
        while(!que.empty()) {
            int size = que.size();
            vector<int> vec;
            for(int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                vec.push_back(node->val);
                if(node->left != nullptr) {
                    que.push(node->left);
                }
                if(node->right != nullptr) {
                    que.push(node->right);
                }
            }
            res.push_back(vec);
        }
        return res;
    }

    // 108.将有序数组转换为二叉搜索树
private:
    TreeNode* traversal(vector<int>& nums, int left, int right) {
        if (left > right) return nullptr;
        int mid = left + ((right - left) / 2);
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = traversal(nums, left, mid - 1);
        root->right = traversal(nums, mid + 1, right);
        return root;
    }
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        TreeNode* root = traversal(nums, 0, nums.size() - 1);
        return root;
    }

    // 98.验证二叉搜索树
    vector<int> inVec;
    bool isValidBST(TreeNode* root) {
        inOrder(root);
        bool res = true;
        for(int i = 1; i < inVec.size(); i++) {
            if(inVec[i] <= inVec[i - 1]) {
                res = false;
            }
        }
        return res;
    }

    void inOrder(TreeNode* node) {
        if(node != nullptr) {
            inOrder(node->left);
            inVec.push_back(node->val);
            inOrder(node->right);
        }
    }

    // 230.二叉搜索树中第 K 小的元素
    vector<int> inVec;
    int kthSmallest(TreeNode* root, int k) {
        inOrder(root);
        return inVec[k - 1];
    }

    void inOrder(TreeNode* node) {
        if(node != nullptr) {
            inOrder(node->left);
            inVec.push_back(node->val);
            inOrder(node->right);
        }
    }

    // 199.二叉树的右视图
    vector<int> rightSideView(TreeNode* root) {
        if(root == nullptr) {
            return {};
        }
        vector<int> res;
        queue<TreeNode*> que;
        que.push(root);
        while(!que.empty()) {
            int size = que.size();
            for(int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                if(i == size - 1){
                    res.push_back(node->val);
                }
                if(node->left != nullptr) {
                    que.push(node->left);
                }
                if(node->right != nullptr) {
                    que.push(node->right);
                }
            }
        }
        return res;
    }

    // 114.二叉树展开为链表
    vector<TreeNode*> vec;
    void flatten(TreeNode* root) {
        if (root == nullptr) return;  // 如果树为空，直接返回
        preOrder(root);
        for (int i = 0; i < vec.size() - 1; i++) {
            vec[i]->right = vec[i + 1];  // 将当前节点的右指针指向下一个节点
            vec[i]->left = nullptr;       // 将左指针设为nullptr
        }
        vec.back()->right = nullptr;  // 确保最后一个节点的右指针为nullptr
        vec.back()->left = nullptr;   // 确保最后一个节点的左指针为nullptr
    }

    void preOrder(TreeNode* node) {
        if (node != nullptr) {
            vec.push_back(node);
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    // 105.从前序与中序遍历序列构造二叉树
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return _rebuild(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
    }

    TreeNode* _rebuild(vector<int>& preorder, int i, int j, vector<int>& inorder, int m, int n)
    {
        if (i > j || m > n)
        {
            return nullptr;
        }

        // 创建当前子树的根节点
        TreeNode* node = new TreeNode(preorder[i]);
        for (int k = m; k <= n; ++k)
        {
            if (preorder[i] == inorder[k]) // 在中序遍历中找子树根节点的下标k
            {
                node->left = _rebuild(preorder, i + 1, i + (k - m), inorder, m, k - 1); // L
                node->right = _rebuild(preorder, i + (k - m) + 1, j, inorder, k + 1, n); // R
                return node;
            }
        }
        return node;
    }

    // 437.路径总和 III
    int rootSum(TreeNode* root, long targetSum) {
        if (!root) {
            return 0;
        }

        int ret = 0;
        if (root->val == targetSum) {
            ret++;
        }

        ret += rootSum(root->left, targetSum - root->val);
        ret += rootSum(root->right, targetSum - root->val);
        return ret;
    }

    int pathSum(TreeNode* root, int targetSum) {
        if (!root) {
            return 0;
        }

        int ret = rootSum(root, targetSum);
        ret += pathSum(root->left, targetSum);
        ret += pathSum(root->right, targetSum);
        return ret;
    }

    // 236.二叉树的最近公共祖先
    //判断节点x是否在树中
    bool InTree(TreeNode* root, TreeNode* x)
    {
        if (root == nullptr) return false;
        if (root == x) return true;
        return InTree(root->left, x) || InTree(root->right, x);
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        //当前节点是其中一个目标节点，则直接返回当前节点
        if (root == p || root == q) return root;
        //去当前左子树中查找p节点
        bool pInLeft = InTree(root->left, p);
        //在左子树中就不在右子树，因此对pInLeft取反，就是其是否在右子树中的情况
        bool pInRight = !pInLeft;
        //对q节点和对p节点一样
        bool qInLeft = InTree(root->left, q);
        bool qInRight = !qInLeft;
        //在当前节点的左右子树中分别找到目标节点，说明当前节点就是最近公共祖先
        if ((pInLeft && qInRight) || (qInLeft && pInRight))
        {
            return root;
        }
        else if (pInLeft && qInLeft)
        {
            //p q都在当前节点的左子树中，因此在左子树中继续递归查找
            return lowestCommonAncestor(root->left, p, q);
        }
        else
        {
            //p q都在当前节点的右子树中，因此在右子树中继续递归查找
            return lowestCommonAncestor(root->right, p, q);
        }
    }

    // 124.二叉树中的最大路径和
    int maxPathSum(TreeNode* root) {
        if (!root) return 0;
        maxPathToLeaf(root);
        return res;
    }
    int maxPathToLeaf(TreeNode* root) {
        if (!root) return 0;
        int left = maxPathToLeaf(root->left);
        int right = maxPathToLeaf(root->right);
        if (left < 0) {
            left = 0;
        }
        if (right < 0) {
            right = 0;
        }
        res = max(res, left + right + root->val);
        return root->val + max(left, right);
    }
private:
    int res = INT_MIN;

// 堆
public:
    // 215.数组中的第K个最大元素
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int> myQue;
        for(int i = 0; i < nums.size(); i++) {
            myQue.push(nums[i]);
        }
        for(int i = 0; i < k - 1; i++) {
            myQue.pop();
        }
        return myQue.top();
    }

    // 347.前 K 个高频元素
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> freqMap;
        for (int num : nums) {
            freqMap[num]++;
        }

        // 定义比较函数对象
        struct Compare {
            bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
                return a.second < b.second; // 大顶堆，频率高的先出队
            }
        };

        priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;

        for (auto& entry : freqMap) {
            pq.push(entry);
        }

        vector<int> res;
        for (int i = 0; i < k; ++i) {
            res.push_back(pq.top().first);
            pq.pop();
        }

        return res;
    }

    // 295. 数据流的中位数
    class MedianFinder {
    private:
        priority_queue<int> maxHeap;         // 存储较小的一半（最大堆）
        priority_queue<int, vector<int>, greater<int>> minHeap;  // 存储较大的一半（最小堆）

    public:
        MedianFinder() {}

        void addNum(int num) {
            // 将新元素插入到合适的堆中
            if (maxHeap.empty() || num <= maxHeap.top()) {
                maxHeap.push(num);
            } else {
                minHeap.push(num);
            }

            // 平衡两个堆的大小
            if (maxHeap.size() > minHeap.size() + 1) {
                minHeap.push(maxHeap.top());
                maxHeap.pop();
            } else if (minHeap.size() > maxHeap.size()) {
                maxHeap.push(minHeap.top());
                minHeap.pop();
            }
        }

        double findMedian() {
            if (maxHeap.size() == minHeap.size()) {
                return (maxHeap.top() + minHeap.top()) / 2.0;
            } else {
                return maxHeap.top();
            }
        }
    };

// 双指针
public:
    // 283. 移动零
    void moveZeroes(vector<int>& nums) {
        int i = 0, j = 0;
        for (; j < nums.size(); j++) {
            if (nums[j] != 0) {
                nums[i++] = nums[j];
            }
        }
        for (int k = i; k < nums.size(); k++) {
            nums[k] = 0;
        }
    }

    // 11.盛最多水的容器
    int maxArea(vector<int>& height) {
        int h1 = 0, h2 = 0;
        int w = 0, v = 0;
        int maxv = 0;
        int l = 0;
        int r = height.size() - 1;
        while(r > l) {
            h1 = height[l];
            h2 = height[r];
            if(h1 > h2) {
                v = h2 * (r - l);
                r--;
            }
            else {
                v = h1 * (r - l);
                l++;
            }
            maxv = max(maxv, v);
        }
        return maxv;
    }

    // 15.三数之和
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        // 找出a + b + c = 0
        // a = nums[i], b = nums[left], c = nums[right]
        for (int i = 0; i < nums.size(); i++) {
            // 排序之后如果第一个元素已经大于零，那么无论如何组合都不可能凑成三元组，直接返回结果就可以了
            if (nums[i] > 0) {
                return result;
            }
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            int left = i + 1;
            int right = nums.size() - 1;
            while (right > left) {
                // 去重复逻辑如果放在这里，0，0，0 的情况，可能直接导致 right<=left 了，从而漏掉了 0,0,0 这种三元组
                if (nums[i] + nums[left] + nums[right] > 0) right--;
                else if (nums[i] + nums[left] + nums[right] < 0) left++;
                else {
                    result.push_back(vector<int>{nums[i], nums[left], nums[right]});
                    while (right > left && nums[right] == nums[right - 1]) right--;
                    while (right > left && nums[left] == nums[left + 1]) left++;
                    right--;
                    left++;
                }
            }

        }
        return result;
    }

    // 42.接雨水
    int trap(vector<int>& height) {
        if (height.size() <= 2) return 0;
        vector<int> maxLeft(height.size(), 0);
        vector<int> maxRight(height.size(), 0);
        int size = maxRight.size();

        // 记录每个柱子左边柱子最大高度
        maxLeft[0] = height[0];
        for (int i = 1; i < size; i++) {
            maxLeft[i] = max(height[i], maxLeft[i - 1]);
        }
        // 记录每个柱子右边柱子最大高度
        maxRight[size - 1] = height[size - 1];
        for (int i = size - 2; i >= 0; i--) {
            maxRight[i] = max(height[i], maxRight[i + 1]);
        }
        // 求和
        int sum = 0;
        for (int i = 0; i < size; i++) {
            int count = min(maxLeft[i], maxRight[i]) - height[i];
            if (count > 0) sum += count;
        }
        return sum;
    }

// 二分查找
public:
    // 35.搜索插入位置
    int searchInsert(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        while(left <= right) {
            int mid = left + (right - left) /2;
            if(nums[mid] == target) {
                return mid;
            }
            else if (nums[mid] > target) {
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
        return left;
    }

    // 74.搜索二维矩阵
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();
        if(matrix[0][0] > target || matrix[m -1][n - 1] < target) {
            return false;
        }
        int l = 0, r = m * n - 1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            int i = mid / n, j = mid % n;
            if(matrix[i][j] == target) {
                return true;
            }
            else if(matrix[i][j] > target) {
                r = mid - 1;
            }
            else {
                l = mid + 1;
            }
        }
        return false;
    }

    // 34.在排序数组中查找元素的第一个和最后一个位置
    vector<int> searchRange(vector<int>& nums, int target) {
        int rightBorder = getRightBorder(nums, target);
        int leftBorder = getleftBorder(nums, target);

        if (rightBorder == -2 || leftBorder == -2) {
            return {-1, -1};
        }
        if (rightBorder - leftBorder > 1) {
            return {leftBorder + 1, rightBorder - 1};
        }
        return {-1, -1};
    }

private:
    int getRightBorder(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        int rightBorder = -2;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] > target) {
                right = mid - 1;
            }
            else {
                left = mid + 1;
                rightBorder = left;
            }
        }
        return rightBorder;
    }

    int getleftBorder(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        int leftBorder = -2;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] >= target) {
                right = mid - 1;
                leftBorder = right;
            }
            else {
                left = mid + 1;
            }
        }
        return leftBorder;
    }

    // 33.搜索旋转排序数组
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if(nums[mid] == target) {
                return mid;
            }
            if(nums[left] <= nums[mid]) {
                if(nums[left] <= target && target < nums[mid]) {
                    right = mid - 1;
                }
                else {
                    left = mid + 1;
                }
            }
            else {
                if(nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;
                }
                else {
                    right = mid - 1;
                }
            }
        }
        return -1;
    }

    // 153.寻找旋转排序数组中的最小值
    int findMin(vector<int>& nums) {
        int l = 0;
        int r = nums.size() - 1;
        while(l < r) {
            int mid = l + (r - l) / 2;
            if(nums[mid] < nums[r]) {
                r = mid;
            }
            else {
                l = mid + 1;
            }
        }
        return nums[l];
    }

    // 4.寻找两个正序数组的中位数
    double findMedianSortedArrays(vector<int>& A, vector<int>& B) {
        // Ensure A is the smaller array
        if (A.size() > B.size()) {
            return findMedianSortedArrays(B, A);
        }

        int m = A.size(), n = B.size();
        int left = 0, right = m;
        int k = (m + n + 1) / 2;  // Left half elements count

        while (left <= right) {
            int i = left + (right - left) / 2;  // mid point for A
            int j = k - i;  // corresponding index in B

            if (i < m && B[j-1] > A[i]) {
                // i is too small, need to increase it
                left = i + 1;
            } else if (i > 0 && A[i-1] > B[j]) {
                // i is too large, need to decrease it
                right = i - 1;
            } else {
                // i is perfect
                int maxLeft = 0;
                if (i == 0) maxLeft = B[j-1];
                else if (j == 0) maxLeft = A[i-1];
                else maxLeft = max(A[i-1], B[j-1]);

                if ((m + n) % 2 == 1) return maxLeft;  // Odd length, return the max of left side

                int minRight = 0;
                if (i == m) minRight = B[j];
                else if (j == n) minRight = A[i];
                else minRight = min(A[i], B[j]);

                return (maxLeft + minRight) / 2.0;  // Even length, return the average of middle two
            }
        }
        return 0.0;  // Error case
    }

// 图论
public:
    // 200.岛屿数量
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        int count = 0;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(!visited[i][j] && grid[i][j] == '1') {
                    count++;
                    bfs(grid, visited, i, j);
                }
            }
        }
        return count;
    }

    int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1};
    void bfs(const vector<vector<char>>& grid, vector<vector<bool>>& visited, int x, int y) {
        queue<pair<int, int>> que;
        que.push({x, y});
        visited[x][y] = true;
        while(!que.empty()) {
            pair<int, int> cur = que.front();
            que.pop();
            int curx = cur.first;
            int cury = cur.second;
            for(int i = 0; i < 4; i++) {
                int nextx = curx + dir[i][0];
                int nexty = cury + dir[i][1];
                if(nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) {
                    continue;
                }
                if(!visited[nextx][nexty] && grid[nextx][nexty] == '1') {
                    bfs(grid, visited, nextx, nexty);
                    visited[nextx][nexty] = true;
                }
            }
        }
    }

    // 994.腐烂的橘子
    int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1};
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int res = 0;
        int cnt = 0;
        queue<pair<int, int>> q;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == 2) {
                    q.push({i, j});
                }
                if(grid[i][j] == 1) {
                    cnt++;
                }
            }
        }
        while(!q.empty()) {
            int span = q.size();
            for(int i = 0; i < span; ++i) {
                pair<int, int> cur = q.front();
                q.pop();
                for(int j = 0; j < 4; j++) {
                    int nextx = cur.first + dir[j][0];
                    int nexty = cur.second + dir[j][1];
                    if(nextx < 0 || nextx >= m || nexty < 0 || nexty >= n) {
                        continue;
                    }
                    if(grid[nextx][nexty] == 1) {
                        grid[nextx][nexty] = 2;
                        q.push({nextx, nexty});
                        cnt--;
                    }
                }
            }
            if(!q.empty()) {
                res++;
            }
        }
        if(cnt > 0) {
            return -1;
        }
        return res;
    }
};