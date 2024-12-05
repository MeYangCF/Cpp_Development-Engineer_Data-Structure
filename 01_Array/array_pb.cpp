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
#include <iostream>
#include <vector>

using namespace std;

int removeElement(vector<int>& nums, int val) {
    int i = 0;
    int j = nums.size() - 1;
    while (i <= j){
        if(nums[j] == val){
            j--;
            continue;
        }
        if( nums[i] == val){
            nums[i] = nums[j];
            j--;
        }
        i++;
    }
    return i;
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