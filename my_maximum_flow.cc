/*
USER: guobich1
TASK: my_maximum_flow
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

bool EK_bfs(vector<vector<int>>& adj, vector<vector<int>>& rG, vector<int>& parent, int s, int t) {
    int V = rG.size();
    queue<int> bfs;
    vector<bool> vis(V, false);
    bfs.push(s), vis[s] = true;
    while (!bfs.empty() && !vis[t]) {
        int u = bfs.front(); bfs.pop();
        for (auto v : adj[u]) {
            if (!vis[v] && rG[u][v] > 0) {
                parent[v] = u, bfs.push(v), vis[v] = true;
            }
        }
    }
    return vis[t];
}

int main() {
    ifstream fin("my_maximum_flow.in");
    ofstream fout("my_maximum_flow.out");
    
    int V, E, s, t;
    int u, v, w;
    fin >> V >> E >> s >> t;
    vector<vector<int>> adj(V), cap(V, vector<int>(V, 0));
    for (int i = 0; i < E; i++) {
        fin >> u >> v >> w;
        cap[u][v] = w;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<vector<int>> rG = cap;
    vector<int> parent(V);

    int max_flow = 0;
    while (EK_bfs(adj, rG, parent, s, t)) {
        int f = INT_MAX;
        for (int v = t; v != s; v = parent[v])
            f = min(f, rG[parent[v]][v]);
        max_flow += f;
        for (int v = t; v != s; v = parent[v]) {
            rG[parent[v]][v] -= f;
            rG[v][parent[v]] += f;
        }
    }

    fout << max_flow << endl;
    for (int u = 0; u < V; u++) {
        for (auto v : adj[u]) {
            if (cap[u][v] > 0 && rG[u][v] < cap[u][v]) 
                fout << u << " " << v << " " << cap[u][v] - rG[u][v] << endl;
        }
    }

    return 0;
}

/*
input data:
6 10 0 5
0 1 16
0 2 13
1 2 10
1 3 12
2 1 4
2 4 14
3 2 9
3 5 20
4 3 7
4 5 4
*/