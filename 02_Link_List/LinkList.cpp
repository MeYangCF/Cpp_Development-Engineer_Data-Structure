/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2024 24-12-6 上午10:19
@description:
*/
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

struct Node{
    Node(int data = 0):data_(data), next_(nullptr){}
    int data_;
    Node* next_;
};

class Clink{
public:
    Clink(){
        //给head_初始化指向头节点
        head_ = new Node();
    }
    ~Clink(){
        //节点的释放
        Node* p = head_ ;
        while (p != nullptr){
            head_ = head_->next_;
            delete p;
            p = head_;
        }
        head_ = nullptr;
    }
    //链表尾插法o(n)
    void InsertTail(int val){
        //先找到当前链表的末尾节点
        Node* p = head_;
        while(p->next_ != nullptr)
            p = p->next_;
        //生成新节点
        Node* node = new Node(val);

        p->next_ = node;
    }
    //链表头插法o(1)
    void InsertHead(int val){
        Node* node = new Node(val);
        node->next_ = head_->next_;
        head_->next_ = node;
    }
    //链表节点的删除
    void Remove(int val){
        Node* p = head_->next_;
        Node* q = head_;
        while (p != nullptr){
            if(p->data_ == val){
                q->next_ = p->next_;
                delete p;
                return;
            }
            else{
                q = p;
                p = p->next_;
            }
        }
    }
    //删除多个链表节点
    void RemoveAll(int val){
        Node* p = head_->next_;
        Node* q = head_;
        while (p != nullptr){
            if(p->data_ == val) {
                q->next_ = p->next_;
                delete p;
                p = q->next_;
            }else{
                q = p;
                p = p->next_;
            }
        }
    }
    //搜索
    bool Find(int val){
        Node* p = head_->next_;
        while (p != nullptr){
            if(p->data_ == val)
                return true;
            else
                p = p->next_;
        }
        return false;
    }
    //链表打印
    void Show(){
        Node* p = head_->next_;
        while(p != nullptr){
            cout << p->data_ << " ";
            p = p->next_;
        }
        cout << endl;
    }
private:
    Node* head_;//指向链表的头节点
};

int main(){
    Clink link;
    srand(time(0));
    for (int i = 0; i < 10; i++)
    {
        int val = rand() % 100;
        link.InsertHead(val);
        cout << val << " ";
    }
    cout << endl;

    link.InsertTail(22);
    link.InsertTail(23);
    link.InsertHead(23);
    link.InsertHead(23);

    link.Show();

    link.Remove(22);
    link.Show();

    link.RemoveAll(23);
    link.Show();
    return 0;
}