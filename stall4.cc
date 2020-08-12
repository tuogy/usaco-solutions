/*
USER: guobich1
TASK: stall4
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

const int maxN = 405;

vector<int> adj[maxN];
int V, s, t;
int cap[maxN][maxN];
bool vis[maxN];
int parent[maxN];

bool EK_bfs() {
    memset(vis, 0, V * sizeof(bool));
    queue<int> bfs;
    bfs.push(s), vis[s] = true;
    while (!bfs.empty() && !vis[t]) {
        int u = bfs.front(); bfs.pop();
        for (auto v : adj[u]) {
            if (!vis[v] && cap[u][v] > 0)
                vis[v] = true, bfs.push(v), parent[v] = u;
        }
    }
    return vis[t];
}

int main() {
    ifstream fin("stall4.in");
    ofstream fout("stall4.out");
    
    int N, M;
    fin >> N >> M;
    V = 2 + N + M;
    s = 0, t = V - 1;
    for (int i = 0; i < V; i++) adj[i].clear();
    for (int l = 1; l <= N; l++) 
        adj[s].push_back(l), adj[l].push_back(s), cap[s][l] = 1;
    for (int r = N + 1; r <= N + M; r++) 
        adj[r].push_back(t), adj[t].push_back(r), cap[r][t] = 1;
    int n, x;
    for (int l = 1; l <= N; l++) {
        fin >> n;
        for (int i = 0; i < n; i++) {
            fin >> x;
            x += N;
            adj[l].push_back(x), adj[x].push_back(l), cap[l][x] = 1;
        }
    }

    int max_match = 0;
    while (EK_bfs()) {
        max_match++;
        for (int v = t; v != s; v = parent[v]) {
            cap[parent[v]][v]--, cap[v][parent[v]]++;
        }
    }
    fout << max_match << endl;

    return 0;
}