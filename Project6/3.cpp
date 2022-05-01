#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef vector<vector<int>> matrix_t;

void lcs(string x, string y, matrix_t& c, matrix_t& b) {
    for (int i = 1; i < x.size(); i++) {
        for (int j = 1; j < y.size(); j++)
            if (x[i] == y[j]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = 1;
            }
            else {
                c[i][j] = max(c[i][j - 1], c[i - 1][j]);
                if (c[i][j - 1] > c[i - 1][j]) {
                    b[i][j] = 2;
                }
                else {
                    b[i][j] = 3;
                }
            }
    }
}

string get_lcs(int i, int j, matrix_t b, string z) {
    if (i == 0 || j == 0) {
        return "";
    }
    else {
        if (b[i][j] == 1) {
            return get_lcs(i - 1, j - 1, b, z) + z[i];
        }
        else if (b[i][j] == 2) {
            return get_lcs(i, j - 1, b, z);
        }
        else if (b[i][j] == 3) {
            return get_lcs(i - 1, j, b, z);
        }
    }
}

int main() {
    string X, Y,result;
    cin >> X;
    cin >> Y;
    X = " " + X;
    Y = " " + Y;
    matrix_t C1(X.size(),vector<int>(Y.size(), 0));
    matrix_t B1(X.size(), vector<int>(Y.size(), 0));

    lcs(X, Y, C1, B1);
    
    cout << C1[X.size() - 1][Y.size() - 1] << endl;
    cout << get_lcs(X.size() - 1, Y.size() - 1, B1, X)<<endl;
}