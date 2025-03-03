/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-03-03 обнГ1:35
@description:
*/
#include <iostream>
using namespace std;

class linkedQueue {
public:
    linkedQueue() {
        head_ = new Node();
        head_->next_ = head_;
        head_->pre_ = head_;
    }

    ~linkedQueue() {
        Node *p = head_->next_;
        while (p != head_) {
            head_->next_ = p->next_;
            p->next_->pre_ = head_;
            delete p;
            p = head_->next_;
        }
        delete head_;
        head_ = nullptr;
    }

public:
    void push(int val) {
        Node *node = new Node(val);
        node->next_ = head_;
        node->pre_ = head_->pre_;
        head_->pre_->next_ = node;
        head_->pre_ = node;
    }

    void pop() {
        Node *p = head_->next_;
        head_->next_ = p->next_;
        p->next_->pre_ = head_;
        delete p;
    }

    int front() const {
        if (empty()) {
            throw "queue is empty";
        }
        return head_->next_->data_;
    }

    int back() const {
        if (empty()) {
            throw "queue is empty";
        }
        return head_->pre_->data_;
    }

    bool empty() {
        return head_->next_ == head_;
    }

private:
    struct Node {
        Node(int data = 0)
            : data_(data)
              , next_(nullptr)
              , pre_(nullptr) {
        }

        int data_;
        Node *next_;
        Node *pre_;
    };

    Node *head_;
};
