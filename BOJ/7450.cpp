#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int num; 
    int weight;
    int count = 0;
    cin >> num;
    vector<int> w(num+1);
    cin >> weight;

    for (int i = 1; i <= num; i++)
    {
        cin >> w[i];
    }
    sort(w.begin() + 1, w.end());
        
    int l = 1, r = num;
    while (l <= r)
    {
         if (w[r] + w[l] > weight) {
             count++; 
             r--; 
         }
         else { 
             count++; 
             r--; 
             l++; 
         }
    }
    cout << count << endl;
}