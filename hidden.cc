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

struct pri {
    int l, r, i;
};

int c[100000];
pri p[100000];

int main() {
    ifstream fin("hidden.in");
    ofstream fout("hidden.out");
    
    int L;
    fin >> L;
    string s(L, ' ');
    for (int i = 0; i < L; i++) fin >> s[i];
    for (int i = 0; i < L; i++) c[i] = s[i] - 'a';
    for (int l = 1; l >> 1 < L; l <<= 1) {
        for (int i = 0; i < L; i++) {
            p[i].l = c[i], p[i].r = c[(i + l) % L], p[i].i = i;
        }
        sort(p, p + L, [](pri& a, pri& b){return a.l < b.l || a.l == b.l && a.r < b.r;});
        for (int i = 0, nc = -1; i < L; i++) {
            if (i && p[i].l == p[i - 1].l && p[i].r == p[i - 1].r) c[p[i].i] = nc;
            else c[p[i].i] = ++nc;
        }
    }
    int bestc = c[0], besti = 0;
    for (int i = 1; i < L; i++) {
        if (c[i] < bestc) bestc = c[i], besti = i;
    }
    cout << besti << endl;

    return 0;
}