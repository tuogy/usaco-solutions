/*
USER: guobich1
TASK: sprime
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

bool isPrime(vector<int>& primes, int n) {
    for (auto p : primes) {
        if (p * p > n) return true;
        else if (n % p == 0) return false;
    }
    return true;
}

void dfs(vector<int>& primes, ofstream& of, int cur, int n, int N) {
    if (n == N) {
        of << cur << endl;
        return;
    }
    for (int i = 1; i < 10; i += 2) {
        if (isPrime(primes, cur * 10 + i)) 
            dfs(primes, of, cur * 10 + i, n + 1, N);
    }
}

int main() {
    ifstream fin("sprime.in");
    ofstream fout("sprime.out");
    
    int N;
    fin >> N;
    int mx = 1;
    for (int i = 0; i < N; i++) mx *= 10;
    int mxroot = (int)sqrt(mx) + 1;
    vector<bool> notprime(mxroot, false);
    for (int i = 2; i < mxroot; i++) {
        if (notprime[i]) continue;
        else {
            for (int j = i * i; j < mxroot; j += i) notprime[j] = true;
        }
    }
    vector<int> primes;
    for (int p = 2; p < mxroot; p++) {
        if (!notprime[p]) primes.push_back(p);
    }
    vector<int> ret;
    for (auto p : {2, 3, 5, 7}) {
        dfs(primes, fout, p, 1, N);
    }

    return 0;
}