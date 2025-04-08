/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-03-03 下午1:18
@description:
*/
/*
#include <iostream>
using namespace std;

class queue {
public:
    queue(int size = 10)
        : cap_(size)
        , front_(0)
        , rear_(0)
        , size_(0) {
        pQue = new int[cap_];
    }
    ~queue() {
        delete[] pQue;
        pQue = nullptr;
    }

public:
    void push(int val) {
        if ((rear_ + 1) % cap_ == front_) {
            expand(2 * cap_);
        }
        pQue[rear_] = val;
        rear_ = (rear_ + 1) % cap_;
        size_++;
    }

    void pop() {
        if (empty()) {
            throw "queue is empty";
        }
        front_ = (front_ + 1) % cap_;
        size_--;
    }

    int front() const {
        if (empty()) {
            throw "queue is empty";
        }
        return pQue[front_];
    }

    int back() const {
        if (empty()) {
            throw "queue is empty";
        }
        return pQue[(rear_ - 1 + cap_) % cap_];
    }

    bool empty() const {
        return front_ == rear_;
    }

    int size() const {
        return size_;
    }

private:
    void expand(int size) {
        int* p = new int[size];
        int i = 0;
        int j = front_;
        for (; j != rear_; i++, j = (j + 1) % cap_) {
            p[i] = pQue[j];
        }
        delete[] pQue;
        pQue = p;
        cap_ = size;
        front_ = 0;
        rear_ = i;
    }

private:
    int* pQue;
    int cap_;
    int front_;
    int rear_;
    int size_;
};
*/
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class Solution {
public:
    // 239. 滑动窗口最大值
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        MyQueue que;
        vector<int> result;
        for (int i = 0; i < k; i++) { // 先将前k的元素放进队列
            que.push(nums[i]);
        }
        result.push_back(que.front()); // result 记录前k的元素的最大值
        for (int i = k; i < nums.size(); i++) {
            que.pop(nums[i - k]); // 滑动窗口移除最前面元素
            que.push(nums[i]); // 滑动窗口前加入最后面的元素
            result.push_back(que.front()); // 记录对应的最大值
        }
        return result;
    }
private:
    class MyQueue { //单调队列（从大到小）
    public:
        deque<int> que; // 使用deque来实现单调队列
        // 每次弹出的时候，比较当前要弹出的数值是否等于队列出口元素的数值，如果相等则弹出。
        // 同时pop之前判断队列当前是否为空。
        void pop(int value) {
            if (!que.empty() && value == que.front()) {
                que.pop_front();
            }
        }
        // 如果push的数值大于入口元素的数值，那么就将队列后端的数值弹出，直到push的数值小于等于队列入口元素的数值为止。
        // 这样就保持了队列里的数值是单调从大到小的了。
        void push(int value) {
            while (!que.empty() && value > que.back()) {
                que.pop_back();
            }
            que.push_back(value);

        }
        // 查询当前队列里的最大值 直接返回队列前端也就是front就可以了。
        int front() {
            return que.front();
        }
    };
};