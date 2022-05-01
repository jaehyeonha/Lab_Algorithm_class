#include <iostream>
#include <vector>
using namespace std;

#define INF 0xffff
typedef vector<vector<int>> matrix_t;
typedef vector<pair<int, int>> set_of_edges;
typedef pair<int, int> edge_t;

void dijkstra(int n, matrix_t& W, set_of_edges& F, vector<int> &touch) {
    int vnear, min;
    vector<int> length(n + 1);
    F.clear();

    for (int i = 2; i <= n; i++) {
        touch[i] = 1;
        length[i] = W[1][i];
    }

    for (int i = 2; i < n; i++) {
        cout << touch[i] << " ";
    }
    cout << touch[n] << endl;

    for (int k = 0; k < n - 1; k++) {
        min = INF;

        for (int i = 2; i <= n; i++) {
            if (0 <= length[i] && length[i] < min) {
                min = length[i];
                vnear = i;
            }
        }

        F.push_back(make_pair(touch[vnear],vnear));

        for (int i = 2; i <= n; i++) {
            if (length[i] > length[vnear] + W[vnear][i]) {
                length[i] = length[vnear] + W[vnear][i];
                touch[i] = vnear;
            }
        }
        length[vnear] = -1;

        for (int i = 2; i < n; i++) {
            cout << touch[i] << " ";
        }
        cout << touch[n] << endl;
    }
}

int main() {
    int n, m;
    int u, v;
    int k, w, ex;
    cin >> n >> m;
    matrix_t W(n + 1, vector<int>(n + 1, INF));
    vector<int> touch(n + 1);

    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        cin >> W[u][v];
    }

    set_of_edges F;
    dijkstra(n, W, F, touch);
    for (edge_t e : F) {
        u = e.first; v = e.second;
        cout << u << " " << v << " " << W[u][v] << endl;
    }

    cin >> k;
    while (k--) {
        vector<int> s;
        cin >> w;
        ex = touch[w];

        while (ex != 1) {
            s.push_back(ex);
            ex = touch[ex];
        }

        cout << 1 << " " ;
        for (int i = s.size()-1; i >= 0; i--) {
            cout << s[i] << " ";
        }
        cout << w << endl;
    }
}