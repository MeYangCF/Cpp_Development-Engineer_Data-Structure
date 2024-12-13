/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2024 24-12-13 上午9:17
@description:
*/

#include <iostream>
using namespace std;

//二分查找的递归实现
int BinarySearch(int arr[], int i, int j, int val){
    if (i > j)
        return -1;
    int mid = (i + j) / 2;
    if(arr[mid] == val)
        return mid;
    else if(arr[mid] > val)
        return BinarySearch(arr, i, mid - 1, val);
    else
        return BinarySearch(arr, mid + 1, j, val);

}

//二分查找的非递归实现
//int BinarySearch(int arr[], int size, int val){
//    int left = 0;
//    int right = size - 1;
//    while (left <= right){
//        int mid = (left + right) / 2;
//        if(arr[mid] == val)
//            return mid;
//        else if(arr[mid] > val)
//            right = mid - 1;
//        else
//            left = mid + 1;
//    }
//    return -1;
//}
int main(){
    int arr[] = {12, 25, 34, 39, 45, 57, 63, 78, 82, 96, 100};
    int size = sizeof arr / sizeof arr[0];
    cout << BinarySearch(arr, 0, size - 1, 39) << endl;
    cout << BinarySearch(arr, 0, size - 1, 45) << endl;
    cout << BinarySearch(arr, 0, size - 1, 12) << endl;
    cout << BinarySearch(arr, 0, size - 1, 64) << endl;
    return 0;
}