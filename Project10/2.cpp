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

int W;
int maxprofit = 0;
float bound;
vector<item_t> items;
vector<int> bestset;

bool compare_item(item_t i, item_t j) {
	if (i.profit_per_unit > j.profit_per_unit)
		return true;
	return false;
};

bool promising(int i, int n, int profit, int weight) {
	int j, k, totweight;
	if (weight >= W) {
		cout << i << " " << weight << " " << profit << " " << bound << " " << maxprofit << endl;
		return false;
	}
	else {
		j = i + 1;
		bound = profit;
		totweight = weight;
		while (j <= n && totweight + items[j].weight <= W) {
			totweight += items[j].weight;
			bound += items[j].profit;
			j++;
		}
		k = j;
		if (k <= n) {
			bound += (W - totweight) * ((float)items[k].profit / items[k].weight);
		}
		cout << i << " " << weight << " " << profit << " " << bound << " " << maxprofit << endl;
		return bound > maxprofit;
	}
}


void knapsack4(int i, int n ,int profit, int weight, vector<int> include) {
	if (weight <= W && profit > maxprofit) {
		maxprofit = profit;
		copy(include.begin()+1, include.end(), bestset.begin()+1); 
	}
	if (promising(i, n, profit, weight)) {
		include[i + 1] = true;
		knapsack4(i + 1, n, profit + items[i + 1].profit, weight + items[i + 1].weight, include);
		include[i + 1] = false;
		knapsack4(i + 1, n, profit, weight, include);
	}
}

int main() {
	int n;
	cin >> n >> W;
	vector<int> include(n + 1);
	items.resize(n+1);
	bestset.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> items[i].weight;
	}
	for (int i = 1; i <= n; i++) {
		cin >> items[i].profit;
		items[i].profit_per_unit = items[i].profit / items[i].weight;
	}

	sort(items.begin() + 1, items.end(), compare_item);

	knapsack4(0, n, 0, 0, include);

	cout << maxprofit << endl;
	for (int i = 1; i <= n; i++){
		if (bestset[i]) {
			cout << items[i].weight << " " << items[i].profit << endl;
		}
	}
}