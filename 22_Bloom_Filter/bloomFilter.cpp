/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2024 24-12-20 下午3:22
@description:
*/

#include <iostream>
#include <vector>
#include "stringhash.h"
#include <string>
using namespace std;

class BloomFilter{
public:
    BloomFilter(int bitSize = 1471)
        : bitSize_(bitSize){
        bitMap_.resize(bitSize / 32 + 1);
    }

public:
    void setBit(const char* str){
        int idx1 = BKDRHash(str) % bitSize_;
        int idx2 = RSHash(str) % bitSize_;
        int idx3 = APHash(str) % bitSize_;

        int index = 0;
        int offset = 0;

        index = idx1 / 32;
        offset = idx1 % 32;
        bitMap_[index] |= (1 << offset);

        index = idx2 / 32;
        offset = idx2 % 32;
        bitMap_[index] |= (1 << offset);

        index = idx3 / 32;
        offset = idx3 % 32;
        bitMap_[index] |= (1 << offset);
    }

    bool getBit(const char* str){
        int idx1 = BKDRHash(str) % bitSize_;
        int idx2 = RSHash(str) % bitSize_;
        int idx3 = APHash(str) % bitSize_;

        int index = 0;
        int offset = 0;

        index = idx1 / 32;
        offset = idx1 % 32;
        if (0 == (bitMap_[index] & (1 << offset)))
            return false;

        index = idx2 / 32;
        offset = idx2 % 32;
        if (0 == (bitMap_[index] & (1 << offset)))
            return false;

        index = idx3 / 32;
        offset = idx3 % 32;
        if (0 == (bitMap_[index] & (1 << offset)))
            return false;

        return true;
    }

private:
    int bitSize_;
    vector<int> bitMap_;
};

class BlackList{
public:
    void add(string url){
        blackList_.setBit(url.c_str());
    }
    bool query(string url){
        return blackList_.getBit(url.c_str());
    }
private:
    BloomFilter blackList_;
};
int main(){
    BlackList list;
    list.add("http://www.baidu.com");
    list.add("http://www.360buy.com");
    list.add("http://www.tmall.com");
    list.add("http://www.tencent.com");

    string url = "http://www.alibaba.com";
    cout << list.query(url) << endl;
    return 0;
}