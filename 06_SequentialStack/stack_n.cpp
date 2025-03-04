/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-03-03 上午10:26
@description:
*/
/*
# include <iostream>
using namespace std;

class stack {
public:
    stack(int size = 10)
        : mTop(0),
          mCap(size) {
        mpStack = new int[mCap];
    }

    ~stack() {
        delete[] mpStack;
        mpStack = nullptr;
    }

public:
    void push(int val) {
        if (mTop == mCap) {
            expand(2 * mCap);
        }
        mpStack[mTop++] = val;
    }

    void pop() {
        if (mTop == 0) {
            throw "stack is empty";
        }
        mTop--;
    }

    int top() const {
        if (mTop == 0) {
            throw "stack is empty";
        }
        return mpStack[mTop - 1];
    }

    bool empty() {
        return mTop == 0;
    }

    int size() const {
        return mTop;
    }

private:
    void expand(int size) {
        int *p = new int[size];
        memcpy(p, mpStack, mTop * sizeof(int));
        delete[] mpStack;
        mpStack = p;
        mCap = size;
    }

private:
    int *mpStack;
    int mTop;
    int mCap;
};
*/

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

// 232.用栈实现队列
class MyQueue {
public:
    MyQueue() {}

    void push(int x) {
        s1.push(x);
    }

    int pop() {
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }

        int val = s2.top();
        s2.pop();
        return val;
    }

    int peek() {
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }

        return s2.top();
    }

    bool empty() {
        return s1.empty() && s2.empty();
    }

private:
    stack<int> s1;
    stack<int> s2;
};

// 225.用队列实现栈
class MyStack {
public:
    MyStack() {
        q1 = new queue<int>;
        q2 = new queue<int>;
    }

    ~MyStack() {
        delete q1;
        delete q2;
        q1 = nullptr;
        q2 = nullptr;
    }

    void push(int x) {
        q1->push(x);
        while (!q2->empty()){
            q1->push(q2->front());
            q2->pop();
        }
        queue<int> *p = q1;
        q1 = q2;
        q2 = p;
    }

    int pop() {
        int val = q2->front();
        q2->pop();
        return val;
    }

    int top() {
        return  q2->front();
    }

    bool empty() {
        return q2->empty();
    }

private:
    queue<int>* q1;
    queue<int>* q2;
};

class Solution {
public:
    // 20.有效的括号
    bool isValid(string s) {
        stack<char> strV;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
                strV.push(s[i]);
            }
            else {
                if (strV.empty()) {
                    return false;
                }
                char tmp = strV.top();
                if ((tmp == '(' && s[i] == ')')
                    || (tmp == '{' && s[i] == '}')
                    || (tmp == '[' && s[i] == ']')) {
                    strV.pop();
                    continue;
                    }
                else {
                    return false;
                }
            }
        }
        return strV.empty();
    }

public:
    // 1047. 删除字符串中的所有相邻重复项
    string removeDuplicates(string s) {
        stack<char> strV;
        for (int i = 0; i < s.size(); i++) {
            if (!strV.empty()) {
                char tmp = strV.top();
                if (tmp == s[i]) {
                    strV.pop();
                }
                else {
                    strV.push(s[i]);
                }
            }
            else {
                strV.push(s[i]);
            }
        }
        string result;
        while (!strV.empty()) {
            result.insert(result.begin(), strV.top());
            strV.pop();
        }
        return result;
    }

public:
    // 150. 逆波兰表达式求值
    int evalRPN(vector<string>& tokens) {
        stack<int> strV;
        for (auto v : tokens) {
            if (v == "+" || v == "-" || v == "*" || v == "/") {
                long long s1 = strV.top();
                strV.pop();
                long long s2 = strV.top();
                strV.pop();
                if (v == "+") {
                    strV.push(s2 + s1);
                }
                if (v == "-") {
                    strV.push(s2 - s1);
                }
                if (v == "*") {
                    strV.push(s2 * s1);
                }
                if (v == "/") {
                    strV.push(s2 / s1);
                }
            }
            else {
                strV.push(stoll(v));
            }
        }
        return strV.top();
    }


};
