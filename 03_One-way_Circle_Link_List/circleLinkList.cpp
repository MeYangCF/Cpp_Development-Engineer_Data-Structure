/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2024 24-12-9 下午9:08
@description:
*/

#include <iostream>
using namespace std;

// 单向循环链表
class CircleLink
{
public:
    CircleLink(){
        head_ = new Node();
        tail_ = head_;
        head_->next_ = head_;
    }
    ~CircleLink(){
        Node* p = head_->next_;

        while (p != head_){
            head_->next_ = p->next_;
            delete p;
            p = head_->next_;
        }

        delete head_;
    }

public:
    void InsertTail(int val){
        Node* node = new Node(val);
        node->next_ = tail_->next_;
        tail_->next_ = node;
        tail_ = node;
    }

    void InsertHead(int val){
        Node* node = new Node(val);
        node->next_ = head_->next_;
        head_->next_ = node;

        if (node->next_ == head_)
            tail_ = node;
    }

    void Remove(int val){
        Node* q = head_;
        Node* p = head_->next_;

        while (p != head_){
            if (p->data_ == val){
                q->next_ = p->next_;
                delete p;

                if (q->next_ == head_){
                    tail_ = q;
                }

                return;
            }else{
                q = p;
                p = p->next_;
            }
        }
    }

    bool Find(int val) const{
        Node* p = head_->next_;

        while (p != head_){
            if (p->data_ == val)
                return true;
        }

        return false;
    }

    void Show() const{
        Node* p = head_->next_;

        while (p != head_){
            cout << p->data_ << " ";
            p = p->next_;
        }

        cout << endl;
    }

private:
    struct Node{
        Node(int data = 0)
            : data_(data)
            , next_(nullptr) {}
        int data_;
        Node* next_;
    };

    Node* head_; // 指向头节点
    Node* tail_; // 指向末尾节点
};

int main(){

}