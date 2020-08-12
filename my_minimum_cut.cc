/*
USER: guobich1
TASK: my_minimum_cut
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

bool EK_bfs(vector<vector<int>>& adj, vector<vector<int>>& rG, vector<int>& parent, vector<bool>& vis, int s, int t) {
    int V = rG.size();
    fill(vis.begin(), vis.end(), false);
    queue<int> bfs;
    bfs.push(s), vis[s] = true;
    while (!bfs.empty() && !vis[t]) {
        int u = bfs.front(); bfs.pop();
        for (auto v : adj[u]) {
            if (!vis[v] && rG[u][v] > 0) 
                vis[v] = true, bfs.push(v), parent[v] = u;
        }
    }
    return vis[t];
}

int main() {
    ifstream fin("my_minimum_cut.in");
    ofstream fout("my_minimum_cut.out");
    
    int V, E, s, t;
    fin >> V >> E >> s >> t;
    vector<vector<int>> adj(V), cap(V, vector<int>(V, 0));
    for (int i = 0; i < E; i++) {
        int u, v, w;
        fin >> u >> v >> w;
        adj[u].push_back(v), adj[v].push_back(u), cap[u][v] = w;
    }
    auto rG = cap;
    vector<int> parent(V, -1);
    vector<bool> vis(V, false);

    while (EK_bfs(adj, rG, parent, vis, s, t)) {
        int f = INT_MAX;
        for (int v = t; v != s; v = parent[v])
            f = min(f, rG[parent[v]][v]);
        for (int v = t; v != s; v = parent[v])
            rG[parent[v]][v] -= f, rG[v][parent[v]] += f;
    }

    for (int i = 0; i < V; i++) {
        for (auto j : adj[i]) {
            if (vis[i] && !vis[j] && cap[i][j] > 0) 
                fout << i << " " << j << endl;
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