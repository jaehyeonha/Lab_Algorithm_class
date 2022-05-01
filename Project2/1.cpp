#include <iostream>
#include <vector>
using namespace std;


int main(){
    int n,min,max;
    cin >> n;
    vector<int> S(n+1);

    for(int i = 1; i<=n; i++){
        cin >> S[i];
    }
    min = max = S[1];

    for(int i = 1; i<=n; i++){
        if(S[i] < min){
            min = S[i];
        }
        if(S[i] > max){
            max = S[i];
        }
    }

    cout<<min<<endl<<max<<endl;
}