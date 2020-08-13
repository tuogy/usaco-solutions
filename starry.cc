/*
USER: guobich1
TASK: starry
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct coord {
    coord(int r=0, int c=0) : r(r), c(c) {}
    int r, c;
};

int W, H;
char starmap[100][100];
int cluster_id[100][100];
coord top_left[500];
coord handle_point[500];
int cluster_w[500], cluster_h[500], cluster_stars[500];
int cluster_prototype_id[500];

int d8r[] = {-1, -1, -1, 0, 1, 1, 1, 0}, d8c[] = {-1, 0, 1, 1, 1, 0, -1, -1};

coord tx_id(coord& c, int w, int h, coord& tl, coord& tl_target) {
    coord d = {c.r - tl.r, c.c - tl.c};
    return {tl_target.r + d.r, tl_target.c + d.c};
}

coord tx_cw(coord& c, int w, int h, coord& tl, coord& tl_target) {
    coord d = {c.r - tl.r, c.c - tl.c};
    return {tl_target.r + d.c, tl_target.c + h - 1 - d.r};
}

coord tx_csym(coord& c, int w, int h, coord& tl, coord& tl_target) {
    coord d = {c.r - tl.r, c.c - tl.c};
    return {tl_target.r + h - 1 - d.r, tl_target.c + w - 1 - d.c};
}

coord tx_ccw(coord& c, int w, int h, coord& tl, coord& tl_target) {
    coord d = {c.r - tl.r, c.c - tl.c};
    return {tl_target.r + w - 1 - d.c, tl_target.c + d.r};
}

coord tx_hflip(coord& c, int w, int h, coord& tl, coord& tl_target) {
    coord d = {c.r - tl.r, c.c - tl.c};
    return {tl_target.r + d.r, tl_target.c + w - 1 - d.c};
}

coord tx_xpose(coord& c, int w, int h, coord& tl, coord& tl_target) {
    coord d = {c.r - tl.r, c.c - tl.c};
    return {tl_target.r + d.c, tl_target.c + d.r};
}

coord tx_vflip(coord& c, int w, int h, coord& tl, coord& tl_target) {
    coord d = {c.r - tl.r, c.c - tl.c};
    return {tl_target.r + h - 1 - d.r, tl_target.c + d.c};
}

coord tx_offxpose(coord& c, int w, int h, coord& tl, coord& tl_target) {
    coord d = {c.r - tl.r, c.c - tl.c};
    return {tl_target.r + w - 1 - d.c, tl_target.c + h - 1 - d.r};
}

coord (*tx_array[])(coord&, int, int, coord&, coord&) = {
    tx_id, tx_csym, tx_hflip, tx_vflip,
    tx_cw, tx_ccw, tx_xpose, tx_offxpose,
};

bool match_cluster(int i, int j) {
    if (i == j) return true;
    else if (cluster_stars[i] != cluster_stars[j]) return false;
    int valid = 0, temp = 1e9+7;
    if (cluster_w[i] == cluster_w[j] && cluster_h[i] == cluster_h[j]) valid |= 0xf;
    if (cluster_w[i] == cluster_h[j] && cluster_h[i] == cluster_w[j]) valid |= 0xf0;
    queue<coord> bfs, bfs_backtrack;
    bfs.push(handle_point[i]);
    cluster_id[handle_point[i].r][handle_point[i].c] = temp;
    while (!bfs.empty() && valid) {
        coord pos = bfs.front(); bfs.pop();
        for (int k = 0; k < 8; k++) {
            if (valid & (1 << k)) {
                coord pos_j = tx_array[k](pos, cluster_w[i], cluster_h[i], top_left[i], top_left[j]);
                if (cluster_id[pos_j.r][pos_j.c] != j) valid ^= 1 << k;
            }
        }
        for (int k = 0; k < 8; k++) {
            coord next = pos;
            next.r += d8r[k], next.c += d8c[k];
            if (next.r < 0 || next.r >= H || next.c < 0 || next.c >= W
                || starmap[next.r][next.c] == '0' || cluster_id[next.r][next.c] != i) continue;
            cluster_id[next.r][next.c] = temp;
            bfs.push(next);
        }
    }

    bfs_backtrack.push(handle_point[i]);
    cluster_id[handle_point[i].r][handle_point[i].c] = i;
    while (!bfs_backtrack.empty()) {
        coord pos = bfs_backtrack.front(); bfs_backtrack.pop();
        for (int k = 0; k < 8; k++) {
            coord next = pos;
            next.r += d8r[k], next.c += d8c[k];
            if (next.r < 0 || next.r >= H || next.c < 0 || next.c >= W
                || starmap[next.r][next.c] == '0' || cluster_id[next.r][next.c] != temp) continue;
            cluster_id[next.r][next.c] = i;
            bfs_backtrack.push(next);
        }
    }

    return valid != 0;
}

int main() {
    ifstream fin("starry.in");
    ofstream fout("starry.out");
    
    memset(cluster_id, -1, 10000*sizeof(int));

    fin >> W >> H;
    char x;
    for (int i = 0; i < H; i++)
    for (int j = 0; j < W; j++)
        fin >> starmap[i][j];

    int cluster_id_cur = 0;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (starmap[i][j] == '1' && cluster_id[i][j] == -1) {
                int ll = INT_MAX, tt = INT_MAX, rr = -1, bb = -1, n_stars = 0;
                queue<coord> bfs;
                bfs.push({i, j}), n_stars++;
                cluster_id[i][j] = cluster_id_cur;
                while (!bfs.empty()) {
                    coord pos = bfs.front(); bfs.pop();
                    tt = min(tt, pos.r); bb = max(bb, pos.r);
                    ll = min(ll, pos.c); rr = max(rr, pos.c);
                    for (int k = 0; k < 8; k++) {
                        coord next = pos;
                        next.r += d8r[k], next.c += d8c[k];
                        if (next.r < 0 || next.r >= H || next.c < 0 || next.c >= W
                            || starmap[next.r][next.c] == '0' || cluster_id[next.r][next.c] != -1) continue;
                        cluster_id[next.r][next.c] = cluster_id_cur;
                        bfs.push(next), n_stars++;
                    }
                }
                handle_point[cluster_id_cur] = {i, j};
                top_left[cluster_id_cur] = {tt, ll};
                cluster_w[cluster_id_cur] = rr - ll + 1;
                cluster_h[cluster_id_cur] = bb - tt + 1;
                cluster_stars[cluster_id_cur] = n_stars;
                cluster_id_cur++;
            }
        }
    }
    
    int n_clusters = cluster_id_cur;
    vector<int> cluster_prototypes;
    for (int cluster_id = 0; cluster_id < n_clusters; cluster_id++) {
        int match_id = -1;
        for (auto prototype_id : cluster_prototypes) {
            if (match_cluster(cluster_id, prototype_id)) {
                match_id = cluster_prototype_id[prototype_id]; break;
            }
        }
        if (match_id == -1) {
            cluster_prototypes.push_back(cluster_id);
            cluster_prototype_id[cluster_id] = (int)cluster_prototypes.size() - 1;
        }
        else {
            cluster_prototype_id[cluster_id] = match_id;
        }
    }

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (starmap[i][j] == '0') fout << '0';
            else fout << char(cluster_prototype_id[cluster_id[i][j]] + 'a');
        }
        fout << endl;
    }

    return 0;
}