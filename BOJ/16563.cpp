#include <iostream>
#include <vector>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    cin >> n;
    vector<int> arr(5000001);
    for (int i = 1; i <= 5000000; i++){
        arr[i] = i;
    }

    for (int i = 2; i * i <= 5000000; i++) {
        if (arr[i] != i) {
            continue;
        }
        for (int j = 2; i * j <= 5000000; j++) {
            if (arr[i * j] == i * j){
                arr[i * j] = i;
            }
        }
    }
        
    for(int i=0; i<n; i++){
        int temp;
        cin >> temp;
        while(temp > 1){
            cout << arr[temp] << " "; 
            temp /= arr[temp];
        }
        cout << "\n"; 
    } 
}