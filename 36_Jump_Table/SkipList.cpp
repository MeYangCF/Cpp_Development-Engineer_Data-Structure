/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-01-10 ионГ10:40
@description:
*/
#include <iostream>
using namespace std;

class SkipList {
public:
    SkipList() {
        head_ = new HeadNode(1);
    }

    ~SkipList() {
        int level = head_->level_;

        for (int i = 0; i < level; i++) {
            Node* cur = head_->next_;

            while (cur != nullptr) {
                Node* tmp = cur->next_;
                delete cur;
                cur = tmp;
            }
            cur = head_;
            head_ = static_cast<HeadNode*>(head_->down_);
            delete cur;
        }
    }

public:
    bool find(int data) {
        Node* pre = head_;
        Node* cur = pre->next_;

        for (;;) {
            if (cur != nullptr) {
                if (cur->data_ < data) {
                    pre = cur;
                    cur = cur->next_;
                    continue;
                } else if (cur->data_ == data) {
                    return true;
                }
            }

            if (pre->down_ == nullptr)
                break;

            pre = pre->down_;
            cur = pre->next_;
        }

        return false;
    }

    void add(int data) {
        if (find(data))
            return;

        int level = getLevel();

        if (level > head_->level_) {
            level = head_->level_ + 1;
            HeadNode* hnode = new HeadNode(level);
            hnode->down_ = head_;
            head_ = hnode;
        }

        Node** nodeList = new Node*[level];
        for (int i = level - 1; i >= 0; i--) {
            nodeList[i] = new Node(data);
            if (i < level - 1)
                nodeList[i]->down_ = nodeList[i + 1];
        }

        Node* head = head_;

        for (int i = head_->level_; i > level; i--)
            head_ = head_->down_;

        Node* pre = head;
        Node* cur = pre->next_;

        for (int i = 0; i < level; i++) {
            while (cur != nullptr && cur->data_ < data) {
                pre = cur;
                cur = cur->next_;
            }

            nodeList[i]->next_ = cur;
            pre->next_ = nodeList[i];
            pre = pre->down_;

            if (pre != nullptr)
                cur = pre->next_;
        }

        delete[] nodeList;
        nodeList = nullptr;
    }

    void remove(int data) {
        Node* pre = head_;
        Node* cur = pre->next_;

        for (;;) {
            if (cur != nullptr) {
                if (cur->data_ < data) {
                    pre = cur;
                    cur = cur->next_;
                    continue;
                } else if (cur->data_ == data) {
                    pre->next_ = cur->next_;
                    delete cur;
                }
            }

            if (pre->down_ == nullptr)
                break;

            pre = pre->down_;

            if (head_->next_ == nullptr) {
                delete head_;
                head_ = static_cast<HeadNode*>(pre);
            }

            cur = pre->next_;
        }
    }

    void show() const{
        Node* head = head_;

        while (head != nullptr){
            Node* cur = head->next_;

            while (cur != nullptr){
                cout << cur->data_ << " ";
                cur = cur->next_;
            }

            cout << endl;
            head = head->down_;
        }

        cout << endl;
    }


private:
    int getLevel() const {
        int level = 1;
        while (rand() % 2 == 1)
            level++;
        return level;
    }

private:
    struct Node {
        Node(int data = int())
            : data_(data)
            , next_(nullptr)
            , down_(nullptr) {}
        int data_;
        Node* next_;
        Node* down_;
    };

    struct HeadNode : public Node {
        HeadNode(int level)
            : level_(level) {}
        int level_;
    };


private:
    HeadNode* head_;
};
int main() {

    return 0;
}