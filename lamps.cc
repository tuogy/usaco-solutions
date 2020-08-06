/*
USER: guobich1
TASK: lamps
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

bool lamps[100];

int main() {
    ifstream fin("lamps.in");
    ofstream fout("lamps.out");
    
    int N, C;
    fin >> N >> C;

    int r;
    vector<int> lampsOn, lampsOff;
    while (true) {
        fin >> r;
        if (r == -1) break;
        else lampsOn.push_back(r - 1);
    }
    while (true) {
        fin >> r;
        if (r == -1) break;
        else lampsOff.push_back(r - 1);
    }

    vector<string> ret;
    for (int b1 : {0, 1}) {
        for (int b2 : {0, 1}) {
            for (int b3 : {0, 1}) {
                for (int b4 : {0, 1}) {
                    int freepress = C - b1 - b2 - b3 - b4;
                    if (freepress < 0 || freepress & 1) continue;
                    memset(lamps, 0, N * sizeof(bool));
                    if (b1) {
                        for (int i = 0; i < N; i++) lamps[i] ^= 1;
                    }
                    if (b2) {
                        for (int i = 0; i < N; i += 2) lamps[i] ^= 1;
                    }
                    if (b3) {
                        for (int i = 1; i < N; i += 2) lamps[i] ^= 1;
                    }
                    if (b4) {
                        for (int i = 0; i < N; i += 3) lamps[i] ^= 1;
                    }
                    bool ok = true;
                    for (int i = 0; i < lampsOn.size() && ok; i++) ok = lamps[lampsOn[i]] == false;
                    for (int i = 0; i < lampsOff.size() && ok; i++) ok = lamps[lampsOff[i]] == true;
                    if (ok) {
                        string cur(N, ' ');
                        for (int i = 0; i < N; i++) cur[i] = lamps[i] ? '0' : '1';
                        ret.emplace_back(cur);
                    }
                    
                }
            }
        }
    }
    sort(ret.begin(), ret.end());
    if (ret.empty()) {
        fout << "IMPOSSIBLE" << endl;
    }
    else {
        for (auto& s : ret) fout << s << endl;
    }
    


    return 0;
}