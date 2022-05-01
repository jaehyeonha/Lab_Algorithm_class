// 카라츠바 알고리즘 구현

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
int cnt = 0;
int threshold;
typedef vector<int> large_integer;

int dig(int n) {
    int digit = 1;
    while ((n / 10) != 0) {
        n /= 10;
        digit++;
    }
    return digit;
}

void roundup_carry(large_integer& n) {
    int carry = 0;
    for (int i = 0; i < n.size(); i++) {
        n[i] += carry;
        carry = n[i] / 10;
        n[i] = n[i] % 10;
    }

    if (carry != 0)
        n.push_back(carry);
    // push_back -> 새로운 원소 추가, carry 값 할당
}

void roundown_borrow(large_integer& n) {
    int borrow = 0;
    for (int i = 0; i < n.size(); i++) {
        n[i] += borrow;
        borrow = 0;
        if (n[i] < 0) {
            n[i] += 10;
            borrow = -1;
        }
    }
    if (n.back() == 0) {
        n.pop_back();
    }
}

large_integer ladd(large_integer a, large_integer b) {
    large_integer c;
    c.resize(max(a.size(), b.size()), 0);

    for (int i = 0; i < c.size(); i++) {
        if (i < a.size()) c[i] += a[i];
        if (i < b.size()) c[i] += b[i];
    }
    roundup_carry(c);
    return c;
}

large_integer lsub(large_integer a, large_integer b) {
    large_integer c;
    c.resize(max(a.size(), b.size()), 0);

    for (int k = 0; k < c.size(); k++) {
        if (a.size() == c.size()) {
            if (k >= b.size()) c[k] = a[k];
            else  c[k] = a[k] - b[k];
        }
        else if (b.size() == c.size()) {
            if (k >= a.size()) c[k] = b[k];
            else  c[k] = b[k] - a[k];
        }
    }

    roundown_borrow(c);
    return c;
}


large_integer lmut(large_integer a, large_integer b) {
    large_integer c;
    c.resize(a.size() + b.size() - 1, 0);

    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            c[i + j] += a[i] * b[j];
        }
    }
    roundup_carry(c);
    return c;
}

void remove_leading_zeros(large_integer& v) {
    while (v.size() != 0 && v.back() == 0)
        v.pop_back();
}

large_integer div_by_exp(large_integer u, int m) {
    large_integer res;
    if (u.size() == 0 || m > u.size())
        res.resize(0);
    else {
        res.resize(u.size() - m, 0);
        for (int i = 0; i < res.size(); i++) {
            res[i] = u[i + m];
        }
        remove_leading_zeros(res);
    }
    return res;
}

large_integer rem_by_exp(large_integer u, int m) {
    large_integer res;
    if (u.size() == 0)
        res.resize(0);
    else {
        int k = m < u.size() ? m : u.size();
        res.resize(k, 0);
        for (int i = 0; i < res.size(); i++) {
            res[i] = u[i];
        }
        remove_leading_zeros(res);
    }
    return res;
}

large_integer pow_by_exp(large_integer u, int m) {
    large_integer res;
    if (u.size() == 0) {
        res.resize(0);
    }
    else {
        res.resize(u.size() + m, 0);
        for (int i = m; i < res.size(); i++)
            res[i] = u[i - m];
    }
    return res;
}

large_integer karatsuba(large_integer u, large_integer v) {
    cnt++;
    large_integer x, y, w, z, r, p, q;
    int n = max(u.size(), v.size());
    if (u.size() == 0 || v.size() == 0) {
        r.resize(0);
        return r;
    }
    else if (n <= threshold) {
        r = lmut(u, v);
        return r;
    }
    else {
        int m = n / 2;
        x = div_by_exp(u, m); y = rem_by_exp(u, m);
        w = div_by_exp(v, m); z = rem_by_exp(v, m);

        r = karatsuba(ladd(x, y), ladd(w, z));
        p = karatsuba(x, w);
        q = karatsuba(y, z);

        return ladd(ladd(pow_by_exp(p, 2 * m), pow_by_exp(lsub(lsub(r, p), q), m)), q);
    }
}

int main() {
    string a, b;
    cin >> threshold >> a >> b;

    large_integer u, v, r;
    u.assign(a.size(), 0);
    v.assign(b.size(), 0);

    for (int i = a.size() - 1; i >= 0; i--)
        u[i] = a[a.size() - 1 - i] - '0';
    for (int i = b.size() - 1; i >= 0; i--)
        v[i] = b[b.size() - 1 - i] - '0';

    r = karatsuba(u, v);
    cout << cnt << endl;
    for (int i = r.size() - 1; i >= 0; i--)
        cout << r[i];

}