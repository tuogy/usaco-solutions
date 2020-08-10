/*
USER: guobich1
TASK: kimbits
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>

using namespace std;
using ll = long long;

ll dp_count[32][32];

int main() {
    ifstream fin("kimbits.in");
    ofstream fout("kimbits.out");
    
    ll N, L, l;
    fin >> N >> L >> l;

    for (int n = 0; n <= N; n++) {
        for (int k = 0; k <= N; k++) {
            if (k == 0) dp_count[n][k] = 1;
            else if (k >= n) dp_count[n][k] = 1LL << n;
            else dp_count[n][k] = dp_count[n - 1][k] + dp_count[n - 1][k - 1];
        }
    }
    while (N) {
        if (l > dp_count[N - 1][L]) {
            fout << '1';
            l -= dp_count[N - 1][L];
            N--, L--;
        }
        else {
            fout << '0';
            N--;
        }
    }
    fout << endl;

    return 0;
}