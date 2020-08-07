/*
USER: guobich1
TASK: zerosum
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>

using namespace std;

char ops[9];
int N;

void dfs(int pos, int tot, int lastn, int sign, ofstream& fout) {
    if (pos == N) {
        if (tot + sign * lastn == 0) {
            fout << 1;
            for (int i = 1; i < N; i++) {
                fout << ops[i] << i + 1;
            }
            fout << endl;
        }
        return;
    }
    else {
        ops[pos] = ' ';
        dfs(pos + 1, tot, lastn * 10 + pos + 1, sign, fout);
        ops[pos] = '+';
        dfs(pos + 1, tot + sign * lastn, pos + 1, 1, fout);
        ops[pos] = '-';
        dfs(pos + 1, tot + sign * lastn, pos + 1, -1, fout);
    }
}

int main() {
    ifstream fin("zerosum.in");
    ofstream fout("zerosum.out");
    
    fin >> N;
    dfs(1, 0, 1, 1, fout);

    return 0;
}