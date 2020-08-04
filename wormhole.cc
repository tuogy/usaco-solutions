/*
USER: guobich1
TASK: wormhole
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

bool isLoop(vector<pair<int, int>>& coords, vector<int>& pairs, int N) {
    for (int i = 0; i < N; i++) {
        int pos = i, count = 0;
        while (count < N + 1) {
            pos = pairs[pos];
            if (pos + 1 == coords.size()) break;
            int y = coords[pos].first;
            int nexty = coords[pos + 1].first;
            if (y != nexty) break;
            else pos++, count++;
        }
        if (count == N + 1) return true;
    }
    return false;
}

vector<vector<int>> gen_pairs(int N) {
    vector<vector<int>> ret;
    vector<int> cur(N, -1);
    int vis = (1 << N) - 1;
    function<void()> dfs = [&](){
        if (vis == 0) {
            ret.push_back(cur);
            return;
        }
        else {
            int l = 0, bitl = 1;
            while ((vis & bitl) == 0) bitl <<= 1, l++;
            for (int r = l + 1, bitr = bitl << 1; r < N; r++, bitr <<= 1) {
                if (vis & bitr) {
                    vis ^= bitl | bitr;
                    cur[l] = r, cur[r] = l;
                    dfs();
                    vis ^= bitl | bitr;
                }
            }
        }
    };
    dfs();
    return ret;
}


int main() {
    ifstream fin("wormhole.in");
    ofstream fout("wormhole.out");
    
    int N, x, y;
    vector<pair<int, int>> coords;
    fin >> N;
    for (int i = 0; i < N; i++) {
        fin >> x >> y;
        coords.push_back({y, x});
    }
    sort(coords.begin(), coords.end());
    auto pairs = gen_pairs(N);
    int ret = 0;
    for (auto& pair : pairs) {
        for (int i = 0; i < N; i++) cout << i << ":" << pair[i] << " ";
        if (isLoop(coords, pair, N)) cout << "loop", ret++;
        cout << endl;
    }
    fout << ret << endl;

    return 0;
}