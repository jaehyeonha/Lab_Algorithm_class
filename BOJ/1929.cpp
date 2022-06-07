#include <iostream>
#include <vector>
using namespace std;

int main(void) {
    int m, n;
    cin >> m >> n;
    vector<int> arr(n+1);
    arr[1] = 1;


    for (int i = 2; i * i <= n; i++) {
        if (arr[i] == 1) {
            continue;
        }
        for (int j = 2; i * j <= n; j++) {
            arr[i * j] = 1;
        }
    }

    for (int i = m; i <= n; i++) {
        if (arr[i] == 0)
            cout << i << "\n";
    }

    return 0;
}