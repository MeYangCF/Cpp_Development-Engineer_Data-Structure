/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-03-05 обнГ6:42
@description:
*/
#include <iostream>
#include <vector>
using namespace std;

void siftDown(vector<int>& nums, int i, int size) {
    int val = nums[i];
    while (i < size / 2) {
        int child = 2 * i + 1;
        if (child + 1 < size && nums[child + 1] > nums[child]) {
            child = child + 1;
        }
        if (nums[child] > val) {
            nums[i] = nums[child];
            i = child;
        } else {
            break;
        }
    }
    nums[i] = val;
}

void HeapSort(vector<int>& nums) {
    int n = nums.size() - 1;
    for (int i = (n - 1) / 2; i >= 0; i--) {
        siftDown(nums, i, nums.size());
    }
    for (int i = n; i > 0; i--) {
        int tmp = nums[0];
        nums[0] = nums[i];
        nums[i] = tmp;
        siftDown(nums, 0, i);
    }
}