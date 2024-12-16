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

void QuickSort(int arr[], int size){

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