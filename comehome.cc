/*
USER: guobich1
TASK: comehome
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

int dist[52][52];

int pasid(char x) {
    if (x >= 'A' && x <= 'Z') return x - 'A' + 26;
    else return x - 'a';
}

int main() {
    ifstream fin("comehome.in");
    ofstream fout("comehome.out");
    
    memset(dist, -1, 52*52*sizeof(int));

    int P, d, ids, idt;
    char s, t;
    fin >> P;
    for (int i = 0; i < 52; i++) dist[i][i] = 0;
    for (int i = 0; i < P; i++) {
        fin >> s >> t >> d;
        ids = pasid(s), idt = pasid(t);
        if (ids == idt) continue;
        if (dist[ids][idt] == -1 || dist[ids][idt] > d)
            dist[ids][idt] = dist[idt][ids] = d;
    }

    int* distz = dist[51], retd = INT_MAX, reti = -1;
    bool vis[51] = {0};
    while (true) {
        int mind = INT_MAX, mini = -1;
        for (int i = 0; i < 51; i++) {
            if (distz[i] >= 0 && distz[i] < mind && !vis[i]) {
                mind = distz[i], mini = i;
            }
        }
        if (mini == -1) break;
        vis[mini] = true;
        if (mini >= 26 && mind < retd) {
            retd = mind, reti = mini;
        }
        else {
            for (int j = 0; j < 51; j++) {
                if (dist[mini][j] >= 0 && (distz[j] == -1 || dist[mini][j] + mind < distz[j])) distz[j] = dist[mini][j] + mind;
            }
        }
    }

    fout << char(reti - 26 + 'A') << " " << retd << endl;

    return 0;
}