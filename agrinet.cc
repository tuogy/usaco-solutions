/*
USER: guobich1
TASK: agrinet
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <queue>
#include <functional>

using namespace std;

int w[100][100];
bool vis[100];

int main() {
    ifstream fin("agrinet.in");
    ofstream fout("agrinet.out");
    
    int N;
    fin >> N;
    memset(vis, 0, N * sizeof(bool));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fin >> w[i][j];
        }
    }

    int ret = 0;

#define PRIM_ELOGV

#ifdef PRIM_V2
    int q = N - 1;
    vis[0] = true;
    while (q) {
        int besti = -1, bestw = INT_MAX;
        for (int i = 1; i < N; i++) {
            if (!vis[i] && w[0][i] < bestw) bestw = w[0][i], besti = i;
        }
        q--, ret += w[0][besti], vis[besti] = true;
        for (int j = 1; j < N; j++) {
            if (!vis[j] && w[besti][j] < w[0][j]) w[0][j] = w[besti][j]; 
        }
    }
#endif

#ifdef PRIM_ELOGV
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 0});
    while (!pq.empty()) {
        auto v = pq.top().second;
        if (vis[v]) {
            pq.pop();
            continue;
        }
        else vis[v] = true;
        ret += pq.top().first;
        pq.pop();
        for (int j = 0; j < N; j++) {
            pq.push({w[v][j], j});
        }
    }
#endif

    fout << ret << endl;
    return 0;
}