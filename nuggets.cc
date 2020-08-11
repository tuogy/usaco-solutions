/*
USER: guobich1
TASK: nuggets
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/*
Suppose v[i] is the nugget size in package i, let's first sort v[1...N] in ascending order.
Let dp[n][k] be the smallest non-negative number x that satisfies the following two conditions:
(1) x can be obtained from the n-smallest nugget sizes v[1...n]
(2) x is equal to k modulo v[1], k=0,...,v[1]-1

(1) implies x = m_1*v[1] + ... + m_n*v[n] for some non-negative integers m1, ..., mn.
If m_n == 0, x is simply dp[n-1][k].
Otherwise, we write x = x' + m_n*v[n] for some x' that is obtainable from v[1...n-1].
From (2), we have x' + m_n * v[n] == k modulo v[1], 
which means x' == k + (v[1] - m_n) * v[n] modulo v[1].
Notice m_n < v[1] because otherwise we can replace m_n with (m_n - v[1]) to get a smaller x.

We can then iterate m_n = 0, ..., v[1] - 1. Once m_n is fixed, x' must also be the smallest number 
that satisfies the modulo condition x' == k + (v[1] - m_n) * v[n] modulo v[1].
This means x' is dp[n-1][(k + (v[1] - m_n) * v[n]) % v[1]]. We select the smallest x from the search.

The complexity of this algorithm is O(N*v_min^2). 
The space complexity is O(v_min) as we notice dp[n] only depends on dp[n-1], and can be optimized with rolling arrays.
*/

const int inf = 21e8;
int v[11];
int dp[2][256];

int main() {
    ifstream fin("nuggets.in");
    ofstream fout("nuggets.out");
    
    int N;
    fin >> N;
    for (int i = 0; i < N; i++) fin >> v[i];
    sort(v, v + N);
    
    auto prev = dp[0], cur = dp[1];
    prev[0] = 0;
    for (int k = 1; k < v[0]; k++) prev[k] = inf;
    for (int n = 1; n < N; n++, swap(cur, prev)) {
        for (int k = 1; k < v[0]; k++) {
            cur[k] = prev[k];
            for (int m = 0; m < v[0]; m++) {
                int r = k + (v[0] - m) * v[n];
                r %= v[0];
                cur[k] = min(cur[k], m * v[n] + prev[r]);
            }
        }
    }
    int ret = 0;
    for (int k = 0; k < v[0]; k++) {
        ret = max(ret, prev[k] - v[0]);
    }
    if (ret > 2000000000) ret = 0;
    fout << ret << endl;


    return 0;
}