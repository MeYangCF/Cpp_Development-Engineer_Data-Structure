/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2024 24-12-6 ����10:03
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
        //��head_��ʼ��ָ��ͷ�ڵ�
        head_ = new Node();
    }
    ~Clink(){
        //�ڵ���ͷ�
        Node* p = head_ ;
        while (p != nullptr){
            head_ = head_->next_;
            delete p;
            p = head_;
        }
        head_ = nullptr;
    }
    //����β�巨o(n)
    void InsertTail(int val){
        //���ҵ���ǰ������ĩβ�ڵ�
        Node* p = head_;
        while(p->next_ != nullptr)
            p = p->next_;
        //�����½ڵ�
        Node* node = new Node(val);

        p->next_ = node;
    }
    //����ͷ�巨o(1)
    void InsertHead(int val){
        Node* node = new Node(val);
        node->next_ = head_->next_;
        head_->next_ = node;
    }
    //�����ڵ��ɾ��
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
    //ɾ����������ڵ�
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
    //����
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
    //������ӡ
    void Show(){
        Node* p = head_->next_;
        while(p != nullptr){
            cout << p->data_ << " ";
            p = p->next_;
        }
        cout << endl;
    }
private:
    Node* head_;//ָ��������ͷ�ڵ�

    friend void ReverseLink(Clink& link);
    friend bool GetLaskKNode(Clink& link, int k, int& val);
    friend void MergeLink(Clink& link1, Clink& link2);
};

//����1������������
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
    if (p == nullptr){
        return;
    }

    head->next_ = nullptr;

    while (p != nullptr){
        Node* q = p->next_;

        // pָ��ָ��Ľڵ����ͷ��
        p->next_ = head->next_;
        head->next_ = p;

        p = q;
    }

}

//ListNode* reverseList(ListNode* head) {
//    if(head == nullptr)
//        return nullptr;
//    ListNode* pre = nullptr;
//    ListNode* p = head;
//    ListNode* tmp;
//    while (p != nullptr){
//        tmp = p->next;
//        p->next = pre;
//        pre = p;
//        p = tmp;
//    }
//    return pre;
//}

//����2��������k���ڵ��ֵ
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

    // pre��ͷ�ڵ㣬p��������k���ڵ�
    while (p != nullptr)
    {
        pre = pre->next_;
        p = p->next_;
    }

    val = pre->data_;
    return true;
}

//����3���ϲ���������ĵ�����
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

// �жϵ������Ƿ���ڻ������ڷ��ػ�����ڽڵ�
bool IsLinkHasCircle(Node *head, int& val){
    Node *fast = head;
    Node *slow = head;
    while (fast != nullptr && fast->next_ != nullptr){
        slow = slow->next_;
        fast = fast->next_->next_;
        if(fast == slow){
            //����ָ���ٴ��������������ڻ�
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

// �ж������������Ƿ��ཻ������ཻ�������ཻ�ڵ��ֵ
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
        // ��һ��������
        int offset = cnt1 - cnt2;
        while (offset-- > 0)
        {
            p = p->next_;
        }
    }
    else
    {
        // �ڶ���������
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

//ɾ������������N���ڵ�
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

//��ת����
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

// �Ƴ�����Ԫ��
//    ListNode* removeElements(ListNode* head, int val) {
//        ListNode* dummyNode = new ListNode();
//        dummyNode->next = head;
//        ListNode* p = head;
//        ListNode* pre = dummyNode;
//        while (p != nullptr){
//            if(p->val == val){
//                pre->next = p->next;
//                p = p->next;
//            }else{
//                p = p->next;
//                pre = pre->next;
//            }
//        }
//       return dummyNode->next;
//    }


//�������
//class MyLinkedList {
//public:
//    MyLinkedList() {
//        dummyNode = new LinkedNode(0);
//        size_ = 0;
//    }
//
//    int get(int index) {
//        if(index < 0 || index > (size_ - 1))
//            return -1;
//        LinkedNode* cur = dummyNode->next;
//        while(index--){
//            cur = cur->next;
//        }
//        return cur->val;
//    }
//
//    void addAtHead(int val) {
//        LinkedNode* newNode =new LinkedNode(val);
//        newNode->next = dummyNode->next;
//        dummyNode->next = newNode;
//        size_++;
//    }
//
//    void addAtTail(int val) {
//        LinkedNode* newNode =new LinkedNode(val);
//        LinkedNode* cur = dummyNode;
//        while (cur->next != nullptr){
//            cur = cur->next;
//        }
//        newNode->next = cur->next;
//        cur->next = newNode;
//        size_++;
//    }
//
//    void addAtIndex(int index, int val) {
//        if(index > size_) return;
//        LinkedNode* newNode =new LinkedNode(val);
//        LinkedNode* cur = dummyNode;
//        while (index--){
//            cur = cur->next;
//        }
//        newNode->next = cur->next;
//        cur->next = newNode;
//        size_++;
//    }
//
//    void deleteAtIndex(int index) {
//        if(index < 0 || index > (size_ - 1))
//            return;
//        LinkedNode* cur = dummyNode;
//        while (index--){
//            cur = cur->next;
//        }
//        LinkedNode* tmp = cur->next;
//        cur->next = cur->next->next;
//        delete tmp;
//        tmp = nullptr;
//        size_--;
//    }
//    struct LinkedNode {
//        int val;
//        LinkedNode* next;
//        LinkedNode(int val):val(val), next(nullptr){}
//    };
//
//private:
//    LinkedNode* dummyNode;
//    int size_;
//};

// �������������еĽڵ�
//    ListNode* swapPairs(ListNode* head) {
//        ListNode* dummyNode = new ListNode(0);
//        dummyNode->next = head;
//
//        if(dummyNode->next == nullptr)
//            return head;
//        ListNode* p = dummyNode;
//        ListNode* q = dummyNode->next;
//        while(q != nullptr && q->next != nullptr){
//            p->next = q->next;
//            q->next = q->next->next;
//            p->next->next = q;
//
//            p = q;
//            q = q->next;
//        }
//        return dummyNode->next;
//    }
int main(){

    return  0;
}