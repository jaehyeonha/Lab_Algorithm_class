#include <iostream>
#include <vector>
using namespace std;

#define INF 999999

typedef vector<vector<int>> matrix_t;

typedef struct node* node_ptr;
typedef struct node {
    int key;
    node_ptr left;
    node_ptr right;
} node_t;



int minimum(int i, int j, int& mink, vector<int>& p, matrix_t& M) {
   int minValue = INF; int value;

    for (int k = i; k <= j; k++) {
        int sum = 0;
        for (int s = i; s <= j; s++) {
            sum += p[s];
        }
        value = M[i][k-1] + M[k + 1][j] + sum;
        if (minValue > value) {
			minValue = value;
			mink = k;
		}
    }

    return minValue;
}

void optsearchtree(int n, vector<int>& p, matrix_t& A, matrix_t& R) {

    for (int i = 1; i <= n; i++) {
        A[i][i - 1] = 0; A[i][i] = p[i];
        R[i][i - 1] = 0; R[i][i] = i;
    }

    A[n + 1][n] = R[n + 1][n] = 0;

    for (int diagonal = 1; diagonal <= n - 1; diagonal++) {
        for (int i = 1; i <= n - diagonal; i++) {
            int j = i + diagonal, k;
            A[i][j] = minimum(i, j, k, p, A);
            R[i][j] = k;
        }
    }
}

node_ptr tree(int i, int j, vector<int>& keys, matrix_t& R) {
    int k = R[i][j];
    if (k == 0) {
        return NULL;
    }
    else {
        node_ptr node = new node_t();
        node->key = keys[k];
        node->left = tree(i, k - 1, keys, R);
        node->right = tree(k + 1, j, keys, R);
        return node;
    }
}

void preorder(node_ptr n,int size, int &pre) {

    pre++;
	if (pre == size) {
        cout << n->key;
    }
	else {
        cout << n->key << " ";
    }

	if (n->left != NULL) {
        preorder(n->left,size,pre);
    }
	if (n->right != NULL) {
        preorder(n->right,size,pre);
    }

}

void inorder(node_ptr n,int size, int &in) {
	
	if (n->left != NULL) {
        inorder(n->left,size,in);
    }

    in++;
	if (in == size) {
        cout << n->key;
    }
	else {
        cout << n->key << " ";
    }

	if (n->right != NULL) {
        inorder(n->right,size,in);
    }
}


int main() {
    int n;
    cin >> n;
    vector<int> K(n + 1);
    vector<int> p(n + 1);
    matrix_t A1(n + 2, vector<int>(n + 2));
    matrix_t R1(n + 2, vector<int>(n + 2));
    int num = 0;

    for (int i = 1; i <= n; i++) {
        cin >> K[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }

    optsearchtree(n, p, A1, R1);

    for (int i = 1; i <= n+1; i++) {
        for (int j = i-1; j <= n; j++) {
            if (j != n) {
                cout << A1[i][j] << " ";
            }
            else {
                cout << A1[i][j] << endl;
            }
        }
    }

    for (int i = 1; i <= n+1; i++) {
        for (int j = i-1; j <= n; j++) {
            if (j != n) {
                cout << R1[i][j] << " ";
            }
            else {
                cout << R1[i][j] << endl;
            }
        }
    }

    cout << A1[1][n] <<endl;

    node_ptr OPST = tree(1, n, K,R1);

    preorder(OPST, n, num);
    cout << endl;
    inorder(OPST, n, num);

}



