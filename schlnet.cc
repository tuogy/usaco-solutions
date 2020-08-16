/*
USER: guobich1
TASK: schlnet
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <functional>

using namespace std;
using ii = pair<int, int>;

int N, t, scc_counter;
bool adj[100][100];
bool vis[100];
int scc_id[100];
vector<ii> dfs_tf;

void dfs(int u, bool reverse) {
    if (vis[u]) return;
    else {
        vis[u] = true;
        if (reverse)
            scc_id[u] = scc_counter;
        for (int v = 0; v < N; v++) {
            if (!reverse && adj[u][v]) dfs(v, false);
            else if (reverse && adj[v][u]) dfs(v, true);
        }
    }
    if (!reverse)
        dfs_tf.push_back({t++, u});
}

int main() {
    ifstream fin("schlnet.in");
    ofstream fout("schlnet.out");
    
    int v;
    fin >> N;
    memset(adj, 0, N * 100 * sizeof(bool));
    for (int i = 0; i < N; i++) {
        while (true) {
            fin >> v;
            if (v == 0) break;
            else adj[i][v - 1] = true;
        }
    }

    dfs_tf.clear(); t = 0;
    memset(vis, 0, N * sizeof(bool));
    for (int i = 0; i < N; i++) 
        dfs(i, false);
    sort(dfs_tf.begin(), dfs_tf.end());

    memset(vis, 0, N * sizeof(bool));
    scc_counter = 0;
    for (auto it = dfs_tf.rbegin(); it != dfs_tf.rend(); it++) {
        int i = it->second;
        if (!vis[i]) {
            dfs(i, true);
            scc_counter++;
        }
    }

    int n_scc = scc_counter;
    vector<unordered_set<int>> adj_scc(n_scc);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (adj[i][j] && scc_id[i] != scc_id[j]) adj_scc[scc_id[i]].insert(scc_id[j]);
        }
    }
    int min_recv = 0, n_scc_leaves = 0;
    bool vis_scc[100] = {0};

    function<void(int)> dfs_scc = [&](int i){
        if (vis_scc[i]) return;
        vis_scc[i] = true;
        if (adj_scc[i].empty()) {
            if (i) n_scc_leaves++;
            return;
        }
        else {
            for (auto j : adj_scc[i]) 
                dfs_scc(j);
        }
    };

    for (int i = 0; i < n_scc; i++) {
        if (!vis_scc[i]) {
            if (n_scc_leaves) n_scc_leaves--;
            min_recv++;
        }
        dfs_scc(i);
    }

    fout << min_recv << endl;
    fout << min_recv - 1 + n_scc_leaves << endl;

    return 0;
}