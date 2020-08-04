/*
USER: guobich1
TASK: pprime
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
using ll = long long;

ll mirror1(int a) {
    ll ret = a;
    for (int _a = a; _a; _a /= 10) ret = ret * 10 + _a % 10;
    return ret;
}

ll mirror2(int a) {
    ll ret = a;
    for (int _a = a / 10; _a; _a /= 10) ret = ret * 10 + _a % 10;
    return ret;
}

bool isPrime(vector<int>& primes, ll n) {
    for (auto p : primes) {
        if (p * p > n) return true;
        else if (n % p == 0) return false;
    }
    return true;
}

void dfs(vector<int>& primes, vector<int>& ret, int cur, int ub) {

    ll num1 = mirror1(cur);
    if (num1 <= ub && isPrime(primes, num1)) ret.push_back(num1);
    ll num2 = mirror2(cur);
    if (num2 <= ub && isPrime(primes, num2)) ret.push_back(num2);

    if (num2 > ub && num1 > ub) return;
    for (int i = 0; i < 10; i++) {
        dfs(primes, ret, cur * 10 + i, ub);
    }
}

int main() {
    ifstream fin("pprime.in");
    ofstream fout("pprime.out");
    
    int a, b;
    fin >> a >> b;

    vector<int> ret;
    bool notprime[10001] = {true, true};
    for (int i = 2; i <= 10000; i++) {
        if (notprime[i]) continue;
        else {
            for (int j = i * i; j <= 10000; j += i) notprime[j] = true;
        }
    }
    vector<int> primes;
    for (int i = 2; i <= 10000; i++) {
        if (!notprime[i]) primes.push_back(i);
    }
    for (int i = 1; i <= 9; i++) {
        dfs(primes, ret, i, b);
    }
    sort(ret.begin(), ret.end());
    auto it = lower_bound(ret.begin(), ret.end(), a);
    for (; it != ret.end(); it++) {
        fout << *it << endl;
    }

    return 0;
}