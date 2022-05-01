#include<iostream>
#include<vector>
using namespace std;

int main()
{
	int n;
    int T = 1, last;
    cin >> n;
    vector<int> start(n+1), end(n+1);

	for (int i = 0; i < n; i++)
	{
		cin >> start[i] >> end[i];
	}
	
    last = end[0];
	for (int i = 0 ; i < n; i++) 
	{
		if (start[i] >= last)
		{	
			T++;
			last = end[i];
		}
	}
    cout << T << endl;

    last = end[0];
    cout << start[0] << " " << end[0] << endl;
    for (int i = 0 ; i < n; i++) 
	{
		if (start[i] >= last)
		{
			cout << start[i] << " " << end[i] << endl;
		    last = end[i];
		}
	}

}