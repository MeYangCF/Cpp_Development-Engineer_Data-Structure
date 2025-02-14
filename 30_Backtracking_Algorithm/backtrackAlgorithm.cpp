/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-02-13 下午3:38
@description:
*/

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// void func(int arr[], int i, int length, int x[]) {
//     if (i == length) {
//         for (int j = 0; j < length; ++j) {
//             if (x[j] == 1) {
//                 cout << arr[j] << " ";
//             }
//         }
//         cout << endl;
//     } else {
//         x[i] = 1;
//         func(arr, i + 1, length, x);
//
//         x[i] = 0;
//         func(arr, i + 1, length, x);
//     }
// }
//
// int main() {
//     int arr[] = {1, 2, 3};
//     int length = sizeof(arr)/sizeof(arr[0]);
//
//     int x[3] = {0};
//     func(arr, 0, length, x);
//     return 0;
// }

//整数选择问题
// int arr[] = {12, 6, 7, 11, 16, 3, 8};
// const int length = sizeof(arr)/sizeof(arr[0]);
// vector<int> x;
// vector<int> bestx;
// unsigned int rmin = 0xFFFFFFFF;
// int sum = 0;
// int r = 0;
//
// void func(int i)
// {
//     if (i == length)
//     {
//         int result = abs(sum - r);
//         if (result < rmin)
//         {
//             rmin = result;
//             bestx = x;
//         }
//     }
//     else
//     {
//         r -= arr[i];
//         sum += arr[i];
//         x.push_back(arr[i]);
//         func(i + 1);
//
//         r += arr[i];
//         sum -= arr[i];
//         x.pop_back();
//         func(i + 1);
//     }
// }
//
// int main()
// {
//     for (int v : arr)
//     {
//         r += v;
//     }
//     func(0);
//     for (int v : bestx)
//     {
//         cout << v << " ";
//     }
//     cout << endl;
//     cout << "min:" << rmin << endl;
//     return 0;
// }

//2N整数选择问题
// int arr[] = {12, 6, 7, 11, 16, 3, 8, 4};
// const int length = sizeof(arr)/sizeof(arr[0]);
// vector<int> x;
// vector<int> bestx;
// int sum = 0;
// int r = 0;
// unsigned int minval = 0xFFFFFFFF;
// int leftcnt = length;
// int cnt = 0;
//
// void func(int i) {
//     if (i == length) {
//         cnt ++;
//         if (x.size() != length / 2) {
//             return;
//         }
//
//         int result = abs(sum - r);
//         if (result < minval) {
//             minval = result;
//             bestx = x;
//         }
//     } else {
//         leftcnt --;
//
//         if (x.size() < length / 2) {
//             sum += arr[i];
//             x.push_back(arr[i]);
//             r -= arr[i];
//             func(i + 1);
//             sum -= arr[i];
//             x.pop_back();
//             r += arr[i];
//         }
//
//         if (x.size() + leftcnt >= length / 2) {
//             func(i + 1);
//         }
//
//         leftcnt ++;
//     }
// }
//
// int main() {
//     for (const int v : arr) {
//         r += v;
//     }
//
//     func(0);
//     for (const int v : bestx) {
//         cout << v << " ";
//     }
//
//     cout << endl;
//     cout << "min:" << minval << endl;
//     cout << "cnt:" << cnt << endl;
//     return 0;
// }

//挑数字问题
// int arr[] = { 4,8,12,16,7,9,3 };
// const int length = sizeof(arr) / sizeof(arr[0]);
// int number = 18;
// vector<int> x;
// int sum = 0;
// int r = 0;
//
// void func(int i) {
//     if (i == length) {
//         if ( sum != number) {
//             return;
//         }
//
//         for (int v : x) {
//             cout << v << " ";
//         }
//         cout << endl;
//     } else {
//         r -= arr[i];
//         if (sum + arr[i] <= number) {
//             sum += arr[i];
//             x.push_back(arr[i]);
//             func(i + 1);
//             sum -= arr[i];
//             x.pop_back();
//         }
//
//         if (sum + r >= number) {
//             func(i + 1);
//         }
//
//         r += arr[i];
//     }
// }
//
// int main() {
//     for (const int v : arr) {
//         r += v;
//     }
//     func(0);
//     return 0;
// }

// int arr[] = {4, 8, 12, 16, 7, 9, 3, 3};
// const int length = sizeof(arr) / sizeof(arr[0]);
// int number = 18;
// vector<int> vec;
//
// void func(int i, int number) {
//     if (number == 0) {
//         for (int v : vec) {
//             cout << v << " ";
//         }
//         cout << endl;
//     } else {
//         for (int k = i; k < length; ++k) {
//             if (number >= arr[k]) {
//                 vec.push_back(arr[k]);
//                 func(k + 1, number - arr[k]);
//                 vec.pop_back();
//             }
//         }
//     }
// }
//
// int main() {
//     func(0, number);
//     return 0;
// }

//0-1背包问题
// int w[] = { 12,5,8,9,6 };
// int v[] = { 9,2,4,7,8 };
// const int length = sizeof(w) / sizeof(w[0]);
// vector<int> x;
// vector<int> bestx;
// int c = 20;
// int cw = 0;
// int cv = 0;
// int bestv = 0;
// int r = 0;
//
// void func(int i) {
//     if (i == length) {
//         if (bestv < cv) {
//             bestv = cv;
//             bestx = x;
//         }
//     } else {
//         r -= v[i];
//         if (cw + w[i] <= c) {
//             cw += w[i];
//             cv += v[i];
//             x.push_back(w[i]);
//             func(i + 1);
//             cw -= w[i];
//             cv -= v[i];
//             x.pop_back();
//         }
//
//         if (cv + r > bestv) {
//             func(i + 1);
//         }
//
//         r += v[i];
//     }
// }
//
// int main() {
//     for (int val : v) {
//         r += val;
//     }
//
//     func(0);
//     for (int w : bestx) {
//         cout << w << " ";
//     }
//
//     cout << endl;
//     cout << "bestv:" << bestv << endl;
//     return 0;
//     return 0;
// }

// 排列树
// void swap(int arr[], int i, int j) {
//     int tmp = arr[i];
//     arr[i] = arr[j];
//     arr[j] = tmp;
// }
//
// void func(int arr[], int i, int length) {
//     if (i == length) {
//         for (int j = 0; j < length; ++j) {
//             cout << arr[j] << " ";
//         }
//
//         cout << endl;
//     } else {
//         for (int k = i; k < length; ++k) {
//             swap(arr, i, k);
//             func(arr, i + 1, length);
//             swap(arr, i ,k);
//         }
//     }
// }
//
// int main() {
//     int arr[] = {1, 2, 3, 4};
//     int length = sizeof(arr) / sizeof(arr[0]);
//     func(arr, 0, length);
//     return 0;
// }

//八皇后问题
// int cnt = 0;
// void swap(int arr[], int i, int j) {
//     int temp = arr[i];
//     arr[i] = arr[j];
//     arr[j] = temp;
// }
//
// bool judge(int arr[], int i) {
//     for (int j = 0; j < i; ++j) {
//         if (i == j || arr[i] == arr[j] || abs(i - j ) == abs(arr[i] - arr[j])) {
//             return false;
//         }
//     }
//
//     return true;
// }
//
// void func(int arr[], int i, int length) {
//     if (i == length) {
//         cnt++;
//         for (int j = 0; j < length; ++j) {
//             cout << arr[j] << " ";
//         }
//
//         cout << endl;
//     } else {
//         for (int k = i;  k < length; ++k) {
//             swap(arr, i, k);
//
//             if (judge(arr, i)) {
//                 func(arr, i + 1, length);
//             }
//
//             swap(arr, i, k);
//         }
//     }
// }
//
// int main() {
//     int ar[] = { 1,2,3,4,5,6,7,8 };
//     int n = 8;
//     func(ar, 0, n);
//     cout << "cnt:" << cnt << endl;
//     return 0;
//     return 0;
// }

//另一种全排列代码

int ar[] = {1, 2, 3};
const int N = 3;
bool state[N];
vector<int> vec;

void func(int i) {
    if (i == N) {
        for (int v : vec) {
            cout << v << " ";
        }

        cout << endl;
    } else {
        for (int k = 0 ; k < N; k++) {
            if (!state[k]) {
                state[k] = true;
                vec.push_back(ar[k]);
                func(i + 1);
                vec.pop_back();
                state[k] = false;
            }
        }
    }
}

int main() {
    func(0);
    return 0;
}