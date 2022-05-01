#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> matrix_t;
int threshold = 0;

void print_matrix(int n, matrix_t M) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            cout << M[i][j] << " ";
        }
        cout << M[i][n - 1] << endl;
    }
}

void resize(int n, matrix_t& mat) {
    mat.resize(n, vector<int>(n, 0));
}

void madd(int n, matrix_t A, matrix_t B, matrix_t& C) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void msub(int n, matrix_t A, matrix_t B, matrix_t& C) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void mmult(int n, matrix_t A, matrix_t B, matrix_t& C) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int s = 0; s < n; s++) {
                C[i][j] += A[i][s] * B[s][j];
            }
        }
    }
}
void partition(int m, matrix_t M, matrix_t& M11, matrix_t& M12, matrix_t& M21, matrix_t& M22) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            M11[i][j] = M[i][j];
            M12[i][j] = M[i][j + m];
            M21[i][j] = M[i + m][j];
            M22[i][j] = M[i + m][j + m];
        }
    }
}

void combine(int m, matrix_t& M, matrix_t M11, matrix_t M12, matrix_t M21, matrix_t M22) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            M[i][j] = M11[i][j];
            M[i][j + m] = M12[i][j];
            M[i + m][j] = M21[i][j];
            M[i + m][j + m] = M22[i][j];
        }
    }
}

void strassen(int n, matrix_t A, matrix_t B, matrix_t& C, int& count) {
    count++;

    if (n <= threshold) {
        mmult(n, A, B, C);
    }
    else {
        matrix_t A11, A12, A21, A22;
        matrix_t B11, B12, B21, B22;
        matrix_t C11, C12, C21, C22;
        matrix_t M1, M2, M3, M4, M5, M6, M7;
        matrix_t L, R;
        int m = n / 2;
        resize(m, A11); resize(m, A12); resize(m, A21); resize(m, A22);
        resize(m, B11); resize(m, B12); resize(m, B21); resize(m, B22);
        resize(m, C11); resize(m, C12); resize(m, C21); resize(m, C22);
        resize(m, C11); resize(m, C12); resize(m, C21); resize(m, C22);
        resize(m, M1); resize(m, M2); resize(m, M3); resize(m, M4); resize(m, M5);
        resize(m, M6); resize(m, M7); resize(m, L); resize(m, R);

        partition(m, A, A11, A12, A21, A22);
        partition(m, B, B11, B12, B21, B22);

        madd(m, A11, A22, L);
        madd(m, B11, B22, R);
        strassen(m, L, R, M1, count);

        madd(m, A21, A22, L);
        strassen(m, L, B11, M2, count);

        msub(m, B12, B22, R);
        strassen(m, A11, R, M3, count);

        msub(m, B21, B11, R);
        strassen(m, A22, R, M4, count);

        madd(m, A11, A12, L);
        strassen(m, L, B22, M5, count);

        msub(m, A21, A11, L);
        madd(m, B11, B12, R);
        strassen(m, L, R, M6, count);

        msub(m, A12, A22, L);
        madd(m, B21, B22, R);
        strassen(m, L, R, M7, count);

        madd(m, M1, M4, L);
        msub(m, L, M5, R);
        madd(m, R, M7, C11);

        madd(m, M3, M5, C12);

        madd(m, M2, M4, C21);

        madd(m, M1, M3, L);
        msub(m, L, M2, R);
        madd(m, R, M6, C22);

        combine(m, C, C11, C12, C21, C22);
    }
}



int main() {
    int n;
    cin >> n >> threshold;
    int count = 0;
    int k = 1;
    while (k < n) {
        k *= 2;
    }
    matrix_t A, B, C;
    resize(k, A); resize(k, B); resize(k, C);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> B[i][j];
        }
    }

    strassen(k, A, B, C, count);
    cout << count << endl;
    print_matrix(n, C);
}