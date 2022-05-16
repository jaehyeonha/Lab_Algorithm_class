#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct item* item_ptr;
typedef struct item {
	int id;
	int weight;
	int profit;
	int profit_per_unit;
} item_t;

typedef vector<vector<int>> matrix_t;
vector<item_t> items;

bool compare_item(item_t i, item_t j) {
	if (i.profit_per_unit > j.profit_per_unit)
		return true;
	return false;
};

int knapsack3(int n, int W, matrix_t& P) {
	if (n == 0 || W <= 0) {
		return 0;
	}

	int lvalue = knapsack3(n - 1, W, P);
	int rvalue = knapsack3(n - 1, W - items[n].weight, P);
	
	if (items[n].weight > W) {
		P[n][W] = lvalue;
	}
	else {
		P[n][W] = max(lvalue, items[n].profit + rvalue);
	}

	return P[n][W];
}

int main() {
	int n, T, num;
	cin >> n;
	items.resize(n+1);
	for (int i = 1; i <= n; i++) {
		cin >> items[i].weight;
	}
	for (int i = 1; i <= n; i++) {
		cin >> items[i].profit;
		items[i].profit_per_unit = items[i].profit / items[i].weight;
	}

	sort(items.begin() + 1, items.end(), compare_item);

	cin >> T;
	for (int i = 0; i < T; i++) {	
		cin >> num;
		matrix_t P(n + 1, vector<int>(num + 1,-1));
		cout << knapsack3(n, num, P) << endl;
		for (int j = 1; j <= n; j++) {
			for (int k = 1; k <= num; k++) {
				if (P[j][k] != -1) {
					cout << j << " " << k << " " << P[j][k] << endl;
				}
			}
		}
	}
}