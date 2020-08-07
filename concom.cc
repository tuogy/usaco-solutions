/*
USER: guobich1
TASK: concom
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;
using ii = pair<int, int>;

int main() {
    ifstream fin("concom.in");
    ofstream fout("concom.out");
    
    vector<int> adj[101];
    int own[101][101] = {0};

    int n, i, j, p, v_max = 0;
    fin >> n;
    for (int ii = 0; ii < n; ii++) {
        fin >> i >> j >> p;
        adj[i].push_back(j);
        own[i][j] = p;
        v_max = max({v_max, i, j});
    }
    for (int i = 1; i <= v_max; i++) {
        if (adj[i].empty()) continue;
        int share[101] = {0};
        queue<int> q;
        q.push(i), share[i] = 100;
        while (!q.empty()) {
            int j = q.front(); q.pop();
            for (auto k : adj[j]) {
                share[k] += own[j][k];
                if (share[k] - own[j][k] <= 50 && share[k] > 50) q.push(k);
            }
        }
        for (int j = 1; j <= v_max; j++) {
            if (i != j && share[j] > 50) 
                fout << i << " " << j << endl;
        }
    }

    return 0;
}