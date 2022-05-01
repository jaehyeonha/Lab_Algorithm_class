#include <iostream>
#include <vector>
using namespace std;

#define INF 999
typedef vector<vector<int>> matrix_t;

void path(matrix_t& P, int u, int v, vector<int>& p)
{
    int k = P[u][v];
    if (k != 0) {
        path(P, u, k, p);
        p.push_back(k);
        path(P, k, v, p);
    }
}


void floyd2(int n, matrix_t& W, matrix_t& D, matrix_t& P)
{
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            D[i][j] = W[i][j];
            P[i][j] = 0;
        }
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (D[i][j] > D[i][k] + D[k][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = k;
                }
            }
        }
    }
}

int main() {
    int n, m;
    int u, v;
    int T;
    cin >> n >> m;
    matrix_t W(n + 1, vector<int>(n + 1, INF));
    matrix_t D(n + 1, vector<int>(n + 1));
    matrix_t P(n + 1, vector<int>(n + 1));

    for (int i = 1; i <= n; i++) {
        W[i][i] = 0;
    }

    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        cin >> W[u][v];
    }

    floyd2(n, W, D, P);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < n; j++) {
            cout << D[i][j] << " ";
        }
        cout << D[i][n] << endl;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < n; j++) {
            cout << P[i][j] << " ";
        }
        cout << P[i][n] << endl;
    }

    cin >> T;
    for (int i = 0; i < T; i++) {
        cin >> u >> v;

        vector <int> p;
        path(P, u, v, p);

        if (D[u][v] != INF) {
            cout << u << " ";
            for (int j = 0; j < p.size(); j++) {
                cout << p[j] << " ";
            }
            cout << v << endl;
        }
        else {
            cout << "NONE" << endl;
        }
    }
}