#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

typedef struct item {
	int index;
	int value;
} item_type;
typedef vector<item_type> item_list;

int cnt=0;
void find_largest(int n, vector<item_type> S, int& large) {
	int i;
	large = S[0].value;
	for (i = 1; i < log(n); i++) {
		cnt++;
		if (S[i].value > large) {
			large = S[i].value;
		}
	}
}

void tournament(int n, item_list S, vector<item_list> &L, item_type& largest) {
	if (n == 1) 
		largest = S[0];
	else {

		item_list winner;
		for (int i = 0; i < n - 1; i += 2) {
			cnt++;
			if (S[i].value > S[i + 1].value) {
				winner.push_back(S[i]);
				L[S[i].index].push_back(S[i + 1]);
			}
			else {
				winner.push_back(S[i + 1]);
				L[S[i+1].index].push_back(S[i]);
			}
		}
		return tournament(n / 2, winner, L, largest);
	}
}

int main() {
	int n, second_largest;
	cin >> n;
	item_type largest;
	item_list S(n);
	for (int i = 0; i < n; i++) {
		S[i].index = i;
		cin >> S[i].value;
	}
	vector<item_list> L(S.size());
	tournament(n, S, L, largest);
	find_largest(n, L[largest.index], second_largest);
	cout << second_largest<< endl;
	cout << cnt << endl;
}