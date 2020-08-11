/*
USER: guobich1
TASK: rockers
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>

using namespace std;

int l[20];
int dp[21][21][21];

int main() {
    ifstream fin("rockers.in");
    ofstream fout("rockers.out");
    
    int N, T, M;
    fin >> N >> T >> M;
    for (int i = 0; i < N; i++) fin >> l[i];
    memset(dp, 0, 21*21*21*sizeof(int));
    for (int n = N - 1; n >= 0; n--) {
        for (int m = M - 1; m >= 0; m--) {
            for (int r = 0; r <= T; r++) {
                dp[n][m][r] = max(dp[n + 1][m][r], dp[n][m + 1][T]);
                if (r >= l[n] && dp[n][m][r] < 1 + dp[n + 1][m][r - l[n]]) 
                    dp[n][m][r] = 1 + dp[n + 1][m][r - l[n]];
            }
        }
    }
    fout << dp[0][0][T] << endl;

    return 0;
}