/*
USER: guobich1
TASK: fact4
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>

using namespace std;

struct Int {
    int fact2;
    int fact5;
    int x;
};

Int convert(int n) {
    Int ret;
    ret.fact2 = ret.fact5 = 0;
    while (n % 2 == 0) ret.fact2++, n /= 2;
    while (n % 5 == 0) ret.fact5++, n /= 5;
    ret.x = n % 10;
    return ret;
}

int main() {
    ifstream fin("fact4.in");
    ofstream fout("fact4.out");
    
    Int cur;
    cur.fact2 = cur.fact5 = 0;
    cur.x = 1;

    int N;
    fin >> N;
    for (int i = 1; i <= N; i++) {
        Int n = convert(i);
        cur.fact2 += n.fact2;
        cur.fact5 += n.fact5;
        cur.x = cur.x * n.x % 10;
    }
    if (cur.fact2 >= cur.fact5) {
        cur.fact2 -= cur.fact5;
        for (int i = 0; i < cur.fact2; i++) cur.x = cur.x * 2 % 10;
    }
    else {
        cur.fact5 -= cur.fact2;
        for (int i = 0; i < cur.fact5; i++) cur.x = cur.x * 5 % 10;
    }
    fout << cur.x << endl;

    return 0;
}