/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-01-14 обнГ2:29
@description:
*/
#include <iostream>
#include <unordered_map>
#include <string>
#include <queue>
#include <functional>
using namespace std;

using uint = unsigned int;

class HuffmanTree {
public:
    HuffmanTree()
        : minHeap_([](Node* n1, Node* n2)->bool
            {return n1->weight_ > n2->weight_;})
        , root_(nullptr) {}
public:
    void create(string str) {
        unordered_map<char, uint> dataMap;

        for (char ch : str)
            dataMap[ch]++;

        for (auto& pair : dataMap)
            minHeap_.push(new Node(pair.first, pair.second));

        while (minHeap_.size() > 1) {
            Node* n1 = minHeap_.top();
            minHeap_.pop();
            Node* n2 = minHeap_.top();
            minHeap_.pop();

            Node* node = new Node('\0', n1->weight_ + n2->weight_);
            node->left_ = n1;
            node->right_ = n2;

            minHeap_.push(node);
        }

        root_ = minHeap_.top();
        minHeap_.pop();
    }

    string encode(string str) {
        getHuffmanCode();

        string encode_str;

        for (char ch : str)
            encode_str.append(codeMap_[ch]);

        return encode_str;
    }

    string decode(string encode) {
        string decode_str;
        Node* cur = root_;

        for (char ch : encode) {
            if (ch == '0')
                cur = cur->left_;
            else
                cur = cur->left_;

            if (cur->left_ == nullptr && cur->right_ == nullptr) {
                decode_str.push_back(cur->data_);
                cur = root_;
            }
        }

        return decode_str;
    }

private:
    struct Node {
        Node(char data, uint weight)
            : data_(data)
            , weight_(weight)
            , left_(nullptr)
            , right_(nullptr) {}
        char data_;
        uint weight_;
        Node* left_;
        Node* right_;
    };

private:
    void getHuffmanCode() {
        string code;
        getHuffmanCode(root_, code);
    }

    void getHuffmanCode(Node* root, string code) {
        if (root_->left_ == nullptr && root_->right_ == nullptr) {
            codeMap_[root_->data_] = code;
            return;
        }

        getHuffmanCode(root_->left_, code + "0");
        getHuffmanCode(root_->right_, code + "1");
    }

private:
    Node* root_;
    unordered_map<char, string> codeMap_;

    using MinHeap = priority_queue<Node*, vector<Node*>, function<bool(Node*, Node*)>>;
    MinHeap minHeap_;
};

int main() {

    return 0;
}