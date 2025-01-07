/*
@autor: Yang ChengFeng
@email: meyangcf@163.com
@date: 25-1-7 ÉÏÎç9:39
@description: 
*/
#include <iostream>
#include <set>
using namespace std;

template<typename T>
class RBTree {
public:
    RBTree() :root_(nullptr){}

    void insert(const T& val) {
        if (root_ == nullptr) {
            root_ = new Node(val);
            return;
        }

        Node* parent = nullptr;
        Node* cur = root_;

        while (cur != nullptr) {
            if (cur->data_ > val) {
                parent = cur;
                cur = cur->left_;
            } else if (cur->data_ > val) {
                parent = cur;
                cur = cur->right_
            } else {
                return;
            }
        }

        Node* node = new Node(val, parent, nullptr, nullptr, RED);

        if (parent->data_ > val)
            parent->left_ = node;
        else
            parent->right_ = node;

        if (RED == color(parent)) {
            fixAfterInsert(node);
        }

    }

    void remove(const T& val) {

    }
private:
    enum Color {
        BLACK,
        RED
    };

    struct Node {
        Node(T data = T(), Node* parent = nullptr,
            Node* left = nullptr, Node* right = nullptr,
            Color color = BLACK)
            : data_(data)
            , left_(left)
            , right_(right)
            , parent_(parent)
            , color_(color) {}
        T data_;
        Node* left_;
        Node* right_;
        Node* parent_;
        Color color_;
    };

    Node* root_;

    Color color(Node* node){
        return node == nullptr ? BLACK : node->color_;
    }

    void setColor(Node* node, Color color){
        node->color_ = color;
    }

    Node* left(Node* node){
        return node->left_;
    }

    Node* right(Node* node){
        return node->right_;
    }

    Node* parent(Node* node){
        return node->parent_;
    }

    void leftRotate(Node* node) {
        Node* child = node->right_;
        child->parent_ = node->parent_;

        if (node->parent_ == nullptr)
            root_ = child;
        else {
            if (node->parent_->left_ == node)
                node->parent_->left_ = child;
            else
                node->parent_->right_ = child;
        }

        node->right_ = child->left_;

        if (child->left_ != nullptr)
            child->left_->parent_ = node;

        child->left_ = node;
        node->parent_ = child;
    }

    void rightRotate(Node* node) {
        Node* child = node->left_;
        child->parent_ = node->parent_;

        if (node->parent_ == nullptr)
            root_ = child;
        else {
            if (node->parent_->left_ == node)
                node->parent_->left_ = child;
            else
                node->parent_->right_ = child;
        }

        node->left_ = child->right_;

        if (child->right_ != nullptr)
            child->right_->parent_ = node;

        child->right_ = node;
        node->parent_ = child;
    }

    void fixAfterInsert(Node* node) {
        while (color(parent(node) == RED)) {
            if (left(parent(parent(node))) == parent(node)) {
                Node* uncle = right(parent(parent(node)));

                if (RED == color(uncle)) {
                    setColor(parent(node), BLACK);
                    setColor(uncle, BLACK);
                    setColor(parent(parent(node)), RED);
                    node = parent(parent(node));
                } else {
                    if (right(parent(node)) == node) {
                        node = parent(node);
                        leftRotate(node);
                    }

                    setColor(parent(node), BLACK);
                    setColor(parent(parent(node)), RED);
                    rightRotate(parent(parent(node)));
                    break;
                }
            } else {
                Node* uncle = left(parent(parent(node)));

                if (RED == color(uncle)) {
                    setColor(parent(node), BLACK);
                    setColor(uncle, BLACK);
                    setColor(parent(parent(node)), RED);
                    node = parent(parent(node));
                } else {
                    if (left(parent(node)) == node) {
                        node = parent(node);
                        rightRotate(node);
                    }

                    setColor(parent(node), BLACK);
                    setColor(parent(parent(node)), RED);
                    leftRotate(parent(parent(node)));
                    break;
                }
            }
        }

        setColor(root_, BLACK);
    }

    void fixAfterRemove(Node* node) {

    }
};

int main() {

}