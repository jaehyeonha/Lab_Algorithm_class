#include <iostream>
#include <vector>
using namespace std;

int count(int A) {
    int cnt = 0;
    for (; A != 0; A >>= 1){
        if (A & 1){
            cnt++;
        }
    }

    return cnt;
}

bool isIn(int i, int A) {
    return (A & (1 << (i - 2))) != 0;
}

int diff(int A, int j) {
    return (A & ~(1 << (j - 2)));
}


int minimum(int n, int i, int &minJ, int A, matrix_t& W, matrix_t& D) {
    int minV = INF, value;

    for (int j = 2; j <= n; j++) {
        if (!isIn(j, A)){
            continue;
        }
    int value = W[i][j] + D[j][diff(A, j)];
        if (minV > value) {
            minV = value;
            minJ = j;
    }
}

    return minV;
}


void travel(int n, matrix_t& W, matrix_t& D, matrix_t& P, int &minlength) {
    int i, j, k, A;
    int subset_size = pow(2, n - 1);

    for (i = 2; i <= n; i++){
        D[i][0] = W[i][1];
    }

    for (k = 1; k <= n - 2; k++){
        for (A = 0; A < subset_size; A++) {
            if (count(A) != k) {
                continue;
            }
            for (i = 2; i <= n; i++) {
                if (isIn(i, A)) {      
                    continue;
                }
                D[i][A] = minimum(n, i, j, A, W, D);
                P[i][A] = j;
            }
        }
    }

    A = subset_size - 1; // A = V - {v1}
    D[1][A] = minimum(n, 1, j, A, W, D);
    P[1][A] = j;
    minlength = D[1][A];
}

void tour(int v, int A, matrix_t& P) {
    int k = P[v][A];
    if (A == 0){
        cout << "1";
    }
    else {
        cout << k << " -> ";
        tour(k, diff(A, k), P);
    }
}   



