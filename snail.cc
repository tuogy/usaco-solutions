/*
USER: guobich1
TASK: snail
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>

using namespace std;

int d4r[] = {0, 1, 0, -1}, d4c[] = {1, 0, -1, 0};

int N, max_len;
char grid[120][120];

void dfs(int r, int c, int d, int steps) {
    int dr = d4r[d], dc = d4c[d], orig_r = r, orig_c = c, orig_steps = steps;
    while (r + dr >= 0 && r + dr < N && c + dc >= 0 && c + dc < N && grid[r + dr][c + dc] == '.') {
        r += dr, c += dc;
        grid[r][c] = 'x';
        steps++;
    }
    if (steps > orig_steps && (r + dr < 0 || r + dr >= N || c + dc < 0 || c + dc >= N || grid[r + dr][c + dc] == '#')) {
        int d1 = d ^ 1, d2 = (d1 + 2) % 4;
        dfs(r, c, d1, steps);
        dfs(r, c, d2, steps);
    }
    else {
        max_len = max(max_len, steps);
    }
    while (r != orig_r || c != orig_c) {
        grid[r][c] = '.';
        r -= dr, c -= dc;
    }
}

int main() {
    ifstream fin("snail.in");
    ofstream fout("snail.out");
    
    int B;
    fin >> N >> B;
    memset(grid, '.', 120*120*sizeof(char));
    for (int i = 0; i < B; i++) {
        char c; int r;
        fin >> c >> r;
        grid[r - 1][c - 'A'] = '#';
    }

    max_len = 0;
    grid[0][0] = 'x';
    dfs(0, 0, 0, 1);
    dfs(0, 0, 1, 1);
    fout << max_len << endl;

    return 0;
}