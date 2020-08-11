/*
USER: guobich1
TASK: fence9
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>

using namespace std;

int my_floor(int num, int den) {
    if (num % den == 0) return num / den;
    else return num / den + (num > 0 ? 0 : -1);
}

int my_ceil(int num, int den) {
    if (num % den == 0) return num / den;
    else return num / den + 1;
}

int main() {
    ifstream fin("fence9.in");
    ofstream fout("fence9.out");
    
    int n, m, p;
    fin >> n >> m >> p;

    int ret = 0;
    for (int y = 1; y <= m; y++) {
        int left = my_ceil(n * y + 1, m);
        int right = my_floor((y - m) * (n - p) - 1, m) + n;
        ret += max(0, right - left + 1);
    }
    fout << ret << endl;

    return 0;
}