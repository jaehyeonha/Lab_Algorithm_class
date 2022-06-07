#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> divisor(n);
    for (int i = 0; i < n; i++) {
        cin >> divisor[i];
    }

    sort(divisor.begin(), divisor.end());

    cout << divisor[0] * divisor[n - 1] << endl;
}