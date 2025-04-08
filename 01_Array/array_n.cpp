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
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
using namespace std;


class Solution {
public:
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

public:
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

    // 26.删除有序数组中的重复项
    int removeDuplicates(vector<int>& nums) {
        int i = 0, j = 0;
        int numsSize = nums.size();
        for (; j < nums.size(); j++) {
            if (nums[i] != nums[j]) {
                i++;
                nums[i] = nums[j];
            }
        }
        for (int k = 0; k < numsSize - i - 1; ++k) {
            nums.pop_back();
        }
        return nums.size();
    }

    // 283.移动零
    void moveZeroes(vector<int>& nums) {
        int i = 0, j = 0;
        for (; j < nums.size(); j++) {
            if (nums[j] != 0) {
                nums[i++] = nums[j];
            }
        }
        for (int k = i; k < nums.size(); k++) {
            nums[k] = 0;
        }
    }

public:
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

public:
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

    // 904.水果成篮
    int totalFruit(vector<int>& fruits) {
        int classNum = 0;
        int result = 0;
        unordered_map<int, int> cnt;
        for (int i = 0, j = 0; i < fruits.size(); ++i) {
            if (++cnt[fruits[i]] == 1) {
                classNum++;
            }
            while (classNum > 2) {
                if (--cnt[fruits[j]] == 0) {
                    classNum--;
                }
                j++;
            }
            result = result > i - j + 1 ? result : (i - j + 1);
        }
        return result;
    }

public:
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

    //54.螺旋矩阵
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        int up = 0, down = 0;
        int m = matrix.size();
        int n = matrix[0].size();

        while (up < m && down < n) {
            for (int j = down; j < n; ++j) {
                res.push_back(matrix[up][j]);
            }
            up++;
            for (int i = up; i < m; ++i) {
                res.push_back(matrix[i][n - 1]);
            }
            n--;
            if (up < m) {
                for (int j = n - 1; j >= down; --j) {
                    res.push_back(matrix[m - 1][j]);
                }
                m--;
            }
            if (down < n) {
                for (int i = m - 1; i >= up; --i) {
                    res.push_back(matrix[i][down]);
                }
                down++;
            }
        }
        return res;
    }

public:
    // 1365.有多少小于当前数字的数字
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
        vector<int> result = nums;
        sort(result.begin(), result.end());
        int hash[101];
        for (int i = nums.size() - 1; i >= 0; i--) {
            hash[result[i]] = i;
        }
        for (int i = 0; i < nums.size(); i++) {
            result[i] = hash[nums[i]];
        }
        return result;
    }

public:
    // 941.有效的山脉数组
    bool validMountainArray(vector<int>& arr) {
        if (arr.size() < 3) return false;
        int left = 0;
        int right = arr.size() - 1;
        while (left < arr.size() - 1 && arr[left] < arr[left + 1]) {
            left++;
        }
        while (right > 0 && arr[right] < arr[right - 1]) {
            right--;
        }
        if (left == right && left != 0 && right != arr.size() - 1) {
            return true;
        }
        return false;
    }

    // bool validMountainArray(vector<int>& arr) {
    //     if (arr.size() < 3) {
    //         return false;
    //     }
    //     int max = arr[0];
    //     int maxIndex = 0;
    //     for (int i = 0; i < arr.size(); ++i) {
    //         if (arr[i] > max) {
    //             max = arr[i];
    //             maxIndex = i;
    //         }
    //     }
    // }
    //     if (max != arr[0] && max != arr[arr.size() - 1] &&  0 < maxIndex < arr.size() - 1) {
    //         int flag1 = -1;
    //         int flag2 = -1;
    //         for (int i = 0; i < maxIndex; i++) {
    //             if (arr[i] >= arr[i + 1]) {
    //                 flag1 = 1;
    //             }
    //         }
    //         for (int i = maxIndex; i < arr.size() - 1; i++) {
    //             if (arr[i] <= arr[i + 1]) {
    //                 flag2 = 1;
    //             }
    //         }
    //         if (flag1 == -1 && flag2 == -1) {
    //             return true;
    //         }
    //         else {
    //             return false;
    //         }
    //     }
    //     return false;
    // }

public:
    // 1207.独一无二的出现次数
    bool uniqueOccurrences(vector<int>& arr) {
        unordered_map<int, int> hash;
        unordered_set<int> hash1;
        for (auto i : arr) {
            ++hash[i];
        }
        for (auto& num : hash) {
            hash1.insert(num.second);
        }
        return hash1.size() == hash.size();
    }

public:
    // 189. 旋转数组
    void rotate(vector<int>& nums, int k) {
        k = k % nums.size();
        vector<int> tmp(k);
        for (int i = nums.size() - k, j = 0; i < nums.size(); j++, i++) {
            tmp[j] = nums[i];
        }
        for (int i = nums.size() - k - 1; i >= 0; i--) {
            nums[i + k] = nums[i];
        }
        for (int i = 0; i < k; i++) {
            nums[i] = tmp[i];
        }
    }

public:
    // 724.寻找数组的中心下标
    int pivotIndex(vector<int>& nums) {
        int sum1 = 0;
        vector<int> temp = nums;
        for (int i = 0; i < nums.size(); i++) {
            sum1 += nums[i];
            nums[i] = sum1;
        }
        int sum2 = 0;
        for (int i = nums.size() - 1; i >=0 ; i--) {
            sum2 += temp[i];
            temp[i] = sum2;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == temp[i]) {
                return i;
            }
        }
        return -1;
    }

public:
    // 922. 按奇偶排序数组II
    vector<int> sortArrayByParityII(vector<int>& nums) {
        int i = 0;
        int j = 0;
        while (i < nums.size() && j < nums.size()) {
            while (!(i % 2 != 0 && nums[i] % 2 == 0)) {
                i++;
                if (i > nums.size() - 1) {
                    break;
                }
            }
            while (!(j % 2 == 0 && nums[j] % 2 != 0)) {
                j++;
                if (j > nums.size() - 1) {
                    break;
                }
            }
            if (i > nums.size() - 1 || j > nums.size() - 1) {
                break;
            }
            int tmp = nums[i];
            nums[i] = nums[j];
            nums[j] = tmp;
        }
        return nums;
    }
};

