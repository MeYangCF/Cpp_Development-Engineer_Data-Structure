/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-03-03 ����1:18
@description:
*/
/*
#include <iostream>
using namespace std;

class queue {
public:
    queue(int size = 10)
        : cap_(size)
        , front_(0)
        , rear_(0)
        , size_(0) {
        pQue = new int[cap_];
    }
    ~queue() {
        delete[] pQue;
        pQue = nullptr;
    }

public:
    void push(int val) {
        if ((rear_ + 1) % cap_ == front_) {
            expand(2 * cap_);
        }
        pQue[rear_] = val;
        rear_ = (rear_ + 1) % cap_;
        size_++;
    }

    void pop() {
        if (empty()) {
            throw "queue is empty";
        }
        front_ = (front_ + 1) % cap_;
        size_--;
    }

    int front() const {
        if (empty()) {
            throw "queue is empty";
        }
        return pQue[front_];
    }

    int back() const {
        if (empty()) {
            throw "queue is empty";
        }
        return pQue[(rear_ - 1 + cap_) % cap_];
    }

    bool empty() const {
        return front_ == rear_;
    }

    int size() const {
        return size_;
    }

private:
    void expand(int size) {
        int* p = new int[size];
        int i = 0;
        int j = front_;
        for (; j != rear_; i++, j = (j + 1) % cap_) {
            p[i] = pQue[j];
        }
        delete[] pQue;
        pQue = p;
        cap_ = size;
        front_ = 0;
        rear_ = i;
    }

private:
    int* pQue;
    int cap_;
    int front_;
    int rear_;
    int size_;
};
*/
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class Solution {
public:
    // 239. �����������ֵ
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        MyQueue que;
        vector<int> result;
        for (int i = 0; i < k; i++) { // �Ƚ�ǰk��Ԫ�طŽ�����
            que.push(nums[i]);
        }
        result.push_back(que.front()); // result ��¼ǰk��Ԫ�ص����ֵ
        for (int i = k; i < nums.size(); i++) {
            que.pop(nums[i - k]); // ���������Ƴ���ǰ��Ԫ��
            que.push(nums[i]); // ��������ǰ����������Ԫ��
            result.push_back(que.front()); // ��¼��Ӧ�����ֵ
        }
        return result;
    }
private:
    class MyQueue { //�������У��Ӵ�С��
    public:
        deque<int> que; // ʹ��deque��ʵ�ֵ�������
        // ÿ�ε�����ʱ�򣬱Ƚϵ�ǰҪ��������ֵ�Ƿ���ڶ��г���Ԫ�ص���ֵ���������򵯳���
        // ͬʱpop֮ǰ�ж϶��е�ǰ�Ƿ�Ϊ�ա�
        void pop(int value) {
            if (!que.empty() && value == que.front()) {
                que.pop_front();
            }
        }
        // ���push����ֵ�������Ԫ�ص���ֵ����ô�ͽ����к�˵���ֵ������ֱ��push����ֵС�ڵ��ڶ������Ԫ�ص���ֵΪֹ��
        // �����ͱ����˶��������ֵ�ǵ����Ӵ�С���ˡ�
        void push(int value) {
            while (!que.empty() && value > que.back()) {
                que.pop_back();
            }
            que.push_back(value);

        }
        // ��ѯ��ǰ����������ֵ ֱ�ӷ��ض���ǰ��Ҳ����front�Ϳ����ˡ�
        int front() {
            return que.front();
        }
    };
};