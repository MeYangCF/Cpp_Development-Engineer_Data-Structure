/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2024 24-12-17 下午3:10
@description:
*/

#include <iostream>
using namespace std;

void Merge(int arr[], int l, int m, int r, int* p){
    int idx = 0;
    int i = l;
    int j = m + 1;
    while (i <= m && j <= r){
        if(arr[i] <= arr[j])
            p[idx++] = arr[i++];
        else
            p[idx++] = arr[j++];
    }
    while (i <= m)
        p[idx++] = arr[i++];

    while (j <= r)
        p[idx++] = arr[j++];

    for (i = l, j = 0; i <= r; i++, j++)
        arr[i] = p[j];
}

void MergeSort(int arr[], int begin, int end, int* p){
    if(begin >= end)
        return;
    int mid = (begin + end) / 2;
    MergeSort(arr, begin, mid, p);
    MergeSort(arr, mid + 1, end, p);
    Merge(arr, begin, mid, end, p);
}

void MergeSort(int arr[], int size){
    int* p = new int[size];
    MergeSort(arr, 0, size - 1, p);
    delete[]p;
}

int main(){
    int arr[10];
    srand(time(nullptr));

    for (int & i : arr)
    {
        i = rand() % 100 + 1;
    }

    for (int v : arr)
    {
        cout << v << " ";
    }
    cout << endl;

    MergeSort(arr, 10);

    for (int v : arr)
    {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}