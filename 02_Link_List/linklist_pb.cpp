/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2024 24-12-6 下午10:03
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

    friend void ReverseLink(Clink& link);
    friend bool GetLaskKNode(Clink& link, int k, int& val);
    friend void MergeLink(Clink& link1, Clink& link2);
};

//问题1：单链表逆序
void ReverseLink(Clink &link){
//    Node* p = link.head_->next_;
//    if (p == nullptr)
//    {
//        return;
//    }
//    Node* q;
//    while(p->next_ != nullptr){
//        q = link.head_->next_;
//        link.head_->next_ = p->next_;
//        p->next_ = link.head_->next_->next_;
//        link.head_->next_->next_ = q;
//    }
    Node* head = link.head_;
    Node* p = head->next_;
    if (p == nullptr)
    {
        return;
    }

    head->next_ = nullptr;

    while (p != nullptr)
    {
        Node* q = p->next_;

        // p指针指向的节点进行头插
        p->next_ = head->next_;
        head->next_ = p;

        p = q;
    }

}

//问题2：求倒数第k个节点的值
bool GetLaskKNode(Clink& link, int k, int& val){
    Node* head = link.head_;
    Node* pre = head;
    Node* p = head;

    if (k < 1)
    {
        return false;
    }

    for (int i = 0; i < k; i++)
    {
        p = p->next_;
        if (p == nullptr)
        {
            return false;
        }
    }

    // pre在头节点，p在正数第k个节点
    while (p != nullptr)
    {
        pre = pre->next_;
        p = p->next_;
    }

    val = pre->data_;
    return true;
}

//问题3：合并两个有序的单链表
void MergeLink(Clink& link1, Clink& link2){
    Node* p = link1.head_->next_;
    Node* q = link2.head_->next_;

    Node* last = link1.head_;
    link2.head_->next_ = nullptr;

    while(p != nullptr && q != nullptr){
        if(p->data_ < q->data_){
            last->next_ = p;
            p = p->next_;
            last = last->next_;
        }
        else{
            last->next_ = q;
            q = q-> next_;
            last = last->next_;
        }
    }
    if(p != nullptr)
        last->next_ = p;
    if(q != nullptr)
        last->next_ = q;
}

// 判断单链表是否存在环，存在返回环的入口节点
bool IsLinkHasCircle(Node *head, int& val){
    Node *fast = head;
    Node *slow = head;
    while (fast != nullptr && fast->next_ != nullptr){
        slow = slow->next_;
        fast = fast->next_->next_;
        if(fast == slow){
            //快慢指针再次遇见，链表存在环
            fast = head;
            while (fast != slow){
                slow = slow->next_;
                fast = fast->next_;
            }
            val = slow->data_;
            return true;
        }
    }
    return false;
}

// 判断两个单链表是否相交，如果相交，返回相交节点的值
bool IsLinkHasMerge(Node* head1, Node* head2, int& val){
    int cnt1 = 0, cnt2 = 0;
    Node* p = head1->next_;
    Node* q = head2->next_;

    while (p != nullptr){
        cnt1++;
        p = p->next_;
    }

    while (q != nullptr){
        cnt2++;
        q = q->next_;
    }

    p = head1;
    q = head2;
    if (cnt1 > cnt2)
    {
        // 第一个链表长
        int offset = cnt1 - cnt2;
        while (offset-- > 0)
        {
            p = p->next_;
        }
    }
    else
    {
        // 第二个链表长
        int offset = cnt2 - cnt1;
        while (offset-- > 0)
        {
            q = q->next_;
        }
    }

    while (p != nullptr && q != nullptr)
    {
        if (p == q)
        {
            val = p->data_;
            return true;
        }
        p = p->next_;
        q = q->next_;
    }

    return false;
}

//删除链表倒数第N个节点
Node* removeNthFromEnd(Node* head, int n) {
    Node* dummyHead = new Node(0);
    dummyHead->next_ = head;
    Node* p = dummyHead;
    Node* pre = dummyHead;
    for (int i = 0; i < n; i++){
        p = p->next_;
    }

    p = p->next_;
    while (p != nullptr)
    {
        pre = pre->next_;
        p = p->next_;
    }
    pre->next_ = pre->next_->next_;
    return dummyHead->next_;
}

//旋转链表
Node* rotateRight(Node* head, int k) {
    Node* p = head;
    Node* q = head;

    if(head == nullptr || k == 0){
        return head;
    }

    int number = 0;
    for(Node* m = head; m != nullptr; m = m->next_)
        number++;
    k = k % number;

    for(int i = 0; i < k; i++){
        p = p->next_;
    }

    while (p->next_ != nullptr){
        q = q->next_;
        p = p->next_;
    }

    p->next_ = head;
    head = q->next_;
    q->next_ = nullptr;

    return head;
}
int main(){

    return  0;
}