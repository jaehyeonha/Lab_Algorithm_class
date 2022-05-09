#include <iostream>
#include <vector>
using namespace std;

int W;
typedef vector<vector<int>> matrix_t;
matrix_t A;

bool promising(int i, int weight, int total,vector<int> w) {
    return (weight + total >= W) && (weight == W || weight + w[i + 1] <= W);
}


void sum_of_subsets(int i, int weight, int total, int& count, vector<int>& w, vector<int>& include) {
    if (promising(i, weight, total, w)) {
        if (weight == W){
            count++;
            vector<int> temp;
            for(int j = 1; j<=i; j++){
               if(include[j]==1){
                   temp.push_back(w[j]);
               }
            }
            A.push_back(temp);
        }
        else {
            include[i + 1] = true;
            sum_of_subsets(i + 1, weight + w[i + 1], total - w[i + 1], count, w,include);
            include[i + 1] = false;
            sum_of_subsets(i + 1, weight, total - w[i + 1], count, w, include);
        }
    }
}

int main(){
    int n;
    cin >> n >> W;
    int count = 0;
    int sum =0;
    vector<int> w(n+1);
    for(int i=1; i<=n; i++){
        cin >> w[i];
        sum += w[i];
    }
    vector<int> include(n+1);

    sum_of_subsets(0,0,sum,count,w,include);

    cout << count << endl;
    for(int i=0; i<count; i++){
        for(int j=0; j<A[i].size()-1; j++){
            cout << A[i][j] << " ";
        }
        cout << A[i][A[i].size()-1]<<endl;
    }
    
}