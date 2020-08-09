/*
USER: guobich1
TASK: inflate
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>

using namespace std;

int dp[10002];

int main() {
    ifstream fin("inflate.in");
    ofstream fout("inflate.out");
    
    int M, N;
    fin >> M >> N;
    memset(dp, 0, (M + 1) * sizeof(int));

    int point, time;
    for (int i = 0; i < N; i++) {
        fin >> point >> time;
        for (int j = time; j <= M; j++) {
            dp[j] = max(dp[j], dp[j - time] + point);
        }
    }
    fout << dp[M] << endl;

    return 0;
}