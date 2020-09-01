/*
USER: guobich1
TASK: hidden
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
    #define cout fout
#endif
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const int mxn = 100000;
int cl[mxn], c[mxn];
int p[2][mxn];

int main() {
    ifstream fin("hidden.in");
    ofstream fout("hidden.out");
    
    int L, nc = 26;
    fin >> L;
    string s(L, ' ');
    for (int i = 0; i < L; i++) fin >> s[i];
    for (int i = 0; i < L; i++) cl[i] = s[i] - 'a';
    for (int l = 1; l >> 1 < L; l <<= 1) {
        auto prev = p[0], cur = p[1];
        for (int i = 0; i < L; i++) cur[i] = i;
        for (int k : {1, 0}) {
            memset(c, 0, (nc + 1) * sizeof(int));
            swap(prev, cur);
            for (int i = 0; i < L; i++) c[cl[i]]++;
            for (int i = 1; i <= nc; i++) c[i] += c[i - 1];
            for (int i = L - 1; i >= 0; i--) cur[--c[cl[(prev[i] + k * l) % L]]] = prev[i];
        }
        nc = -1;
        for (int i = 0; i < L; i++) {
            if (i && cl[cur[i]] == cl[cur[i - 1]] && cl[(cur[i] + l) % L] == cl[(cur[i - 1] + l) % L]) cl[cur[i]] = nc;
            else cl[cur[i]] = ++nc;
        }
    }
    int bestc = cl[0], besti = 0;
    for (int i = 1; i < L; i++) {
        if (cl[i] < bestc) bestc = cl[i], besti = i;
    }
    cout << besti << endl;

    return 0;
}