#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

typedef vector<int> LargeInteger;
int threshold = 0;

void roundup_carry(LargeInteger& v) {
    int carry = 0;
    for (int i = 0; i < v.size(); i++) {
        v[i] += carry;
        carry = v[i] / 10;
        v[i] = v[i] % 10;
    }
    if (carry != 0) {
        v.push_back(carry);
    }
}

void lmult(LargeInteger a, LargeInteger b, LargeInteger& c) {
    c.resize(a.size() + b.size() - 1);
    fill(c.begin(), c.end(), 0);
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            c[i + j] += a[i] * b[j];
        }
    }
    roundup_carry(c);
}


void ladd(LargeInteger a, LargeInteger b, LargeInteger& c) {
    c.resize(max(a.size(), b.size()));
    fill(c.begin(), c.end(), 0);
    for (int i = 0; i < c.size(); i++) {
        if (i < a.size()) {
            c[i] += a[i];
        }
        if (i < b.size()) {
            c[i] += b[i];
        }
    }
    roundup_carry(c);
}

void remove_leading_zeros(LargeInteger& v) {
    while (v.size() != 0 && v.back() == 0) {
        v.pop_back();
    }
}

void div_by_exp(LargeInteger u, int m, LargeInteger& v) {
    if (u.size() == 0) {
        v.resize(0);
    }
    else {
        int k = m < u.size() ? m : u.size();
        v.resize(u.size() - k);
        copy(u.begin() + k, u.end(), v.begin());
    }
}

void rem_by_exp(LargeInteger u, int m, LargeInteger& v) {
    if (u.size() == 0) {
        v.resize(0);
    }
    else {
        int k = m < u.size() ? m : u.size();
        v.resize(k);
        copy(u.begin(), u.begin() + k, v.begin());
        remove_leading_zeros(v);
    }
}

void pow_by_exp(LargeInteger u, int m, LargeInteger& v) {
    if (u.size() == 0) {
        v.resize(0);
    }
    else {
        v.resize(u.size() + m);
        fill(v.begin(), v.end(), 0);
        copy(u.begin(), u.end(), v.begin() + m);
    }
}

void prod(LargeInteger u, LargeInteger v, LargeInteger& r, int &count) {
    count++;
    LargeInteger x, y, w, z;
    LargeInteger t1, t2, t3, t4, t5, t6, t7, t8;
    int n = max(u.size(), v.size());

    if (u.size() == 0 || v.size() == 0) {
        r.resize(0);
    }
    else if (n <= threshold) {
        lmult(u, v, r);
    }
    else {
        int m = n / 2;
        div_by_exp(u, m, x); rem_by_exp(u, m, y);
        div_by_exp(v, m, w); rem_by_exp(v, m, z);

        prod(x, w, t1, count); pow_by_exp(t1, 2 * m, t2);

        prod(x, z, t3, count); prod(w, y, t4, count); ladd(t3, t4, t5); pow_by_exp(t5, m, t6);

        prod(y, z, t7, count);

        ladd(t2, t6, t8); ladd(t8, t7, r);
    }
}

int main() {
    int count = 0;
    cin >> threshold;
    string S1, S2;
    cin >> S1 >> S2;
    LargeInteger A(S1.size()), B(S2.size()), C;
    for (int i = 0; i < S1.size(); i++) {
        A[i] = S1[S1.size() - i - 1] - '0';
    }
    for (int i = 0; i < S2.size(); i++) {
        B[i] = S2[S2.size() - i - 1] - '0';
    }

    prod(A, B, C, count);

    cout << count << endl;
    for (int i = 0; i < C.size(); i++) {
        cout << C[C.size() - i - 1];
    }
    cout << endl;
}
