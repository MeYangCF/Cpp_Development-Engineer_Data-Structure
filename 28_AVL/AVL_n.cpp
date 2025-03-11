/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-03-11 обнГ2:07
@description:
*/
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

template<typename T>
class AVLTree {
public:
    AVLTree() :root_(nullptr) {}

    void insert(const T& val) {
        root_ = insert(root_, val);
    }

    void remove(const T& val) {
        root_ = remove(root_, val);
    }

private:
    struct Node {
        Node (T data = T())
            : data_(data)
            , left_(nullptr)
            , right_(nullptr)
            , height_(1) {}
        T data_;
        Node* left_;
        Node* right_;
        int height_;
    };

    int height(Node* node) {
        return node == nullptr ? 0 : node->height_;
    }

    Node* rightRotate(Node* node) {
        Node* child = node->left_;
        node->left_ = child->left_;
        child->right_ = node;
        node->height_ = max(height(node->left_), height(node->right_)) + 1;
        child->height_ = max(height(child->left_), height(child->right_)) + 1;
        return child;
    }

    Node* leftRotate(Node* node) {
        Node* child = node->right_;
        node->right_ = child->left_;
        child->left_ = node;
        node->height_ = max(height(node->left_), height(node->right_)) + 1;
        child->height_ = max(height(child->left_), height(child->right_)) + 1;
        return child;
    }

    Node* leftBalance(Node* node) {
        node->left_ = leftRotate(node->left_);
        return rightRotate(node);
    }

    Node* rightBalance(Node* node) {
        node->right_ = rightRotate(node->right_);
        return leftRotate(node);
    }

    Node* insert(Node* node, const T& val) {
        if (node == nullptr) {
            return new Node(val);
        }

        if (node->data_ > val) {
            node->left_ = insert(node->left_, val);
            if (height(node->left_) - height(node->right_) > 1) {
                if (height(node->left_->left_) >= height(node->left_->right_)) {
                    node = rightRotate(node);
                }
                else {
                    node = leftBalance(node);
                }
            }
        }
        else if (node->data_ < val) {
            node ->right_ = insert(node->right_, val);
            if (height(node->right_->right_) >= height(node->right_->left_)) {
                node = leftRotate(node);
            }
            else {
                node = rightBalance(node);
            }
        }
        else {
            return node;
        }
        node->height_ = max(height(node->left_), height(node->right_)) + 1;
        return node;
    }

    Node* remove(Node* node, const T& val) {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->data_ > val) {
            node->left_ = remove(node->left_, val);
            if (height(node->right) - height(node->left_) > 1) {
                if (height(node->right_->right_) >= height(node->right_->left_)) {
                    node = leftRotate(node);
                }
                else {
                    node = rightBalance(node);
                }
            }
        }
        else if (node->data_ < val) {
            node->right_ = remove(node->right_, val);
            if (height(node->left_) - height(node->right_) > 1) {
                if (height(node->left_->left_) >= height(node->left_->right_)) {
                    node = rightRotate(node);
                }
                else {
                    node = leftBalance(node);
                }
            }
        }
        else {
            if (node->left_ != nullptr && node->right_ != nullptr) {
                if (height(node->left_) >= height(node->right_)) {
                    Node* pre = node->left_;
                    while (pre->right_ != nullptr) {
                        pre = pre->right_;
                    }
                    node->data_ = pre->data_;
                    node->left_ = remove(node->left_, pre->data_);
                }
                else {
                    Node* post = node->right_;
                    while (post->left_ != nullptr) {
                        post = post->left_;
                    }
                    node->data_ = post->data_;
                    node->right_ = remove(node->right_, post->data_);
                }
            }
            else {
                if (node->left_ != nullptr) {
                    Node* left = node->left_;
                    delete node;
                    return left;
                }
                else if (node->right_ != nullptr) {
                    Node* right = node->right_;
                    delete node;
                    return right;
                }
                else {
                    delete node;
                    return nullptr;
                }
            }
        }

        node->height_ = max(height(node->left_), height(node->right_)) + 1;
        return node;
    }
    Node* root_;
};