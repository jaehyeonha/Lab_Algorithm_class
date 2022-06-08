#include <iostream>
#include <vector>
using namespace std;

int main(void) {
    int m, n;
    cin >> m >> n;
    vector<int> arr(n+1);
    for (int i = 1; i <= n; i++){
        arr[i] = i;
    }

    for (int i = 2; i * i <= n; i++) {
        if (arr[i] != i) {
            continue;
        }
        for (int j = 2; i * j <= n; j++) {
            arr[i * j] = i;
        }
    }

    for (int i = m; i <= n; i++) {
        if (arr[i] == i)
            cout << i << "\n";
    }

    return 0;
}