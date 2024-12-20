/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2024 24-12-20 上午11:31
@description:
*/

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <memory>
using namespace std;

int main(){
    vector<int> vec{12, 78, 90, 78, 123, 8, 9, 90};

    int max = vec[0];
    for(int i = 1; i < vec.size(); i++)
        if(vec[i] > max)
            max = vec[i];

    int* bitmap = new int[max / 32 + 1]();
    unique_ptr<int> ptr(bitmap);

    for(auto key : vec){
        int index = key / 32;
        int offset = key % 32;

        if(0 == (bitmap[index] & (1 << offset)))
            bitmap[index] |= (1 << offset);
        else
            cout << key << "重复出现过!" << endl;
    }
    return 0;
}