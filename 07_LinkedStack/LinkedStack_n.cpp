/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-03-03 обнГ12:58
@description:
*/
#include <iostream>
using namespace std;

class LinkedStack {
public:
    LinkedStack()
        : size_(0) {
        head_ = new Node();
    }

    ~LinkedStack() {
        Node* p = head_;
        while (p != nullptr) {
            head_ = p->next;
            delete p;
            p = head_;
        }
    }

public:
    void push(int val) {
        Node* node = new Node(val);
        node->next = head_->next;
        head_->next = node;
        size_++;
    }

    void pop() {
        if (empty()) {
            throw "stack is empty";
        }
        Node* p = head_->next;
        head_->next = p->next;
        delete p;
        size_--;
    }

    int top() const {
        if (empty()) {
            throw "stack is empty";
        }
        return head_->next->data;
    }

    bool empty() const {
        return head_->next == nullptr;
    }

    int size() const {
        return size_;
    }

private:
    struct Node {
        Node(int val = 0)
            : data(val)
            , next(nullptr){}
        int data;
        Node* next;
    };
    Node* head_;
    int size_;
};
