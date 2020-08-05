/*
USER: guobich1
TASK: frac1
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>

using namespace std;

int gcd(int a, int b) {
    int tmp;
    while (b) {
        tmp = a, a = b, b = tmp % b;
    }
    return a;
}

using ii = pair<int, int>;

int main() {
    ifstream fin("frac1.in");
    ofstream fout("frac1.out");
    
    int N;
    fin >> N;
    fout << "0/1" << endl;

    auto cmp = [](ii a, ii b) {
        return a.first * b.second > a.second * b.first;
    };
    priority_queue<ii, vector<ii>, decltype(cmp)> pq(cmp);

    for (int i = 1; i <= N; i++) pq.push({1, i});
    while (!pq.empty()) {
        auto frac = pq.top(); pq.pop();
        fout << frac.first << '/' << frac.second << endl;
        frac.first++;
        while (frac.first <= frac.second) {
            if (gcd(frac.first, frac.second) == 1) {
                pq.push(frac); break;
            }
            frac.first++;
        }
    }

    return 0;
}