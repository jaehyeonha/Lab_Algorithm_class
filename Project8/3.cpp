#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct item* item_ptr;
typedef struct item {
	int id;
	int weight;
	int profit;
	int profit_per_unit; // = profit / weight
} item_t;

int W;
vector<item_t> items;

bool compare_item(item_t i, item_t j) {
	if (i.profit_per_unit > j.profit_per_unit)
		return true;
	return false;
};

void knapsack1(int n,  int& maxprofit, int& totweight, vector<item_t>& temp) {
	maxprofit = totweight = 0;
	for (int i = 1; i <= n; i++) {
		if (totweight + items[i].weight < W) {
			temp.resize(i + 1);
			temp[i].profit = items[i].profit;
			temp[i].weight = items[i].weight;
			maxprofit += items[i].profit;
			totweight += items[i].weight;
		}
		else {
			temp.resize(i + 1);
			temp[i].profit = (W - totweight) * items[i].profit_per_unit;
			temp[i].weight = (W - totweight);
			maxprofit += (W - totweight) * items[i].profit_per_unit;
			totweight += (W - totweight);
			break; 
		}
	}
}

int main() {
	int n;
	int T;
	int maxprofit, totweight;
	vector<item_t> temp;
	cin >> n;
	items.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> items[i].weight;
	}
	for (int i = 1; i <= n; i++) {
		cin >> items[i].profit;
		items[i].profit_per_unit = items[i].profit / items[i].weight;
	}

	sort(items.begin()+1, items.end(), compare_item);
	
	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> W;
		knapsack1(n, maxprofit, totweight,temp);
		cout << maxprofit<<endl;
		for (int j = 1; j <temp.size(); j++) {
			cout << temp[j].weight << " " << temp[j].profit<<endl;
		}
	}

}

