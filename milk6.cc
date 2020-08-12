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

vector<int> cap[32][32];
vector<ll> rG[32][32];
vector<int> edge_id[32][32];
bool vis[32];
int parent[32];
int parent_edge[32];

bool bfs() {
    memset(vis, 0, V * sizeof(bool));
    queue<int> q;
    q.push(s), vis[s] = true;
    while (!q.empty() && !vis[t]) {
        int u = q.front(); q.pop();
        for (auto v : adj[u]) {
            if (vis[v]) continue;
            for (int i = 0; i < rG[u][v].size(); i++) {
                if (rG[u][v][i] > 0) {
                    q.push(v), vis[v] = true;
                    parent[v] = u, parent_edge[v] = i;
                    break;
                }
            }
        }
    }
    return vis[t];
}

int main() {
    ifstream fin("milk6.in");
    ofstream fout("milk6.out");
    
    fin >> V >> E;
    s = 0, t = V - 1;
    for (int i = 0; i < V; i++) {
        adj[i].clear();
        for (int j = 0; j < V; j++) {
            cap[i][j].clear();
            rG[i][j].clear();
            edge_id[i][j].clear();
        }
    }

    vector<vector<bool>> adj_mat(V, vector<bool>(V, false));
    for (int i = 0; i < E; i++) {
        int u, v, w;
        fin >> u >> v >> w;
        u--, v--;
        adj_mat[u][v] = adj_mat[v][u] = true;
        cap[u][v].push_back(w), cap[v][u].push_back(0);
        rG[u][v].push_back(w * E + 1LL), rG[v][u].push_back(0);
        edge_id[u][v].push_back(i), edge_id[v][u].push_back(i);
    }
    // modify capacity to generate valid solutions
    // parallel edges

    for (int i = 0; i < V; i++) {
        for (int j = i; j < V; j++) {
            if (adj_mat[i][j]) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }

    while (bfs()) {
        ll f = LLONG_MAX;
        for (int v = t; v != s; v = parent[v])
            f = min(f, rG[parent[v]][v][parent_edge[v]]);
        for (int v = t; v != s; v = parent[v])
            rG[parent[v]][v][parent_edge[v]] -= f, rG[v][parent[v]][parent_edge[v]] += f;
    }

    vector<int> ret;
    int min_cut = 0;
    for (int u = 0; u < V; u++) {
        if (!vis[u]) continue;
        for (int v = 0; v < V; v++) {
            if (vis[v]) continue;
            for (int i = 0; i < rG[u][v].size(); i++) {
                if (cap[u][v][i] > 0 && rG[u][v][i] == 0)
                    min_cut += cap[u][v][i], ret.push_back(edge_id[u][v][i] + 1);
            }
        }
    }
    
    fout << min_cut << " " << ret.size() << endl;
    sort(ret.begin(), ret.end());
    for (int i = 0; i < ret.size(); i++) fout << ret[i] << endl;

    return 0;
}