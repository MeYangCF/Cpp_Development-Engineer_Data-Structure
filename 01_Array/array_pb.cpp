/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2024 24-12-5 下午7:19
@description:
*/


#include <iostream>
#include <vector>
using namespace std;

//逆序字符串
void Reverse(char arr[], int size){
    char *p = arr;
    char *q = arr + size - 1;

    while (p < q){
        char ch = *p;
        *p = *q;
        *q = ch;
        p++;
        q--;
    }
}

//奇偶数调整问题
void AdjustArray(int arr[], int size){
    int *p = arr;
    int *q = arr + size -1;

    while (p < q){
        while(p < q && (*p & 0x1) != 0)
            p++;

        while(p < q && (*q & 0x1) == 0)
            q--;

        int tmp = *p;
        *p = *q;
        *q = tmp;
        p++;
        q--;
    }
}

//移除元素问题
int removeElement(vector<int>& nums, int val){
    int slowindex = 0;

    for(int fastindex = 0; fastindex < nums.size(); fastindex++){
        if(nums[fastindex] != val)
            nums[slowindex++] = nums[fastindex];
    }

    return slowindex;
}

//二分查找
int search(vector<int>& nums, int target){
    int left = 0;
    int right = nums.size() - 1;

    while(left <= right){
        int index = (left + right)/2;

        if(nums[index] < target)
            left = index + 1;
        else if (nums[index] > target)
            right = index - 1;
        else
            return index;
    }
    return -1;
}


//有序数组的平方
vector<int> sortedSquares(vector<int>& nums){
    vector<int> results(nums.size());
    int i = 0;
    int j = nums.size() - 1;
    int k = nums.size() - 1;

    while (i <= j){
        if(nums[i] * nums[i] <= nums[j] * nums[j]){
            results[k--] = nums[j] * nums[j];
            j--;
        }else{
            results[k--] = nums[i] * nums[i];
            i++;
        }
    }

    return results;
}

//长度最小的子数组
int minSubArrayLen(int target, vector<int>& nums){
    int sum = 0;
    int result = INT_MAX;
    int sublength = 0;
    int i = 0;

    for(int j = 0; j < nums.size(); j++){
        sum += nums[j];

        while(sum >= target){
            sublength = j - i + 1;
            result = result < sublength ? result : sublength;
            sum -= nums[i++];
        }
    }

    if(result == INT_MAX){
        result = 0;
    }

    return result;
}
