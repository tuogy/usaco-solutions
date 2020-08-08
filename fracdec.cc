/*
USER: guobich1
TASK: fracdec
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    ifstream fin("fracdec.in");
    ofstream fout("fracdec.out");
    stringstream oss;
    
    int N, D;
    fin >> N >> D;

    vector<int> vis(D, -1);
    vector<int> frac;

    frac.push_back(N / D);
    N %= D;
    while (N) {
        if (vis[N] >= 0) break;
        vis[N] = frac.size();
        N *= 10;
        frac.push_back(N / D);
        N %= D;
    }

    oss << frac[0] << ".";
    if (N == 0) {
        if (frac.size() == 1) oss << "0";
        else {
            for (int i = 1; i < frac.size(); i++) oss << frac[i];
        }
        oss << endl;
    }
    else {
        for (int i = 1; i < vis[N]; i++) oss << frac[i];
        oss << "(";
        for (int i = vis[N]; i < frac.size(); i++) oss << frac[i];
        oss << ")" << endl;
    }

    char x;
    int count = 0;
    while (oss >> x) {
        fout << x;
        count++;
        if (count == 76) {
            fout << endl;
            count = 0;
        }
    }
    if (count) fout << endl;

    return 0;
}