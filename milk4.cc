/*
USER: guobich1
TASK: milk4
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <set>

const int maxn = 20001, inf = 0x3f3f3f3f;
int min_npails[maxn], pail_smallest[maxn], pail_next[maxn];

using namespace std;

int main() {
    ifstream fin("milk4.in");
    ofstream fout("milk4.out");
    
    memset(min_npails, 0x3f, maxn * sizeof(int)); min_npails[0] = 0;
    memset(pail_smallest, 0x3f, maxn * sizeof(int)); pail_smallest[0] = 0;
    memset(pail_next, 0, maxn * sizeof(int)); pail_next[0] = -1;

    int Q, P, p;
    set<int> pails;
    fin >> Q >> P;
    for (int i = 0; i < P; i++) {
        fin >> p; pails.insert(p);
    }
    for (auto it = pails.rbegin(); it != pails.rend(); it++) {
        int vol = *it;
        for (int r = 0; r < vol; r++) {
            int best_n = min_npails[r], best_next = r;
            for (int i = r; i <= Q; i += vol) {
                if (min_npails[i] >= best_n + 1) {
                    min_npails[i] = best_n + 1;
                    pail_smallest[i] = vol;
                    pail_next[i] = best_next;
                }
                else if (min_npails[i] == best_n) {
                    bool select_i = true, skip = false;
                    for (int v_i = i, v_best = best_next; !skip && v_i && v_best; v_i = pail_next[v_i], v_best = pail_next[v_best]) {
                        if (pail_smallest[v_i] < pail_smallest[v_best]) select_i = true, skip = true;
                        else if (pail_smallest[v_i] > pail_smallest[v_best]) select_i = false, skip = true;
                    }

                    if (select_i) best_next = i;
                }
                else {
                    best_n = min_npails[i], best_next = i;
                }
            }
        }
    }

    fout << min_npails[Q];
    for (int i = Q; i; i = pail_next[i]) {
        fout << " " << pail_smallest[i];
    }
    fout << endl;

    return 0;
}