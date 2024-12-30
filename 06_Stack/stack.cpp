/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2024 24-12-10 下午9:10
@description:
*/

#include <iostream>
using namespace std;

class SeqStack{
public:
    SeqStack(int size = 10)
        : mtop(0)
        , mcap(size) {
        mpStack = new int[mcap];
    }

    ~SeqStack() {
        delete[] mpStack;
        mpStack = nullptr;
    }

public:
    void push(int val) {
        if(mtop == mcap)
            expand(2 * mcap);

        mpStack[mtop++] = val;
    }

    void pop() {
        if(mtop == 0)
            throw "stack is empty";

        mtop--;
    }

    int top() const {
        if(mtop == 0)
            throw "stack is empty";

        return mpStack[mtop - 1];
    }

    bool empty() {
        return mtop == 0;
    }

    int size() const {
        return mtop;
    }

private:
    int *mpStack;
    int mtop;
    int mcap;

private:
    void expand(int size) {
        int *p = new int[size];
        memcpy(p, mpStack, mtop * sizeof(int));
        delete[] mpStack;
        mpStack = p;
        mcap = size;
    }
};

int main() {
    int arr[] = { 12,4,56,7,89,31,53,75 };
    SeqStack s;

    for (int v : arr)
        s.push(v);

    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }

    cout << endl;
    return 0;
}