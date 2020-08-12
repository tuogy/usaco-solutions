/*
USER: guobich1
TASK: shuttle
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int N;
vector<int> ret;

bool dfs(string& cur, int pos_, int balance, int rdepth) {
    if (balance == 0 && pos_ == N) return true;
    else if (rdepth == 0) return false;
    if (pos_ - 2 >= 0 && cur[pos_ - 2] == 'W' && cur[pos_ - 1] == 'B') {
        cur[pos_ - 2] = ' ', cur[pos_] = 'W';
        ret.push_back(pos_ - 2);
        if (dfs(cur, pos_ - 2, balance - 1, rdepth - 1)) return true;
        ret.pop_back();
        cur[pos_] = ' ', cur[pos_ - 2] = 'W';
    }
    if (pos_ - 1 >= 0 && cur[pos_ - 1] == 'W') {
        cur[pos_ - 1] = ' ', cur[pos_] = 'W';
        ret.push_back(pos_ - 1);
        if (dfs(cur, pos_ - 1, balance, rdepth - 1)) return true;
        ret.pop_back();
        cur[pos_] = ' ', cur[pos_ - 1] = 'W';
    }
    if (pos_ + 1 <= 2 * N && cur[pos_ + 1] == 'B') {
        cur[pos_ + 1] = ' ', cur[pos_] = 'B';
        ret.push_back(pos_ + 1);
        if (dfs(cur, pos_ + 1, balance, rdepth - 1)) return true;
        ret.pop_back();
        cur[pos_] = ' ', cur[pos_ + 1] = 'B';
    }
    if (pos_ + 2 <= 2 * N && cur[pos_ + 1] == 'W' && cur[pos_ + 2] == 'B') {
        cur[pos_ + 2] = ' ', cur[pos_] = 'B';
        ret.push_back(pos_ + 2);
        if (dfs(cur, pos_ + 2, balance - 1, rdepth - 1)) return true;
        ret.pop_back();
        cur[pos_] = ' ', cur[pos_ + 2] = 'B';
    }
    return false;
}

int main() {
    ifstream fin("shuttle.in");
    ofstream fout("shuttle.out");
    
    fin >> N;
    string cur = string(N, 'W') + " " + string(N, 'B');
    ret.clear();
    ret.reserve(2 * N * N);
    int step = 0;
    while (true) {
        if (dfs(cur, N, N * N, step)) break;
        else step++;
    }
    int c = 0;
    for (int i = 0; i < ret.size() - 1; i++, c++) fout << ret[i] + 1 << (c % 20 == 19 ? '\n' : ' ');
    fout << ret.back() + 1 << endl;

    return 0;
}