/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-03-10 ÏÂÎç9:05
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
class BSTree {
public:
    BSTree(Comp comp = Comp())
        : root_(nullptr)
        , comp_(comp) {}

    ~BSTree() {
        if (root_ != nullptr) {
            queue<Node*> s;
            s.push(root_);
            while (!s.empty()) {
                Node* front = s.front();
                s.pop();
                if (front->left_ != nullptr) {
                    s.push(front->left_);
                }
                if (front->right_ != nullptr) {
                    s.push(front->right_);
                }
                delete front;
            }
        }
    }

    void n_insert(const T& val) {
        if (root_ == nullptr) {
            root_ = new Node(val);
            return;
        }
        Node* parent = nullptr;
        Node* cur = root_;
        while (cur != nullptr) {
            if (cur->data_ == val) {
                return;
            }
            else if (comp_(cur->data_, val)) {
                parent = cur;
                cur = cur->right_;
            }
            else {
                parent = cur;
                cur = cur->left_;
            }
        }
        if (comp_(val, parent->data_)) {
            parent->left_ = new Node(val);
        }
        else {
            parent->right_ = new Node(val);
        }
    }

    void insert(const T& val) {
        root_ = insert(root_, val);
    }

    void n_remove(const T& val) {
        if (root_ == nullptr) {
            return;
        }
        Node* parent = nullptr;
        Node* cur = root_;
        while (cur != nullptr) {
            if (cur->data_ == val) {
                break;
            }
            else if (comp_(cur->data_, val)) {
                parent = cur;
                cur = cur->right_;
            }
            else {
                parent = cur;
                cur = cur->left_;
            }
        }
        if (cur == nullptr) {
            return;
        }
        if (cur->left_ != nullptr && cur->right_ != nullptr) {
            parent = cur;
            Node* pre = cur->left_;
            while (pre->right_ != nullptr) {
                parent = pre;
                pre = pre->right_;
            }
            cur->data_ = pre->data_;
            cur = pre;
        }
        Node* child = cur->left_;
        if (child == nullptr) {
            child = cur->right_;
        }
        if (parent == nullptr) {
            root_ = child;
        }
        else {
            if (parent->left_ == cur) {
                parent->left_ = child;
            }
            else {
                parent->right_ = child;
            }
        }
        delete cur;
    }

    void remove(const T& val) {
        root_ = remove(root_, val);
    }

    bool n_query(const T& val) {
        Node* cur = root_;
        while (cur != nullptr) {
            if (cur->data_ == val) {
                return true;
            }
            else if (comp_(cur->data_, val)) {
                cur = cur->right_;
            }
            else {
                cur = cur->left_;
            }
        }
        return false;
    }

    bool query(const T& val) {
        return nullptr != query(root_, val);
    }

    void n_preOrder() {
        if (root_ == nullptr) {
            return;
        }
        stack<Node*> s;
        s.push(root_);
        while (!s.empty()) {
            Node* top = s.top();
            s.pop();
            cout << top->data_ << " ";
            if (top->right_ != nullptr) {
                s.push(top->right_);
            }
            if (top->left_ != nullptr) {
                s.push(top->left_);
            }
        }
        cout << endl;
    }

    void preOrder() {
        preOrder(root_);
    }

    void n_inorder() {
        if (root_ ==  nullptr) {
            return;
        }
        stack<Node*> s;
        Node* cur = root_;
        while (!s.empty() || cur != nullptr) {
            if (cur != nullptr) {
                s.push(cur);
                cur = cur->left_;
            }
            else {
                Node* top = s.top();
                s.pop();
                cout << top->data_ << " ";
                cur = top->right_;
            }
        }
        cout << endl;
    }

    void inOrder() {
        inOrder(root_);
        cout << endl;
    }

    void n_postOrder() {
        if (root_ == nullptr) {
            return;
        }
        stack<Node*> s1;
        stack<Node*> s2;
        s1.push(root_);
        while (!s1.empty()) {
            Node* top = s1.top();
            s1.pop();
            s2.push(top);
            if (top->left_ != nullptr) {
                s1.push(top->left_);
            }
            if (top->right_ != nullptr) {
                s1.push(top->right_);
            }
        }
        while (!s2.empty()) {
            cout << s2.top()->data_ << " ";
            s2.pop();
        }
        cout << endl;
    }

    void postOrder() {
        postOrder(root_);
        cout << endl;
    }

    void n_levelOrder() {
        if (root_ == nullptr) {
            return;
        }
        queue<Node*> que;
        que.push(root_);
        while (!que.empty()) {
            Node* front = que.front();
            que.pop();
            cout << front->data_ << " ";
            if (front->left_ != nullptr) {
                que.push(front->left_);
            }
            if (front->right_ != nullptr) {
                que.push(front->right_);
            }
        }
        cout << endl;
    }

    void levelOrder() {
        int h = high();
        for (int i = 0; i < h; ++i) {
            levelOrder(root_, i);
        }
        cout << endl;
    }

    int high() {
        return high(root_);
    }

    int number() {
        return number(root_);
    }

    void findValues(vector<T>& vec, int i, int j) {
        findValues(root_, vec, i, j);
    }

    bool isBSTree() {
        Node* pre = nullptr;
        return isBSTree(root_, pre);
    }

    bool isChildTree(BSTree<T, Comp>& child) {
        if (child.root_ == nullptr) {
            return true;
        }
        Node* cur = root_;
        while (cur != nullptr) {
            if (cur->data_ == child.root_->data_) {
                break;
            }
            else if (comp_(cur->data_, child.root_->data_)) {
                cur = cur->right_;
            }
            else {
                cur = cur->left_;
            }
        }
        if (cur == nullptr) {
            return false;
        }
        return isChildTree(cur, child.root_);
    }

    int getLCA(int val1, int val2) {
        Node* node = getLCA(root_, val1, val2);
        if (node == nullptr) {
            throw "no LCA!";
        }
        else {
            return node->data_;
        }
    }

    void mirror01() {
        mirror01(root_);
    }

    bool mirror02() {
        if (root_ == nullptr) {
            return true;
        }
        return mirror02(root_->left_, root_->right_);
    }

    void rebuild(int pre[], int i, int j, int in[], int m, int n) {
        root_ = _rebuild(pre, i, j, in, m, n);
    }

    bool isBalance() {
        int l = 0;
        bool flag = true;
        isBalance02(root_, l, flag);
        return flag;
    }

    int getVal(int k) {
        Node* node = getVal(root_, k);
        if (node == nullptr) {
            string err = "no No.";
            err += k;
            throw err;
        }
        else {
            return node->data_;
        }
    }

public:
    struct Node {
        Node(T data = T())
            : data_(data)
            , left_(nullptr)
            , right_(nullptr) {}
        T data_;
        Node* left_;
        Node* right_;
    };

    Node* insert(Node* node, const T& val) {
        if (node == nullptr) {
            return new Node(val);
        }
        if (node == val) {
            return node;
        }
        else if (comp_(node->data_, val)) {
            node->right_ = insert(node->right_, val);
        }
        else {
            node->left_ = insert(node->left_, val);
        }
        return node;
    }

    Node* remove(Node* node, const T& val) {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->data_ == val) {
            if (node->left_ != nullptr && node->right_ != nullptr) {
                Node* pre = node->left_;
                while (pre->right_ != nullptr) {
                    pre = pre->right_;
                }
                node->data_ = pre->data_;
                node->left_ = remove(node->left_, pre->data_);
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
        else if (comp_(node->data_, val)) {
            node->right = remove(node->right_, val);
        }
        else {
            node->left_ = remove(node->left_, val);
        }
        return node;
    }

    Node* query(Node* node, const T& val) {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->data== val) {
            return node;
        }
        else if (comp_(node->data_, val)) {
            return query(node->right_, val);
        }
        else {
            return query(node->left_, val);
        }
    }

    void preOrder(Node* node) {
        if (node != nullptr) {
            cout << node->data_ << " ";
            preOrder(node->left_);
            preOrder(node->right_);
        }
    }

    void inOrder(Node* node)
    {
        if (node != nullptr) {
            inOrder(node->left_);
            cout << node->data_ << " ";
            inOrder(node->right_);
        }
    }

    void postOrder(Node* node) {
        if (node != nullptr) {
            postOrder(node->left_);
            postOrder(node->right_);
            cout << node->data_ << " ";
        }
    }

    void levelOrder(Node* node, int i) {
        if (node == nullptr) {
            return;
        }
        if (i == 0) {
            cout << node->data_ << " ";
        }
        levelOrder(node->left_, i - 1);
        levelOrder(node->right_, i - 1);
    }

    int high(Node* node) {
        if (root_ == nullptr) {
            return 0;
        }
        int left = high(node->left_);
        int right = high(node->right_);
        return left > right ? left + 1 : right + 1;
    }

    int number(Node* node) {
        if (node == nullptr) {
            return  0;
        }
        int left = number(node->left_);
        int right = number(node->right_);
        return left + right + 1;
    }

    void findValues(Node* node, vector<T>& vec, int i, int j) {
        if (node != nullptr) {
            if (node->data_ > i) {
                findValues(node->left_, vec, i, j);
            }
            if (node->data_ >= i && node->data_ <= j) {
                vec.push_back(node->data_);
            }
            if (node->data_ < j) {
                findValues(node->right_, vec, i, j);
            }
        }
    }

    bool isBSTree(Node* node, Node*& pre) {
        if (node == nullptr) {
            return true;
        }
        if (!isBSTree(node->left_, pre)) {
            return false;
        }
        if (pre != nullptr) {
            if (comp_(node->data_, pre->data_)) {
                return false;
            }
        }
        pre = node;
        return isBSTree(node->right_, pre);
    }

    bool isChildTree(Node* father, Node* child) {
        if (father == nullptr && child == nullptr) {
            return true;
        }

        if (father == nullptr) {
            return false;
        }
        if (child == nullptr) {
            return true;
        }
        if (father->data_ != child->data_) {
            return false;
        }

        return isChildTree(father->left_, child->left_)
            && isChildTree(father->right_, child->right_);
    }

    Node* getLCA(Node* node, int val1, int val2) {
        if (node == nullptr) {
            return nullptr;
        }
        if (comp_(node->data_, val1) && comp_(node->data_, val2)) {
            return getLCA(node->right_, val1, val2);
        }
        else if (comp_(val1, node->data_) && comp_(val2, node->data_)) {
            return getLCA(node->left_, val1, val2);
        }
        else {
            return node;
        }
    }

    void mirror01(Node* node) {
        if (node == nullptr)
            return;
        Node* tmp = node->left_;
        node->left_ = node->right_;
        node->right_ = tmp;
        mirror01(node->left_);
        mirror01(node->right_);
    }

    bool mirror02(Node* node1, Node* node2) {
        if (node1 == nullptr && node2 == nullptr) {
            return true;
        }
        if (node1 == nullptr || node2 == nullptr) {
            return false;
        }
        if (node1->data_ != node2->data_) {
            return false;
        }
        return mirror02(node1->left_, node2->right_)
            && mirror02(node1->right_, node2->left_);
    }

    Node* _rebuild(int pre[], int i, int j, int in[], int m, int n) {
        if (i > j || m > n) {
            return nullptr;
        }
        Node* node = new Node(pre[i]);
        for (int k = m; k <= n; ++k) {
            if (pre[i] == in[k]) {
                node->left_ = _rebuild(pre, i + 1, i + (k - m), in, m, k - 1); // L
                node->right_ = _rebuild(pre, i + (k - m) + 1, j, in, k + 1, n); // R
                return node;
            }
        }
        return node;
    }

    bool isBalance(Node* node)
    {
        if (node == nullptr) {
            return true;
        }
        if (!isBalance(node->left_)) {
            return false;
        }
        if (!isBalance(node->right_)) {
            return false;
        }
        int left = high(node->left_);
        int right = high(node->right_);
        return abs(left - right) <= 1;
    }

    int isBalance02(Node* node, int l, bool& flag)
    {
        if (node == nullptr) {
            return l;
        }
        int left = isBalance02(node->left_, l + 1, flag);
        if (!flag) {
            return left;
        }
        int right = isBalance02(node->right_, l + 1, flag);
        if (!flag) {
            return right;
        }
        if (abs(left - right) > 1) {
            flag = false;
        }
        return max(left, right);
    }

    int i = 1;
    Node* getVal(Node* node, int k) {
        if (node == nullptr) {
            return nullptr;
        }

        Node* left = getVal(node->right_, k);
        if (left != nullptr)
            return left;
        if (i++ == k) {
            return node;
        }
        return getVal(node->left_, k);
    }

    Node* root_;
    Comp comp_;
};