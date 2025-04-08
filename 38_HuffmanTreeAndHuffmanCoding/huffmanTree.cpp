/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-01-14 ����2:29
@description:
*/
// 38_���������͹���������.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include <iostream>
#include <unordered_map>
#include <string>
#include <queue>
#include <functional>
using namespace std;

using uint = unsigned int;

// ʵ�ֹ�������
class HuffmanTree
{
public:
	HuffmanTree()
		: minHeap_([](Node* n1, Node* n2)->bool
			{return n1->weight_ > n2->weight_; })
		, root_(nullptr)
	{}

	// ������������
	void create(string str)
	{
		// ��ͳ���ַ���Ȩֵ
		unordered_map<char, uint> dataMap;
		for (char ch : str)
		{
			dataMap[ch]++;
		}

		// ���ɽڵ㣬����С������
		for (auto& pair : dataMap)
		{
			minHeap_.push(new Node(pair.first, pair.second));
		}

		while (minHeap_.size() > 1)
		{
			// ��ȡ����Ȩֵ��С��
			Node* n1 = minHeap_.top();
			minHeap_.pop();

			Node* n2 = minHeap_.top();
			minHeap_.pop();

			// ���ɸ��ڵ�
			Node* node = new Node('\0', n1->weight_ + n2->weight_);
			node->left_ = n1;
			node->right_ = n2;

			minHeap_.push(node);
		}

		root_ = minHeap_.top();
		minHeap_.pop();
	}

	// encode
	string encode(string str)
	{
		getHuffmanCode();

		string encode_str;
		for (char ch : str)
		{
			encode_str.append(codeMap_[ch]);
		}
		return encode_str;
	}

	// decode
	string decode(string encode)
	{
		string decode_str;
		Node* cur = root_;

		for (char ch : encode)
		{
			if (ch == '0')
			{
				cur = cur->left_;
			}
			else
			{
				cur = cur->right_;
			}

			if (cur->left_ == nullptr && cur->right_ == nullptr)
			{
				decode_str.push_back(cur->data_);
				cur = root_;
			}
		}
		return decode_str;
	}

private:
	struct Node
	{
		Node(char data, uint weight)
			: data_(data)
			, weight_(weight)
			, left_(nullptr)
			, right_(nullptr)
		{}

		char data_;   // �ַ�����
		uint weight_; // �ڵ��Ȩֵ
		Node* left_;  // ָ�����ӽڵ�
		Node* right_; // ָ���Һ��ӽڵ�
	};

private:
	// �������������
	void getHuffmanCode()
	{
		string code;
		getHuffmanCode(root_, code);

		/*for (auto& pair : codeMap_)
		{
			cout << pair.first << " : " << pair.second << endl;
		}
		cout << endl;*/
	}

	void getHuffmanCode(Node* root, string code)
	{
		// VLR
		if (root->left_ == nullptr && root->right_ == nullptr)
		{
			codeMap_[root->data_] = code;
			return;
		}

		getHuffmanCode(root->left_, code + "0");
		getHuffmanCode(root->right_, code + "1");
	}

private:
	Node* root_; // ָ����ڵ�
	unordered_map<char, string> codeMap_; // �洢�ַ���Ӧ�Ĺ���������

	using MinHeap = priority_queue<Node*, vector<Node*>, function<bool(Node*, Node*)>>;
	MinHeap minHeap_;
};

int main()
{
	string str = "ABACDAEFDEGGAHGNNMBHJGUTUYHBBNBNBJHGSUYTUYTRFHGTHJ";

	HuffmanTree htree;
	htree.create(str);
	string encode = htree.encode(str);
	cout << "encode:" << encode << endl;

	cout << "decode:" << htree.decode(encode) << endl;
}