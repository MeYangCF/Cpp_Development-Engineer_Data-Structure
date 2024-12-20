/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2024 24-12-20 上午10:08
@description:
*/

# include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <stdlib.h>
#include <time.h>
#include <string>
using namespace std;


int main(){
    string src = "jjhfgiyuhrtytrs";

    unordered_map<int, int> m;
    for(char ch : src){
        m[ch]++;
    }

    for(char ch : src){
        if(m[ch] == 1){
            cout << "第一个没有重复出现过的字符是:" << ch << endl;
            return 0;
        }
    }

    cout << "所有字符都有重复出现过!" << endl;
    return 0;
}

/*
int main(){
    vector<int> vec;

    srand(time(nullptr));

    for(int i = 0; i < 1000; i++){
        vec.push_back(rand() % 10000);
    }

    // 找第一个出现重复的数字
    // 找所有重复出现的数字unordered_multiset
    unordered_set<int> s1;
    for(auto key : vec){
        auto it = s1.find(key);
        if(it == s1.end())
            s1.insert(key);
        else{
            cout << "key:" << key << endl;
            break;
        }
    }

    // 统计重复数字以及出现的次数
    unordered_map<int, int> m1;
    for(int key : vec){
//        auto it = m1.find(key);
//        if(it == m1.end())
//            m1.emplace(key, 1);
//        else
//            it->second += 1;
        m1[key]++; // 简便操作
    }
    for(auto pair : m1){
        if(pair.second > 1){
            cout << "key:" << pair.first << " cnt:"
                 << pair.second << endl;
        }
    }

    // 一组数据有些数字是重复的，把重复的数字过滤掉，每个数字只出现一次
    unordered_set<int> s2;
    for(auto key : vec)
        s2.emplace(key);
    return 0;
}
*/