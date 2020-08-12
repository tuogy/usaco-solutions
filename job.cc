/*
USER: guobich1
TASK: job
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

const int maxT = 40001;
int ta[30], tb[30];
int ga[30], gb[30];
int readyB[1000];

int main() {
    ifstream fin("job.in");
    ofstream fout("job.out");
    
    int N, m1, m2;
    fin >> N >> m1 >> m2;
    for (int i = 0; i < m1; i++) fin >> ta[i];
    for (int i = 0; i < m2; i++) fin >> tb[i];

    memset(ga, 0, m1 * sizeof(int));
    for (int i = 0; i < N; i++) {
        int best_t = maxT, best_j = -1;
        for (int j = 0; j < m1; j++) {
            if (ga[j] + ta[j] < best_t) 
                best_t = ga[j] + ta[j], best_j = j;
        }
        ga[best_j] += ta[best_j];
        readyB[i] = ga[best_j];
    }
    fout << *max_element(ga, ga + m1) << " ";

    int tl = 0, tr = maxT;
    while (tl < tr - 1) {
        int t = (tl + tr) / 2;
        for (int i = 0; i < m2; i++) gb[i] = t;
        bool ok = true;
        for (int i = N - 1; i >= 0 && ok; i--) {
            int best_t = INT_MIN, best_j = -1;
            for (int j = 0; j < m2; j++) {
                if (gb[j] - tb[j] > best_t)
                    best_t = gb[j] - tb[j], best_j = j;
            }
            gb[best_j] -= tb[best_j];
            if (gb[best_j] < readyB[i]) ok = false;
        }
        if (ok) tr = t;
        else tl = t;
    }
    fout << tr << endl;

    return 0;
}