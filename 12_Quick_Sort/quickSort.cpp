/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2024 24-12-16 下午4:52
@description:
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int Partation(int arr[], int l, int r){
    // 优化2：选择基准数的优化，“三数取中”法   arr[l]   arr[r]   arr[(l+r)/2]
    int val = arr[l];

    while (l < r){
        while (l < r && arr[r] > val)
            r--;
        if(l < r){
            arr[l] = arr[r];
            l++;
        }
        while (l < r && arr[l] < val)
            l++;
        if (l < r){
            arr[r] = arr[l];
            r--;
        }
    }
    arr[l] = val;
    return l;
}

void QuickSort(int arr[], int begin, int end){
    if(begin >= end)
        return;
//    优化1：当[begin, end]序列元素个数小到指定数量，采用插入排序
//    if(end - begin <= 50){
//        InsertSort(arr, begin, end);
//        return;
//    }
    int pos = Partation(arr, begin, end);

    QuickSort(arr, begin, pos - 1);
    QuickSort(arr, pos + 1, end);
}

void QuickSort(int arr[], int size){
    return QuickSort(arr, 0, size - 1);
}

int main(){
    int arr[10];
    srand(time(NULL));

    for (int i = 0; i < 10; i++)
    {
        arr[i] = rand() % 100 + 1;
    }

    for (int v : arr)
    {
        cout << v << " ";
    }
    cout << endl;

    QuickSort(arr, 10);

    for (int v : arr)
    {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}