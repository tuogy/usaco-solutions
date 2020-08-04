/*
USER: guobich1
TASK: barn1
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>


using namespace std;

int main() {
    ifstream fin("barn1.in");
    ofstream fout("barn1.out");
    
    int M, S, C, minS, maxS, cur;
    fin >> M >> S >> C;

    vector<int> ps;
    priority_queue<int> gaps;

    for (int i = 0; i < C; i++) {
        fin >> cur;
        ps.push_back(cur);
    }
    sort(ps.begin(), ps.end());
    minS = ps[0];
    maxS = ps.back();
    for (int i = 1; i < C; i++) {
        if (ps[i] - ps[i - 1] > 1) gaps.push(ps[i] - ps[i - 1] - 1);
    }
    int ret = maxS - minS + 1;
    while (M > 1 && !gaps.empty()) {
        ret -= gaps.top();
        gaps.pop();
        M--;
    }

    fout << ret << endl;

    return 0;
}