/*
USER: guobich1
TASK: runround
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void gen_round(int digits, vector<int>& cur, int dg, vector<int>& rounds) {
    if (cur.size() == dg) {
        int vis[10] = {0};
        int nvis = 0, i = 0;
        while (!vis[cur[i]]) {
            vis[cur[i]] = 1, nvis++;
            i = (i + cur[i]) % dg;
        }
        if (nvis == dg && i == 0) {
            int num = 0;
            for (auto n : cur) num = num * 10 + n;
            rounds.push_back(num);
        }
    }
    else {
        for (int d = 1; d <= 9; d++) {
            int bit = 1 << d;
            if (digits & bit) {
                cur.push_back(d);
                digits ^= bit;
                gen_round(digits, cur, dg, rounds);
                digits ^= bit;
                cur.pop_back();
            }
        }
    }
}

int main() {
    ifstream fin("runround.in");
    ofstream fout("runround.out");
    
    int M;
    fin >> M;
    int dg = 0;
    for (int m = M; m; m /= 10) dg++;

    int digits = (1 << 10) - 1;
    vector<int> cur, rounds;
    gen_round(digits, cur, dg, rounds);
    cur.clear();
    if (dg + 1 <= 9) gen_round(digits, cur, dg + 1, rounds);
    int res = INT_MAX;
    for (auto r : rounds) {
        if (r > M && r < res) res = r;
    }
    
    fout << res << endl;

    return 0;
}