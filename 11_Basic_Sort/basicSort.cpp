/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2024 24-12-16 下午2:04
@description:
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

//冒泡排序
void BubbleSort(int arr[], int size){
    for (int i = 0; i < size-1; i++){
        bool flag = false;
        for (int j = 0; j < size - 1 - i; j++){
            if (arr[j] > arr[j + 1]){
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                flag = true;
            }
        }
        if (!flag)
            return;
    }
}

//选择排序
void ChoiceSort(int arr[], int size){
    for(int i = 0; i < size - 1; i++){
        int min = arr[i];
        int k = i;
        for(int j = i + 1; j < size; j++){
            if (arr[j] < min)
            {
                min = arr[j];
                k = j;
            }
        }
        if (k != i)
        {
            int tmp = arr[i];
            arr[i] = arr[k];
            arr[k] = tmp;
        }
    }
}

//插入排序
void InsertSort(int arr[], int size){
    for(int i = 1; i < size; i++){
        int val = arr[i];
        int j = i - 1;
        for( ;j >= 0; j--){
            if(arr[j] <= val)
                break;
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = val;
    }
}

//希尔排序
void ShellSort(int arr[], int size){
    for (int gap = size / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < size; i++)
        {
            int val = arr[i];
            int j = i - gap;
            for (;  j >= 0; j -= gap)
            {
                if (arr[j] <= val)
                {
                    break;
                }
                arr[j + gap] = arr[j];
            }
            arr[j + gap] = val;
        }
    }
}

int main(){
    const int COUNT = 100000;
    int* arr = new int[COUNT];
    int* brr = new int[COUNT];
    int* crr = new int[COUNT];
    int* drr = new int[COUNT];

    srand(time(NULL));

    for (int i = 0; i < COUNT; i++)
    {
        int val = rand() % COUNT;
        arr[i] = val;
        brr[i] = val;
        crr[i] = val;
        drr[i] = val;
    }

    clock_t begin, end;

    begin = clock();
    BubbleSort(arr, COUNT);
    end = clock();
    cout << "BubbleSort spend:" << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

    begin = clock();
    ChoiceSort(brr, COUNT);
    end = clock();
    cout << "ChoiceSort spend:" << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

    begin = clock();
    InsertSort(crr, COUNT);
    end = clock();
    cout << "InsertSort spend:" << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

    begin = clock();
    ShellSort(drr, COUNT);
    end = clock();
    cout << "ShellSort spend:" << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

    return 0;
}

//int main()
//{
//    int arr[10];
//    srand(time(NULL));
//
//    for (int i = 0; i < 10; i++)
//    {
//        arr[i] = rand() % 100 + 1;
//    }
//
//    for (int v : arr)
//    {
//        cout << v << " ";
//    }
//    cout << endl;
//
//    ShellSort(arr, 10);
//
//    for (int v : arr)
//    {
//        cout << v << " ";
//    }
//    cout << endl;
//}