/*
USER: guobich1
TASK: ariprog
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream fin("ariprog.in");
    ofstream fout("ariprog.out");
    
    int N, M, UB;
    fin >> N >> M;
    UB = 2 * M * M;
    vector<bool> isbisq(UB + 1, false);
    for (int p = 0; p <= M; p++) {
        for (int q = p; q <= M; q++) {
            isbisq[p * p + q * q] = true;
        }
    }
    vector<int> bisq;
    for (int i = 0; i <= UB; i++) {
        if (isbisq[i]) bisq.push_back(i);
    }
    vector<pair<int, int>> res;
    for (int i = 0; i < bisq.size(); i++) {
        for (int ii = i + 1; ii < bisq.size(); ii++) {
            int d = bisq[ii] - bisq[i];
            if (bisq[i] + (N - 1) * d <= UB && isbisq[bisq[i] + (N - 1) * d]) {
                bool ok = true;
                for (int k = 0; k < N && ok; k++) {
                    ok &= isbisq[bisq[i] + k * d];
                }
                if (ok) res.push_back({d, bisq[i]});
            }
        }
    }
    sort(res.begin(), res.end());
    for (auto& pr : res) {
        fout << pr.second << " " << pr.first << endl;
    }
    if (res.empty()) fout << "NONE" << endl;

    return 0;
}