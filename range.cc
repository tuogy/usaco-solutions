/*
USER: guobich1
TASK: range
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>

using namespace std;

int n_squares[251];
bool line[250];
int dp[2][250];

int main() {
    ifstream fin("range.in");
    ofstream fout("range.out");
    
    int N;
    fin >> N;
    char x;
    memset(dp[0], 0, N * sizeof(int));
    memset(n_squares, 0, (N + 1) * sizeof(int));
    auto prev = dp[0], cur = dp[1];
    for (int i = 0; i < N; i++, swap(prev, cur)) {
        for (int j = 0; j < N; j++) {
            fin >> x;
            line[j] = x == '1';
            if (line[j])
                cur[j] = min({j ? cur[j - 1] : 0, j ? prev[j - 1] : 0, prev[j]}) + 1;
            else cur[j] = 0;
            n_squares[cur[j]]++;
        }
    }
    for (int i = 249; i >= 0; i--) n_squares[i] += n_squares[i + 1];
    for (int i = 2; i <= 250; i++) {
        if (n_squares[i]) fout << i << " " << n_squares[i] << endl;
        else break;
    }

    return 0;
}