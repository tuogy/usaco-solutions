/*
USER: guobich1
TASK: bigbrn
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <unordered_set>

using namespace std;

int dp[2][1001];

int main() {
    ifstream fin("bigbrn.in");
    ofstream fout("bigbrn.out");
    
    unordered_set<int> tree;
    int N, T, r, c;
    fin >> N >> T;
    for (int i = 0; i < T; i++) {
        fin >> r >> c;
        tree.insert(r * (N + 1) + c);
    }
    memset(dp, 0, 2 * 1001 * sizeof(int));
    auto prev = dp[0], cur = dp[1];
    int ret = 0;
    for (int r = 1; r <= N; r++) {
        for (int c = 1; c <= N; c++) {
            if (tree.find(r * (N + 1) + c) == tree.end()) {
                cur[c] = min({cur[c - 1], prev[c], prev[c - 1]}) + 1;
                ret = max(ret, cur[c]);
            }
            else cur[c] = 0;
        }
        swap(cur, prev);
    }
    fout << ret << endl;

    return 0;
}