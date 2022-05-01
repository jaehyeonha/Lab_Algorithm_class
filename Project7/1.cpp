#include <iostream>
#include <vector>
using namespace std;

#define INF 0xffff
typedef vector<vector<int>> matrix_t;
typedef vector<pair<int, int>> set_of_edges;
typedef pair<int, int> edge_t;

void prim(int n, matrix_t& W, set_of_edges& F) {
    int vnear, min;
    vector<int> nearest(n + 1), distance(n + 1);
    F.clear();

    for (int i = 2; i <= n; i++) {
        nearest[i] = 1;
        distance[i] = W[1][i];
    }
    
    for (int i = 2; i < n; i++) {
        cout << nearest[i] << " ";
    }
    cout << nearest[n] << endl;

    for (int k = 0; k < n-1; k++) {
        min = INF;

        for (int i = 2; i <= n; i++) {
            if (0 <= distance[i] && distance[i] < min) {
                min = distance[i];
                vnear = i;
            }
        }

        F.push_back(make_pair(vnear, nearest[vnear]));
        distance[vnear] = -1;

        for (int i = 2; i <= n; i++) {
            if (distance[i] > W[i][vnear]) {
                distance[i] = W[i][vnear];
                nearest[i] = vnear;
            }
        }

        for (int i = 2; i < n; i++) {
            cout << nearest[i] << " ";
        }
        cout << nearest[n] << endl;
    }
}


int main() {
    int n, m;
    int u, v;
    cin >> n >> m;
    matrix_t W(n + 1, vector<int>(n + 1, INF));

    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        cin>>W[u][v];
        W[v][u] = W[u][v];
    }

    set_of_edges F;
    prim(n, W, F);
    for (edge_t e : F) {
        u = e.first; v = e.second;
        cout << u << " " << v << " " << W[u][v] << endl;
    }
}