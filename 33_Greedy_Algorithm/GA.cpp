/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-02-18 上午10:23
@description:
*/

#include <iostream>
#include <algorithm>
using namespace std;

//硬币选择问题
int main() {
    int arr[] = {1, 3, 5};
    int length = sizeof(arr) / sizeof(arr[0]);
    int c = 11;

    sort(arr, arr + length, [](int a, int b)->bool{return a > b;});

    int idx = 0;
    int cnt = 0;
    while (c > 0) {
        if (c >= arr[idx]) {
            c -= arr[idx];
            cnt++;
        }
        else {
            idx++;
        }
    }

    cout << cnt << endl;
    return 0;
}