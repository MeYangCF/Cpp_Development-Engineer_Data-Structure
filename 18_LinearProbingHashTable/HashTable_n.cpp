/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-03-08 ����4:29
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
    // 242.��Ч����ĸ��λ��
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
    // 349. ��������Ľ���
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
    // 202.������
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
    // 454.�������II
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        unordered_map<int, int> umap; //key:a+b����ֵ��value:a+b��ֵ���ֵĴ���
        // ������A�ʹ�B���飬ͳ����������Ԫ��֮�ͣ��ͳ��ֵĴ������ŵ�map��
        for (int a : A) {
            for (int b : B) {
                umap[a + b]++;
            }
        }
        int count = 0; // ͳ��a+b+c+d = 0 ���ֵĴ���
        // �ٱ�����C�ʹ�D���飬�ҵ���� 0-(c+d) ��map�г��ֹ��Ļ����Ͱ�map��key��Ӧ��valueҲ���ǳ��ִ���ͳ�Ƴ�����
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
    // 383. �����
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
    // 205. ͬ���ַ���
    bool isIsomorphic(string s, string t) {
        unordered_map<char, char> map1;
        unordered_map<char, char> map2;
        for (int i = 0, j = 0; i < s.size(); i++, j++) {
            if (map1.find(s[i]) == map1.end()) { // map1����s[i] �� t[j]��ӳ��
                map1[s[i]] = t[j];
            }
            if (map2.find(t[j]) == map2.end()) { // map2����t[j] �� s[i]��ӳ��
                map2[t[j]] = s[i];
            }
            // ����ӳ�� ��Ӧ���ϣ����̷���false
            if (map1[s[i]] != t[j] || map2[t[j]] != s[i]) {
                return false;
            }
        }
        return true;
    }

public:
    // 1002. ���ҹ����ַ�
    vector<string> commonChars(vector<string>& A) {
        vector<string> result;
        if (A.size() == 0) return result;
        int hash[26] = {0}; // ����ͳ�������ַ������ַ����ֵ���СƵ��
        for (int i = 0; i < A[0].size(); i++) { // �õ�һ���ַ�����hash��ʼ��
            hash[A[0][i] - 'a']++;
        }

        int hashOtherStr[26] = {0}; // ͳ�Ƴ���һ���ַ������ַ��ĳ���Ƶ��
        for (int i = 1; i < A.size(); i++) {
            memset(hashOtherStr, 0, 26 * sizeof(int));
            for (int j = 0; j < A[i].size(); j++) {
                hashOtherStr[A[i][j] - 'a']++;
            }
            // ����hash����֤hash��ͳ��26���ַ��������ַ�������ֵ���С����
            for (int k = 0; k < 26; k++) {
                hash[k] = min(hash[k], hashOtherStr[k]);
            }
        }
        // ��hashͳ�Ƶ��ַ�������ת�������ʽ
        for (int i = 0; i < 26; i++) {
            while (hash[i] != 0) { // ע��������while������ظ����ַ�
                string s(1, i + 'a'); // char -> string
                result.push_back(s);
                hash[i]--;
            }
        }

        return result;
    }
};