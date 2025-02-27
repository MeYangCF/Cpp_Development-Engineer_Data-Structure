/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-02-26 下午8:48
@description:
*/

/*
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

class Array {
public:
    Array(int size = 10)
        : mCap(size)
        , mCur(0) {
        mpArr = new int[size];
    }

    ~Array() {
        delete[] mpArr;
        mpArr = nullptr;
    }
public:
    void push_back(int val) {
        if (mCur == mCap) {
            expand(2 * mCap);
        }
        mpArr[mCur++] = val;
    }

    void pop_back() {
        if (mCur == 0) {
            return;
        }
        mCur--;
    }

    void insert(int pos, int val) {
        if (pos < 0 || pos > mCur) {
            return;
        }
        if (mCur == mCap) {
            expand(2 * mCap);
        }
        for (int i = mCur - 1; i > pos; --i) {
            mpArr[i + 1] = mpArr[i];
        }
        mpArr[pos] = val;
        mCur++;
    }

    void erase(int pos) {
        if (pos < 0 || pos > mCur) {
            return;
        }
        for (int i = pos + 1; i < mCur; ++i) {
            mpArr[i - 1] = mpArr[i];
        }
        mCur--;
    }

    int find(int val) const {
        for (int i = 0; i < mCur; ++i) {
            if (mpArr[i] == val) {
                return i;
            }
        }
        return -1;
    }

private:
    void expand(int size) {
        int* p = new int[size];
        memcpy(p, mpArr, size * sizeof(int));
        delete[] mpArr;
        mpArr = p;
        mCur = size;
    }

private:
    int* mpArr;
    int mCap;
    int mCur;
};
*/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// 704.二分查找
int search(vector<int>& nums, int target) {
    int l = 0;
    int r = nums.size() - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (nums[mid] == target) {
            return mid;
        }
        else if (nums[mid] < target) {
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
    return -1;
}

// 35.搜索插入位置
int searchInsert(vector<int>& nums, int target) {
    int l = 0, r = nums.size() - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (nums[mid] == target) {
            return mid;
        }
        else if (nums[mid] < target) {
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
    return l;
}

//34.在排序数组中查找元素的第一个和最后一个位置
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int rightBorder = getRightBorder(nums, target);
        int leftBorder = getleftBorder(nums, target);

        if (rightBorder == -2 || leftBorder == -2) {
            return {-1, -1};
        }
        if (rightBorder - leftBorder > 1) {
            return {leftBorder + 1, rightBorder - 1};
        }
        return {-1, -1};
    }

private:
    int getRightBorder(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        int rightBorder = -2;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] > target) {
                right = mid - 1;
            }
            else {
                left = mid + 1;
                rightBorder = left;
            }
        }
        return rightBorder;
    }
    
    int getleftBorder(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        int leftBorder = -2;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] >= target) {
                right = mid - 1;
                leftBorder = right;
            }
            else {
                left = mid + 1;
            }
        }
        return leftBorder;
    }
};

// 27.移除元素
int removeElement(vector<int>& nums, int val) {
    int fastPtr = 0;
    int slowPtr = 0;
    for (; fastPtr < nums.size(); ++fastPtr) {
        if (nums[fastPtr] != val) {
            nums[slowPtr++] = nums[fastPtr];
        }
    }
    return slowPtr;
}

// 977.有序数组的平方
vector<int> sortedSquares(vector<int>& nums) {
    vector<int> result;
    int left = 0;
    int right = nums.size() - 1;
    while (left <= right) {
        int leftValue = nums[left] * nums[left];
        int rightValue = nums[right] * nums[right];
        if (leftValue >= rightValue) {
            result.push_back(leftValue);
            left++;
        }
        else {
            result.push_back(rightValue);
            right--;
        }
    }
    reverse(result.begin(), result.end());
    return result;
}

// 209.长度最小的子数组
int minSubArrayLen(int target, vector<int>& nums) {
    int i = 0;
    int j = 0;
    int sum = 0;
    int result = INT_MAX;
    for (; i < nums.size(); ++i) {
        sum += nums[i];
        while (sum >= target) {
            result = min(result, i - j + 1);
            sum -= nums[j++];
        }
    }
    return result == INT_MAX ? 0 : result;
}

// 59.螺旋矩阵Ⅱ
vector<vector<int>> generateMatrix(int n) {
    vector<vector<int>> result(n, vector<int>(n, 0));
    int startx = 0, starty = 0;
    int end = 1;
    int count = 1;
    int loop = n / 2;
    while (loop --) {
        int i = startx;
        int j = starty;
        for (; j < n - end; ++j) {
            result[i][j] = count++;
        }
        for (; i < n - end; ++i) {
            result[i][j] = count++;
        }
        for (; j > starty; --j) {
            result[i][j] = count++;
        }
        for (; i > startx; --i) {
            result[i][j] = count++;
        }
        startx++;
        starty++;

        end++;
    }
    if (n % 2 != 0) {
        result[n / 2][n / 2] = count;
    }
    return result;
}