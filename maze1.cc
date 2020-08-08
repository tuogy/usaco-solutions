/*
USER: guobich1
TASK: maze1
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int maze[202][80];
int d4r[] = {1, 0, -1, 0}, d4c[] = {0, 1, 0, -1};

int main() {
    ifstream fin("maze1.in");
    ofstream fout("maze1.out");
    
    int W, H;
    fin >> W >> H;
    char x;
    fin.get(x);
    for (int r = 0; r <= 2 * H; r++) {
        for (int c = 0; c <= 2 * W; c++) {
            fin.get(x);
            if (x == '|' || x == '-') maze[r][c] = -1;
            else maze[r][c] = INT_MAX;
        }
        fin.get(x);
    }

    vector<pair<int, int>> exits;
    for (int c = 1; c <= 2 * W; c += 2) {
        if (maze[0][c] == INT_MAX) {
            auto pr = make_pair(1, c);
            if (exits.empty() || exits[0] != pr) exits.push_back(pr);
        }
        if (maze[2 * H][c] == INT_MAX) {
            auto pr = make_pair(2 * H - 1, c);
            if (exits.empty() || exits[0] != pr) exits.push_back(pr);
        }
    }
    for (int r = 1; r <= 2 * H; r += 2) {
        if (maze[r][0] == INT_MAX) {
            auto pr = make_pair(r, 1);
            if (exits.empty() || exits[0] != pr) exits.push_back(pr);
        }
        if (maze[r][2 * W] == INT_MAX) {
            auto pr = make_pair(r, 2 * W - 1);
            if (exits.empty() || exits[0] != pr) exits.push_back(pr);
        }
    }

    queue<pair<int, int>> bfs, bfs_next;
    while (!exits.empty()) {
        bfs.push(exits.back()), exits.pop_back();
        int cost = 0;
        while (!bfs.empty()) {
            cost++;
            while (!bfs.empty()) {
                int r = bfs.front().first, c = bfs.front().second;
                bfs.pop();
                if (maze[r][c] <= cost) continue;
                else maze[r][c] = cost;
                for (int k = 0; k < 4; k++) {
                    int rr = r + 2 * d4r[k], cc = c + 2 * d4c[k];
                    int rh = r + d4r[k], ch = c + d4c[k];
                    if (rr < 0 || rr > 2 * H || cc < 0 || cc > 2 * W || maze[rh][ch] == -1) continue;
                    bfs_next.push({rr, cc});
                }
            }
            bfs.swap(bfs_next);
        }
    }

    int ret = 0;
    for (int r = 1; r <= 2 * H; r += 2) {
        for (int c = 1; c <= 2 * W; c += 2) {
            ret = max(ret, maze[r][c]);
        }
    }
    fout << ret << endl;


    return 0;
}