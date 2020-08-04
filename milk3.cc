/*
USER: guobich1
TASK: milk3
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

bool vis[21*21*21];
bool visC[21];
int A, B, C;

int hash3(int a, int b, int c) {
    return a * 21 * 21 + b * 21 + c;
}

void dfs(int a, int b, int c) {
    if (vis[hash3(a, b, c)]) return;
    vis[hash3(a, b, c)] = true;
    if (a == 0) visC[c] = true;
    int a2b = min(a, B - b), a2c = min(a, C - c);
    int b2a = min(b, A - a), b2c = min(b, C - c);
    int c2a = min(c, A - a), c2b = min(c, B - b);
    dfs(a - a2b, b + a2b, c);
    dfs(a - a2c, b, c + a2c);
    dfs(a + b2a, b - b2a, c);
    dfs(a, b - b2c, c + b2c);
    dfs(a + c2a, b, c - c2a);
    dfs(a, b + c2b, c - c2b);
}


int main() {
    ifstream fin("milk3.in");
    ofstream fout("milk3.out");
    
    fin >> A >> B >> C;
    memset(vis, 0, 21*21*21*sizeof(bool));
    memset(visC, 0, 21*sizeof(bool));
    dfs(0, 0, C);
    for (int i = 0; i < C; i++) {
        if (visC[i]) fout << i << " ";
    }
    fout << C << endl;

    return 0;
}