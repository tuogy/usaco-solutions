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

const int inf = 21e8;
int a[11];
int dp[2][256];

int main() {
    ifstream fin("nuggets.in");
    ofstream fout("nuggets.out");
    
    int N;
    fin >> N;
    for (int i = 0; i < N; i++) fin >> a[i];
    sort(a, a + N);
    
    auto prev = dp[0], cur = dp[1];
    prev[0] = 0;
    for (int k = 1; k < a[0]; k++) prev[k] = inf;
    for (int n = 1; n < N; n++, swap(cur, prev)) {
        for (int k = 1; k < a[0]; k++) {
            cur[k] = prev[k];
            for (int m = 0; m < a[0]; m++) {
                int r = k + (a[0] - m) * a[n];
                r %= a[0];
                cur[k] = min(cur[k], m * a[n] + prev[r]);
            }
        }
    }
    int ret = 0;
    for (int k = 0; k < a[0]; k++) {
        ret = max(ret, prev[k] - a[0]);
    }
    if (ret > 2000000000) ret = 0;
    fout << ret << endl;


    return 0;
}