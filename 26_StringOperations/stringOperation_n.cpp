/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-03-07 ����8:35
@description:
*/
/*
#include <iostream>
#include <memory>
#include <mutex>
using namespace std;

int BF(string s, string t) {
    int i = 0;
    int j = 0;
    while (i < s.size() && j < t.size()) {
        if (s[i] == t[j]) {
            i++;
            j++;
        }
        else {
            i = i - j + 1;
            j = 0;
        }
    }
    if (j == t.size()) {
        return i - j;
    }
    else {
        return -1;
    }
}

int* getNext(string str) {
    int* next = new int[str.size()];
    int j = 0;
    int k = -1;
    next[j] = k;
    while (j < str.size() - 1) {
        if (-1 == k || str[k] == str[j]) {
            j++;
            k++;
            if (str[k] == str[j]) {
                next[j] = next[k];
            }
            else {
                next[j] = k;
            }
        }
        else {
            k = next[k];
        }
    }
    return next;
}

int KMP(const string& s, const string& t) {
    int i = 0;
    int j = 0;
    int* next = getNext(t);
    unique_ptr<int> ptr(next);
    int size_s = s.size();
    int size_t = t.size();
    while (i < size_s && j < size_t) {
        if (-1 == j || s[i] == t[j]) {
            i++;
            j++;
        }
        else {
            j = next[j];
        }
    }
    if (j == t.size()) {
        return i - j;
    }
    else {
        return -1;
    }
}
*/
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Solution {
public:
    // 344.��ת�ַ���
    void reverseString(vector<char>& s) {
        int i = 0;
        int j = s.size() - 1;
        while (i < j) {
            swap(s[i], s[j]);
            i++;
            j--;
        }
    }

public:
    // 541. ��ת�ַ���II
    string reverseStr(string s, int k) {
        int strSize = s.size();
        int conI = strSize / (2 * k);
        int conF = strSize % (2 * k);
        int j = 0;
        for (int i = 0; i < conI; i++) {
            reversesubStrg(s, j, k);
            j += 2 * k;
        }
        if (conF < k) {
            reversesubStrg(s, j, conF);
        } else {
            reversesubStrg(s, j, k);
        }
        return s;
    }

private:
    void reversesubStrg(string& s, int begin, int length) {
        int i = begin;
        int j = begin + length - 1;
        while (i < j) {
            swap(s[i], s[j]);
            i++;
            j--;
        }
    }

public:
    // 151.��ת�ַ�����ĵ���
    string reverseWords(string s) {
        vector<string> words;
        int i = 0;
        while (i < (int)s.size()) {
            while (i < (int)s.size() && s[i] == ' ') {
                i++;
            }
            if (i >= (int)s.size()) {
                break;
            }
            string word;
            while (i < (int)s.size() && s[i] != ' ') {
                word.push_back(s[i]);
                i++;
            }
            words.push_back(word);
        }
        string result;
        for (int j = (int)words.size() - 1; j >= 0; j--) {
            if (!result.empty()) {
                result.push_back(' ');
            }
            result.append(words[j]);
        }
        return result;
    }

public:
    // 28. �ҳ��ַ����е�һ��ƥ������±�
    int strStr(string haystack, string needle) {
        int i = 0;
        int j = 0;
        vector<int> next = getNext(needle);
        int size1 = haystack.size();
        int size2 = needle.size();
        while (i < size1 && j < size2) {
            if (-1 == j || haystack[i] == needle[j]) {
                i++;
                j++;
            }
            else {
                j = next[j];
            }
        }
        if (j == needle.size()){
            return i - j;
        }
        else {
            return -1;
        }
    }

private:
    vector<int> getNext(string str) {
        vector<int> next(str.size());
        int j = 0;
        int k = -1;
        next[j] = k;
        while (j < (int)str.size() - 1)
        {
            if (-1 == k || str[k] == str[j]) {
                j++;
                k++;
                if (str[k] == str[j]) {
                    next[j] = next[k];
                } else {
                    next[j] = k;
                }
            } else {
                k = next[k];
            }
        }
        return next;
    }

public:
    // 459.�ظ������ַ���
    bool repeatedSubstringPattern (string s) {
        if (s.size() == 0) {
            return false;
        }
        int next[s.size()];
        getNext(next, s);
        int len = s.size();
        if (next[len - 1] != -1 && len % (len - (next[len - 1] + 1)) == 0) {
            return true;
        }
        return false;
    }
private:
    void getNext (int* next, const string& s){
        next[0] = -1;
        int j = -1;
        for(int i = 1;i < s.size(); i++){
            while(j >= 0 && s[i] != s[j + 1]) {
                j = next[j];
            }
            if(s[i] == s[j + 1]) {
                j++;
            }
            next[i] = j;
        }
    }

public:
    // 925.��������
    bool isLongPressedName(string name, string typed) {
        int i = 0, j = 0;
        while (i < name.size() && j < typed.size()) {
            if (name[i] == typed[j]) { // ��ͬ��ͬʱ���ƥ��
                j++; i++;
            } else { // ����ͬ
                if (j == 0) return false; // ����ǵ�һλ�Ͳ���ֱͬ�ӷ���false
                // j��Խ�ظ������ƶ���ͬʱ��ֹjԽ��
                while(j < typed.size() && typed[j] == typed[j - 1]) j++;
                if (name[i] == typed[j]) { // j��Խ�ظ���֮���ٴκ�name[i]ƥ��
                    j++; i++; // ��ͬ��ͬʱ���ƥ��
                }
                else return false;
            }
        }
        // ˵��nameû��ƥ���꣬���� name:"pyplrzzzzdsfa" type:"ppyypllr"
        if (i < name.size()) return false;

        // ˵��typeû��ƥ���꣬���� name:"alex" type:"alexxrrrrssda"
        while (j < typed.size()) {
            if (typed[j] == typed[j - 1]) j++;
            else return false;
        }
        return true;
    }

public:
    // 844.�ȽϺ��˸���ַ���
    bool backspaceCompare(string s, string t) {
        stack<char> tmpStk;
        for (int i = 0; i < static_cast<int>(s.size()) - 1; i++) {
            if ( s[i] != '#') {
                tmpStk.push(s[i]);
            }
            else {
                if (!tmpStk.empty()) {
                    tmpStk.pop();
                }
            }
        }
        string sRes = "";
        while (!tmpStk.empty()) {
            sRes.push_back(tmpStk.top());
            tmpStk.pop();
        }
        for (int i = 0; i < static_cast<int>(t.size()) - 1; i++) {
            if ( t[i] != '#') {
                tmpStk.push(t[i]);
            }
            else {
                if (!tmpStk.empty()) {
                    tmpStk.pop();
                }
            }
        }
        string tRes = "";
        while (!tmpStk.empty()) {
            tRes.push_back(tmpStk.top());
            tmpStk.pop();
        }
        return sRes == tRes;
    }
};