/*
USER: guobich1
TASK: game1
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>

using namespace std;

int a[100];
int dp_f[100][100], dp_s[100][100];

int main() {
    ifstream fin("game1.in");
    ofstream fout("game1.out");
    
    int N;
    fin >> N;
    for (int i = 0; i < N; i++) fin >> a[i];
    for (int len = 0; len <= N - 1; len++) {
        for (int l = 0, r; l + len < N; l++) {
            r = l + len;
            if (len == 0) dp_f[l][r] = a[l], dp_s[l][r] = 0;
            else {
                if (a[l] + dp_s[l + 1][r] > a[r] + dp_s[l][r - 1]) {
                    dp_f[l][r] = a[l] + dp_s[l + 1][r];
                    dp_s[l][r] = dp_f[l + 1][r];
                }
                else {
                    dp_f[l][r] = a[r] + dp_s[l][r - 1];
                    dp_s[l][r] = dp_f[l][r - 1];
                }
            }
        }
    }
    fout << dp_f[0][N - 1] << " " << dp_s[0][N - 1] << endl;

    return 0;
}