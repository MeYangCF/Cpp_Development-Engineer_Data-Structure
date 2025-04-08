/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2024 24-12-25 ����2:27
@description:
*/
// BST��.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include <iostream>
#include <functional>
#include <stack>
#include <queue>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

// BST������ʵ��
template<typename T, typename Comp = less<T>>
class BSTree
{
public:
	// ��ʼ�����ڵ�ͺ�������+lambda���ʽ
	BSTree(Comp comp = Comp())
		:root_(nullptr)
		, comp_(comp)
	{}
	// �������˼���ͷ�BST�����нڵ���Դ
	~BSTree()
	{
		if (root_ != nullptr)
		{
			queue<Node*> s;
			s.push(root_);
			while (!s.empty())
			{
				Node* front = s.front();
				s.pop();

				if (front->left_ != nullptr)
				{
					s.push(front->left_);
				}
				if (front->right_ != nullptr)
				{
					s.push(front->right_);
				}
				delete front;
			}
		}
	}

	// �ǵݹ�������
	void n_insert(const T& val)
	{
		// ��Ϊ�գ����ɸ��ڵ�
		if (root_ == nullptr)
		{
			root_ = new Node(val);
			return;
		}
		// �������ʵĲ���λ�ã���¼���ڵ��λ��
		Node* parent = nullptr;
		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ == val)
			{
				// ������Ԫ����ͬ��ֵ
				return;
			}
			else if (comp_(cur->data_, val))
			{
				parent = cur;
				cur = cur->right_;
			}
			else
			{
				parent = cur;
				cur = cur->left_;
			}
		}

		// ���½ڵ���뵽parent�ڵ�ĺ�����
		if (comp_(val, parent->data_))
		{
			parent->left_ = new Node(val);
		}
		else
		{
			parent->right_ = new Node(val);
		}
	}
	// �ݹ�������
	void insert(const T& val)
	{
		root_ = insert(root_, val);
	}
	// �ǵݹ�ɾ������
	void n_remove(const T& val)
	{
		// ����ֱ�ӷ���
		if (root_ == nullptr)
		{
			return;
		}

		// ������ɾ���ڵ�
		Node* parent = nullptr;
		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ == val)
			{
				break; // �ҵ���ɾ���ڵ�
			}
			else if (comp_(cur->data_, val))
			{
				parent = cur;
				cur = cur->right_;
			}
			else
			{
				parent = cur;
				cur = cur->left_;
			}
		}

		// û�ҵ���ɾ���ڵ�
		if (cur == nullptr)
		{
			return;
		}

		// ���3 =�� ɾ��ǰ���ڵ㣨�������1��2��
		if (cur->left_ != nullptr && cur->right_ != nullptr)
		{
			parent = cur;
			Node* pre = cur->left_;
			while (pre->right_ != nullptr)
			{
				parent = pre;
				pre = pre->right_;
			}
			cur->data_ = pre->data_;
			cur = pre; // ��curָ��ǰ���ڵ㣬ת�������1��2
		}

		// curָ��ɾ���ڵ㣬parentָ���丸�ڵ㣬ͬһ�������1����2
		Node* child = cur->left_;
		if (child == nullptr)
		{
			child = cur->right_;
		}

		if (parent == nullptr) // ������� ��ʾɾ�����Ǹ��ڵ�
		{
			root_ = child;
		}
		else
		{
			// �Ѵ�ɾ���ڵ�ĺ���(nullptr���߲���)д���丸�ڵ���Ӧ��ַ����
			if (parent->left_ == cur)
			{
				parent->left_ = child;
			}
			else
			{
				parent->right_ = child;
			}
		}

		delete cur; // ɾ����ǰ�ڵ�
	}
	// �ݹ�ɾ������
	void remove(const T& val)
	{
		root_ = remove(root_, val);
	}
	// �ǵݹ��ѯ����
	bool n_query(const T& val)
	{
		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ == val)
			{
				return true;
			}
			else if (comp_(cur->data_, val))
			{
				cur = cur->right_;
			}
			else
			{
				cur = cur->left_;
			}
		}
		return false;
	}
	// �ݹ��ѯ����
	bool query(const T& val)
	{
		return nullptr != query(root_, val);
	}

	// �ݹ�ǰ���������
	void preOrder()
	{
		cout << "[�ݹ�]ǰ�����:";
		preOrder(root_);
		cout << endl;
	}
	// �ǵݹ�ǰ���������
	void n_preOrder()
	{
		cout << "[�ǵݹ�]ǰ�����:";
		if (root_ == nullptr)
		{
			return;
		}

		stack<Node*> s;
		s.push(root_);
		while (!s.empty())
		{
			Node* top = s.top();
			s.pop();

			cout << top->data_ << " "; // V

			if (top->right_ != nullptr)
			{
				s.push(top->right_);   // R
			}

			if (top->left_ != nullptr)
			{
				s.push(top->left_);    // L
			}
		}
		cout << endl;
	}
	// �ݹ������������
	void inOrder()
	{
		cout << "[�ݹ�]�������:";
		inOrder(root_);
		cout << endl;
	}
	// �ǵݹ������������
	void n_inOrder()
	{
		cout << "[�ǵݹ�]�������:";
		if (root_ == nullptr)
		{
			return;
		}
		stack<Node*> s;
		Node* cur = root_;

		while (!s.empty() || cur != nullptr)
		{
			if (cur != nullptr)
			{
				s.push(cur);
				cur = cur->left_;
			}
			else
			{
				Node* top = s.top();
				s.pop();
				cout << top->data_ << " ";
				cur = top->right_;
			}
		}

		cout << endl;
	}
	// �ݹ�����������
	void postOrder()
	{
		cout << "[�ݹ�]�������:";
		postOrder(root_);
		cout << endl;
	}
	// �ǵݹ�����������
	void n_postOrder()
	{
		cout << "[�ǵݹ�]�������:";
		if (root_ == nullptr)
		{
			return;
		}
		stack<Node*> s1;
		stack<Node*> s2;
		s1.push(root_);
		while (!s1.empty())
		{
			Node* top = s1.top();
			s1.pop();

			s2.push(top); // V
			if (top->left_ != nullptr)
			{
				s1.push(top->left_);  // L
			}
			if (top->right_ != nullptr)
			{
				s1.push(top->right_);  // R
			}
		}
		while (!s2.empty())
		{
			cout << s2.top()->data_ << " ";
			s2.pop();
		}
		cout << endl;
	}
	// �ݹ�����������
	void levelOrder()
	{
		cout << "[�ݹ�]�������:";
		int h = high(); // ���Ĳ���
		for (int i = 0; i < h; ++i)
		{
			levelOrder(root_, i); // �ݹ�������Ĳ�����
		}
		cout << endl;
	}
	// �ǵݹ�����������
	void n_levelOrder()
	{
		cout << "[�ǵݹ�]�������:";
		if (root_ == nullptr)
		{
			return;
		}
		queue<Node*> que;
		que.push(root_);
		while (!que.empty())
		{
			Node* front = que.front();
			que.pop();

			cout << front->data_ << " ";
			if (front->left_ != nullptr)
			{
				que.push(front->left_);
			}
			if (front->right_ != nullptr)
			{
				que.push(front->right_);
			}
		}
		cout << endl;
	}

	// �ݹ������������
	int high()
	{
		return high(root_);
	}
	// �ݹ���������ڵ����
	int number()
	{
		return number(root_);
	}
	// �����������Ԫ��ֵ[i, j]
	void findValues(vector<T>& vec, int i, int j)
	{
		findValues(root_, vec, i, j);
	}
	// �ж϶������Ƿ���BST��
	bool isBSTree()
	{
		Node* pre = nullptr;
		return isBSTree(root_, pre);
	}
	// �ж���������
	bool isChildTree(BSTree<T, Comp>& child)
	{
		// �ڵ�ǰ����������child�ĸ��ڵ�
		if (child.root_ == nullptr)
		{
			return true;
		}

		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ == child.root_->data_)
			{
				break;
			}
			else if (comp_(cur->data_, child.root_->data_))
			{
				cur = cur->right_;
			}
			else
			{
				cur = cur->left_;
			}
		}
		if (cur == nullptr)
		{
			return false;
		}
		return isChildTree(cur, child.root_);
	}
	// ����������Ƚڵ�
	int getLCA(int val1, int val2)
	{
		Node* node = getLCA(root_, val1, val2);
		if (node == nullptr)
		{
			throw "no LCA!";
		}
		else
		{
			return node->data_;
		}
	}
	// ����ת
	void mirror01()
	{
		mirror01(root_);
	}
	// ����Գ�
	bool mirror02()
	{
		if (root_ == nullptr)
			return true;
		return mirror02(root_->left_, root_->right_);
	}
	// �ؽ�������
	void rebuild(int pre[], int i, int j, int in[], int m, int n)
	{
		root_ = _rebuild(pre, i, j, in, m, n);
	}
	// �ж�ƽ����
	bool isBalance()
	{
		int l = 0;
		bool flag = true;
		isBalance02(root_, l, flag);
		return flag;
	}
	// ����������K���ڵ�
	int getVal(int k)
	{
		Node* node = getVal(root_, k);
		if (node == nullptr)
		{
			string err = "no No.";
			err += k;
			throw err;
		}
		else
		{
			return node->data_;
		}
	}
public:
	// �������ڵ㶨��
	struct Node
	{
		Node(T data = T())
			:data_(data)
			, left_(nullptr)
			, right_(nullptr)
		{}
		T data_; // ������
		Node* left_; // ������
		Node* right_; // �Һ�����
	};
	// �ݹ�ǰ�������ʵ�� VLR
	void preOrder(Node* node)
	{
		if (node != nullptr)
		{
			cout << node->data_ << " "; // ����V
			preOrder(node->left_); // L
			preOrder(node->right_); // R
		}
	}
	// �ݹ����������ʵ�� LVR
	void inOrder(Node* node)
	{
		if (node != nullptr)
		{
			inOrder(node->left_); // L
			cout << node->data_ << " "; // V
			inOrder(node->right_); // R
		}
	}
	// �ݹ���������ʵ�� LRV
	void postOrder(Node* node)
	{
		if (node != nullptr)
		{
			postOrder(node->left_); // L
			postOrder(node->right_); // R
			cout << node->data_ << " "; // V
		}
	}
	// �ݹ���������ʵ��
	void levelOrder(Node* node, int i)
	{
		if (node == nullptr)
			return;

		if (i == 0)
		{
			cout << node->data_ << " ";
			return;
		}
		levelOrder(node->left_, i - 1);
		levelOrder(node->right_, i - 1);
	}
	// �ݹ�ʵ������������� ����nodeΪ���ڵ�������ĸ߶Ȳ����ظ߶�ֵ
	int high(Node* node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		int left = high(node->left_); // L
		int right = high(node->right_); // R
		return left > right ? left + 1 : right + 1; // V
	}
	// �ݹ���������ڵ������ʵ�� ����nodeΪ���ڵ�����Ľڵ�������������
	int number(Node* node)
	{
		if (node == nullptr)
			return 0;
		int left = number(node->left_);  // L
		int right = number(node->right_); // R
		return left + right + 1; // V
	}
	// �ݹ�������ʵ��
	Node* insert(Node* node, const T& val)
	{
		if (node == nullptr)
		{
			// �ݹ�������ҵ�����val��λ�ã������½ڵ㲢������ڵ��ַ
			return new Node(val);
		}

		if (node->data_ == val)
		{
			return node;
		}
		else if (comp_(node->data_, val))
		{
			node->right_ = insert(node->right_, val);
		}
		else
		{
			node->left_ = insert(node->left_, val);
		}
		return node;
	}
	// �ݹ��ѯ����ʵ��
	Node* query(Node* node, const T& val)
	{
		if (node == nullptr)
			return nullptr;

		if (node->data_ == val)
		{
			return node;
		}
		else if (comp_(node->data_, val))
		{
			return query(node->right_, val);
		}
		else
		{
			return query(node->left_, val);
		}
	}
	// �ݹ�ɾ������ʵ��
	Node* remove(Node* node, const T& val)
	{
		if (node == nullptr)
			return nullptr;

		if (node->data_ == val) // �ҵ���ɾ���ڵ�
		{
			// ���3
			if (node->left_ != nullptr && node->right_ != nullptr)
			{
				// ��ǰ���ڵ�
				Node* pre = node->left_;
				while (pre->right_ != nullptr)
				{
					pre = pre->right_;
				}
				node->data_ = pre->data_;
				// ͨ���ݹ�ֱ��ɾ��ǰ���ڵ�
				node->left_ = remove(node->left_, pre->data_);
			}
			else // ���1�����2
			{
				if (node->left_ != nullptr)
				{
					// ɾ���ڵ��Ժ󣬰ѷǿյ����ӷ��أ�����ʱ�����丸�ڵ��ַ��
					Node* left = node->left_;
					delete node;
					return left;
				}
				else if (node->right_ != nullptr)
				{
					// ɾ���ڵ��Ժ󣬰ѷǿյ��Һ��ӷ��أ�����ʱ�����丸�ڵ��ַ��
					Node* right = node->right_;
					delete node;
					return right;
				}
				else // ɾ������û�к��ӵĽڵ�  Ҷ�ӽڵ�
				{
					delete node;
					return nullptr; // ����ʱ�����丸�ڵ��ַ��Ϊnullptr
				}
			}
		}
		else if (comp_(node->data_, val))
		{
			node->right_ = remove(node->right_, val);
		}
		else
		{
			node->left_ = remove(node->left_, val);
		}
		return node; // �ѵ�ǰ�ڵ㷵�ظ����ڵ㣬���¸��ڵ���Ӧ�ĵ�ַ��
	}
	// �����������Ԫ��ֵ[i, j]ʵ��
	void findValues(Node* node, vector<T>& vec, int i, int j)
	{
		if (node != nullptr)
		{
			// �ڵ�ǰ�ڵ��������������
			if (node->data_ > i)
			{
				findValues(node->left_, vec, i, j); // L
			}

			if (node->data_ >= i && node->data_ <= j)// V
			{
				vec.push_back(node->data_); // �洢��������Ԫ�ص�ֵ
			}

			// �ڵ�ǰ�ڵ��������������
			if (node->data_ < j)
			{
				findValues(node->right_, vec, i, j); // R
			}
		}
	}
	// �ж϶������Ƿ���BST����ʵ�� ����BST�����������һ��������ص�
	bool isBSTree(Node* node, Node*& pre)
	{
		if (node == nullptr)
		{
			return true;
		}

		if (!isBSTree(node->left_, pre)) // L ��Ҫ�ж�ʹ�ݹ����������
		{
			return false;
		}
		// V
		if (pre != nullptr)
		{
			if (comp_(node->data_, pre->data_)) // ��Ҫ�ж�ʹ�ݹ����������
			{
				return false;
			}
		}
		pre = node; // �������������ǰ���ڵ�

		return isBSTree(node->right_, pre); // R

		// V
		//if (node->left_ != nullptr && comp_(node->data_, node->left_->data_))
		//{
		//	return false;
		//}

		//if (node->right_ != nullptr && comp_(node->right_->data_, node->data_))
		//{
		//	return false;
		//}

		//if (!isBSTree(node->left_)) // L �жϵ�ǰ�ڵ��������
		//{
		//	return false;
		//}

		//return isBSTree(node->right_); // R �жϵ�ǰ�ڵ��������
	}
	// �ж���������ʵ��
	bool isChildTree(Node* father, Node* child)
	{
		if (father == nullptr && child == nullptr)
		{
			return true;
		}

		if (father == nullptr) // ���������еĽڵ㣬��ǰ������û��
		{
			return false;
		}

		if (child == nullptr)
		{
			return true;
		}

		// �ж�ֵ����ͬ
		if (father->data_ != child->data_)  // V
		{
			return false;
		}

		return isChildTree(father->left_, child->left_) // L
			&& isChildTree(father->right_, child->right_); // R
	}
	// ����������Ƚڵ�ʵ��
	Node* getLCA(Node* node, int val1, int val2)
	{
		if (node == nullptr)
		{
			return nullptr;
		}

		if (comp_(node->data_, val1) && comp_(node->data_, val2))
		{
			return getLCA(node->right_, val1, val2);
		}
		else if (comp_(val1, node->data_) && comp_(val2, node->data_))
		{
			return getLCA(node->left_, val1, val2);
		}
		else
		{
			return node;
		}
	}
	// ����ת
	void mirror01(Node* node)
	{
		if (node == nullptr)
			return;

		// V
		Node* tmp = node->left_;
		node->left_ = node->right_;
		node->right_ = tmp;

		mirror01(node->left_);  // L
		mirror01(node->right_); // R
	}
	// ����Գ�
		bool mirror02(Node* node1, Node* node2)
		{
			if (node1 == nullptr && node2 == nullptr)
			{
				return true;
			}
			if (node1 == nullptr || node2 == nullptr)
			{
				return false;
			}
			if (node1->data_ != node2->data_)
			{
				return false;
			}
			return mirror02(node1->left_, node2->right_)
				&& mirror02(node1->right_, node2->left_);
		}
	// �ؽ��������ݹ�ʵ��
	Node* _rebuild(int pre[], int i, int j, int in[], int m, int n)
	{
		if (i > j || m > n)
		{
			return nullptr;
		}

		// ������ǰ�����ĸ��ڵ�
		Node* node = new Node(pre[i]); // ��ǰ��ĵ�һ�����ִ����������ڵ�  V
		for (int k = m; k <= n; ++k)
		{
			if (pre[i] == in[k]) // ��������������������ڵ���±�k
			{
				node->left_ = _rebuild(pre, i + 1, i + (k - m), in, m, k - 1); // L
				node->right_ = _rebuild(pre, i + (k - m) + 1, j, in, k + 1, n); // R
				return node;
			}
		}
		return node;
	}
	// �ж�ƽ���� Ч�ʱȽϵ�
	bool isBalance(Node* node)
	{
		if (node == nullptr)
			return true;
		if (!isBalance(node->left_))  // L
			return false;
		if (!isBalance(node->right_))  // R
			return false;

		int left = high(node->left_);
		int right = high(node->right_);
		return abs(left - right) <= 1;   // V
	}
	// �ж�ƽ���� Ч�ʸ� �ݹ�����У���¼�˽ڵ�ĸ߶�ֵ  ���ؽڵ�߶�ֵ
	int isBalance02(Node* node, int l, bool& flag)
	{
		if (node == nullptr)
		{
			return l;
		}

		int left = isBalance02(node->left_, l + 1, flag); // L
		if (!flag)
			return left;
		int right = isBalance02(node->right_, l + 1, flag); // R
		if (!flag)
			return right;

		// V
		if (abs(left - right) > 1) // �ڵ�ʧ����
		{
			flag = false;
		}
		return max(left, right);
	}
	// ����������K���ڵ�
	int i = 1;
	Node* getVal(Node* node, int k)
	{
		if (node == nullptr)
			return nullptr;

		Node* left = getVal(node->right_, k); // R
		if (left != nullptr)
			return left;
		// V
		if (i++ == k) // ��VRL��˳���£��ҵ�������k��Ԫ��
		{
			return node;
		}
		return getVal(node->left_, k); // L
	}

	Node* root_; // ָ��BST���ĸ��ڵ�
	Comp comp_; // ����һ����������
};

void test01() // �����Ƿ���BST��
{
	using Node = BSTree<int>::Node;
	BSTree<int> bst;
	bst.root_ = new Node(40);
	Node* node1 = new Node(20);
	Node* node2 = new Node(60);
	Node* node3 = new Node(30);
	Node* node4 = new Node(80);

	bst.root_->left_ = node1;
	bst.root_->right_ = node2;
	node2->left_ = node3;
	node2->right_ = node4;

	cout << bst.isBSTree() << endl;
}
void test02() // ���������ж�����
{
	int ar[] = { 58,24,67,0,34,62,69,5,41,64,78 };
	BSTree<int> bst;
	for (int v : ar)
	{
		bst.insert(v);
	}

	using Node = BSTree<int>::Node;
	BSTree<int> bst1;
	bst1.root_ = new Node(67);
	Node* node1 = new Node(62);
	Node* node2 = new Node(69);
	Node* node3 = new Node(60);
	bst1.root_->left_ = node1;
	bst1.root_->right_ = node2;
	node1->left_ = node3;

	cout << bst.isChildTree(bst1) << endl;
}
void test03() // ����LCA����
{
	int ar[] = { 58,24,67,0,34,62,69,5,41,64,78 };
	BSTree<int> bst;
	for (int v : ar)
	{
		bst.insert(v);
	}

	cout << bst.getLCA(64, 62) << endl;
}
void test04() // ���Ծ���Գ�
{
	using Node = BSTree<int>::Node;
	BSTree<int> bst;
	bst.root_ = new Node(40);
	Node* node1 = new Node(20);
	Node* node2 = new Node(20);
	Node* node3 = new Node(10);
	Node* node4 = new Node(15);
	Node* node5 = new Node(15);
	Node* node6 = new Node(10);

	bst.root_->left_ = node1;
	bst.root_->right_ = node2;
	node1->left_ = node3;
	node1->right_ = node4;
	node2->left_ = node5;
	//node2->right_ = node6;

	cout << bst.mirror02() << endl;
}
void test05() // �����ؽ�������
{
	BSTree<int> bst;
	int pre[] = { 58,24,0,5,34,41,67,62,64,69,78 };
	int in[] = { 0,5,24,34,41,58,62,64,67,69,78 };
	bst.rebuild(pre, 0, 10, in, 0, 10);
	bst.preOrder();
	bst.inOrder();
}
int main()
{
	using Elm = pair<int, string>;
	using Functor = function<bool(pair<int, string>, pair<int, string>)>;
	BSTree<Elm, Functor> bst([](Elm p1, Elm p2)->bool {
		return p1.first > p2.first;
		});

	/*test05();*/
	/*test04();*/
	/*test03();*/
	/*test02();*/
	/*test01();*/

	//int ar[] = {58,24,67,0,34,62,69,5,41,64,78};
	//BSTree<int> bst;
	//for (int v : ar)
	//{
	//	//bst.n_insert(v);
	//	bst.insert(v);
	//}
	//cout << bst.isBalance() << endl;
	//bst.insert(12);
	//cout << bst.isBalance() << endl;
	//bst.inOrder();
	//cout << bst.getVal(2) << endl;

	//bst.inOrder();
	//bst.mirror01();
	//bst.inOrder();

	/*bst.preOrder();
	bst.n_preOrder();
	bst.inOrder();
	bst.n_inOrder();*/
	//bst.postOrder();
	//bst.n_postOrder();
	//bst.levelOrder();
	//bst.n_levelOrder();
	//cout << bst.high() << endl;
	//cout << bst.number() << endl;

	//cout << bst.query(12) << endl;
	//bst.insert(12);
	//cout << bst.query(12) << endl;

	//bst.inOrder();

	//vector<int> vec;
	//bst.findValues(vec, 10, 60);
	//for (int v : vec)
	//{
	//	cout << v << " ";
	//}
	//cout << endl;

	//cout << bst.isBSTree() << endl;

	/*bst.remove(12);
	bst.remove(34);
	bst.remove(58);
	bst.inOrder();*/

	/*bst.n_insert(12);
	cout << bst.n_query(12) << endl;

	bst.n_remove(12);
	bst.n_remove(34);
	bst.n_remove(58);

	cout << bst.n_query(12) << endl;*/

	return 0;
}