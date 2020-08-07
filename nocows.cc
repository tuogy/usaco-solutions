/*
USER: guobich1
TASK: nocows
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>

using namespace std;

const int mod = 9901;
int dp[100][200];
int dp_prefix[100][200];

int main() {
    ifstream fin("nocows.in");
    ofstream fout("nocows.out");
    
    int N, K;
    fin >> N >> K;
    memset(dp, 0, 100*200*sizeof(int));
    memset(dp_prefix, 0, 100*200*sizeof(int));

    dp[1][1] = 1;
    for (int k = 1; k <= K; k++) {
        int n_max = min((1 << min(8, k)) - 1, N);
        for (int n = (k << 1) - 1; n <= n_max; n++) {
            for (int l = 1; l <= n - 2; l++) {
                int r = n - 1 - l;
                dp[k][n] += dp[k - 1][l] * dp_prefix[k - 2][r];
                dp[k][n] += dp_prefix[k - 2][l] * dp[k - 1][r];
                dp[k][n] += dp[k - 1][l] * dp[k - 1][r];
                dp[k][n] %= mod;
            }
        }
        for (int n = 1; n <= n_max; n++) {
            dp_prefix[k][n] = (dp_prefix[k - 1][n] + dp[k][n]) % mod;
        }
    }

    fout << dp[K][N] << endl;


    return 0;
}