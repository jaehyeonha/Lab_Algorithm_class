#include <iostream>
#include <vector>
using namespace std;

typedef unsigned long long LongInt;

LongInt fib3(LongInt n,int max)
{   LongInt cur = 1;
    LongInt pre = 0;
    LongInt temp = 0;

    for(int i=0; i<n; i++){
        temp = (cur + pre) % max;
        pre = cur;
        cur = temp;
    }

    return pre;
}




int main(){
    int n;
    int max;
    cin >> n >> max;
    cout << fib3(n,max)<<endl;
}