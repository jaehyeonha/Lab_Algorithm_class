#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define INF 9999

typedef vector<int> ordered_set;
typedef struct node* node_pointer;
typedef struct node {
	int level;
	ordered_set path;
	int bound;
} nodetype;

struct compare {
	bool operator()(node_pointer u, node_pointer v) {
		if (u->bound > v->bound)
			return true;
		return false;
	}
};

typedef priority_queue<node_pointer, vector<node_pointer>, compare> priority_queue_of_node;

typedef vector<vector<int>> matrix_t;

int length(ordered_set path, matrix_t& W) {
	vector<int>::iterator it;
	int len = 0;
	for (it = path.begin(); it != path.end(); it++) {
		if (it != path.end() - 1) {
			len += W[*it][*(it + 1)];
		}
	}
	return len;
}

bool hasOutgoing(int v, ordered_set path) {
	vector<int>::iterator it;
	for (it = path.begin(); it != path.end() - 1; it++) {
		if (*it == v) {
			return true;
		}
	}
	return false;
}

bool hasIncoming(int v, ordered_set path) {
	vector<int>::iterator it;
	for (it = path.begin() + 1; it != path.end(); it++) {
		if (*it == v) {
			return true;
		}
	}
	return false;
}

bool isIn(int i, ordered_set path) {
	for (int j = 0; j < path.size(); j++) {
		if (i == path[j]) {
			return true;
		}
	}
	return false;
}

int bound(node_pointer v, int n, matrix_t& W) {
	int lower = length(v->path, W);
	for (int i = 1; i <= n; i++) {
		if (hasOutgoing(i, v->path)) {
			continue;
		}
		int min = INF;
		for (int j = 1; j <= n; j++) {
			if (i == j) {
				continue;
			}
			if (j == 1 && i == v->path[v->path.size() - 1]) {
				continue;
			}
			if (hasIncoming(j, v->path)) {
				continue;
			}
			if (min > W[i][j]) {
				min = W[i][j];
			}
		}
		lower += min;
	}
	return lower;
}

node_pointer create_node(int level, ordered_set path, int n, matrix_t& W) {
	node_pointer v = new nodetype;
	v->level = level;
	for (int i = 0; i < path.size(); i++) {
		v->path.push_back(path[i]);
	}
	v->bound = bound(v, n, W);
	return v;
}

void travel2(ordered_set& opttour, int& minlength, int n, matrix_t& W) {
	priority_queue_of_node PQ;
	node_pointer u, v;
	minlength = INF;
	vector<int> temp(1, 1);

	v = create_node(0, temp, n ,W);
	cout << v->level << " " << v->bound << " ";
	for (int j = 0; j < v->path.size()-1; j++) {
		cout << v->path[j] << " ";
	}
	cout <<v->path[v->path.size()-1]<< endl;
	PQ.push(v);

	while (!PQ.empty()) {
		v = PQ.top();
		PQ.pop();

		if (v->bound < minlength) {
			for (int i = 2; i <= n; i++) {
				if (isIn(i, v->path)) {
					continue;
				}
				u = create_node(v->level + 1, v->path,n,W);
				u->path.push_back(i);

				if (u->level == n - 2) {
					for (int k = 2; k <= n; k++) {
						if (isIn(k, u->path)) {
							continue;
						}
						u->path.push_back(k);
					}
					u->path.push_back(1);

					if (length(u->path, W) > INF) {
						cout << u->level << " " << "INF" << " ";
					}
					else {
						cout << u->level << " " << length(u->path, W) << " ";
					}
					for (int j = 0; j < u->path.size()-1; j++) {
						cout << u->path[j] << " ";
					}
					cout << u->path[u->path.size() - 1] << endl;

					if (length(u->path, W) < minlength) {
						minlength = length(u->path, W);
						copy(u->path.begin(), u->path.end(), opttour.begin());
					}
				}
				else {
					u->bound = bound(u, n, W);

					if (u->bound > INF) {
						cout << u->level << " " << "INF" << " ";
					}
					else {
						cout << u->level << " " << u->bound << " ";
					}
					for (int j = 0; j < u->path.size()-1; j++) {
						cout << u->path[j] << " ";
					}
					cout << u->path[u->path.size() - 1] << endl;

					if (u->bound < minlength)
						PQ.push(u);
				}
			}

		}
	}
}




int main() {
	int n, m;
	int u, v;
	int minlength = 0;
	cin >> n >> m;
	matrix_t W(n + 1, vector<int>(n + 1, INF));
	ordered_set opttour(n + 1);
	for (int i = 1; i <= n; i++) {
		W[i][i] = 0;
	}

	for (int i = 0; i < m; i++) {
		cin >> u >> v;
		cin >> W[u][v];
	}
	travel2(opttour, minlength, n, W);

	cout << minlength << endl;
	for (int i = 0; i < opttour.size()-1; i++) {
		cout << opttour[i] << " ";
	}
	cout << opttour[opttour.size() - 1] << endl;
}


