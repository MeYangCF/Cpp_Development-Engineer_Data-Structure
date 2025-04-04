/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-03-05 обнГ4:34
@description:
*/
#include <functional>
#include <iostream>
using namespace std;

class PriorityQueue {
public:
    using Comp = function<bool(int, int)>;
    PriorityQueue(int cap = 20, Comp comp = less<int>())
        : size_(0)
        , cap_(cap)
        , comp_(comp) {
        que_ = new int[cap_];
    }

    PriorityQueue(Comp comp)
        : size_(0)
        , cap_(20)
        , comp_(comp) {
        que_ = new int[cap_];
    }

    ~PriorityQueue() {
        delete[] que_;
        que_ = nullptr;
    }

public:
    void push(int val) {
        if (size_ == cap_) {
            int* p = new int[2 * cap_];
            memcpy(p, que_, cap_ * sizeof( int));
            delete[] que_;
            que_ = p;
            cap_ *= 2;
        }

        if (size_ == 0) {
            que_[size_] = val;
        }
        else {
            sifUp(size_, val);
        }
        size_++;
    }

    void pop() {
        if (size_ == 0) {
            throw "container is empty!";
        }
        size_--;
        if (size_ > 0) {
            sifDown(0, que_[size_]);
        }
    }

    bool empty() const {
        return size_ == 0;
    }

    int top() const {
        if (size_ == 0) {
            throw "container is empty!";
        }
        return que_[0];
    }

    int size() const {
        return size_;
    }

private:
    void sifUp(int i, int val) {
        while (i > 0) {
            int father = (i - 1) / 2;
            if (comp_(val, que_[father])) {
                que_[i] = que_[father];
                i = father;
            }
            else {
                break;
            }
        }
        que_[i] = val;
    }

    void sifDown(int i, int val) {
        while (i < size_ / 2) {
            int child = 2 * i + 1;
            if (child + 1 < size_ && comp_(que_[child + 1], que_[child])) {
                child = child + 1;
            }
            if (comp_(que_[child], val)) {
                que_[i] = que_[child];
                i = child;
            }
            else {
                break;;
            }
        }
        que_[i] = val;
    }

private:
    int* que_;
    int size_;
    int cap_;
    Comp comp_;
};