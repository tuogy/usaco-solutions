/*
USER: guobich1
TASK: subset
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

long long dp[400][40];

int main() {
    ifstream fin("subset.in");
    ofstream fout("subset.out");
    
    int N;
    fin >> N;
    int target = N * (N + 1) >> 1;
    if (target & 1) {
        fout << 0 << endl;
        return 0;
    }
    target >>= 1;

    memset(dp, 0, 400*40*sizeof(long long));
    for (int i = 1; i <= target; i++) dp[i][0] = 0;
    for (int i = 0; i <= N; i++) dp[0][i] = 1;
    for (int t = 1; t <= N; t++) {
        for (int s = 1; s <= target; s++) {
            dp[s][t] = dp[s][t - 1];
            if (s >= t) dp[s][t] += dp[s - t][t - 1];
        }
    }
    fout << dp[target][N] / 2 << endl;

    return 0;
}