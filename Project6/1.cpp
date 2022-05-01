#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define INF 999999
typedef vector<vector<int>> matrix_t;

int minimum(int i, int j, int& mink, vector<int>& d, matrix_t& M){
    int minValue = INF, value;

    for (int k = i; k <= j - 1; k++) {
        value = M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j];
        if (minValue > value) {
            minValue = value;
            mink = k;
        }
    }

    return minValue;
}


void minmult(int n, vector<int>& d, matrix_t& M, matrix_t& P) {
    for (int i = 1; i <= n; i++){
        M[i][i] = 0;
    }

    for (int diagonal = 1; diagonal <= n - 1; diagonal++){
        for (int i = 1; i <= n - diagonal; i++) {
            int j = i + diagonal,k;
            M[i][j] = minimum(i, j, k, d, M);
            P[i][j] = k;
        }
    }
}

void order(int i, int j, matrix_t& P, string& s){
    if (i == j){
        s += string("(A") + to_string(i)+")";
    }
    else {
        int k = P[i][j];
        s += string("(");
        order(i, k, P, s);
        order(k + 1, j, P, s);
        s += string(")");
    }
}


int main(){
    int n;
    cin>>n;
    vector<int> d(n+1);
    matrix_t M1(n+1,vector<int>(n+1));
    matrix_t P1(n+1,vector<int>(n+1));
    string s1;

    for(int i=0; i<=n; i++){
        cin>>d[i];
    }

    minmult(n,d,M1,P1);
    order(1,n,P1,s1);

    for(int i=1; i<=n; i++){
        for(int j=i; j<=n; j++){
            if(j != n){
                cout<<M1[i][j]<<" ";
            }
            else{
                cout<<M1[i][j]<<endl;
            }
        }
    }
    for(int i=1; i<=n; i++){
        for(int j=i; j<=n; j++){
            if(j != n){
                cout<<P1[i][j]<<" ";
            }
            else{
                cout<<P1[i][j]<<endl;
            }
        }
    }
   
    cout<<M1[1][n]<<endl;

    cout<<s1<<endl;
}
