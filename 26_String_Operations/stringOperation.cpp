/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2024 24-12-24 обнГ2:21
@description:
*/

#include <iostream>
#include <memory>
using namespace std;

int BF(string s, string t){
    int i = 0;
    int j = 0;

    while (i < s.size() && j < t.size()){
        if(s[i] == t[j]){
            i++;
            j++;
        }else{
            i = i - j + 1;
            j = 0;
        }
    }

    if(j == t.size())
        return i - j;
    else
        return -1;
}

int* getNext(string str){
    int* next = new int[str.size()];
    int j = 0;
    int k = -1;
    next[j] = k;

    while(j < str.size() - 1){
        if(k == -1 || str[j] == str[k]){
            k++;
            j++;

            if(str[j] == str[k])
                next[j] = next[k];
            next[j] = k;
        }else{
            k = next[k];
        }
    }

    return next;
}

int KMP(const string &s, const string &t){
    int i = 0;
    int j = 0;
    int* next = getNext(t);
    unique_ptr<int> ptr(next);

    int size_s = s.size();
    int size_t = t.size();
    while (i < size_s && j < size_t) {
        if (j == -1 || s[i] == t[j]) {
            i++;
            j++;
        } else
            j = next[j];
    }
    if(j == t.size())
        return i - j;
    else
        return -1;
}

int main(){
    string s = "abcabdefabcabc";
    string t = "abcabc";

    int pos = KMP(s, t);
    cout << pos << endl;
    return 0;
}