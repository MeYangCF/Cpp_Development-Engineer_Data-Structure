/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-02-19 上午9:38
@description:
*/

#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>
using namespace std;

/*
class Digraph {
public:
    void readFile(sring filePath) {
        FilE* pf = fopen(filePath.c_str(), "r");
        if (pf ==nullptr) {
            throw filePath + "not found";
        }

        vertics.emplace_back("");

        while (!feof(pf)) {
            char line[1024] = {0};
            fgets(line, sizeof(line), pf);
            string linestr(line);
            vertics.emplace_back(linestr.substr(0, linestr.size() - 1));

            fgets(line, sizeof(line), pf);
            char* vertic_no != strtok(line, ",");
            while (vertic_no != nullptr) {
                int vex =atoi(vertic_no);
                if (vex >= 0) {
                    vertics.back().adjList_.emplace_back(vex);
                }
                vertic_no = strtok(nullptr, ",");
            }
        }
        fclose(pf);
    }

    void show() const {
        for (int i = 1; i < vertics.size(); i++) {
            cout << vertics[i].data_ << ":";
            for (auto no : vertics[i].adjList_) {
                cout << no << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void dfs() {
        vector<bool> visited(vertics.size(), false);
        dfs(1, visited);
        cout << endl;
    }

    void bfs() {
        vector<bool> visited(vertics.size(), false);
        queue<int> que;

        que.push(1);
        visited[1] = true;

        while (!que.empty()) {
            int cur_no = que.front();
            que.pop();

            cout << vertics[cur_no].data_ << " ";
            for (auto no : vertics[cur_no].adjList_) {
                if (!visited[no]) {
                    que.push(no);
                    visited[no] = true;
                }
            }
        }
        cout << endl;
    }

    void shorPath(int start, int end) {
        vector<bool> visited(vertics.size(), false);
        queue<int> que;
        vector<int> path(vertics.size(), 0);

        que.push(start);
        visited[start] = true;
        while (!que.empty()) {
            int cur_no = que.front();
            if (cur_no == end) {
                break;
            }
            que.pop();
            for (auto no : vertics[cur_no].adjList_) {
                if (!visited[no]) {
                    que.push(no);
                    visited[no] = true;
                    path[no] = cur_no;
                }
            }
        }

        if (!que.empty()) {
            showPath(end, path);
        }
        else {
            cout << "不存在有效的最短路径！"<< endl;
        }
        cout << endl;
    }

private:
    void dfs(int start, vector<bool>& visited) {
        if (visited[start]) {
            return;
        }
        cout << vertics[start].data_ << " ";
        visited[start] = true;

        for (auto no : vertics[start].adjList_) {
            dfs(no, visited);
        }
    }

    void showPath(int end, vector<int>& path){
        if (end == 0)
            return;

        showPath(path[end], path);
        cout << vertics[end].data_ << " ";
    }
private:
    struct Vertic {
        Vertic(string data)
            : data_(data)
            {}
        string data_;
        list<int> adjList_;
    };
private:
    vector<Vertic> vertics;
};

int main() {
    Digraph graph;
    graph.readFile("data.txt");
    graph.show();
    graph.dfs();
    graph.bfs();

    cout << "================" << endl;
    graph.shortPath(1, 3);
    return 0;
}
*/

//dijkstra
/*
using uint = unsigned int;
const uint INF = INT_MAX;

//未优化的算法

int Dijkstra(vector<vector<uint>>& graph, int start, int end) {
    const int N = graph.size();
    vector<uint> dis(N, 0);
    vector<bool> use(N, false);

    use[start] = true;
    for (int i = 0; i < N; i++) {
        dis[i] = graph[start][i];
    }

    for (int i = 1; i < N; i++) {
        int k = -1;
        int min = INF;
        for (int j = 0; j < N; j++) {
            if (!use[j] && dis[j] < min) {
                min = dis[j];
                k = j;
            }
        }

        if (k == -1) {
            break;
        }

        use[k] = true;

        for (int j = 0; j < N; j++) {
            if (!use[j] && min + graph[k][j] < dis[j]) {
                dis[j] = min + graph[k][j];
            }
        }
    }

    for (int d : dis) {
        cout << d << " ";
    }
    cout << endl;
    return dis[end];
}


//引入小根堆进行优化
int Dijkstra_1(vector<vector<uint>>& graph, int start, int end) {
    const int N = graph.size();
    vector<uint> dis(N, 0);
    vector<bool> use(N, false);

    priority_queue<pair<uint, int>, vector<pair<uint, int>>, greater<pair<uint, int>>> que;
    use[start] = true;
    for (int i = 0; i < N; i++) {
        dis[i] = graph[start][i];
        if (i != start) {
            que.emplace(graph[start][i], i);
        }
    }

    while (!que.empty()) {
        auto pair = que.top();
        que.pop();
        if (pair.first == INF) {
            break;
        }
        int k = pair.second;
        int min = pair.first;
        if (use[k]) {
            continue;
        }
        use[k] = true;
        for (int j = 0; j < N; j++) {
            if (!use[j] && min + graph[k][j] < dis[j]) {
                dis[j] = min + graph[k][j];
                que.emplace(dis[j], k);
            }
        }
    }

    for (int d : dis) {
        cout << d << " ";
    }
    cout << endl;
    return dis[end];
}

int main() {
    vector<vector<uint>> graph = {
        {0, 6, 3, INF, INF, INF},
        {6, 0, 2, 5, INF, INF},
        {3, 2, 0, 3, 4, INF},
        {INF, 5, 3, 0, 2, 3},
        {INF, INF, 4, 2, 0, 5},
        {INF, INF, INF, 3, 5, 0},
    };

    int distance = Dijkstra(graph, 0, 1);
    if (distance == INF) {
        cout << "不存在有效路径!" << endl;
    }
    else {
        cout << "distance:" << distance << endl;
    }    return 0;
}
*/

//Floyd
using uint = unsigned int;
const uint INF = INT_MAX;

int main() {
    vector<vector<uint>> graph = {
        {0, 6, 3, INF, INF, INF},
        {6, 0, 2, 5, INF, INF},
        {3, 2, 0, 3, 4, INF},
        {INF, 5, 3, 0, 2, 3},
        {INF, INF, 4, 2, 0, 5},
        {INF, INF, INF, 3, 5, 0},
    };

    for (int k = 0; k < graph.size(); k++) {
        for (int i = 0; i < graph.size(); i++) {
            for (int j = 0; j < graph.size(); j++) {
                graph[i][j] = min(graph[i][j], graph[i][k]+graph[k][j]);
            }
        }
    }

    for (auto line : graph){
        for (auto dis : line){
            cout << dis << " ";
        }
        cout << endl;
    }
}