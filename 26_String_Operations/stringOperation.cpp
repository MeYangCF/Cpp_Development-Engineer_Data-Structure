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

    while (j < str.size() - 1){
        if(-1 == k || str[k] == str[j]){
            j++;
            k++;

            if(str[k] == str[j])
                next[j] = next[k];
            else
                next[j] = k;
        } else
            k = next[k];
    }

    return next;
}

int KMP(string s, string t){
    int i = 0;
    int j = 0;
    int* next = getNext(t);
    unique_ptr<int> ptr(next);
    cout << t << " : ";

    for(int m = 0; m < t.size(); m++)
        cout << next[m] << " ";

    cout << endl;
    int size1 = s.size();
    int size2 = t.size();

    while (i < size1 && j < size2){
        if(-1 == j || s[i] == t[j]){
            i++;
            j++;
        }else{
            j = next[j];
        }
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