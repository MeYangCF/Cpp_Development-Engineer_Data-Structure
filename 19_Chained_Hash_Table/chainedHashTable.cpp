/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2024 24-12-19 下午4:12
@description:
*/

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

class HashTable{
public:
    HashTable(int size = primes_[0], double loadFactor = 0.75)
        : useBucketNum_(0)
        , loadFactor_(loadFactor)
        , primeIdx_(0){
        if(size != primes_[0]){
            for(; primeIdx_ < PRIME_SIZE; primeIdx_++){
                if(primes_[primeIdx_] >= size)
                    break;
            }
            if(primeIdx_ == PRIME_SIZE)
                primeIdx_--;
        }
        table_.resize(primes_[primeIdx_]);
    }

public:
    void insert(int key){
        double factor = useBucketNum_ * 1.0 / table_.size();
        cout << "factor:" << factor << endl;
        if(factor > loadFactor_)
            expand();
        int idx = key % table_.size();
        if(table_[idx].empty()){
            useBucketNum_++;
            table_[idx].emplace_front(key);
        } else{
            auto it = ::find(table_[idx].begin(), table_[idx].end(), key);
            if(it == table_[idx].end())
                table_[idx].emplace_front(key);
        }
    }

    void erase(int key){
        int idx = key % table_.size();
        auto it = ::find(table_[idx].begin(), table_[idx].end(), key);
        if(it != table_[idx].end()){
            table_[idx].erase(it);
            if(table_[idx].empty())
                useBucketNum_--;
        }
    }

    bool  find(int key){
        int idx = key % table_.size();
        auto it = ::find(table_[idx].begin(), table_[idx].end(), key);
        return it != table_[idx].end();
    }

private:
    void expand(){
        if(primeIdx_ + 1 == PRIME_SIZE)
            throw "hashtable can not expand anymore!";
        primeIdx_++;
        useBucketNum_ = 0;

        vector<list<int>> oldTable;
        table_.swap(oldTable);
        table_.resize(primes_[primeIdx_]);

        for(auto list : oldTable){
            for(auto key : list){
                int idx = key % table_.size();
                if(table_[idx].empty())
                    useBucketNum_++;
                table_[idx].emplace_front(key);
            }
        }
    }

private:
    vector<list<int>> table_;
    int useBucketNum_;
    double loadFactor_;

    static const int PRIME_SIZE = 10;
    static int primes_[PRIME_SIZE];
    int primeIdx_;
};

int HashTable::primes_[PRIME_SIZE] = { 3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773 };

int main(){
    HashTable htable;
    htable.insert(21);
    htable.insert(32);
    htable.insert(14);
    htable.insert(15);

    htable.insert(22);

    htable.insert(67);

    cout << htable.find(67) << endl;
    htable.erase(67);
    cout << htable.find(67) << endl;
    return 0;
}