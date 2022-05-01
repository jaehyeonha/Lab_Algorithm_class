#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> matrix_t;

bool hole(int size, int x, int y, matrix_t tro) {
    for (int i = x; i < x + size; i++) {
        for (int j = y; j < y + size; j++) {
            if (tro[i][j] != -1) {
                return false;
            }
        }
    }
    return true;
}

void tromino(int size, int x, int y, int& count, matrix_t& tro) {
    count++;
    int halfsize = size / 2;
    if (hole(halfsize, x, y, tro)) {
        tro[x + halfsize - 1][y + halfsize - 1] = count;
    }
    if (hole(halfsize, x, y + halfsize, tro)) {
        tro[x + halfsize - 1][y + halfsize] = count;
    }
    if (hole(halfsize, x + halfsize, y, tro)) {
        tro[x + halfsize][y + halfsize - 1] = count;
    }
    if (hole(halfsize, x + halfsize, y + halfsize, tro)) {
        tro[x + halfsize][y + halfsize] = count;
    }

    if (size == 2)
        return;

    tromino(halfsize, x, y, count, tro);
    tromino(halfsize, x, y + halfsize, count, tro);
    tromino(halfsize, x + halfsize, y, count, tro);
    tromino(halfsize, x + halfsize, y + halfsize, count, tro);
}

int main() {
    int n;
    int x, y;
    cin >> n >> x >> y;
    int count = 0;

    matrix_t A(n, vector<int>(n, -1));
    A[x][y] = 0;

    tromino(n, 0, 0, count, A);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            cout << A[i][j] << " ";
        }
        cout << A[i][n - 1] << endl;
    }


}