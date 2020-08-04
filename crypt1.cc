/*
USER: guobich1
TASK: crypt1
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>

using namespace std;


int alldigits(int a, int b) {
    int ret = 0;
    int p1 = a * (b % 10);
    int p2 = a * (b / 10);
    int p = a * b;
    if (a < 100 || a > 999 || b < 10 || b > 99 || p1 < 100 || p1 > 999 
    || p2 < 100 || p2 > 999 || p < 1000 || p > 9999) return -1;
    for (auto num : {a, b, p1, p2, p}) {
        while (num) {
            ret |= 1 << (num % 10);
            num /= 10;
        }
    }
    return ret;
}


int main() {
    ifstream fin("crypt1.in");
    ofstream fout("crypt1.out");
    
    int N, c, req = 0, ret = 0;
    fin >> N;
    for (int i = 0; i < N; i++) {
        fin >> c;
        req |= (1 << c);
    }

    for (int a = 100; a < 1000; a++) {
        for (int b = 10; b < 100; b++) {
            int cc = alldigits(a, b);
            if ((cc & req) == cc) ret++;
        }
    }
    fout << ret << endl;

    return 0;
}