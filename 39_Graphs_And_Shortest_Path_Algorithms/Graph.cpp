/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-02-19 ÉÏÎç9:38
@description:
*/

#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>
using namespace std;

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

    return 0;
}
