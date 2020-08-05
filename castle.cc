/*
USER: guobich1
TASK: castle
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int N, M;
pair<int, int> uf_parent[50][50];
int uf_rank[50][50];
int uf_count[50][50];
int walls[50][50];

int d4i[] = {0, -1, 0, 1};
int d4j[] = {-1, 0, 1, 0};

pair<int, int> uf_find(int i, int j) {
    auto pr = uf_parent[i][j];
    if (pr.first != i || pr.second != j) {
        uf_parent[i][j] = uf_find(pr.first, pr.second);
    }
    return uf_parent[i][j];
}

void uf_union(pair<int, int> a, pair<int, int> b) {
    a = uf_find(a.first, a.second);
    b = uf_find(b.first, b.second);
    if (a != b) {
        if (uf_rank[a.first][a.second] < uf_rank[b.first][b.second]) swap(a, b);
        if (uf_rank[a.first][a.second] == uf_rank[b.first][b.second]) uf_rank[a.first][a.second]++;
        uf_parent[b.first][b.second] = a;
        uf_count[a.first][a.second] += uf_count[b.first][b.second];
    }
}

int main() {
    ifstream fin("castle.in");
    ofstream fout("castle.out");

    fin >> M >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            fin >> walls[i][j];
            uf_count[i][j] = 1;
            uf_rank[i][j] = 0;
            uf_parent[i][j] = {i, j};
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < 4; k++) {
                if (!(walls[i][j] & (1 << k))) {
                    int ii = i + d4i[k], jj = j + d4j[k];
                    uf_union({i, j}, {ii, jj});
                }
            }
        }
    }

    bool vis[50*50] = {0};
    int rooms = 0, mx = 0, mxc = 0, mxc_j = -1, mxc_i = -1, mxc_k = -1;
    for (int j = 0; j < M; j++) {
        for (int i = N - 1; i >= 0; i--) {
            auto p = uf_find(i, j);
            if (!vis[p.first * M + p.second]) {
                vis[p.first * M + p.second] = true;
                rooms++, mx = max(mx, uf_count[p.first][p.second]);
            }
            for (auto k : {1, 2}) {
                int ii = i + d4i[k], jj = j + d4j[k];
                if (ii < 0 || jj >= M) continue;
                auto q = uf_find(ii, jj);
                if (p != q && uf_count[p.first][p.second] + uf_count[q.first][q.second] > mxc) {
                    mxc = uf_count[p.first][p.second] + uf_count[q.first][q.second];
                    mxc_i = i, mxc_j = j, mxc_k = k;
                }
            }
        }
    }

    fout << rooms << endl << mx << endl << mxc << endl 
    << mxc_i + 1 << " " << mxc_j + 1 << " " << (mxc_k == 1 ? 'N' : 'E') << endl;

    return 0;
}