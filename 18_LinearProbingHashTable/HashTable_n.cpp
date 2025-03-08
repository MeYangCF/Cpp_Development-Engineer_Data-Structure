/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-03-08 下午4:29
@description:
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
    // 242.有效的字母异位词
    bool isAnagram(string s, string t) {
        unordered_map<char, int>strHash_s;
        unordered_map<char, int>strHash_t;
        for (int i = 0; i < static_cast<int>(s.size()); i++) {
            strHash_s[s[i]]++;
        }
        for (int i = 0; i < static_cast<int>(t.size()); i++) {
            strHash_t[t[i]]++;
        }
        return strHash_s == strHash_t;
    }

public:
    // 349. 两个数组的交集
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> tmpSet;
        for (int i = 0; i < nums1.size(); i++) {
            tmpSet.insert(nums1[i]);
        }
        vector<int> result;
        sort(nums2.begin(), nums2.end());
        nums2.erase(unique(nums2.begin(), nums2.end()), nums2.end());
        for (int i = 0; i < nums2.size(); i++) {
            if (tmpSet.find(nums2[i]) != tmpSet.end()) {
                result.push_back(nums2[i]);
            }
        }
        return result;
    }

public:
    // 202.快乐数
    bool isHappy(int n) {

    }
};