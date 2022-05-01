#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> matrix_t;

void matrixmult(int n, int k, int m, matrix_t A, matrix_t B, matrix_t& C) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            C[i][j] = 0;
            for (int s = 1; s <= k; s++) {
                C[i][j] += A[i][s] * B[s][j];
            }
        }
    }
}

int main() {
    int n, k, m;
    cin >> n >> k >> m;
    matrix_t A(n + 1, vector<int>(k + 1));
    matrix_t B(k + 1, vector<int>(m + 1));
    matrix_t C(n + 1, vector<int>(m + 1));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            cin >> A[i][j];
        }
    }
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> B[i][j];
        }
    }

    matrixmult(n, k, m, A, B, C);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < m; j++) {
            cout << C[i][j] << " ";
        }
        cout << C[i][m] << endl;
    }
}