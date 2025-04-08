/*
@autor: Yang ChengFeng
@email: meyangcf@163.com
@date: 25-1-8 ����10:38
@description: 
*/
// 36_Trie�ֵ���.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>
using namespace std;

// Trie�ֵ���
class trieTree
{
public:
	trieTree()
	{
		root_ = new TrieNode('\0', 0);
	}

	~trieTree()
	{
		queue<TrieNode*> que;
		que.push(root_);

		while (!que.empty())
		{
			TrieNode* front = que.front();
			que.pop();
			// �ѵ�ǰ�ڵ�ĺ��ӽڵ�ȫ�������
			for (auto& pair : front->nodeMap_)
			{
				que.push(pair.second);
			}
			// �ͷŵ�ǰ�ڵ���Դ
			delete front;
		}
	}

public:
	// ��ӵ���
	void add(const string& word)
	{
		TrieNode* cur = root_;

		for (int i = 0; i < word.size(); i++)  // O(m)
		{
			auto childIt = cur->nodeMap_.find(word[i]);
			if (childIt == cur->nodeMap_.end())
			{
				// ��Ӧ�ַ��Ľڵ�û�У�������
				TrieNode* child = new TrieNode(word[i], 0);
				cur->nodeMap_.emplace(word[i], child);
				cur = child;
			}
			else
			{
				// ��Ӧ���ַ��ڵ��Ѿ����ڣ��ƶ�curָ���Ӧ���ַ��ڵ�
				cur = childIt->second;
			}
		}

		// curָ����word���ʵ����һ���ڵ�
		cur->freqs_++;
	}

	// ɾ������
	void remove(const string& word)
	{
		TrieNode* cur = root_;
		TrieNode* del = root_; // ���ĸ��ڵ㿪ʼɾ��
		char delch = word[0];

		for (int i = 0; i < word.size(); i++)
		{
			auto childIt = cur->nodeMap_.find(word[i]);
			if (childIt == cur->nodeMap_.end())
			{
				return;
			}

			// pool  po ���2�����3
			if (cur->freqs_ > 0 || cur->nodeMap_.size() > 1)
			{
				del = cur;
				delch = word[i];
			}

			// cur�ƶ����ӽڵ�
			cur = childIt->second;
		}

		// curָ����ĩβ�ַ��ڵ㣻word�����Ǵ��ڵ�
		if (cur->nodeMap_.empty())
		{
			// ��ʼɾ��
			TrieNode* child = del->nodeMap_[delch];
			del->nodeMap_.erase(delch);

			// �ͷ���Ӧ�Ľڵ��ڴ�
			queue<TrieNode*> que;
			que.push(child);

			while (!que.empty())
			{
				TrieNode* front = que.front();
				que.pop();
				// �ѵ�ǰ�ڵ�ĺ��ӽڵ�ȫ�������
				for (auto& pair : front->nodeMap_)
				{
					que.push(pair.second);
				}
				// �ͷŵ�ǰ�ڵ���Դ
				delete front;
			}
		}
		else
		{
			// ���1
			// ��ǰ����ĩβ�ַ����滹���ַ��ڵ㣬�����κνڵ�ɾ������
			cur->freqs_ = 0;
		}
	}

	// ��ѯ����
	int query(const string& word)
	{
		TrieNode* cur = root_;
		for (int i = 0; i < word.size(); i++) // O(m)
		{
			auto childIt = cur->nodeMap_.find(word[i]);
			if (childIt == cur->nodeMap_.end())
			{
				return 0;
			}
			// �ƶ�curָ����һ�����ʵ��ַ��ڵ���
			cur = childIt->second;
		}

		return cur->freqs_;
	}

	// ǰ������ֵ���
	void preOrder()
	{
		string word;
		vector<string> wordList;
		preOrder(root_, word, wordList);
		for (auto word : wordList)
		{
			cout << word << endl;
		}
		cout << endl;
	}

	// ����ǰ׺����
	vector<string> queryPrefix(const string& prefix)
	{
		TrieNode* cur = root_;
		for (int i = 0; i < prefix.size(); i++)
		{
			auto childIt = cur->nodeMap_.find(prefix[i]);
			if (childIt == cur->nodeMap_.end())
			{
				// vector<string> vec{};
				return {};
			}
			cur = childIt->second;
		}

		// cur��ָ����ǰ׺�����һ���ַ��ڵ���
		vector<string> wordlist;
		preOrder(cur, prefix.substr(0, prefix.size()-1), wordlist);
		return wordlist;
	}

private:
	// �ڵ����Ͷ���
	struct TrieNode
	{
		TrieNode(char ch, int freqs)
			: ch_(ch)
			, freqs_(freqs)
		{}

		// �ڵ�洢���ַ�����
		char ch_;
		// ���ʵ�ĩβ�ַ��洢���ʵ�����(Ƶ��)
		int freqs_;
		// �洢���ӽڵ��ַ����ݺͽڵ�ָ��Ķ�Ӧ��ϵ
		map<char, TrieNode*> nodeMap_;
	};

private:
	void preOrder(TrieNode* cur, string word, vector<string> &wordlist)
	{
		// ǰ����� VLR
		if (cur != root_)   // V
		{
			word.push_back(cur->ch_);
			if (cur->freqs_ > 0)
			{
				// �Ѿ�������һ����Ч�ĵ���
				wordlist.emplace_back(word);
			}
		}

		// �ݹ鴦���ӽڵ�
		for (auto pair : cur->nodeMap_)
		{
			preOrder(pair.second, word, wordlist);
		}
	}

private:
	TrieNode* root_; // ָ�����ĸ��ڵ�
};

int main()
{
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
	{
		cout << word << endl;
	}
	cout << endl;

	trie.remove("hellw");
	cout << "=====================" << endl;
	trie.preOrder();
 }