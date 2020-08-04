/*
USER: guobich1
TASK: milk
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
using namespace std;

const int maxN = 2000000;
int amount_at_price[1001];

int main() {
    ifstream fin("milk.in");
    ofstream fout("milk.out");
    
    memset(amount_at_price, 0, sizeof(int) * 1001);
    int N, M, p, a;
    fin >> N >> M;
    for (int i = 0; i < M; i++) {
        fin >> p >> a;
        if (amount_at_price[p] < maxN) amount_at_price[p] += a;
    }
    int ret = 0;
    for (int i = 0; N; i++) {
        ret += i * min(N, amount_at_price[i]);
        N -= min(N, amount_at_price[i]);
    }
    fout << ret << endl;

    return 0;
}