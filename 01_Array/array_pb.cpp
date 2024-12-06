/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2024 24-12-5 下午7:19
@description:
*/

//逆序字符串
/*
#include <iostream>
#include <string.h>
using namespace std;

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

int main(){
    char arr[] = "Hello world!";
    Reverse(arr, strlen(arr));
    cout << arr << endl;
    return 0;
}
*/

//奇偶数调整问题
/*
#include <iostream>
#include <time.h>
using namespace std;

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

int main(){
    int arr[10] = {0};
    srand(time(0));
    for(int i = 0; i < 10; i++){
        arr[i] = rand() % 100;
    }

    for(int v : arr)
        cout << v << " ";
    cout << endl;

    AdjustArray(arr, 10);

    for(int v : arr)
        cout << v << " ";
    cout << endl;

    return 0;
}
*/

//移除元素问题
/*
#include <iostream>
#include <vector>
using namespace std;

int removeElement(vector<int>& nums, int val) {
    int slowindex = 0;
    for(int fastindex = 0; fastindex < nums.size(); fastindex++){
        if(nums[fastindex] != val)
            nums[slowindex++] = nums[fastindex];
    }
    return slowindex;
}

int main(){
    vector<int>nums {2};
    int len = removeElement(nums, 3);
    cout << len << endl;
    for(int v : nums)
        cout << v << " ";
    cout << endl;
    return 0;
}
*/

//二分查找
/*
#include <iostream>
#include <vector>
using namespace std;

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

int main(){
    vector<int> nums{-1,0,3,5,9,12};
    int index = search(nums, 2);
    cout << index << endl;
}
*/

//有序数组的平方
/*
#include <iostream>
#include <vector>
using namespace std;

vector<int> sortedSquares(vector<int>& nums) {
    vector<int> results(nums.size());
    int i = 0;
    int j = nums.size() - 1;
    int k = nums.size() - 1;
    while (i <= j){
        if(nums[i] * nums[i] <= nums[j] * nums[j]){
            results[k--] = nums[j] * nums[j];
            j--;
        }
        else{
            results[k--] = nums[i] * nums[i];
            i++;
        }
    }
    return results;
}

int main(){
    vector<int> nums{-7,-3,2,3,11};
    nums = sortedSquares(nums);
    for(int i = 0; i < nums.size(); i++)
        cout << nums[i] << " ";
}
*/

//长度最小的子数组
/*
#include <iostream>
#include <vector>
using namespace std;

int minSubArrayLen(int target, vector<int>& nums) {
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

int main(){
    vector<int> nums{2,3,1,2,4,3};
    int result = minSubArrayLen(7, nums);
    cout << result << endl;
}
*/