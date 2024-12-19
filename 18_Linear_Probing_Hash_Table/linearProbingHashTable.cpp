/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2024 24-12-19 下午2:43
@description:
*/

#include <iostream>
using namespace std;

enum State{
    STATE_UNUSE,
    STATE_USING,
    STATE_DEL,
};

struct Bucket{
    Bucket(int key = 0, State state = STATE_UNUSE)
        :key_(key)
        ,state_(state){}

    int key_;
    State state_;
};

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

        tableSize_ = primes_[primeIdx_];
        table_ = new Bucket[tableSize_];
    }

    ~HashTable(){
        delete[]table_;
        table_ = nullptr;
    }

public:
    bool insert(int key){
        double factor = useBucketNum_ * 1.0 / tableSize_;
        cout << "factor:" << factor << endl;
        if(factor > loadFactor_)
            expand();
        int idx = key % tableSize_;
        int i = idx;
        do{
            if(table_[i].state_ != STATE_USING){
                table_[i].state_ = STATE_USING;
                table_[i].key_ = key;
                useBucketNum_++;
                return true;
            }
            i = (i + 1) % tableSize_;
        } while (i != idx);

        return false;
    }

    bool erase(int key){
        int idx = key % tableSize_;
        int i = idx;
        do{
            if(table_[i].state_ == STATE_USING && table_[i].key_ == key){
                table_[i].state_ = STATE_DEL;
                useBucketNum_--;
            }
            i = (i + 1) % tableSize_;
        } while (table_[i].state_ != STATE_UNUSE && i != idx);

        return true;
    }

    bool find(int key){
        int idx = key % tableSize_;
        int i = idx;
        do{
            if(table_[i].state_ == STATE_USING && table_[i].key_ == key)
                return true;
            i = (i + 1) % tableSize_;
        } while (table_[i].state_ != STATE_UNUSE && i != idx);

        return false;
    }

private:
    void expand(){
        ++primeIdx_;
        if(primeIdx_ == PRIME_SIZE)
            throw "HashTable is too large, can not expand anymore!";
        Bucket* newTable = new Bucket[primes_[primeIdx_]];
        for(int i = 0; i < tableSize_; i++){
            if(table_[i].state_ == STATE_USING){
                int idx = table_[i].key_ % primes_[primeIdx_];
                int k = idx;
                do{
                    if(newTable[k].state_ != STATE_USING){
                        newTable[k].state_ = STATE_USING;
                        newTable[k].key_ = table_[i].key_;
                        break;
                    }
                    k = (k + 1) % primes_[primeIdx_];
                } while (k != idx);
            }
        }

        delete[]table_;
        table_ = newTable;
        tableSize_ = primes_[primeIdx_];
    }

private:
    Bucket* table_;
    int tableSize_;
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

    cout << htable.find(21) << endl;
    htable.erase(21);
    cout << htable.find(21) << endl;
    return 0;
}