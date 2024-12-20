/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2024 24-12-20 下午7:12
@description:
*/

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <functional>
#include <unordered_map>
using namespace std;

int main(){
    vector<int> vec;
    srand(time(nullptr));
    for (int i = 0; i < 10000; i++)
        vec.push_back(rand() % 1000);
    int k = 3;
    unordered_map<int, int> map;
    for(auto key : vec)
        map[key]++;
    using Type = pair<int, int>;
    using Comp = function<bool(Type&, Type&)>;
    priority_queue<Type, vector<Type>, Comp> maxheap(
            [](Type& a, Type& b)->bool {
                return a.second < b.second;
            });
    auto it = map.begin();
    for (int i = 0; i < k; i++, ++it)
        maxheap.push(*it);

    for (; it != map.end(); ++it){
        if (maxheap.top().second > it->second){
            maxheap.pop();
            maxheap.push(*it);
        }
    }

    while (!maxheap.empty()){
        cout << "key:" << maxheap.top().first
             << " cnt:" << maxheap.top().second << endl;
        maxheap.pop();
    }

    // 统计重复次数最大的前3个数字
//    int k = 3;
//    unordered_map<int, int> map;
//    for (auto key : vec)
//        map[key]++;
//
//    // 放入大根堆的时候，需要放key-value键值对
//    using Type = pair<int, int>;
//    using Comp = function<bool(Type&, Type&)>;
//    priority_queue<Type, vector<Type>, Comp> minheap(
//        [](Type& a, Type& b)->bool {
//            return a.second > b.second;
//        });
//
//    auto it = map.begin();
//    for (int i = 0; i < k; i++, ++it)
//        minheap.push(*it);
//
//    for (; it != map.end(); ++it){
//        if (minheap.top().second < it->second){
//            minheap.pop();
//            minheap.push(*it);
//        }
//    }
//
//    while (!minheap.empty()){
//        cout << "key:" << minheap.top().first
//            << " cnt:" << minheap.top().second << endl;
//        minheap.pop();
//    }
    return 0;
}

/*
int main(){
    //求最小的5个元素
    vector<int> vec;
    srand(time(nullptr));
    for(int i = 0; i < 1000; i++)
        vec.push_back(rand() % 10000);
//    priority_queue<int> minheap;
//    int k = 5;
//    for(int i = 0; i < 5; i++)
//        minheap.push(vec[i]);
//    for(int i = 5; i < vec.size(); i++){
//        if(minheap.top() > vec[i]){
//            minheap.pop();
//            minheap.push(vec[i]);
//        }
//    }
//
//    while (!minheap.empty()){
//        cout << minheap.top() << " ";
//        minheap.pop();
//    }

    //求最大的5个元素
    priority_queue<int, vector<int>, greater<int>> minheap;
    int k = 5;
    for(int i = 0; i < 5; i++)
        minheap.push(vec[i]);
    for(int i = 5; i < vec.size(); i++){
        if(minheap.top() < vec[i]){
            minheap.pop();
            minheap.push(vec[i]);
        }
    }

    while (!minheap.empty()){
        cout << minheap.top() << " ";
        minheap.pop();
    }

    return 0;
}
 */