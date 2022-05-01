#include <iostream>
#include <vector>
using namespace std;

void binsearch(int n, vector<int>& S, int& location, int &count){
    int low, high, mid;
    low = 1; high = n;
    location = 0;
    count = 0;
    while (low <= high && location == 0) {
        count++;
        mid = (low + high) / 2;
        if (mid-1 == S[mid]){
            location = mid;
        }
        else if (mid-1 < S[mid]){
            high = mid - 1;
        }
        else{
            low = mid + 1;
        }
    }
}

int main(){
    int n;
    int count,location;
    cin >> n;
    vector<int> S(n+1);

    for(int i=1; i<=n; i++){
       cin >> S[i];
    }

    binsearch(n,S,location,count);
    cout<<location-1<<endl<<count<<endl;

}