/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-03-04 …œŒÁ10:57
@description:
*/

#include <iostream>
#include <vector>
using namespace std;

// √∞≈›≈≈–Ú
void BubbleSort(vector<int> &nums) {
    for (int i = 0; i < nums.size() - 1; i++) {
        bool flag = false;
        for (int j = 0; j < nums.size() - 1 - i; j++) {
            if (nums[j] > nums[j + 1]) {
                const int tmp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = tmp;
                flag = true;
            }
        }
        if (!flag)
            return;
    }
}

// —°‘Ò≈≈–Ú
void ChoiceSort(vector<int> &nums) {
    for (int i = 0; i < nums.size() - 1; i++) {
        int min = nums[i];
        int k = i;
        for (int j = i + 1; j < nums.size(); j++) {
            if (nums[j] < min) {
                min = nums[j];
                k = j;
            }
        }
        if (k != i) {
            const int tmp = nums[i];
            nums[i] = nums[k];
            nums[k] = tmp;
        }
    }
}

// ≤Â»Î≈≈–Ú
void InsertSort(vector<int> &nums) {
    for (int i = 1; i < nums.size(); i++) {
        int val = nums[i];
        int j = i - 1;
        for (; j >= 0; j--) {
            if (nums[j] <= val) {
                break;
            }
            nums[j + 1] = nums[j];
        }
        nums[j + 1] = val;
    }
}

//œ£∂˚≈≈–Ú
void shellSort(vector<int> &nums) {
    for (int gap = nums.size() / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < nums.size(); i++) {
            int val = nums[i];
            int j = i - gap;
            for (; j >= 0; j -= gap) {
                if (nums[j] <= val) {
                    break;;
                }
                nums[j + gap] = nums[j];
            }
            nums[j + gap] = val;
        }
    }
}
