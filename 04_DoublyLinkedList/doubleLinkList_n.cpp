/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-03-01 обнГ8:03
@description:
*/

# include <iostream>
#include <Windows.h>
using namespace std;

struct Node {
    Node(int data = 0)
        : data_(data)
        , next_(nullptr)
        , pre_(nullptr) {}
    int data_;
    Node* next_;
    Node* pre_;
};

class DoubleLink {
public:
    DoubleLink() {
        head_ = new Node();
    }

    ~DoubleLink() {
        Node* p = head_;
        while (p != head_) {
            head_ = head_->next_;
            delete p;
            p = head_;
        }
    }

public:
    void InsertHead(int val) {
        Node* node = new Node(val);
        node->next_ = head_->next_;
        node->pre_ = head_;
        if (head_->next_ != nullptr) {
            head_->next_->pre_ = node;
        }
        head_->next_ = node;
    }

    void InsertTail(int val) {
        Node* p = head_;
        while (p->next_ != nullptr) {
            p = p->next_;
        }
        Node* node = new Node(val);
        node->pre_ = p;
        p->next_ = node;
    }

    void Remove(int val) {
        Node* p = head_->next_;
        while (p != nullptr) {
            if (p->data_ == val) {
                p->pre_->next_ = p->next_;
                if (p->next_ != nullptr) {
                    p->next_->pre_ = p->next_;
                }
                delete p;
                return;
            }
            else {
                p = p->next_;
            }
        }
    }

    bool Find(int val){
        Node* p = head_->next_;
        while (p != nullptr){
            if (p->data_ == val)
                return true;
            else
                p = p->next_;
        }
        return false;
    }

    void Show(){
        Node* p = head_->next_;
        while (p != nullptr){
            cout << p->data_ << " ";
            p = p->next_;
        }
        cout << endl;
    }

private:
    Node* head_;
};
