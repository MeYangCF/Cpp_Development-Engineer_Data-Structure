/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-03-03 ÏÂÎç1:18
@description:
*/

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