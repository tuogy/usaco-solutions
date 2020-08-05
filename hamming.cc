/*
USER: guobich1
TASK: hamming
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int N, B, D;

bool dfs(bool vis[], int cur, vector<int>& ret) {
    if (ret.size() == N) return true;
    else {
        for (int i = cur + 1; i < (1 << B); i++) {
            if (!vis[i]) {
                bool flipped[256] = {0};
                for (int j = i; j < (1 << B); j++) {
                    if (!vis[j] && __builtin_popcount(i ^ j) < D) flipped[j] = true, vis[j] = true;
                }
                ret.push_back(i);
                if (dfs(vis, i, ret)) return true;
                else {
                    ret.pop_back();
                    for (int j = i; j < (1 << B); j++) {
                        if (flipped[j]) vis[j] = false;
                    }
                }
            }
        }
    }
    return false;
}

int main() {
    ifstream fin("hamming.in");
    ofstream fout("hamming.out");
    
    fin >> N >> B >> D;

    int ub = 1 << B;
    bool vis[512] = {0};
    vector<int> ret;
    dfs(vis, -1, ret);

    for (int i = 0; i < N; i++) {
        fout << (i % 10 ? " " : "") << ret[i] << ((i % 10 == 9 || i == N - 1) ? "\n" : "");
    }

    return 0;
}