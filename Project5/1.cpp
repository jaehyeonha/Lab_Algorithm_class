#include <iostream>
#include <vector>
using namespace std;

int bin2(int n, int k, int max){
    vector<int> B(k+1 , 1);

    for(int i=0; i<n; i++) {
        for(int j=min(i,k); j>0; j--)
            B[j] = (B[j-1] + B[j]) % max;
    }

    return B[k];
}

int main(){
    int n,k;
    int max;
    cin >> n >> k >> max;
    cout << bin2(n, k, max) << endl;
}
