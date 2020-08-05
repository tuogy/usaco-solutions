/*
USER: guobich1
TASK: holstein
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

struct Status {
    vector<int> nuits;
    vector<int> labels;
    int cur;
};

int main() {
    ifstream fin("holstein.in");
    ofstream fout("holstein.out");
    
    int V, G;
    fin >> V;
    vector<int> req(V);
    for (int i = 0; i < V; i++) fin >> req[i];
    fin >> G;
    vector<vector<int>> spoons(G, vector<int>(V));
    for (int i = 0; i < G; i++) {
        for (int j = 0; j < V; j++) fin >> spoons[i][j];
    }
    queue<Status> bfs;
    for (int i = 0; i < G; i++) {
        Status s;
        s.nuits = spoons[i];
        s.labels = {i};
        s.cur = i;
        bfs.emplace(s);
    }
    while (!bfs.empty()) {
        auto& s = bfs.front();
        bool ok = true;
        for (int i = 0; i < V && ok; i++) {
            if (s.nuits[i] < req[i]) ok = false;
        }
        if (ok) {
            fout << s.labels.size();
            for (auto l : s.labels) {
                fout << ' ' << l + 1;
            }
            fout << endl;
            return 0;
        }
        else {
            for (int i = s.cur + 1; i < G; i++) {
                Status s_next = s;
                s_next.cur = i;
                s_next.labels.push_back(i);
                for (int j = 0; j < V; j++) {
                    s_next.nuits[j] += spoons[i][j];
                }
                bfs.emplace(s_next);
            }
            bfs.pop();
        }
    }

    return 0;
}