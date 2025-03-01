/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-03-01 обнГ8:15
@description:
*/
#include <iostream>
using namespace std;

struct Node {
    Node(int data=0)
        : data_(data)
        , next_(nullptr)
        , pre_(nullptr){}
    int data_;
    Node* next_;
    Node* pre_;
};

class DoubleCircleLink {
public:
    DoubleCircleLink() {
        head_ = new Node();
        head_->next_ = head_;
        head_->pre_ = head_;
    }

    ~DoubleCircleLink() {
        Node* p = head_->next_;
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
    void InsertHead(int val) {
        Node* node = new Node(val);
        node->next_ = head_->next_;
        node->pre_ = head_;
        head_->next_->pre_ = node;
        head_->next_ = node;
    }

    void InsertTail(int val) {
        Node* p = head_->pre_;
        Node* node = new Node(val);
        node->pre_ = p;
        p->next_ = node;
        node->next_ = head_;
        head_->pre_ = node;
    }

    void Remove(int val) {
        Node* p = head_->next_;
        while (p != head_) {
            if (p->data_ == val) {
                p->pre_->next_ = p->next_;
                p->next_->pre_ = p->pre_;
                delete p;
                return;
            }
            else {
                p = p->next_;
            }
        }
    }

    bool Find(int val) {
        Node* p = head_->next_;
        while (p != head_) {
            if (p->data_ == val) {
                return true;
            }
            else {
                p = p->next_;
            }
        }
        return false;
    }

    void Show(){
        Node* p = head_->next_;
        while (p != head_){
            cout << p->data_ << " ";
            p = p->next_;
        }
        cout << endl;
    }

private:
    Node* head_;
};