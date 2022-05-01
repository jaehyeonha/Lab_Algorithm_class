#include <iostream>
#include <vector>
using namespace std;

void partition(int low, int high, int& pivotpoint, vector<int>& S, int &count){
    count++;
    int pivotitem = S[low];
    int j = low;

    for (int i = low + 1; i <= high; i++){
        if (S[i] < pivotitem) {
            j++;
            swap(S[i], S[j]);
        }
    }

    pivotpoint = j;
    swap(S[low], S[pivotpoint]);
}

void quicksort(int low, int high, vector<int> &S, int &count){
    int pivotpoint;
    if (low < high) {
        partition(low, high, pivotpoint, S, count);
        quicksort(low, pivotpoint - 1, S, count);
        quicksort(pivotpoint + 1, high, S, count);
    }
}

int main(){
    int n;
    cin >> n;
    int count = 0;
    int pivot = 0;
    vector<int> S(n+1);

    for(int i=1; i<=n; i++){
        cin >> S[i];
    }

    partition(1,n,pivot,S,count);
    for(int i=1; i<n; i++){
        cout << S[i] << " ";
    }
    cout << S[n] << endl;
    quicksort(1, pivot - 1, S, count);
    quicksort(pivot+1, n, S, count);
    
    cout << count << endl;
    for(int i=1; i<n; i++){
        cout << S[i] << " ";
    }
    cout << S[n] << endl;

    
}
