/*
USER: guobich1
TASK: money
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using ll = long long;

int main() {
    ifstream fin("money.in");
    ofstream fout("money.out");
    
    int V, N;
    fin >> V >> N;
    vector<ll> coins(V), dp(N + 1);
    for (int i = 0; i < V; i++) fin >> coins[i];
    sort(coins.begin(), coins.end());

    dp[0] = 1;
    for (int v = 0; v < V; v++) {
        for (int n = coins[v]; n <= N; n++) {
            dp[n] += dp[n - coins[v]];
        }
    }
    fout << dp[N] << endl;


    return 0;
}