/*
USER: guobich1
TASK: my_bipartite_match
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
    vector<bool> vis(V, 0);
    queue<int> bfs;
    bfs.push(s), vis[s] = true;
    while (!bfs.empty() && !vis[t]) {
        int u = bfs.front(); bfs.pop();
        for (auto v : adj[u]) {
            if (!vis[v] && rG[u][v] > 0)
                vis[v] = true, parent[v] = u, bfs.push(v);
        }
    }
    return vis[t];
}

int main() {
    ifstream fin("my_bipartite_match.in");
    ofstream fout("my_bipartite_match.out");
    
    int ns, nt, l, r;
    fin >> ns >> nt;
    int s = 0, t = ns + nt + 1;
    vector<vector<int>> adj(t + 1);
    vector<vector<int>> cap(t + 1, vector<int>(t + 1, 0));
    for (int l = 1; l <= ns; l++) cap[s][l] = 1, adj[s].push_back(l), adj[l].push_back(s);
    for (int r = ns + 1; r <= ns + nt; r++) cap[r][t] = 1, adj[t].push_back(r), adj[r].push_back(t);
    while (fin >> l >> r) {
        l++, r += ns + 1;
        adj[l].push_back(r);
        adj[r].push_back(l);
        cap[l][r] = 1;
    }
    vector<vector<int>> rG = cap;
    vector<int> parent(t + 1, -1);

    int max_match = 0;
    while (EK_bfs(adj, rG, parent, s, t)) {
        int f = INT_MAX;
        for (int v = t; v != s; v = parent[v])
            f = min(f, rG[parent[v]][v]);
        max_match += f;
        for (int v = t; v != s; v = parent[v])
            rG[parent[v]][v] -= f, rG[v][parent[v]] += f;
    }

    fout << max_match << endl;
    for (int l = 1; l <= ns; l++) {
        for (int r = 1; r <= nt; r++) {
            if (cap[l][ns + r] && !rG[l][ns + r])
                fout << l - 1 << " " << r - 1 << endl;
        }
    }

    return 0;
}

/*
input data:
6 6
0 1
0 2
2 0
2 3
3 2
4 2
4 3
5 5
*/