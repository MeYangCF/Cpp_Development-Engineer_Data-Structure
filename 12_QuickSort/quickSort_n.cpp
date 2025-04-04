/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-03-04 обнГ2:21
@description:
*/
#include <iostream>
#include <vector>
using namespace std;

int Partation(vector<int>& nums, int l, int r) {
    int val = nums[l];
    while (l < r) {
        while (l < r && nums[r] > val) {
            r--;
        }
        if (l < r) {
            nums[l] = nums[r];
            l++;
        }
        while (l < r && nums[l] < val) {
            l++;
        }
        if (l < r) {
            nums[r] = nums[l];
            r--;
        }
    }
    nums[l] = val;
    return l;
}

void QuickSort(vector<int>& nums, int begin, int end) {
    if (begin >= end) {
        return;
    }
    int pos = Partation(nums, begin, end);
    QuickSort(nums, begin, pos - 1);
    QuickSort(nums, pos + 1, end);
}

void QuickSort(vector<int>& nums) {
    QuickSort(nums, 0, nums.size() - 1);
}