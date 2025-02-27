/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-02-27 обнГ8:36
@description:
*/
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