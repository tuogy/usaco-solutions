/*
USER: guobich1
TASK: prefix
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

using namespace std;

using ull = unsigned long long;

int main() {
    ifstream fin("prefix.in");
    ofstream fout("prefix.out");
    
    char x;
    ull hash = 0;
    unordered_set<ull> primitives;
    while (true) {
        fin.get(x);
        if (x == '.') break;
        else {
            if (x >= 'A' && x <= 'Z') {
                hash = hash * 27 + x - 'A' + 1;
            }
            else {
                primitives.insert(hash);
                hash = 0;
            }
        }
    }
    int valid = 1, cur = 0, ret = 0;
    ull prev[11] = {0};
    while (fin.get(x)) {
        if (x >= 'A' && x <= 'Z') {
            cur++;
            valid = (valid << 1) & 0xfff;
            bool ok = false;
            for (int l = min(10, cur); l > 0; l--) {
                prev[l] = prev[l - 1] * 27 + x - 'A' + 1;
                if (!ok && (valid & (1 << l)) && primitives.find(prev[l]) != primitives.end()) {
                    ok = true;
                    valid |= 1;
                }
            }
            if (ok) ret = max(ret, cur);
        }
    }
    fout << ret << endl;

    return 0;
}