/*
USER: guobich1
TASK: ditch
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

int V, E;
vector<int> adj[200];
int cap[200][200];
int rG[200][200];
int parent[200];
bool vis[200];

bool EK_bfs(int s, int t) {
    memset(vis, 0, V*sizeof(bool));
    queue<int> bfs;
    bfs.push(s), vis[s] = true;
    while (!bfs.empty() && !vis[t]) {
        int u = bfs.front(); bfs.pop();
        for (int v : adj[u]) {
            if (!vis[v] && rG[u][v] > 0) 
                bfs.push(v), vis[v] = true, parent[v] = u;
        }
    }
    return vis[t];
}

int main() {
    ifstream fin("ditch.in");
    ofstream fout("ditch.out");
    
    fin >> E >> V;
    int s = 0, t = V - 1;
    for (int i = 0; i < V; i++) adj[i].clear();
    memset(cap, 0, V*200*sizeof(int));
    for (int i = 0; i < E; i++) {
        int u, v, w;
        fin >> u >> v >> w;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
        cap[u][v] += w;
    }
    memcpy(rG, cap, V*200*sizeof(int));

    int max_flow = 0;
    while (EK_bfs(s, t)) {
        int flow = INT_MAX;
        for (int v = t; v != s; v = parent[v])
            flow = min(flow, rG[parent[v]][v]);
        max_flow += flow;
        for (int v = t; v != s; v = parent[v])
            rG[parent[v]][v] -= flow, rG[v][parent[v]] += flow;
    }

    fout << max_flow << endl;

    return 0;
}