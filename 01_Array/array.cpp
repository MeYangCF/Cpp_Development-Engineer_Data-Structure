//
// Created by 杨成峰 on 24-12-4.
//
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

//数组实现
class Array {
public:
    Array(int size = 10);
    ~Array();
    //末尾增加元素
    void push_back(int val);
    //末尾删除元素
    void pop_back();
    //按位置增加元素
    void insert(int pos, int val);
    //按位置删除
    void erase(int pos);
    //元素查询
    int find(int val);
    //输出数组元素
    void show();
private:
    int *mpArr;//指向可扩容数组的内存
    int mCap;//数组的容量
    int mCur;//数组的有效元素个数
    //内部数组扩容接口
    void expand(int size);
};

Array::Array(int size) :mCap(size),mCur(0){
    mpArr = new int[mCap];
}

Array::~Array() {
    delete []mpArr;
    mpArr = nullptr;
}

void Array::push_back(int val) {
    if (mCur == mCap)
        expand(2 * mCap);
    mpArr[mCur++] = val;
}

void Array::pop_back() {
    if (mCur == 0)
        return;
    mCur--;
}

void Array::insert(int pos, int val) {
    if (pos < 0 || pos > mCur)
        return;;
    if (mCur == mCap)
        expand(2 * mCap);
    for (int i = mCur - 1; i >= pos; i--)
        mpArr[i + 1] = mpArr[i];
    mpArr[pos] = val;
    mCur++;
}

void Array::erase(int pos) {
    if (pos < 0 || pos > mCur -1)
        return;
    for (int i = pos + 1; i < mCur; i++)
        mpArr[i - 1] = mpArr[i];
    mCur--;
}

int Array::find(int val) {
    for (int i = 0; i < mCur; i++)
        if (mpArr[i] == val)
            return i;
    return -1;
}

void Array::show() {
    for (int i = 0; i < mCur; i++)
        cout << mpArr[i] << " ";
    cout << endl;
}


void Array::expand(int size) {
    int *p = new int[size];
    memcpy(p, mpArr, sizeof(int) * mCap);
    delete []mpArr;
    mpArr = p;
    mCap = size;
}


int main() {
    Array arr;
    srand(time(0));
    for (int i = 0; i < 10; i++)
        arr.push_back(rand() % 100);

    arr.show();

    arr.pop_back();
    arr.show();

    arr.insert(0, 100);
    arr.show();

    arr.insert(10, 200);
    arr.show();

    int pos = arr.find(100);
    if (pos != -1) {
        arr.erase(pos);
        arr.show();
    }
    return 0;
}