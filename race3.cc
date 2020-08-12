/*
USER: guobich1
TASK: race3
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

vector<int> adj[50], adj_inverse[50];

int main() {
    ifstream fin("race3.in");
    ofstream fout("race3.out");
    
    int x, v = 0;
    for (int i = 0; i < 50; i++) adj[i].clear(), adj_inverse[i].clear();
    while (fin >> x) {
        if (x == -1) break;
        else if (x == -2) v++;
        else adj[v].push_back(x), adj_inverse[x].push_back(v);
    }
    int s = 0, t = v - 1;

    vector<int> unavoid;
    for (int i = 1; i < t; i++) {
        queue<int> bfs;
        vector<bool> vis(v, false);
        bfs.push(s), vis[s] = true;
        while (!bfs.empty() && !vis[t]) {
            int u = bfs.front(); bfs.pop();
            if (u == i) continue;
            for (auto v : adj[u]) {
                if (!vis[v]) bfs.push(v), vis[v] = true;
            }
        }
        if (!vis[t]) unavoid.push_back(i);
    }
    fout << unavoid.size();
    for (int i = 0; i < unavoid.size(); i++) fout << ' ' << unavoid[i];
    fout << endl;

    vector<int> split;
    int i;
    for (auto p : unavoid) {
        vector<int> status(v, 0);
        queue<int> bfs;

        // color first course to 1
        bfs.push(s), status[s] = 1;
        while (!bfs.empty()) {
            int u = bfs.front(); bfs.pop();
            if (u == p) continue;
            for (auto v : adj[u]) {
                if (status[v] == 0) {
                    status[v] = 1, bfs.push(v);
                }
                else if (status[v] == 1) continue;
            }
        }
        // if (status[p] != 1) goto fail => this cannot happen by definition of a good course

        // verify that all nodes colored 1 are reachable from p
        bfs.push(p), status[p] = 2;
        while (!bfs.empty()) {
            int u = bfs.front(); bfs.pop();
            for (auto v : adj_inverse[u]) {
                if (status[v] == 1) {
                    status[v] = 2, bfs.push(v);
                }
                else if (status[v] == 2) continue;
            }
        }
        for (i = 0; i < v; i++) 
            if (status[i] != 2 && status[i] != 0) goto fail;
        
        // color second course to -1
        bfs.push(p), status[p] = -1;
        while (!bfs.empty()) {
            int u = bfs.front(); bfs.pop();
            for (auto v : adj[u]) {
                if (status[v] == 0) {
                    status[v] = -1, bfs.push(v);
                }
                else if (status[v] == -1) continue;
                else goto fail; // course 2 cannot reach course 1
            }
        }
        // if (status[t] != -1) goto fail => this cannot happen by definition of a good course

        // verify all nodes colored -1 can be reached from finish
        bfs.push(t), status[t] = -2;
        while (!bfs.empty()) {
            int u = bfs.front(); bfs.pop();
            if (u == p) continue;
            for (auto v : adj_inverse[u]) {
                if (status[v] == -1) {
                    status[v] = -2, bfs.push(v);
                }
                else if (status[v] == -2) continue;
                // else goto fail; => this cannot happen, otherwise u should have been in course 1 during first bfs
            }
        }
        for (i = 0; i < v; i++) 
            if (status[i] != 2 && status[i] != -2) goto fail;

        split.push_back(p); continue;

        fail:;
    }
    fout << split.size();
    for (int i = 0; i < split.size(); i++) fout << ' ' << split[i];
    fout << endl;

    return 0;
}