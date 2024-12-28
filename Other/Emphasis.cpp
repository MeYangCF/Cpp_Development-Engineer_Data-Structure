#include <iostream>
#include <string>
#include <memory>
#include <stack>
using namespace std;

int BF(string mainString, string subString){
    int mainIndex = 0;
    int subIndex = 0;

    while (mainIndex < mainString.size() && subIndex < subString.size()){
        if(mainString[mainIndex] == subString[subIndex]){
            mainIndex++;
            subIndex++;
        }else{
            mainIndex = mainIndex - subIndex + 1;
            subIndex = 0;
        }
    }

    if(subIndex == subString.size())
        return mainIndex - subIndex;
    else
        return -1;
}

int* getNext(string subString){
    int* next = new int[subString.size()];
    int subIndex = 0;
    int kLength = -1;
    next[subIndex] = kLength;

    while (subIndex < subString.size() - 1){
        if(-1 == kLength || subString[kLength] == subString[subIndex]){
            subIndex++;
            kLength++;

            if(subString[kLength] == subString[subIndex])
                next[subIndex] = next[kLength];
            else
                next[subIndex] = kLength;
        } else{
            kLength = next[kLength];
        }
    }

    return next;
}

int KMP(const string &mainString, const string &subString){
    int mainIndex = 0;
    int subIndex = 0;
    int* next = getNext(subString);
    unique_ptr<int> nextPtr(next);
    int mainSize = static_cast<int>(mainString.size());
    int subSize = static_cast<int>(subString.size());

    while (mainIndex < mainSize && subIndex < subSize){
        if(-1 == subIndex || mainString[mainIndex] == subString[subIndex]){
            mainIndex++;
            subIndex++;
        }else{
            subIndex = next[subIndex];
        }
    }

    if(subIndex == subSize)
        return mainIndex - subIndex;
    else
        return -1;
}

template<typename T, typename Comp = less<T>>
class BSTree{
public:
    BSTree(Comp comp = Comp())
        : root_(nullptr)
        , comp_(comp){}

    ~BSTree(){}

public:
    void nonRecursiveInsert(const T& insertVal){
        if(root_ == nullptr){
            root_ = new Node(insertVal);
            return;
        }


        Node* parentNode = nullptr;
        Node* curNode = root_;

        while(curNode != nullptr){
            if(curNode->data_ == insertVal)
                return;
            else if(comp_(insertVal, curNode->data_)){
                parentNode = curNode;
                curNode = curNode->left_;
            }else{
                parentNode = curNode;
                curNode = curNode->right_;
            }
        }

        if(comp_(insertVal, parentNode->data_))
            parentNode->left_ = new Node(insertVal);
        else
            parentNode->right_ = new Node(insertVal);
    }

    void recursiveInsert(const T& insertVal){
        root_ = recursiveInsert(root_, insertVal);
    }

    void nonRecursiveRemove(const T& removeVal){
        if(root_ == nullptr)
            return;

        Node* parentNode = nullptr;
        Node* curNode = root_;

        while (curNode != nullptr){
            if(curNode->data_ == removeVal)
                break;
            else if(comp_(removeVal, curNode->data_)){
                parentNode = curNode;
                curNode = curNode->left_;
            }else{
                parentNode = curNode;
                curNode = curNode->right_;
            }
        }

        if(curNode == nullptr)
            return;

        if(curNode->left_ != nullptr && curNode->right_ != nullptr){
            Node* preNode = curNode->left_;

            while(curNode->right_ != nullptr){
                parentNode = preNode;
                preNode = preNode->right_;
            }

            curNode->data_ = preNode->data_;
            curNode = preNode;
        }

        Node* childNode = curNode->left_;

        if(childNode == nullptr)
            childNode = curNode->right_;

        if(parentNode == nullptr)
            root_ = childNode;
        else{
            if(parentNode->left_ == curNode)
                parentNode->left_ = childNode;
            else
                parentNode->right_ = childNode;
        }

        delete curNode;
    }

    void recursiveRemove(const T& removeVal){
        root_ = recursiveRemove(root_, removeVal);
    }

    bool nonRecursiveQuery(const T& queryVal){
        Node* curNode = root_;

        while(curNode != nullptr){
            if(curNode->data_ == queryVal)
                return true;
            else if(comp_(queryVal, curNode->data_))
                curNode = curNode->left_;
            else
                curNode = curNode->right_;
        }

        return false;
    }

    bool recursiveQuery(const T& queryVal){
        return nullptr != recursiveQuery(root_, queryVal);
    }

    void nonRecursivePreOrder(){
        if(root_ == nullptr)
            return;

        stack<Node*> preOrderStack;
        preOrderStack.push(root_);

        while(!preOrderStack.empty()){
            Node* topNode = preOrderStack.top();
            preOrderStack.pop();
            cout << topNode->data_ << " ";

            if(topNode->right_ != nullptr)
                preOrderStack.push(topNode->right_);

            if(topNode->left_ != nullptr)
                preOrderStack.push(topNode->left_);
        }
    }

    void recursivePreOrder(){
        recursivePreOrder(root_);
    }

    void nonRecursiveInOrder(){
        if(root_ == nullptr)
            return;

        stack<Node*> inOrderStack;
        Node* curNode = root_;

        while (!inOrderStack.empty() || curNode != nullptr){
            if(curNode != nullptr){
                inOrderStack.push(curNode);
                curNode = curNode->left_;
            }else{
                Node* topNode = inOrderStack.top();
                inOrderStack.pop();
                cout << topNode->data_ << " ";
                curNode = topNode->right_;
            }
        }
    }

    void recursiveInOrder(){
        recursiveInOrder(root_);
    }

    void nonRecursivePostOrder(){

    }

    void recursivePostOrder(){
        recursivePostOrder(root_);
    }

public:
    struct Node{
        Node(T data = T())
            : data_(data)
            , left_(nullptr)
            , right_(nullptr){}
        T data_;
        Node* left_;
        Node* right_;
    };

    Node* root_;
    Comp comp_;

    Node* recursiveInsert(Node* insertNode, const T& insertVal){
            if(insertNode == nullptr)
                return new Node(insertVal);

            if(insertNode->data_ == insertVal)
                return insertNode;
            else if(comp_(insertVal, insertNode->data_))
                insertNode->left_ = recursiveInsert(insertNode->left_, insertVal);
            else
                insertNode->right_ = recursiveInsert(insertNode->right_, insertVal);

           return insertNode;
        }

    Node* recursiveRemove(Node* removeNode, const T& removeVal){
        if(root_ == nullptr)
            return nullptr;

        if(removeNode->data_ == removeVal){
            if(removeNode->left_ != nullptr && removeNode->right_ != nullptr){
                Node* preNode = removeNode->left_;

                while(preNode->right_ != nullptr)
                    preNode = preNode->right_;

                removeNode->data_ = preNode->data_;
                removeNode->left_ = recursiveRemove(removeNode->left_, preNode->data_);
            }else{
                if(removeNode->left_ != nullptr){
                    Node* leftNode = removeNode->left_;
                    delete removeNode;
                    return leftNode;
                }else if(removeNode->right_ != nullptr){
                    Node* rightNode = removeNode->right_;
                    delete removeNode;
                    return rightNode;
                }else{
                    delete removeNode;
                    return nullptr;
                }
            }
        }else if(comp_(removeVal, removeNode->data_))
            removeNode->left_ = recursiveRemove(removeNode->left_, removeVal);
        else
            removeNode->right_ = recursiveRemove(removeNode->right_, removeVal);

        return removeNode;
    }

    Node* recursiveQuery(Node* queryNode, const T& queryVal){
        if(queryNode == nullptr)
            return nullptr;

        if(queryNode->data_ == queryVal)
            return queryNode;
        else if(comp_(queryVal, queryNode->data_))
            return recursiveQuery(queryNode->left_, queryVal);
        else
            return recursiveQuery(queryNode->right_, queryVal);
    }

    void recursivePreOrder(Node* preOrderNode){
        if(preOrderNode != nullptr){
            cout << preOrderNode->data_ << " ";
            recursivePreOrder(preOrderNode->left_);
            recursivePreOrder(preOrderNode->right_);
        }
    }

    void recursiveInOrder(Node* inOrderNode){
        if(inOrderNode != nullptr){
            recursivePreOrder(inOrderNode->left_);
            cout << inOrderNode->data_ << " ";
            recursivePreOrder(inOrderNode->right_);
        }
    }

    void recursivePostOrder(Node* postOrderNode){
        if(postOrderNode != nullptr){
            recursivePreOrder(postOrderNode->left_);
            recursivePreOrder(postOrderNode->right_);
            cout << postOrderNode->data_ << " ";
        }
    }
};
int main()
{
    return 0;
}