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
        auto p0 = p[0];
        for (int i = 0; i < L; i++) p0[i] = i;
        for (int k : {1, 0}) {
            memset(c, 0, (nc + 1) * sizeof(int));
            for (int i = 0; i < L; i++) c[cl[i]]++;
            for (int i = 1; i <= nc; i++) c[i] += c[i - 1];
            for (int i = L - 1; i >= 0; i--) p[k][--c[cl[(p[k ^ 1][i] + k * l) % L]]] = p[k ^ 1][i];
        }
        nc = -1;
        for (int i = 0; i < L; i++) {
            if (i && cl[p0[i]] == cl[p0[i - 1]] && cl[(p0[i] + l) % L] == cl[(p0[i - 1] + l) % L]) cl[p0[i]] = nc;
            else cl[p0[i]] = ++nc;
        }
    }
    int bestc = cl[0], besti = 0;
    for (int i = 1; i < L; i++) {
        if (cl[i] < bestc) bestc = cl[i], besti = i;
    }
    cout << besti << endl;

    return 0;
}