/*
USER: guobich1
TASK: camelot
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

bool has_knight[30][26];
int cost_knight[30][26];
int cost_king[30][26];
int cost_rider[30][26];
bool vis[30][26][2];

const int inf = 0x3f3f3f3f;
int mkr[] = {0, 1, 1, 1, 0, -1, -1, -1}, mkc[] = {1, 1, 0, -1, -1, -1, 0, 1};
int mnr[] = {1, 2, 2, 1, -1, -2, -2, -1}, mnc[] = {2, 1, -1, -2, -2, -1, 1, 2};

struct coord {
    coord(int a=0, int b=0) {r = a, c = b;}
    int r, c;
};

struct dijk {
    dijk(int _step, int _r, int _c, bool _king) {
        step = _step;
        pos = {_r, _c};
        has_king = _king;
    }
    int step;
    coord pos;
    bool has_king;
};

int main() {
    ifstream fin("camelot.in");
    ofstream fout("camelot.out");
    
    int R, C, r, n_knights = 0; 
    char cc;
    fin >> R >> C;
    fin >> cc >> r;
    coord pos_king(r - 1, cc - 'A');
    memset(has_knight, 0, R*26*sizeof(bool));
    while (fin >> cc >> r) {
        has_knight[r - 1][cc - 'A'] = true;
        n_knights++;
    }

    // compute cost king
    vector<vector<bool>> vis_king(R, vector<bool>(C, false));
    queue<pair<coord, int>> bfs_king;
    bfs_king.push({pos_king, 0}); vis_king[pos_king.r][pos_king.c] = true;
    while (!bfs_king.empty()) {
        coord pos = bfs_king.front().first;
        int step = bfs_king.front().second;
        cost_king[pos.r][pos.c] = step;
        bfs_king.pop();
        for (int k = 0; k < 8; k++) {
            int rr = pos.r + mkr[k], cc = pos.c + mkc[k];
            if (rr < 0 || rr >= R || cc < 0 || cc >= C || vis_king[rr][cc]) continue;
            vis_king[rr][cc] = true;
            bfs_king.push({{rr, cc}, step + 1});
        }
    }

    int bestm = inf;
    auto cmp_dijk = [](dijk& a, dijk& b){return a.step > b.step;};

    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            priority_queue<dijk, vector<dijk>, decltype(cmp_dijk)> dijk_rider(cmp_dijk);

            // compute cost
            memset(vis, 0, R*26*2*sizeof(bool));
            memset(cost_knight, 0x3f, R*26*sizeof(int));
            memset(cost_rider, 0x3f, R*26*sizeof(int));
            dijk_rider.push({0, r, c, true});
            int count_knight = 0, count_rider = 0, best_delta = inf, curm = 0;
            while (!dijk_rider.empty() && 
                   count_rider < n_knights &&  // riders must arrive later than knights. when all riders have been computed we are done
                   curm < bestm // bestm can be updated with (curm + cost_king) or (curm + knight_pickup_path - knight_shortest_path + cost_king_pickup).
                ) {
                int step = dijk_rider.top().step;
                coord pos = dijk_rider.top().pos;
                int has_king = dijk_rider.top().has_king;
                dijk_rider.pop();
                if (vis[pos.r][pos.c][has_king]) continue;
                else vis[pos.r][pos.c][has_king] = true;
                if (!has_king) {
                    cost_rider[pos.r][pos.c] = step;
                    if (has_knight[pos.r][pos.c]) {
                        best_delta = min(best_delta, step - cost_knight[pos.r][pos.c]);
                        count_rider++;
                    }
                }
                else {
                    cost_knight[pos.r][pos.c] = step;
                    if (has_knight[pos.r][pos.c]) {
                        curm += step;
                        count_knight++;
                    }
                    if (!vis[pos.r][pos.c][0] && cost_rider[pos.r][pos.c] >= step + cost_king[pos.r][pos.c]) {
                        cost_rider[pos.r][pos.c] = step + cost_king[pos.r][pos.c];
                        dijk_rider.push({step + cost_king[pos.r][pos.c], pos.r, pos.c, false});
                    }
                }

                for (int k = 0; k < 8; k++) {
                    int rr = pos.r + mnr[k], cc = pos.c + mnc[k];
                    if (rr < 0 || rr >= R || cc < 0 || cc >= C || vis[rr][cc][has_king] || 
                    has_king && cost_knight[rr][cc] < step + 1 || !has_king && cost_rider[rr][cc] < step + 1) continue;
                    if (has_king) cost_knight[rr][cc] = step + 1;
                    else cost_rider[rr][cc] = step + 1;
                    dijk_rider.push({step + 1, rr, cc, has_king > 0});
                }
            }

            if (count_knight < n_knights) continue;
            curm += min(cost_king[r][c], best_delta);
            if (curm < bestm) bestm = curm;
        }
    }
    fout << bestm << endl;

    return 0;
}