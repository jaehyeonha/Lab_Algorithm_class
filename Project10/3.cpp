#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<vector<int>> matrix_t;

matrix_t make_graph(int n, int m) {
	int imove[8] = { -2, -1, 1, 2, 2, 1, -1, -2 };
	int jmove[8] = { 1, 2, 2, 1, -1 ,-2 ,-2, -1 };
	matrix_t graph(n * m);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < 8; k++) {
				int ni = i + imove[k];
				int nj = j + jmove[k];
				if (0 <= ni && ni < n && 0 <= nj && nj < m) {
					graph[i * m + j].push_back(ni * m + nj);
				}
			}
		}
	}

	return graph;
}

void tour1(int k, int v, int s, int n, int m, int& count, matrix_t& graph, vector<int>& mark) {
	if (k == n * m) {
		for (int i = 0; i < graph[v].size(); i++) {
			if (s == graph[v][i]) {
				count++;
			}
		}
	}
	else {
		for (int i = 0; i < graph[v].size(); i++) {
			if (mark[graph[v][i]] == 0) {
				mark[graph[v][i]] = k + 1;
				tour1(k + 1, graph[v][i], s, n, m, count, graph, mark);
				mark[graph[v][i]] = 0;
			}
		}
	}
}

void tour2(int k, int v, int s, int n, int m, int& count, matrix_t& graph, vector<int>& mark) {
	if (k == n * m) {
		count++;
	}
	else {
		for (int i = 0; i < graph[v].size(); i++) {
			if (mark[graph[v][i]] == 0) {
				mark[graph[v][i]] = k + 1;
				tour2(k + 1, graph[v][i], s, n, m, count, graph, mark);
				mark[graph[v][i]] = 0;
			}
		}
	}
}

int main() {
	int n, m;
	int T;
	int count = 0;
	cin >> n >> m;
	cin >> T;
	matrix_t graph = make_graph(n, m);
	vector<int> mark1(n * m, 0);
	mark1[0] = 1;
	tour1(1, 0, 0, n, m, count, graph, mark1);
	cout << count << endl;

	for (int i = 0; i < T; i++) {
		int temp1, temp2;
		count = 0;
		cin >> temp1 >> temp2;
		vector<int> mark2(n * m, 0);
		mark2[temp1 * m + temp2] = 1;
		tour2(1, temp1 * m + temp2, temp1 * m + temp2, n, m, count, graph, mark2);
		cout << count << endl;
	}

}