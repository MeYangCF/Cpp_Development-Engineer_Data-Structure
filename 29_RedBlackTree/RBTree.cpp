/*
@autor: Yang ChengFeng
@email: meyangcf@163.com
@date: 25-1-7 ����9:39
@description: 
*/
// RB.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include <iostream>
using namespace std;

// ���������
template<typename T>
class RBTree {
public:
	RBTree() : root_(nullptr) {
	}

	// �������
	void insert(const T &val) {
		if (root_ == nullptr) {
			root_ = new Node(val);
			return;
		}

		Node *parent = nullptr;
		Node *cur = root_;
		while (cur != nullptr) {
			if (cur->data_ > val) {
				parent = cur;
				cur = cur->left_;
			} else if (cur->data_ < val) {
				parent = cur;
				cur = cur->right_;
			} else {
				return;
			}
		}

		// ���õ�ǰ�ڵ��parent����ɫ
		Node *node = new Node(val, parent, nullptr, nullptr, RED);
		if (parent->data_ > val) {
			parent->left_ = node;
		} else {
			parent->right_ = node;
		}

		// ����²���ĺ�ɫ�ڵ㣬���ڵ�Ҳ�Ǻ�ɫ���������������ʣ����в����������
		if (RED == color(parent)) {
			fixAfterInsert(node);
		}
	}

	// ɾ������
	void remove(const T &val) {
		if (root_ == nullptr) {
			return;
		}

		Node *cur = root_;
		while (cur != nullptr) {
			if (cur->data_ > val) {
				cur = cur->left_;
			} else if (cur->data_ < val) {
				cur = cur->right_;
			} else {
				break;
			}
		}

		// û�ҵ�val�ڵ㷵��
		if (cur == nullptr) {
			return;
		}

		// ɾ��ǰ���ڵ� �����
		if (cur->left_ != nullptr && cur->right_ != nullptr) {
			Node *pre = cur->left_;
			while (pre->right_ != nullptr) {
				pre = pre->right_;
			}
			cur->data_ = pre->data_;
			cur = pre; // curָ��ǰ���ڵ�
		}

		// ɾ��curָ��Ľڵ�  ���һ�Ͷ�
		Node *child = cur->left_; // ��childָ��Ϊ�յĺ���
		if (child == nullptr) {
			child = cur->right_;
		}

		// left right parent
		if (child != nullptr) {
			child->parent_ = cur->parent_;
			if (cur->parent_ == nullptr) {
				// root_ -> cur_
				root_ = child;
			} else {
				if (cur->parent_->left_ == cur) {
					cur->parent_->left_ = child;
				} else {
					cur->parent_->right_ = child;
				}
			}

			Color c = color(cur);
			delete cur;

			if (c == BLACK) // ɾ�����Ǻ�ɫ�ڵ㣬Ҫ����ɾ����������
			{
				fixAfterRemove(child);
			}
		} else {
			// child == nullptr
			if (cur->parent_ == nullptr) {
				delete cur;
				root_ = nullptr;
				return;
			} else {
				// ɾ����cur����Ҷ�ӽڵ�
				if (color(cur) == BLACK) {
					fixAfterRemove(cur);
				}

				if (cur->parent_->left_ == cur) {
					cur->parent_->left_ = nullptr;
				} else {
					cur->parent_->right_ = nullptr;
				}

				delete cur;
			}
		}
	}

private:
	// �ڵ����ɫ
	enum Color {
		BLACK,
		RED
	};

	// �ڵ�����
	struct Node {
		Node(T data = T(), Node *parent = nullptr,
		     Node *left = nullptr, Node *right = nullptr,
		     Color color = BLACK)
			: data_(data)
			  , left_(left)
			  , right_(right)
			  , parent_(parent)
			  , color_(color) {
		}

		T data_;
		Node *left_;
		Node *right_;
		Node *parent_; // ָ��ǰ�ڵ�ĸ��ڵ�
		Color color_; // �ڵ����ɫ
	};

	// ���ؽڵ����ɫ
	Color color(Node *node) {
		return node == nullptr ? BLACK : node->color_;
	}

	// ���ýڵ���ɫ
	void setColor(Node *node, Color color) {
		node->color_ = color;
	}

	// ���ؽڵ������
	Node *left(Node *node) {
		return node->left_;
	}

	// ���ؽڵ���Һ���
	Node *right(Node *node) {
		return node->right_;
	}

	// ���ؽڵ�ĸ���
	Node *parent(Node *node) {
		return node->parent_;
	}

	// ����ת
	void leftRotate(Node *node) {
		Node *child = node->right_;
		child->parent_ = node->parent_;
		if (node->parent_ == nullptr) {
			// node�������root�ڵ�
			root_ = child;
		} else {
			if (node->parent_->left_ == node) {
				// node�ڸ��ڵ������
				node->parent_->left_ = child;
			} else {
				// node�ڸ��ڵ���Һ���
				node->parent_->right_ = child;
			}
		}

		node->right_ = child->left_;
		if (child->left_ != nullptr) {
			child->left_->parent_ = node;
		}

		child->left_ = node;
		node->parent_ = child;
	}

	// ����ת
	void rightRotate(Node *node) {
		Node *child = node->left_;
		child->parent_ = node->parent_;
		if (node->parent_ == nullptr) {
			// nodeԭ������root�ڵ�
			root_ = child;
		} else {
			if (node->parent_->left_ == node) {
				// node�ڸ��ڵ�����
				node->parent_->left_ = child;
			} else {
				// node�ڸ��ڵ���ұ�
				node->parent_->right_ = child;
			}
		}

		node->left_ = child->right_;
		if (child->right_ != nullptr) {
			child->right_->parent_ = node;
		}

		child->right_ = node;
		node->parent_ = child;
	}

	// ������Ĳ����������
	void fixAfterInsert(Node *node) {
		// �����ǰ��ɫ�ڵ�ĸ��ڵ�Ҳ�Ǻ�ɫ����������
		while (color(parent(node)) == RED) {
			if (left(parent(parent(node))) == parent(node)) {
				// ����Ľڵ�������������
				Node *uncle = right(parent(parent(node)));
				if (RED == color(uncle)) // ���һ
				{
					setColor(parent(node), BLACK);
					setColor(uncle, BLACK);
					setColor(parent(parent(node)), RED);
					node = parent(parent(node)); // ��������
				} else {
					// �ȴ��������
					if (right(parent(node)) == node) {
						node = parent(node);
						leftRotate(node);
					}

					// ͳһ���������
					setColor(parent(node), BLACK);
					setColor(parent(parent(node)), RED);
					rightRotate(parent(parent(node)));
					break; // �����Ѿ����
				}
			} else {
				// ����Ľڵ�������������
				Node *uncle = left(parent(parent(node)));
				if (RED == color(uncle)) // ���һ
				{
					setColor(parent(node), BLACK);
					setColor(uncle, BLACK);
					setColor(parent(parent(node)), RED);
					node = parent(parent(node)); // ��������
				} else {
					// �ȴ��������
					if (left(parent(node)) == node) {
						node = parent(node);
						rightRotate(node);
					}

					// ͳһ���������
					setColor(parent(node), BLACK);
					setColor(parent(parent(node)), RED);
					leftRotate(parent(parent(node)));
					break; // �����Ѿ����
				}
			}
		}

		// �˴�ǿ��rootΪ��ɫ�ڵ�
		setColor(root_, BLACK);
	}

	// �������ɾ����������
	void fixAfterRemove(Node *node) {
		while (node != root_ && color(node) == BLACK) {
			if (left(parent(node)) == node) {
				// ɾ���ĺ�ɫ�ڵ���������
				Node *brother = right(parent(node));
				if (color(brother) == RED) // �����
				{
					setColor(parent(node), RED);
					setColor(brother, BLACK);
					leftRotate(parent(node));
					brother = right(parent(node));
				}

				if (color(left(brother)) == BLACK
				    && color(right(brother)) == BLACK) // �����
				{
					setColor(brother, RED);
					node = parent(node);
				} else {
					if (color(right(brother)) != RED) // �����
					{
						setColor(brother, RED);
						setColor(left(brother), BLACK);
						rightRotate(brother);
						brother = right(parent(node));
					}

					// ��ᵽ���һ
					setColor(brother, color(parent(node)));
					setColor(parent(node), BLACK);
					setColor(right(brother), BLACK);
					leftRotate(parent(node));
					break;
				}
			} else {
				// ɾ���ĺ�ɫ�ڵ���������
				Node *brother = left(parent(node));
				if (color(brother) == RED) // �����
				{
					setColor(parent(node), RED);
					setColor(brother, BLACK);
					rightRotate(parent(node));
					brother = left(parent(node));
				}

				if (color(left(brother)) == BLACK
				    && color(right(brother)) == BLACK) // �����
				{
					setColor(brother, RED);
					node = parent(node);
				} else {
					if (color(left(brother)) != RED) // �����
					{
						setColor(brother, RED);
						setColor(right(brother), BLACK);
						leftRotate(brother);
						brother = left(parent(node));
					}

					// ��ᵽ���һ
					setColor(brother, color(parent(node)));
					setColor(parent(node), BLACK);
					setColor(left(brother), BLACK);
					rightRotate(parent(node));
					break;
				}
			}
		}

		// �������nodeָ��Ľڵ��Ǻ�ɫ��ֱ��Ϳ�ɺ�ɫ����������
		setColor(node, BLACK);
	}

	// ָ�������ĸ��ڵ�
	Node *root_;
};

int main() {
	RBTree<int> rb;
	for (int i = 1; i <= 10; ++i) {
		rb.insert(i);
	}

	rb.remove(9);
	rb.remove(10);
	rb.remove(5);
	rb.remove(3);

	return 0;
}
