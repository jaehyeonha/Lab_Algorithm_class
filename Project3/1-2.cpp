#include <iostream>
#include <vector>
using namespace std;

unsigned long long fib4(int n)
{
    vector<unsigned long long> a(n + 1);
    a[0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            a[i] += a[j] * a[i - j - 1];
        }
    }

    return a[n];
}

int main() {
    int n;
    cin >> n;
    cout << fib4(n) << endl;
}