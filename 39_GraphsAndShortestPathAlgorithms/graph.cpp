/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-03-17 下午6:52
@description:
*/

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <list>
#include <queue>
using namespace std;


class Digraph
{
public:
	void readFile(string filePath) {
		FILE* pf = fopen(filePath.c_str(), "r");
		if (pf == nullptr) {
			throw filePath + " not exists!";
		}
		vertics.emplace_back("");
		while (!feof(pf)) {
			char line[1024] = { 0 };
			fgets(line, 1024, pf);
			string linestr(line);
			vertics.emplace_back(linestr.substr(0, linestr.size()-1));
			fgets(line, 1024, pf);
			char* vertic_no = strtok(line, ",");
			while (vertic_no != nullptr) {
				int vex = atoi(vertic_no);
				if (vex > 0) {
					vertics.back().adjList_.emplace_back(vex);
				}
				vertic_no = strtok(nullptr, ",");
			}
		}

		fclose(pf);
	}

	void show() const {
		for (int i = 1; i < vertics.size(); i++) {
			cout << vertics[i].data_ << " : ";
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
			for (auto no : vertics[cur_no].adjList_)
			{
				if (!visited[no]) {
					que.push(no);
					visited[no] = true;
				}
			}
		}
		cout << endl;
	}

	void shortPath(int start, int end) {
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
			for (auto no : vertics[cur_no].adjList_)
			{
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
			cout << "不存在有效的最短路径!" << endl;
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

	void showPath(int end, vector<int>& path) {
		if (end == 0) {
			return;
		}
		showPath(path[end], path);
		cout << vertics[end].data_ << " ";
	}

private:
	struct Vertic {
		Vertic(string data)
			: data_(data) {}
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
/*
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
using namespace std;

int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1}; // 四个方向
void bfs(const vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y) {
	queue<pair<int, int>> que;
	que.push({x, y});
	visited[x][y] = true; // 只要加入队列，立刻标记
	while(!que.empty()) {
		pair<int ,int> cur = que.front(); que.pop();
		int curx = cur.first;
		int cury = cur.second;
		for (int i = 0; i < 4; i++) {
			int nextx = curx + dir[i][0];
			int nexty = cury + dir[i][1];
			if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) continue;  // 越界了，直接跳过
			if (!visited[nextx][nexty] && grid[nextx][nexty] == 1) {
				que.push({nextx, nexty});
				visited[nextx][nexty] = true; // 只要加入队列立刻标记
			}
		}
	}
}

int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> grid(n, vector<int>(m, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> grid[i][j];
		}
	}

	vector<vector<bool>> visited(n, vector<bool>(m, false));

	int result = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (!visited[i][j] && grid[i][j] == 1) {
				result++; // 遇到没访问过的陆地，+1
				bfs(grid, visited, i, j); // 将与其链接的陆地都标记上 true
			}
		}
	}
	cout << result << endl;
}
