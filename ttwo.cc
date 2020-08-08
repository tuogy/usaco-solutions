/*
USER: guobich1
TASK: ttwo
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <algorithm>

const int N = 10;
bool grid[100];
int dr[] = {-1, 0, 1, 0}, dc[] = {0, 1, 0, -1};
bool vis[400][400];

using namespace std;

int main() {
    ifstream fin("ttwo.in");
    ofstream fout("ttwo.out");
    
    char x;
    pair<int, int> pF, pC;
    int dF = 0, dC = 0, rr, cc;
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            fin.get(x);
            if (x == '*') grid[r * N + c] = false;
            else grid[r * N + c] = true;
            if (x == 'F') pF = {r, c};
            else if (x == 'C') pC = {r, c};
        }
        fin.get(x);
    }
    vis[((pF.first * 10) + pF.second) * 4 + dF][((pC.first * 10) + pC.second) * 4 + dC] = true;
    
    int clock = 0;
    while (pF != pC) {
        rr = pF.first + dr[dF];
        cc = pF.second + dc[dF];
        if (rr < 0 || rr >= N || cc < 0 || cc >= N || !grid[rr * N + cc]) dF = (dF + 1) % 4;
        else pF = {rr, cc};

        rr = pC.first + dr[dC];
        cc = pC.second + dc[dC];
        if (rr < 0 || rr >= N || cc < 0 || cc >= N || !grid[rr * N + cc]) dC = (dC + 1) % 4;
        else pC = {rr, cc};

        bool& v = vis[((pF.first * 10) + pF.second) * 4 + dF][((pC.first * 10) + pC.second) * 4 + dC];
        if (v) {
            clock = 0; break;
        }
        else {
            v = true; clock++;
        }
    }
    
    fout << clock << endl;


    return 0;
}