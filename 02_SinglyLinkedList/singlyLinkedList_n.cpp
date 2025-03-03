/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-02-27 下午8:36
@description:
*/
/*
# include <iostream>
#include <mutex>
#include <stdlib.h>
using namespace std;

class Clink {
public:
    Clink() {
        head_ = new Node();
    }

    ~Clink() {
        Node* p = head_;
        while (p != nullptr) {
            head_ = head_->next_;
            delete p;
            p = head_;
        }
        head_ = nullptr;
    }

public:
    void InsertTail(int val) {
        Node* p = head_;
        while (p->next_ != nullptr) {
            p = p->next_;
        }

        Node* node = new Node(val);
        p->next_ = node;
    }

    void InsertHead(int val) {
        Node* node = new Node(val);
        node->next_ = head_->next_;
        head_->next_ = node;
    }

    void Remove(int val) {
        Node* pre = head_;
        Node* p = head_->next_;
        while (p != nullptr) {
            if (p->data_ == val) {
                pre->next_ = p->next_;
                delete p;
                return;
            }
            else {
                pre = p;
                p = p->next_;
            }
        }
    }

    void RemoveAll(int val) {
        Node* pre = head_;
        Node* p = head_->next_;
        while (p != nullptr) {
            if (p->data_ == val) {
                pre->next_ = p->next_;
                delete p;
                p = pre->next_;
            }
            else {
                pre = p;
                p = p->next_;
            }
        }
    }

    bool Find(int val) {
        Node* p = head_->next_;
        while (p != nullptr) {
            if (p->data_ = val) {
                return true;
            }
            else {
                p = p->next_;
            }
        }
        return false;
    }

    void Show() {
        Node* p = head_->next_;
        while (p != nullptr) {
            cout << p->data_ << " ";
            p = p->next_;
        }
        cout << endl;
    }

private:
    struct Node {
        Node(int data = 0)
            : data_(data)
            , next_(nullptr){}
        int data_;
        Node* next_;
    };

private:
    Node* head_;
};
*/

# include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    // 203. 移除链表元素
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* dummyNode = new ListNode();
        dummyNode->next = head;
        ListNode* pre = dummyNode;
        ListNode* p = head;
        while (p != nullptr) {
            if (p->val == val) {
                pre->next = p->next;
                p = p->next;
            }
            else {
                p = p->next;
                pre = pre->next;
            }
        }
        return dummyNode->next;
    }

public:
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

public:
    // 24. 两两交换链表中的节点
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

public:
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

public:
    // 160.链表相交
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int countA = 0;
        int countB = 0;
        ListNode* p = headA;
        while (p != nullptr) {
            p = p->next;
            countA++;
        }
        ListNode* q = headB;
        while (q != nullptr) {
            q = q->next;
            countB++;
        }
        p = headA;
        q = headB;
        int n = abs(countA - countB);
        if (countA > countB) {
            for (int i = 0; i < n; i++) {
                p = p->next;
            }
        }
        else {
            for (int i = 0; i < n; i++) {
                q = q->next;
            }
        }
        while (p != q) {
            p = p->next;
            q = q->next;
        }
        return p;
    }

    // 142.环形链表II
    ListNode *detectCycle(ListNode *head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                ListNode* index1 = fast;
                ListNode* index2 = head;
                while (index1 != index2) {
                    index1 = index1->next;
                    index2 = index2->next;
                }
                return index2;
            }
        }
        return nullptr;
    }
};

// 707.设计链表
class MyLinkedList {
public:
    MyLinkedList() {
        head = new Node();
        size = 0;
    }

    int get(int index) {
        if (index < 0 || index > size - 1) {
            return -1;
        }
        Node* cur = head->next;

        while(index--)
            cur = cur->next;

        return cur->val;
    }

    void addAtHead(int val) {
        Node* node = new Node(val);
        node->next = head->next;
        head->next = node;
        size++;
    }

    void addAtTail(int val) {
        Node* p = head;
        while (p->next != nullptr) {
            p = p->next;
        }

        Node* node = new Node(val);
        p->next = node;
        size++;
    }

    void addAtIndex(int index, int val) {
        if (index < 0 || index > size) {
            return;
        }
        Node* p = head;
        while (index--) {
            p = p->next;
        }
        Node* node = new Node(val);
        node->next = p->next;
        p->next = node;
        size++;
    }

    void deleteAtIndex(int index) {
        if (index < 0 || index > size - 1) {
            return;
        }
        Node* p = head;
        while (index--) {
            p = p->next;
        }
        Node* tmp = p->next;
        p->next = tmp->next;
        delete tmp;
        tmp = nullptr;
        size--;
    }

private:
    struct Node {
        Node(int data = 0)
            : val(data)
            , next(nullptr) {}
        int val;
        Node* next;
    };

    Node* head;
    int size;
};