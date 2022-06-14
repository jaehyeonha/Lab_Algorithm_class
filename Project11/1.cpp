#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

typedef struct node* node_pointer;
typedef struct node {
	int level;
	int weight;
	int profit;
	int profit_per_unit;
	float bound;
} nodetype;

int W;
int maxprofit = 0;
vector<nodetype> items;

struct compare {
	bool operator()(node_pointer u, node_pointer v) {
		if (u->bound < v->bound)
			return true;
		return false;
	}
};

typedef priority_queue<node_pointer, vector<node_pointer>, compare> priority_queue_of_node;

bool compare_item(nodetype i, nodetype j) {
	if (i.profit_per_unit > j.profit_per_unit)
		return true;
	return false;
};

float bound(node_pointer u, int n) {
	int j, k, totweight; float result;
	if (u->weight >= W){
		return 0;
    }
	else {
		j = u->level + 1;
		result = u->profit;
		totweight = u->weight;

		while (j <= n && totweight + items[j].weight <= W) {
			totweight += items[j].weight;
			result += items[j].profit;
			j++;
		}
		if (j <= n) {
			result += (W - totweight) * ((float)items[j].profit / items[j].weight);
		}
        
		return result;
	}
}

node_pointer create_node(int level, int weight, int profit, int n) {
	node_pointer v = new nodetype;
	v->level = level;
	v->weight = weight;
	v->profit = profit;
	v->bound = bound(v, n);
	return v;
}

void knapsack6(int n) {
	priority_queue_of_node PQ; node_pointer u, v, s;
	maxprofit = 0;
	s = create_node(0, 0, 0, n);
	PQ.push(s);
	cout << s->level << " " << s->weight << " " << s->profit << " " << s->bound << endl;
	
    while (!PQ.empty()) {
		v = PQ.top();
		PQ.pop();

		if (v->bound > maxprofit) {
			u = create_node(v->level + 1,
				v->weight + items[v->level + 1].weight,
				v->profit + items[v->level + 1].profit, n);
			
            cout << u->level << " " << u -> weight << " " << u->profit << " " << u->bound  << endl;
			
            if (u->weight <= W && u->profit > maxprofit){
				maxprofit = u->profit;
            }
			
            if (u->bound > maxprofit){
				PQ.push(u);
            
            }
			
            u = create_node(v->level + 1, v->weight, v->profit, n);
			
            cout << u->level << " " << u->weight << " " << u->profit << " " << u->bound << endl;
			
            if (u->bound > maxprofit){
				PQ.push(u);
            }
		}
	}
}

int main() {
	int n;
	cin >> n >> W;
	items.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> items[i].weight;
	}
	for (int i = 1; i <= n; i++) {
		cin >> items[i].profit;
		items[i].profit_per_unit = items[i].profit / items[i].weight;
	}

	sort(items.begin() + 1, items.end(), compare_item);

	knapsack6(n);

	cout << maxprofit << endl;
}
