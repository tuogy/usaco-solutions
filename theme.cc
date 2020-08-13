/*
USER: guobich1
TASK: theme
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;
using ll = long long;

const ll base = 176;
const ll mod = 1e9 + 7;
int notes[5000];
int delta[5000];

int main() {
    ifstream fin("theme.in");
    ofstream fout("theme.out");
    
    int N;
    fin >> N;
    for (int i = 0; i < N; i++) fin >> notes[i];
    for (int i = 0; i + 1 < N; i++) delta[i] = notes[i + 1] - notes[i] + 88; // min: 1 max: 175
   
    int tl = 0, tr = N - 2;
    while (tl < tr - 1) {
        int T = tl + (tr - tl) / 2;
        ll rkhash = 0, base_T = 1;
        unordered_map<ll, vector<int>> um;

        for (int i = 0; i < T; i++) {
            rkhash = rkhash * base + delta[i];
            rkhash %= mod;
            base_T = base_T * base % mod;
        }
        um[rkhash] = {0};

        bool match = false;
        for (int i = T; i < N - 1 && !match; i++) {
            rkhash = rkhash * base + delta[i];
            rkhash += (mod - delta[i - T]) * base_T % mod;
            rkhash %= mod;
            int cur_start = i - T + 1;
            if (um.find(rkhash) == um.end()) um[rkhash] = {cur_start};
            else {
                for (auto prev_start : um[rkhash]) {
                    bool identical = true;
                    for (int i = 0; i < T && identical; i++) 
                        if (delta[prev_start + i] != delta[cur_start + i]) identical = false;
                    if (identical) {
                        match = prev_start + T < cur_start;
                        goto skip;
                    }
                }
                um[rkhash].push_back(cur_start);
                skip:;
            }
        }
        if (match) tl = T;
        else tr = T;
    }
    int max_theme_len = tl + 1;
    if (max_theme_len < 5) fout << 0 << endl;
    else fout << max_theme_len << endl;

    return 0;
}