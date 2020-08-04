/*
USER: guobich1
TASK: skidesign
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream fin("skidesign.in");
    ofstream fout("skidesign.out");
    
    int N;
    fin >> N;
    vector<int> hs(N);
    for (int i = 0; i < N; i++) fin >> hs[i];
    int ret = INT_MAX;
    for (int l = 0; l + 17 <= 100; l++) {
        int h = l + 17, cost = 0;
        for (int i = 0; i < N; i++) {
            int newh = max(l, min(h, hs[i]));
            cost += (newh - hs[i]) * (newh - hs[i]);
        }
        if (cost < ret) ret = cost;
    }
    fout << ret << endl;

    return 0;
}