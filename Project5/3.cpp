#include <iostream>
#include <vector>
#define newMatrix(n,s) vector<vector<int> > n(s, vector<int>(s , 0))
using namespace std;

void path3(int n, vector <vector<int>> t, vector<vector<int>>&c,  vector<vector<int>> &path){
     for (int i = n - 1; i >= 0; i--){
      for (int j = 0; j <= i; j++) {
        if(c[i+1][j]> c[i+1][j+1]){
            path[i][j]=j;
        }
        else{
            path[i][j]=j+1;
        }
        c[i][j] = c[i + 1][path[i][j]] + t[i][j];
      }
   }   
}

int main() {
    int n;
    cin>>n;
    vector <vector<int>> triangle(n+1, vector <int>(n+1, 0));
    vector <vector<int>> cache(n+1, vector <int>(n+1, 0));
    vector <vector<int>> path(n+1, vector<int>(n+1, 0));


   for (int i=0; i<n; i++){
        for (int j=0; j<=i; j++){
            cin>>triangle[i][j];
        }
    }

   path3(n, triangle, cache, path);
   cout << cache[0][0] << endl;

   int s=0;
   for (int i = 0; i < n; i++){
       cout<<triangle[i][s]<<" ";
       s=path[i][s];
   }
}