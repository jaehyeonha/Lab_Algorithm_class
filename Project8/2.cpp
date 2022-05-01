#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
using namespace std;

typedef struct node* node_ptr;
typedef struct node {
    char symbol;
    int frequency;
    node_ptr left;
    node_ptr right;
} node_t;

struct compare {
    bool operator()(node_ptr p, node_ptr q) {
        return p->frequency > q->frequency;
    }
};

typedef priority_queue<node_ptr, vector<node_ptr>, compare> PriorityQueue;

void huffman(int n, PriorityQueue& PQ)
{
    for (int i = 1; i <= n - 1; i++) {
        node_ptr p = PQ.top(); PQ.pop();
        node_ptr q = PQ.top(); PQ.pop();
        node_ptr r = new node_t(); 
        r->symbol = '+';
        r->frequency = p->frequency + q->frequency;
        r->left = p;
        r->right = q;
        PQ.push(r);
    }
}

void preorder(node_ptr n) {

    cout << n->symbol << ":" << n->frequency << " ";

    if (n->left != NULL) {
        preorder(n->left);
    }
    if (n->right != NULL) {
        preorder(n->right);
    }
}

void inorder(node_ptr n) {

    if (n->left != NULL) {
        inorder(n->left);
    }

    cout << n->symbol << ":" << n->frequency << " ";

    if (n->right != NULL) {
        inorder(n->right);
    }
}

void decode(node_ptr root, vector<int>& code, map <char, vector<int>>& decoder)
{
    if (root->symbol != '+') {
        vector<int> ret;
        ret.resize(code.size());
        copy(code.begin(), code.end(), ret.begin());
        decoder.insert(make_pair(root->symbol, ret));
    }
    else if (root != NULL) {
        code.push_back(0);
        decode(root->left, code, decoder);
        code.pop_back();
        code.push_back(1);
        decode(root->right, code, decoder);
        code.pop_back();
    }
}


int main() {
    int n;
    cin >> n;
    PriorityQueue PQ;
    vector<node_ptr> r(n + 1,0);
    vector<int> code;
    map <char, vector<int>> decoder;
    string str;

    for (int i = 0; i < n; i++) {
        r[i]= new node_t();
        cin >> r[i]->symbol;
    }
    for (int i = 0; i < n; i++) {
        cin >> r[i]->frequency;
        PQ.push(r[i]);
    }

    huffman(n, PQ);

    node_ptr tree= PQ.top();
    preorder(tree);
    cout << endl;
    inorder(tree);
    cout << endl;

    decode(tree, code, decoder);

    cin >> n;
    for (int i = 0; i < n; i++) {
        vector<int> result;
        cin >> str;
        for (int j = 0; j < str.length(); j++) {
            result = decoder.find(str[j])->second;
            for (int k = 0; k < result.size(); k++) {
                cout << result[k];
            }
        }
        cout << endl;
    }

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> str;
        string result;
        node_ptr current = tree;
        for (int j = 0; j < str.length(); j++) {
            if (str[j] == '0')
                current = current->left;
            if (str[j] == '1')
                current = current->right;
            if (current->left == NULL && current->right == NULL)
            {
                result += current->symbol;
                current = tree;
            }
        }
        cout << result << endl;
    }
}