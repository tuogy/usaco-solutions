/*
USER: guobich1
TASK: telecow
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

const int inf = 10000;
int N, M, s, t;
vector<int> adj[200];
int cap[200][200];
int rG[200][200];
int parent[200];
bool vis[200];

bool bfs() {
    memset(vis, 0, N * 2 * sizeof(bool));
    queue<int> q;
    q.push(s), vis[s] = true;
    while (!q.empty() && !vis[t]) {
        int u = q.front(); q.pop();
        for (auto v : adj[u]) {
            if (!vis[v] && rG[u][v] > 0) 
                vis[v] = true, q.push(v), parent[v] = u;
        }
    }
    return vis[t];
}


int main() {
    ifstream fin("telecow.in");
    ofstream fout("telecow.out");
    
    fin >> N >> M >> s >> t;
    s--, t--;
    s = s << 1 | 1; t <<= 1;
    memset(cap, 0, N * 2 * 200 * sizeof(int));
    for (int i = 0; i < N; i++) {
        int in = i << 1, out = i << 1 | 1;
        adj[in].clear(); adj[out].clear();
        adj[in].push_back(out);
        cap[in][out] = 1;
    }
    cap[s - 1][s] = cap[t][t + 1] = inf;

    for (int i = 0; i < M; i++) {
        int u, v;
        fin >> u >> v; u--, v--;
        int ui = u << 1, uo = ui | 1, vi = v << 1, vo = vi | 1;
        adj[uo].push_back(vi);
        adj[vo].push_back(ui);
        cap[uo][vi] = inf;
        cap[vo][ui] = inf;
    }
    memcpy(rG, cap, N * 2 * 200 * sizeof(int));

    int min_cut = 0;
    while (bfs()) {
        min_cut++;
        for (int v = t; v != s; v = parent[v])
            rG[parent[v]][v]--, rG[v][parent[v]]++;
    }
    fout << min_cut << endl;

    vector<int> cuts;
    for (int i = 0; i < N && min_cut; i++) {
        if (i == s >> 1 || i == t >> 1) continue;

        int in = i << 1, out = i << 1 | 1;
        adj[in].clear();
        cap[in][out] = 0;

        memcpy(rG, cap, N * 2 * 200 * sizeof(int));
        int min_cut_new = 0;
        while (bfs()) {
            min_cut_new++;
            for (int v = t; v != s; v = parent[v])
                rG[parent[v]][v]--, rG[v][parent[v]]++;
        }

        if (min_cut_new == min_cut - 1) {
            min_cut--; cuts.push_back(i + 1);
        }
        else {
            adj[in].push_back(out);
            cap[in][out] = 1;
        }
    }

    for (int i = 0; i < cuts.size(); i++) {
        if (i) fout << ' ';
        fout << cuts[i];
    }
    fout << endl;

    return 0;
}