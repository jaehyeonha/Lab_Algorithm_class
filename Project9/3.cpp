#include <iostream>
#include <vector>
using namespace std;

int n;
typedef vector<vector<int>> matrix_t;

bool promising(int i, matrix_t& W, vector<int>& vcolor) {
    int j = 1;
    bool flag = true;
    while (j < i && flag) {
        if (W[i][j] && vcolor[i] == vcolor[j]) {
            flag = false;
        }
        j++;
    }

    return flag;
}


void m_coloring(int i, int m, int& count, matrix_t& W, vector<int>& vcolor) {
    int color;
    if (promising(i, W, vcolor)) {
        if (i == n) {
            count++;
            vcolor[0] = 0;
        }
        else {
            for (color = 1; color <= m; color++) {
                vcolor[i + 1] = color;
                m_coloring(i + 1, m, count, W, vcolor);
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
    vector <int> vcolor(n + 1, -1);
    for (int i = 0; i < k; i++) {
        cin >> u >> v;
        W[u][v] = 1;
        W[v][u] = 1;
    }
    while (1) {
        m++;
        m_coloring(0, m, count, W, vcolor);
        if (vcolor[0] != -1) {
            break;
        }
    }
    cout << m << endl;
    cout << count << endl;
}

