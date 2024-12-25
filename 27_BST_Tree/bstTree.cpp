/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2024 24-12-25 обнГ2:27
@description:
*/
#include <iostream>
#include <functional>
#include <stack>
#include <queue>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

template<typename T, typename Comp = less<T>>
class BSTree{
public:
    BSTree(Comp comp = Comp())
        : root_(nullptr)
        , comp_(comp){}
    ~BSTree(){

    }

    void n_insert(const T& val){
        if(root_ == nullptr){
            root_ = new Node(val);
            return;
        }

        Node* parent = nullptr;
        Node* cur = root_;

        while(cur != nullptr){
            if(cur->data_ == val)
                return;
            else if(comp_(cur->data_, val)){
                parent = cur;
                cur = cur->right_;
            }else{
                parent = cur;
                cur = cur->left_;
            }
        }

        if(comp_(val, parent->data_))
            parent->left_ = new Node(val);
        else
            parent->right_ = new Node(val);
    }

    void n_remove(const T& val){
        if(root_ == nullptr)
            return;

        Node* parent = nullptr;
        Node* cur = root_;

        while (cur != nullptr){
            if(cur->data_ == val)
                break;
            else if(comp_(cur->data_, val)){
                parent = cur;
                cur = cur->right_;
            }else{
                parent = cur;
                cur = cur->left_;
            }
        }

        if(cur == nullptr)
            return;

        if(cur->left_ != nullptr && cur->right_ != nullptr){
            parent = cur;
            Node* pre = cur->left_;

            while (pre->right_ != nullptr){
                parent = pre;
                pre = pre->right_;
            }

            cur->data_ = pre->data_;
            cur = pre;
        }

        Node* child = cur->left_;

        if(child == nullptr)
            child = cur ->right_;

        if(parent == nullptr)
            root_ = child;
        else{
            if(parent->left_ == cur)
                parent->left_ = child;
            else
                parent->right_ = child;
        }

        delete cur;
    }

    bool n_query(const T& val){
        Node* cur = root_;

        while(cur != nullptr){
            if(cur->data_ == val)
                return true;
            else if(comp_(cur->data_, val))
                cur = cur->right_;
            else
                cur = cur->left_;
        }

        return false;
    }

public:
    struct Node{
        Node(T data = T())
            : data_(data)
            , left_(nullptr)
            , right_(nullptr){}
        T data_;
        Node* left_;
        Node* right_;
    };

    Node* root_;
    Comp comp_;
};
int main(){

    return 0;
}