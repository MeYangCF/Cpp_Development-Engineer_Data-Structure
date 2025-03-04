/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-03-04 ÏÂÎç8:13
@description:
*/
#include <iostream>
#include <vector>
using namespace std;

void Merge(vector<int>& nums, int l, int m, int r, vector<int>& ass) {
    int idx = 0;
    int i = l;
    int j = m + 1;
    while (i <= m && j <= r) {
        if (nums[i] <= nums[j]) {
            ass[idx++] = nums[i++];
        }
        else {
            ass[idx++] = nums[j++];
        }
    }
    while (i <= m) {
        ass[idx++] = nums[i++];
    }
    while (j <= r) {
        ass[idx++] = nums[j++];
    }
    for (i = l, j = 0; i <= r; i++, j++) {
        nums[i] = ass[j];
    }
}

void MergeSort(vector<int>& nums, int begin, int end, vector<int>& ass) {
    if (begin >= end) {
        return;
    }
    int mid = begin + (end - begin) / 2;
    MergeSort(nums, begin, mid, ass);
    MergeSort(nums, mid + 1, end, ass);
    Merge(nums, begin, mid, end, ass);
}

void MergeSort(vector<int>& nums, int size) {
    vector<int> ass(size);
    MergeSort(nums, 0, nums.size() - 1, ass);
}