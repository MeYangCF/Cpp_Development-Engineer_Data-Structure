/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-03-25 下午9:27
@description:
*/

#include <algorithm>
#include <iostream>
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

    }

    // 206.反转链表
    ListNode* reverseList(ListNode* head) {

    }

    // 234.回文链表
    bool isPalindrome(ListNode* head) {

    }

    // 141.环形链表
    bool hasCycle(ListNode *head) {

    }

    // 21.合并两个有序的链表
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {

    }

    // 2.两数相加
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

    }

    // 19.删除链表的倒数第N个节点
    ListNode* removeNthFromEnd(ListNode* head, int n) {

    }

    // 24.两两交换链表中的节点
    ListNode* swapPairs(ListNode* head) {

    }

    // 25.k个一组的翻转链表
    ListNode* reverseKGroup(ListNode* head, int k) {

    }

    // 138.随机链表的复制
    Node* copyRandomList(Node* head) {

    }

    // 148.排序链表
    ListNode* sortList(ListNode* head) {

    }

    // 23.合并k个升序链表
    ListNode* mergeKLists(vector<ListNode*>& lists) {

    }

    // 146.LRU缓存
    class LRUCache {
    public:
        LRUCache(int capacity) {

        }

        int get(int key) {

        }

        void put(int key, int value) {

        }
    };

};