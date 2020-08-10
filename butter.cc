/*
USER: guobich1
TASK: butter
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

int cows[800];

int main() {
    ifstream fin("butter.in");
    ofstream fout("butter.out");
    
    int N, P, C, x, y, w;
    fin >> N >> P >> C;
    memset(cows, 0, P * sizeof(bool));
    vector<vector<pair<int, int>>> adj(P);
    for (int i = 0; i < N; i++) {
        fin >> x; cows[x - 1]++;
    }
    for (int i = 0; i < C; i++) {
        fin >> x >> y >> w;
        adj[x - 1].push_back({y - 1, w});
        adj[y - 1].push_back({x - 1, w});
    }

    int bestd = INT_MAX;
    for (int s = 0; s < P; s++) {
        int ncow = 0, curd = 0;
        vector<int> dist(P, 0x3f3f3f3f);
        vector<bool> vis(P, false);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        dist[s] = 0;
        pq.push({0, s});
        while (!pq.empty() && ncow < N && curd < bestd) {
            int v = pq.top().second; pq.pop();
            if (vis[v]) continue;
            else vis[v] = true;
            if (cows[v]) ncow += cows[v], curd += cows[v] * dist[v];
            for (auto pr : adj[v]) {
                int u = pr.first, d_vu = pr.second;
                if (vis[u]) continue;
                if (dist[u] > dist[v] + d_vu) dist[u] = dist[v] + d_vu, pq.push({dist[u], u});
            }
        }
        if (ncow == N && curd < bestd) bestd = curd; 
    }
    fout << bestd << endl;

    return 0;
}