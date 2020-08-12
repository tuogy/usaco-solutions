/*
USER: guobich1
TASK: buylow
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <deque>
#include <vector>
#include <algorithm>

using namespace std;

class BigInt {
public:
    vector<int> digits;

    BigInt(int n) {
        digits.clear();
        while (n) {
            digits.push_back(n % 10);
            n /= 10;
        }
    }

    void operator+=(const BigInt& b) {
        int carry = 0;
        for (int i = 0; i < max(digits.size(), b.digits.size()); i++) {
            int left = (i >= digits.size() ? 0 : digits[i]);
            int right = (i >= b.digits.size() ? 0 : b.digits[i]);
            int s = left + right + carry;
            carry = s / 10;
            s %= 10;
            if (i >= digits.size()) digits.push_back(s);
            else digits[i] = s; 
        }
        if (carry) digits.push_back(carry);
    }

    void operator-=(const BigInt& b) {
        int borrow = 0;
        for (int i = 0; i < digits.size(); i++) {
            int left = digits[i];
            int right = (i >= b.digits.size() ? 0 : b.digits[i]);
            int s = left - right - borrow;
            if (s < 0) s += 10, borrow = 1;
            else borrow = 0;
            digits[i] = s;
        }
        while (digits.size() > 1 && digits.back() == 0) digits.pop_back();
    }

    void operator=(const BigInt& b) {
        digits = b.digits;
    }

    string to_string() {
        string ret;
        for (auto it = digits.rbegin(); it != digits.rend(); ++it) ret += *it + '0';
        return ret;
    }
};

using iI = pair<int, BigInt>;
int p[5000];

int main() {
    ifstream fin("buylow.in");
    ofstream fout("buylow.out");
    
    int N;
    fin >> N;
    for (int i = 0; i < N; i++) fin >> p[i];
    vector<deque<iI>> dp;
    vector<BigInt> dp_sum;
    for (int i = 0; i < N; i++) {
        auto it = lower_bound(dp.begin(), dp.end(), p[i], [](const deque<iI>& dq, int v){return dq.back().first > v;});
        int i_dp = it - dp.begin();
        if (i_dp == 0) {
            if (it == dp.end()) {
                dp_sum.push_back(1);
                dp.push_back(deque<iI>{{p[i], 1}});
            }
            else if (dp[i_dp].back().first < p[i]) {
                dp_sum[i_dp] += 1; 
                dp[i_dp].push_back({p[i], 1});
            }
        }
        else {
            while (dp[i_dp - 1].front().first <= p[i]) {
                auto c = dp[i_dp - 1].front().second;
                dp_sum[i_dp - 1] -= c;
                dp[i_dp - 1].pop_front();
            }
            auto cur = make_pair(p[i], dp_sum[i_dp - 1]);
            if (it == dp.end()) {
                dp.push_back(deque<iI>{cur});
                dp_sum.push_back(cur.second);
            }
            else if (it->back().first < p[i]) {
                it->push_back(cur);
                dp_sum[i_dp] += cur.second;
            }
            else {
                dp_sum[i_dp] += cur.second;
                dp_sum[i_dp] -= it->back().second;
                it->back().second = cur.second;
            }
        }
    }
    fout << dp_sum.size() << " " << dp_sum.back().to_string() << endl;
    

    return 0;
}