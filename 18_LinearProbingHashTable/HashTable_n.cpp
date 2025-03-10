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
        unordered_set<int> set;
        while(1) {
            int sum = getSum(n);
            if (sum == 1) {
                return true;
            }
            if (set.find(sum) != set.end()) {
                return false;
            } else {
                set.insert(sum);
            }
            n = sum;
        }
    }
private:
    int getSum(int n) {
        int sum = 0;
        while (n) {
            sum += (n % 10) * (n % 10);
            n /= 10;
        }
        return sum;
    }

public:
    // 454.四数相加II
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        unordered_map<int, int> umap; //key:a+b的数值，value:a+b数值出现的次数
        // 遍历大A和大B数组，统计两个数组元素之和，和出现的次数，放到map中
        for (int a : A) {
            for (int b : B) {
                umap[a + b]++;
            }
        }
        int count = 0; // 统计a+b+c+d = 0 出现的次数
        // 再遍历大C和大D数组，找到如果 0-(c+d) 在map中出现过的话，就把map中key对应的value也就是出现次数统计出来。
        for (int c : C) {
            for (int d : D) {
                if (umap.find(0 - (c + d)) != umap.end()) {
                    count += umap[0 - (c + d)];
                }
            }
        }
        return count;
    }

public:
    // 383. 赎金信
    bool canConstruct(string ransomNote, string magazine) {
        unordered_map<char, int> tmpMap;
        for (auto c : magazine) {
            tmpMap[c]++;
        }
        for (int i = 0; i < ransomNote.size(); i++) {
            if (tmpMap[ransomNote[i]] > 0) {
                tmpMap[ransomNote[i]]--;
            }
            else {
                return false;
            }
        }
        return true;
    }

public:
    // 205. 同构字符串
    bool isIsomorphic(string s, string t) {
        unordered_map<char, char> map1;
        unordered_map<char, char> map2;
        for (int i = 0, j = 0; i < s.size(); i++, j++) {
            if (map1.find(s[i]) == map1.end()) { // map1保存s[i] 到 t[j]的映射
                map1[s[i]] = t[j];
            }
            if (map2.find(t[j]) == map2.end()) { // map2保存t[j] 到 s[i]的映射
                map2[t[j]] = s[i];
            }
            // 发现映射 对应不上，立刻返回false
            if (map1[s[i]] != t[j] || map2[t[j]] != s[i]) {
                return false;
            }
        }
        return true;
    }

public:
    // 1002. 查找共用字符
    vector<string> commonChars(vector<string>& A) {
        vector<string> result;
        if (A.size() == 0) return result;
        int hash[26] = {0}; // 用来统计所有字符串里字符出现的最小频率
        for (int i = 0; i < A[0].size(); i++) { // 用第一个字符串给hash初始化
            hash[A[0][i] - 'a']++;
        }

        int hashOtherStr[26] = {0}; // 统计除第一个字符串外字符的出现频率
        for (int i = 1; i < A.size(); i++) {
            memset(hashOtherStr, 0, 26 * sizeof(int));
            for (int j = 0; j < A[i].size(); j++) {
                hashOtherStr[A[i][j] - 'a']++;
            }
            // 更新hash，保证hash里统计26个字符在所有字符串里出现的最小次数
            for (int k = 0; k < 26; k++) {
                hash[k] = min(hash[k], hashOtherStr[k]);
            }
        }
        // 将hash统计的字符次数，转成输出形式
        for (int i = 0; i < 26; i++) {
            while (hash[i] != 0) { // 注意这里是while，多个重复的字符
                string s(1, i + 'a'); // char -> string
                result.push_back(s);
                hash[i]--;
            }
        }

        return result;
    }
};