/*
USER: guobich1
TASK: hidden
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
using ull = unsigned long long;

const ull base = 1ULL << 55;

class BigInt {
public:
    vector<ull> digits;
    BigInt(int n=0) {
        digits.clear();
        for (; n; n /= base) digits.push_back(n % base);
        if (digits.empty()) digits.push_back(0);
    }

    BigInt& operator+=(const BigInt& rval) {
        int l_size = digits.size(), r_size = rval.digits.size();
        int max_size = max(l_size, r_size);
        ull carry = 0;
        for (int i = 0; i < max_size || carry; i++) {
            ull left = i < l_size ? digits[i] : 0;
            ull right = i < r_size ? rval.digits[i] : 0;
            ull sum = left + right + carry;
            carry = sum / base;
            sum %= base;
            if (i < l_size) digits[i] = sum;
            else digits.push_back(sum);
        }
        return *this;
    }

    BigInt& operator-=(const BigInt& rval) {
        int l_size = digits.size(), r_size = rval.digits.size();
        ull borrow = 0;
        for (int i = 0; i < r_size || borrow; i++) {
            ull left = digits[i];
            ull right = i < r_size ? rval.digits[i] : 0;
            if (left < right + borrow) {
                digits[i] = base + left - right - borrow;
                borrow = 1;
            }
            else {
                digits[i] = left - right - borrow;
                borrow = 0;
            }
        }
        while (digits.size() > 1 && digits.back() == 0) digits.pop_back();
        return *this;
    }

    BigInt& multiply_by_const(int rval, ull carry=0) {
        int l_size = digits.size();
        for (int i = 0; i < l_size || carry; i++) {
            ull left = i < l_size ? digits[i] : 0;
            ull prod = left * rval + carry;
            carry = prod / base;
            prod %= base;
            if (i < l_size) digits[i] = prod;
            else digits.push_back(prod);
        }
        while (digits.size() > 1 && digits.back() == 0) digits.pop_back();
        return *this;
    }

    bool operator<(const BigInt& rval) {
        int l_size = digits.size(), r_size = rval.digits.size();
        if (l_size < r_size) return true;
        else if (l_size > r_size) return false;
        else {
            for (int i = l_size - 1; i >= 0; i--) {
                if (digits[i] < rval.digits[i]) return true;
                else if (digits[i] > rval.digits[i]) return false;
            }
        }
        return false;
    }

    void print() {
        for (auto it = digits.rbegin(); it != digits.rend(); it++) cout << *it << " ";
        cout << endl;
    }
};

char str[100000];

int main() {
    ifstream fin("hidden.in");
    ofstream fout("hidden.out");
    
    int L, K = 27; char c;
    fin >> L;
    for (int i = 0; i < L; i++) {
        fin >> c; str[i] = c;
    }

    BigInt best(0), po2(1);
    for (int i = 0; i < L; i++) {
        best.multiply_by_const(K, str[i] - 'a' + 1);
        po2.multiply_by_const(K);
        cout << i << " " << best.digits.size() << endl;
    }

    BigInt tails[27];
    for (int i = 1; i <= 26; i++) {
        tails[i] = po2;
        tails[i].multiply_by_const(i);
    }

    int ret = 0;
    BigInt cur = best;
    for (int i = 0; i < L - 1; i++) {
        int c = str[i] - 'a' + 1;
        cur.multiply_by_const(K, c);
        cur -= tails[c];
        if (cur < best) {
            ret = i + 1;
            best = cur;
        }
    }

    fout << ret << endl;

    return 0;
}