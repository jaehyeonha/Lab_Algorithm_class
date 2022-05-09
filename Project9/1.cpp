#include <iostream>
#include <vector>
#include <string>
using namespace std;

int n;

bool promising(int i, vector<int> col) {
    int k = 1;
    bool flag = true;
        while (k < i && flag) {
        if ((col[i] == col[k]) || (abs(col[i] - col[k]) == i - k)) {
            flag = false;
        }
        k++;
    }

    return flag;
}


void queens(int i, vector<int>& col, int& count, vector<int>& max) {
    int j;
    if (promising(i, col)) {
        if (i == n) {
            count++;
            string s = "";
            for (int k = 1; k <= n; k++) {
                s += to_string(col[k]);
            }
            max.resize(s.length());
            vector<int> temp;
            for (int k = 0; k < s.length(); k++) {
                temp.push_back(s[k]-'0');
            }
            
            for (int k = 0; k < s.length(); k++) {
                if ((temp[k]) != (max[k])) {
                    if (temp[k] > max[k]) {
                        for (int t = 0; t < s.length(); t++) {
                            max[t] = temp[t];
                        }
                    }
                    break;
                }
            }
        }
        else {
            for (j = 1; j <= n; j++) {
                col[i + 1] = j;
                queens(i + 1, col, count, max);
            }
        }
    }
}

int main() {
    int count = 0;

    cin >> n;
    vector<int> max;
    vector<int> S(n + 1);

    queens(0, S, count, max);

    cout << count << endl;
    for (int i = 0; i < max.size(); i++) {
        cout << max[i];
    }
}
