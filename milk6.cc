/*
USER: guobich1
TASK: milk6
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
using ll = long long;

int V, E, s, t;
vector<int> adj[32];

ll cap[32][32];
int cap_orig[32][32];
ll rG[32][32];
int edge_id[32][32];
bool vis[32];
int parent[32];

bool bfs() {
    memset(vis, 0, V * sizeof(bool));
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
    ifstream fin("milk6.in");
    ofstream fout("milk6.out");
    
    fin >> V >> E;
    s = 0, t = V - 1;
    for (int i = 0; i < V; i++) adj[i].clear();
    for (int i = 0; i < E; i++) {
        int u, v; ll w;
        fin >> u >> v >> w;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
        cap_orig[u][v] += w;
        cap[u][v] += w * E + 1;
        edge_id[u][v] = i;
    }
    // modify capacity to generate valid solutions
    // parallel edges

    memcpy(rG, cap, V * 32 * sizeof(ll));
    while (bfs()) {
        ll f = LLONG_MAX;
        for (int v = t; v != s; v = parent[v])
            f = min(f, rG[parent[v]][v]);
        for (int v = t; v != s; v = parent[v])
            rG[parent[v]][v] -= f, rG[v][parent[v]] += f;
    }

    vector<int> ret;
    int min_cut = 0;
    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) {
            if (vis[u] && !vis[v] && cap_orig[u][v] > 0) {
                min_cut += cap_orig[u][v];
                ret.push_back(edge_id[u][v] + 1);
            }
        }
    }
    fout << min_cut << " " << ret.size() << endl;
    sort(ret.begin(), ret.end());
    for (int i = 0; i < ret.size(); i++) fout << ret[i] << (i + 1 == ret.size() ? '\n' : ' ');

    return 0;
}