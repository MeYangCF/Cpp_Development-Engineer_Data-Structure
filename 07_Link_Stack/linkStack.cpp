/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2024 24-12-11 下午2:58
@description:
*/

#include <iostream>
using namespace std;

//链式栈
class LinkStack
{
public:
    LinkStack(): size_(0)
    {
        head_ = new Node;
    }
    ~LinkStack()
    {
        Node* p = head_;
        while (p != nullptr)
        {
            head_ = head_->next_;
            delete p;
            p = head_;
        }
    }

public:
    // 入栈 O(1)   把链表头节点后面，第一个有效节点的位置，当作栈顶位置
    void push(int val)
    {
        // head_ -> 1
        // head_ -> 2 -> 1
        Node* node = new Node(val);
        node->next_ = head_->next_;
        head_->next_ = node;
        size_++;
    }
    // 出栈 O(1)
    void pop()
    {
        if (head_->next_ == nullptr)
            throw "stack is empty!";
        Node* p = head_->next_;
        head_->next_ = p->next_;
        delete p;
        size_--;
    }
    // 获取栈顶元素
    int top() const
    {
        if (head_->next_ == nullptr)
            throw "stack is empty!";
        return head_->next_->data_;
    }
    // 判空
    bool empty() const
    {
        return head_->next_ == nullptr;
    }
    // 返回栈元素个数   遍历一遍链表，记录节点个数O(n)    想达到O(1)
    int size() const
    {
        return size_;
    }

private:
    struct Node
    {
        Node(int data = 0) : data_(data), next_(nullptr) {}
        int data_;
        Node* next_;
    };

    Node* head_;
    int size_;
};

int main(){
    int arr[] = { 12,4,56,7,89,31,53,75 };
    LinkStack s;

    for (int v : arr)
    {
        s.push(v);
    }

    cout << s.size() << endl;

    while (!s.empty())
    {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;

    cout << s.size() << endl;

    return 0;
}