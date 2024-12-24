/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2024 24-12-10 下午5:22
@description:
*/

#include <iostream>
using namespace std;

struct Node{
    Node(int data=0)
            : data_(data)
            , next_(nullptr)
            , pre_(nullptr){}
    int data_;
    Node* next_;
    Node* pre_;
};

class DoubleLink{
public:
    DoubleLink(){
        head_ = new Node();
    }
    ~DoubleLink(){
        Node* p = head_;

        while (p != nullptr){
            head_ = head_->next_;
            delete p;
            p = head_;
        }
    }

public:
    void InsertHead(int val){
        Node* node = new Node(val);
        node->next_ = head_->next_;
        node->pre_ = head_;

        if (head_->next_ != nullptr)
            head_->next_->pre_ = node;

        head_->next_ = node;
    }

    void InsertTail(int val){
        Node* p = head_;

        while (p->next_ != nullptr)
            p = p->next_;

        Node* node = new Node(val);
        node->pre_ = p;
        p->next_ = node;
    }

    void Remove(int val){
        Node* p = head_->next_;

        while (p != nullptr){
            if (p->data_ == val){
                p->pre_->next_ = p->next_;

                if (p->next_ != nullptr)
                    p->next_->pre_ = p->pre_;

                delete p;
                //p = next;
                return;
            }else
                p = p->next_;
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

int main()
{
    DoubleLink dlink;

    dlink.InsertHead(100);

    dlink.InsertTail(20);
    dlink.InsertTail(12);
    dlink.InsertTail(78);
    dlink.InsertTail(32);
    dlink.InsertTail(7);
    dlink.InsertTail(90);
    dlink.Show();

    dlink.InsertHead(200);
    dlink.Show();

    dlink.Remove(200);
    dlink.Show();

    dlink.Remove(90);
    dlink.Show();

    dlink.Remove(78);
    dlink.Show();
}