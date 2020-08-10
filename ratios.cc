/*
USER: guobich1
TASK: ratios
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int n[3], a[3], b[3], c[3];

int verify(int x0, int x1, int x2) {
    int aa = x0 * a[0] + x1 * a[1] + x2 * a[2];
    int bb = x0 * b[0] + x1 * b[1] + x2 * b[2];
    int cc = x0 * c[0] + x1 * c[1] + x2 * c[2];
    if (aa + bb + cc == 0) return -1;
    int r[3];
    if (n[0] == 0) {
        if (aa > 0) return -1;
        else r[0] = -1;
    }
    else if (aa % n[0]) return -1;
    else r[0] = aa / n[0];

    if (n[1] == 0) {
        if (bb > 0) return -1;
        else r[1] = -1;
    }
    else if (bb % n[1]) return -1;
    else r[1] = bb / n[1];
    
    if (n[2] == 0) {
        if (cc > 0) return -1;
        else r[2] = -1;
    }
    else if (cc % n[2]) return -1;
    else r[2] = cc / n[2];
    
    int prev = -1;
    for (int i = 0; i < 3; i++) {
        if (r[i] == -1) continue;
        else if (prev == -1) prev = r[i];
        else if (prev != r[i]) return -1;
    }
    return prev;
}

int main() {
    ifstream fin("ratios.in");
    ofstream fout("ratios.out");
    
    for (int i = 0; i < 3; i++) fin >> n[i];
    for (int i = 0; i < 3; i++) fin >> a[i] >> b[i] >> c[i];
    if (n[0] == 0 && n[1] == 0 && n[2] == 0) {
        fout << 0 << " " << 0 << " " << 0 << " " << 0 << endl;
        return 0;
    }

    vector<int> best;
    int minx = INT_MAX, q;
    for (int x0 = 0; x0 < 100; x0++) {
        for (int x1 = 0; x1 < 100; x1++) {
            for (int x2 = 0; x2 < 100; x2++) {
                if (x0 + x1 + x2 >= minx) continue;
                int qq = verify(x0, x1, x2);
                if (qq >= 0) {
                    minx = x0 + x1 + x2;
                    best = {x0, x1, x2};
                    q = qq;
                }
            }
        }
    }
    if (best.empty()) {
        fout << "NONE" << endl;
    }
    else fout << best[0] << " " << best[1] << " " << best[2] << " " << q << endl;

    return 0;
}