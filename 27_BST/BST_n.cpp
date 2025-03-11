/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-03-10 下午9:05
@description:
*/
/*
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

    Node* root_;
    Comp comp_;
};
*/
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
using namespace std;

 struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class nextNode {
public:
    int val;
    nextNode* left;
    nextNode* right;
    nextNode* next;

    nextNode() : val(0), left(nullptr), right(nullptr), next(nullptr) {}

    nextNode(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}

    nextNode(int _val, nextNode* _left, nextNode* _right, nextNode* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
s
class Solution {
public:
    // 144.二叉树的前序遍历
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        preOrder(root, res);
        return res;
    }
private:
    void preOrder(TreeNode* node, vector<int>& res) {
        if (node != nullptr) {
            res.push_back(node->val);
            preOrder(node->left, res);
            preOrder(node->right, res);
        }
    }

public:
    // 94.二叉树的中序遍历
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        inOrder(root, res);
        return res;
    }
private:
    void inOrder(TreeNode* node, vector<int>& res) {
        if (node != nullptr) {
            inOrder(node->left, res);
            res.push_back(node->val);
            inOrder(node->right, res);
        }
    }

public:
    // 145.二叉树的后序遍历
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        postOrder(root, res);
        return res;
    }
private:
    void postOrder(TreeNode* node, vector<int>& res) {
        if (node != nullptr) {
            postOrder(node->left, res);
            postOrder(node->right, res);
            res.push_back(node->val);
        }
    }

public:
    // 102.二叉树的层序遍历
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> que;
        if (root != nullptr) {
            que.push(root);
        }
        vector<vector<int>> result;
        while (!que.empty()) {
            int size = que.size();
            vector<int> vec;
            for (int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                vec.push_back(node->val);
                if (node->left != nullptr) {
                    que.push(node->left);
                }
                if (node->right != nullptr) {
                    que.push(node->right);
                }
            }
            result.push_back(vec);
        }
        return result;
    }

public:
    // 107.二叉树的层次遍历 II
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        queue<TreeNode*> que;
        if (root != nullptr) {
            que.push(root);
        }
        vector<vector<int>> result;
        while (!que.empty()) {
            int size = que.size();
            vector<int> vec;
            for (int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                vec.push_back(node->val);
                if (node->left != nullptr) {
                    que.push(node->left);
                }
                if (node->right != nullptr) {
                    que.push(node->right);
                }
            }
            result.push_back(vec);
        }
        reverse(result.begin(), result.end());
        return result;
    }

public:
    // 199.二叉树的右视图
    vector<int> rightSideView(TreeNode* root) {
        queue<TreeNode*> que;
        if (root != nullptr) {
            que.push(root);
        }
        vector<int> result;
        while (!que.empty()) {
            int size = que.size();
            for (int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                if (i == size - 1) {
                    result.push_back(node->val);
                }
                if (node->left != nullptr) {
                    que.push(node->left);
                }
                if (node->right != nullptr) {
                    que.push(node->right);
                }
            }
        }
        return result;
    }

public:
    // 637.二叉树的层平均值
    vector<double> averageOfLevels(TreeNode* root) {
        queue<TreeNode*> que;
        if (root != nullptr) {
            que.push(root);
        }
        vector<double> result;
        while (!que.empty()) {
            int size = que.size();
            double sum = 0;
            for (int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                sum += node->val;
                if (node->left != nullptr) {
                    que.push(node->left);
                }
                if (node->right != nullptr) {
                    que.push(node->right);
                }
            }
            result.push_back(double(sum / size));
        }
        return result;
    }

public:
    // 429.N叉树的层序遍历
    vector<vector<int>> levelOrder(Node* root) {
        queue<Node*> que;
        if (root != nullptr) {
            que.push(root);
        }
        vector<vector<int>> result;
        while (!que.empty()) {
            int size = que.size();
            vector<int> vec;
            for (int i = 0; i < size; i++) {
                Node* node = que.front();
                que.pop();
                vec.push_back(node->val);
                for (int j = 0; j < node->children.size(); j++) {
                    que.push(node->children[j]);
                }
            }
            result.push_back(vec);
        }
        return result;
    }

public:
    // 515.在每个树行中找最大值
    vector<int> largestValues(TreeNode* root) {
        queue<TreeNode*> que;
        if (root != nullptr) {
            que.push(root);
        }
        vector<int> result;
        while (!que.empty()) {
            int size = que.size();
            int max = que.front()->val;
            for (int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                if (node->val > max) {
                    max = node->val;
                }
                if (node->left != nullptr) {
                    que.push(node->left);
                }
                if (node->right != nullptr) {
                    que.push(node->right);
                }
            }
            result.push_back(max);
        }
        return result;
    }

public:
    // 116.填充每个节点的下一个右侧节点指针
    nextNode* connect(nextNode* root) {
        queue<nextNode*> que;
        if (root != nullptr) {
            que.push(root);
        }
        while (!que.empty()) {
            int size = que.size();
            for (int i = 0; i < size; i++) {
                nextNode* prenode = que.front();
                que.pop();
                if (i != size - 1) {
                    nextNode* node = que.front();
                    prenode->next = node;
                }
                else {
                    prenode->next = nullptr;
                }

                if (prenode->left != nullptr) {
                    que.push(prenode->left);
                }
                if (prenode->right != nullptr) {
                    que.push(prenode->right);
                }
            }
        }
        return root;
    }

public:
    // 117.填充每个节点的下一个右侧节点指针II
    nextNode* connect2(nextNode* root) {
        queue<nextNode*> que;
        if (root != nullptr) {
            que.push(root);
        }
        while (!que.empty()) {
            int size = que.size();
            for (int i = 0; i < size; i++) {
                nextNode* prenode = que.front();
                que.pop();
                if (i != size - 1) {
                    nextNode* node = que.front();
                    prenode->next = node;
                }
                else {
                    prenode->next = nullptr;
                }

                if (prenode->left != nullptr) {
                    que.push(prenode->left);
                }
                if (prenode->right != nullptr) {
                    que.push(prenode->right);
                }
            }
        }
        return root;
    }

public:
    // 104.二叉树的最大深度
    int maxDepth(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int left = maxDepth(root->left);
        int right = maxDepth(root->right);
        return left > right ? left + 1 : right + 1;
    }

public:
    // 111.二叉树的最小深度
    int minDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        int depth = 0;
        queue<TreeNode*> que;
        que.push(root);
        while(!que.empty()) {
            int size = que.size();
            depth++;
            for (int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                if (node->left) que.push(node->left);
                if (node->right) que.push(node->right);
                if (!node->left && !node->right) {
                    return depth;
                }
            }
        }
        return depth;
    }
};