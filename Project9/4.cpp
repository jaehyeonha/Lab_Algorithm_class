#include <iostream>
#include <vector>
using namespace std;

int n;
typedef vector<vector<int>> matrix_t;

bool promising(int i, vector<int>& vindex, matrix_t& W) {
	int j;
	bool flag;
	if (i == n - 1 && !W[vindex[n - 1]][vindex[0]])
		flag = false;
	else if (i > 0 && !W[vindex[i - 1]][vindex[i]])
		flag = false;
	else {
		flag = true;
		j = 1;
		while (j < i && flag) {
			if (vindex[i] == vindex[j])
				flag = false;
			j++;
		}
	}
	return flag;
}


void hamiltonian(int i, int& count, vector<int>& vindex,matrix_t& W) {
	int j;
	if (promising(i, vindex, W)) {
		if (i == n - 1) {
			count++;
		}
		else{
			for (j = 2; j <= n; j++) {
				vindex[i + 1] = j;
				hamiltonian(i + 1, count, vindex, W);
			}
        }
	}
}

int main() {
	int k;
	int u, v;
	int count = 0;
	int m = 0;
	cin >> n >> k;
	matrix_t W(n + 1, vector<int>(n + 1, 0));
	vector <int> vindex(n);
	vindex[0] = 1;
	for (int i = 0; i < k; i++) {
		cin >> u >> v;
		W[u][v] = 1;
		W[v][u] = 1;
	}
	hamiltonian(0, count, vindex, W);
	cout << count;
}