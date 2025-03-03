/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-03-03 ÉÏÎç10:26
@description:
*/
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
