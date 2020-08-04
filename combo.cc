/*
USER: guobich1
TASK: combo
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <cmath>


using namespace std;

int main() {
    ifstream fin("combo.in");
    ofstream fout("combo.out");
    
    int N, a[2][3];
    fin >> N;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            fin >> a[i][j];
            a[i][j]--;
        }
    }

    int tot = min(N, 5);
    int total = 2 * tot * tot * tot;

    int both = 1;
    for (int j = 0; j < 3; j++) {
        int dist = min((a[0][j] - a[1][j] + N) % N, (a[1][j] - a[0][j] + N) % N);
        both *= min(N, max(0, 5 - dist));
    }

    fout << total - both << endl;


    return 0;
}