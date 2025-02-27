/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-02-26 ÏÂÎç8:48
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