/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-02-18 上午10:23
@description:
*/

#include <iostream>
#include <algorithm>
using namespace std;

//1.硬币选择问题
/*
int main() {
    int arr[] = {1, 3, 5};
    int length = sizeof(arr) / sizeof(arr[0]);
    int c = 11;

    sort(arr, arr + length, [](int a, int b)->bool{return a > b;});

    int idx = 0;
    int cnt = 0;
    while (c > 0) {
        if (c >= arr[idx]) {
            c -= arr[idx];
            cnt++;
        }
        else {
            idx++;
        }
    }

    cout << cnt << endl;
    return 0;
}
*/

//2.部分背包问题
/*
struct Product {
    double getPrice() const {
        return v * 1.0 / w;
    }
    bool operator>(const Product &other) const {
        return getPrice() > other.getPrice();
    }
    int id;
    int w;
    int v;
};

int main() {
    int w[] = {8, 6, 4, 2, 5};
    int v[] = {6, 4, 7, 8, 6};
    const int n = sizeof(w) / sizeof(w[0]);
    int c = 12;
    int x[n] = {0};

    Product pros[n];
    for (int i = 0; i < n; ++i) {
        pros[i].id = i;
        pros[i].w = w[i];
        pros[i].v = v[i];
    }

    sort(pros, pros + n, [](const Product &p1, const Product &p2)->bool {return p1 > p2; });

    double bestv = 0.0;
    for (int i = 0; i < n; ++i) {
        if (pros[i].w <= c) {
            bestv += pros[i].v;
            c -= pros[i].w;
        }
        else {
            bestv = bestv + pros[i].v * (c * 1.0 / pros[i].w);
            x[pros[i].id] = 1;
            break;
        }

        x[pros[i].id] = 1;
    }

    cout << "bestv:" << bestv << endl;
    for (int v : x) {
        cout << v << " ";
    }
    cout << endl;

    return 0;
}
*/

//3.柜台提供服务问题

struct Counter {
    bool operator<(const Counter &other) const {
        return time < other.time;
    }
    int id;
    int time;
};

int main() {
    int arr[] = {3, 2, 4};
    const int m = sizeof(arr) / sizeof(arr[0]);
    int n = 15;

    Counter cons[m];
    for (int i = 0; i < m; ++i) {
        cons[i].id = i;
        cons[i].time = arr[i];
    }

    sort(cons, cons + m);

    int mintime = 0;
    int x[m] = {0};

    for (int i = 0; i < n; ++i) {
        int time = cons[0].time * (x[0] + 1);
        int j = 1;
        for (; j < m; ++j) {
            int t = cons[j].time * (x[j] + 1);
            if (t <= time) {
                x[j]++;

                if (t > mintime) {
                    mintime = t;
                }
            }
        }

        if (j == m) {
            x[0]++;
            mintime = cons[j].time; * x[0];
        }
    }

    cout << mintime << endl;
    for (int i = 0; i < m; ++i) {
        cout << arr[cons[i].id] << " : " << x[i] << endl;
    }

    return 0;
}