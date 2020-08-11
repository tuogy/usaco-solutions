/*
USER: guobich1
TASK: fence
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <set>
#include <vector>

using namespace std;

int main() {
    ifstream fin("fence.in");
    ofstream fout("fence.out");
    
    int F;
    multiset<int> adj[500];
    int x, y;
    fin >> F;
    for (int i = 0; i < F; i++) {
        fin >> x >> y; x--, y--;
        adj[x].insert(y);
        adj[y].insert(x);
    }
    stack<int> estk;
    vector<int> ret;
    int v = -1, v_odd = -1;
    for (int i = 0; i < 500; i++) {
        if (adj[i].size() % 2 && v_odd == -1) v_odd = i;
        else if (adj[i].size() && v == -1) v = i;
    }
    if (v_odd >= 0) v = v_odd;
    estk.push(v);
    while (!estk.empty()) {
        v = estk.top();
        if (adj[v].empty()) {
            estk.pop();
            ret.push_back(v);
        }
        else {
            auto it = adj[v].begin();
            auto jt = adj[*it].find(v);
            estk.push(*it);
            adj[*it].erase(jt);
            adj[v].erase(it);
        }
    }
    reverse(ret.begin(), ret.end());
    for (auto i : ret) {
        fout << i + 1 << endl;
    }

    return 0;
}