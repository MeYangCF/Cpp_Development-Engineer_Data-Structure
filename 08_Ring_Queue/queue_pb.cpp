/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2024 24-12-12 上午10:43
@description:
*/

#include <iostream>
#include <stack>
#include <queue>
using namespace std;

//用栈实现队列
//class MyQueue {
//public:
//    MyQueue() {
//
//    }
//
//    void push(int x) {
//        s1.push(x);
//    }
//
//    int pop() {
//        if(s2.empty()){
//            while (!s1.empty()){
//                s2.push(s1.top());
//                s1.pop();
//            }
//        }
//        int val = s2.top();
//        s2.pop();
//        return val;
//    }
//
//    int peek() {
//        if(s2.empty()){
//            while (!s1.empty()){
//                s2.push(s1.top());
//                s1.pop();
//            }
//        }
//        return s2.top();
//    }
//
//    bool empty() {
//        return s1.empty() && s2.empty();
//    }
//
//private:
//    stack<int> s1;
//    stack<int> s2;
//};

//class MyStack {
//public:
//    MyStack() {
//        q1 = new queue<int>;
//        q2 = new queue<int>;
//    }
//
//    ~MyStack(){
//        delete q1;
//        delete q2;
//        q1 = nullptr;
//        q2 = nullptr;
//
//    }
//
//    void push(int x) {
//        q1->push(x);
//        while (!q2->empty()){
//            q1->push(q2->front());
//            q2->pop();
//        }
//
//        queue<int> *p = q1;
//        q1 = q2;
//        q2 = p;
//    }
//
//    int pop() {
//        int val = q2->front();
//        q2->pop();
//        return val;
//    }
//
//    int top() {
//        return  q2->front();
//    }
//
//    bool empty() {
//        return q2->empty();
//    }
//
//private:
//    queue<int> *q1;
//    queue<int> *q2;
//};

//滑动窗口最大值
vector<int> maxSlidingWindow(vector<int>& nums, int k) {

}

int main(){

    return 0;
}