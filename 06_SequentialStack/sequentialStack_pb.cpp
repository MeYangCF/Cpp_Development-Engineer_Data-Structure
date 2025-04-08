/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2024 24-12-10 下午9:10
@description:
*/

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

//括号匹配问题
bool isValid(string s) {
    stack<char> strV;

    for(int i = 0; i < s.size(); i++){
        if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
            strV.push(s[i]);
        } else {
            if (strV.empty())
                return false;

            char tmp = strV.top();

            if ((tmp == '(' && s[i] == ')')
               || (tmp == '{' && s[i] == '}')
               || (tmp == '[' && s[i] == ']')) {
                strV.pop();
                continue;
            }else{
                return false;
            }
        }
    }

    return strV.empty();
}

//逆波兰表达式求值
int evalRPN(vector<string>& tokens) {
    stack<int> valStack;

    for (auto val : tokens) {
        if(val == "+" || val == "-" || val == "*" || val == "/") {
            long long num1 = valStack.top();
            valStack.pop();
            long long num2 = valStack.top();
            valStack.pop();

            if(val == "+") valStack.push(num2 + num1);
            if(val == "-") valStack.push(num2 - num1);
            if(val == "*") valStack.push(num2 * num1);
            if(val == "/") valStack.push(num2 / num1);
        } else
            valStack.push(stoll(val));
    }

    return valStack.top();
}

//中缀转后缀表达式
bool Priority(char ch, char topch){
    if((ch == '*' || ch == '/') && (topch == '+' || topch == '-'))
        return true;

    if(topch == '(' && ch != ')')
        return true;

    return false;
}

string MiddleToEndExpr(string expr)
{
    string result;
    stack<char> s;

    for (char ch : expr){
        if (ch >= '0' && ch <= '9'){
            result.push_back(ch);
        }else{
            for (;;){
                if (s.empty() || ch == '('){
                    s.push(ch);
                    break;
                }
                char topch = s.top();
                if (Priority(ch, topch)){
                    s.push(ch);
                    break;
                }else{
                    s.pop();
                    if (topch == '(')
                        break;
                    result.push_back(topch);
                }
            }
        }
    }
    while (!s.empty()){
        result.push_back(s.top());
        s.pop();
    }
    return result;
}



//删除字符串中的所有相邻重复项
string removeDuplicates(string s) {
    stack<char> strCheck;
    for(auto val : s){
        if(strCheck.empty() || val != strCheck.top())
            strCheck.push(val);
        else
            strCheck.pop();
    }

    string result = "";

    while (!strCheck.empty()) {
        result += strCheck.top();
        strCheck.pop();
    }

    reverse (result.begin(), result.end());
    return result;
}