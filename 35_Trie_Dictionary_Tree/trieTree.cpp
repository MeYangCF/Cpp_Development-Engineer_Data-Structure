/*
@autor: Yang ChengFeng
@email: meyangcf@163.com
@date: 25-1-8 ÉÏÎç10:38
@description: 
*/
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>
using namespace std;

class trieTree {
public:
    trieTree() {
        root_ = new TrieNode('\0', 0);
    }

    ~trieTree() {
        queue<TrieNode*> que;
        que.push(root_);

        while (!que.empty()) {
            TrieNode* front = que.front();
            que.pop();

            for (auto& pair : front->nodeMap_)
                que.push(pair.second);

            delete front;
        }
    }

public:
    void add(const string& word) {
        TrieNode* cur = root_;

        for (int i = 0; i < word.size(); i++) {
            auto childIt = cur->nodeMap_.find(word[i]);

            if (childIt == cur->nodeMap_.end()) {
                TrieNode* child = new TrieNode(word[i], 0);
                cur->nodeMap_.emplace(word[i], child);
                cur = child;
            } else
                cur = childIt->second;
        }

        cur->freqs_++;
    }

    void remove(const string& word) {
        TrieNode* cur = root_;
        TrieNode* del = root_;
        char delch = word[0];

        for (int i = 0; i < word.size(); i++) {
            auto childIt = cur->nodeMap_.find(word[i]);

            if (childIt == cur->nodeMap_.end())
                return;

            if (cur->freqs_ > 0 || cur->nodeMap_.size() > 1) {
                del = cur;
                delch = word[i];
            }

            cur = childIt->second;
        }

        if (cur->nodeMap_.empty()) {
            TrieNode* child = del->nodeMap_[delch];
            del->nodeMap_.erase(delch);

            queue<TrieNode*> que;
            que.push(child);

            while (!que.empty()) {
                TrieNode* front = que.front();
                que.pop();

                for (auto& pair : front->nodeMap_)
                    que.push(pair.second);

                delete front;
            }
        } else
            cur->freqs_ = 0;
    }

    int query(const string& word) {
        TrieNode* cur = root_;

        for (int i = 0; i < word.size(); i++) {
            auto childIt = cur->nodeMap_.find(word[i]);

            if (childIt == cur->nodeMap_.end())
                return 0;

            cur = childIt->second;
        }

        return cur->freqs_;
    }

    void preOrder() {
        string word;
        vector<string> wordlist;
        preOrder(root_, word, wordlist);

        for (auto word : wordlist)
            cout << word << endl;
    }

    vector<string> queryPrefix(const string& prefix) {
        TrieNode* cur = root_;

        for (int i = 0; i < prefix.size(); i++) {
            auto childIt = cur->nodeMap_.find(prefix[i]);

            if (childIt == cur->nodeMap_.end())
                return {};

            cur = childIt->second;
        }

        vector<string> wordlist;
        preOrder(cur, prefix.substr(0, prefix.size() - 1), wordlist);
        return wordlist;
    }
private:
    struct TrieNode {
        TrieNode(char ch, int freqs_)
            : ch_(ch)
            , freqs_(freqs_) {}
        char ch_;
        int freqs_;
        map<char, TrieNode*> nodeMap_;
    };

private:
    void preOrder(TrieNode* cur, string word, vector<string>& wordlist) {
        if (cur != root_) {
            word.push_back(cur->ch_);

            if (cur->freqs_ > 0)
                wordlist.emplace_back(word);
        }

        for (auto pair : cur->nodeMap_)
            preOrder(pair.second, word, wordlist);
    }
private:
    TrieNode* root_;
};
int main() {
    trieTree trie;
    trie.add("hello");
    trie.add("hello");
    trie.add("helloo");
    trie.add("hel");
    trie.add("hel");
    trie.add("hel");
    trie.add("china");
    trie.add("ch");
    trie.add("ch");
    trie.add("heword");
    trie.add("hellw");

    cout << trie.query("hello") << endl;
    cout << trie.query("helloo") << endl;
    cout << trie.query("hel") << endl;
    cout << trie.query("china") << endl;
    cout << trie.query("ch") << endl;

    cout << "=====================" << endl;
    trie.preOrder();
    cout << "=====================" << endl;
    vector<string> words = trie.queryPrefix("he");

    for (auto word : words)
        cout << word << endl;
    cout << endl;

    trie.remove("hellw");
    cout << "=====================" << endl;
    trie.preOrder();
    return 0;
}