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

bool dp[2][250][250];

int main() {
    ifstream fin("range.in");
    ofstream fout("range.out");
    
    int N;
    fin >> N;
    char x;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fin >> x;
            dp[0][i][j] = x == '1';
        }
    }
    auto prev = dp[0], cur = dp[1];
    for (int s = 2, count = 0;; s++, count = 0, swap(cur, prev)) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i == 0 || j == 0) cur[i][j] = false;
                else if (prev[i][j] && prev[i - 1][j] && prev[i][j - 1] && prev[i - 1][j - 1]) {
                    cur[i][j] = true;
                }
                else cur[i][j] = false;
                count += cur[i][j];
            }
        }
        if (count == 0) break;
        else fout << s << " " << count << endl;
    }

    return 0;
}