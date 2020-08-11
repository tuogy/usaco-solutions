/*
USER: guobich1
TASK: fence6
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int inf = 0x3f3f3f3f;
int map_v[10000];
int dist[200][200];

int main() {
    ifstream fin("fence6.in");
    ofstream fout("fence6.out");
    
    int N, u, v, w, nl, nr;
    fin >> N;
    vector<int> edge_weight(N), edge_v_left(N), edge_v_right(N);
    vector<vector<int>> edge_adj_left(N), edge_adj_right(N);

    for (int i = 0; i < N; i++) {
        fin >> v >> w >> nl >> nr;
        v--;
        edge_weight[v] = w;
        for (int j = 0; j < nl; j++) {
            fin >> u; u--;
            edge_adj_left[v].push_back(u);
        }
        for (int j = 0; j < nr; j++) {
            fin >> u; u--;
            edge_adj_right[v].push_back(u);
        }
    }

    int n_v = 0;
    memset(map_v, -1, 10000*sizeof(int));
    for (int i = 0; i < N; i++) {
        int vl_min = min(i, *min_element(edge_adj_left[i].begin(), edge_adj_left[i].end()));
        int vl_max = max(i, *max_element(edge_adj_left[i].begin(), edge_adj_left[i].end()));
        int vr_min = min(i, *min_element(edge_adj_right[i].begin(), edge_adj_right[i].end()));
        int vr_max = max(i, *max_element(edge_adj_right[i].begin(), edge_adj_right[i].end()));
        int vl = vl_min * 100 + vl_max;
        int vr = vr_min * 100 + vr_max;
        if (map_v[vl] == -1) {
            map_v[vl] = n_v++;
        }
        edge_v_left[i] = map_v[vl];
        if (map_v[vr] == -1) {
            map_v[vr] = n_v++;
        }
        edge_v_right[i] = map_v[vr];
    }

    vector<vector<int>> adj(n_v);
    for (int i = 0; i < N; i++) {
        int vl = edge_v_left[i], vr = edge_v_right[i];
        adj[vl].push_back(vr);
        adj[vr].push_back(vl);
        dist[vl][vr] = dist[vr][vl] = edge_weight[i];
    }
    int best_peri = INT_MAX;
    for (int i = 0; i < N; i++) {
        int vl = edge_v_left[i], vr = edge_v_right[i];
        int tmp = dist[vl][vr];
        dist[vl][vr] = dist[vr][vl] = inf;
        vector<int> dist_vl(n_v, inf);
        vector<bool> vis(n_v, false);
        dist_vl[vl] = 0;
        while (!vis[vr]) {
            int dist_shortest = inf, v_shortest = -1;
            for (int j = 0; j < n_v; j++) {
                if (!vis[j] && dist_vl[j] < dist_shortest) 
                    dist_shortest = dist_vl[j], v_shortest = j;
            }
            if (v_shortest == -1) break;
            vis[v_shortest] = true;
            for (int u : adj[v_shortest]) {
                if (dist_vl[u] > dist_shortest + dist[v_shortest][u])
                    dist_vl[u] = dist_shortest + dist[v_shortest][u];
            }
        }
        if (vis[vr] && dist_vl[vr] + tmp < best_peri) {
            best_peri = dist_vl[vr] + tmp;
        }
        dist[vl][vr] = tmp;
    }
    fout << best_peri << endl;

    return 0;
}