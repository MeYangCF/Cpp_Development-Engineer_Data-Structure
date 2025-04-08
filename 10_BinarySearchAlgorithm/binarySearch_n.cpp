/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-03-04 ����10:48
@description:
*/
#include <iostream>
using namespace std;

// �ǵݹ�ʵ��
int noBinarySearch(int arr[], int size, int val) {
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int mid = left + (right - left)/2;
        if (arr[mid] == val) {
            return mid;
        }
        else if (arr[mid] > val) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return -1;
}

// �ݹ�ʵ��
int BinarySearch(int arr[], int i, int j, int val) {
    if (i > j) {
        return -1;
    }
    int mid = i + (j - i) / 2;
    if (arr[mid] == val) {
        return mid;
    }
    else if (arr[mid] > val) {
        return BinarySearch(arr, i, mid - 1, val);
    }
    else {
        return BinarySearch(arr, mid + 1, j, val);
    }
}
