/*
USER: guobich1
TASK: frameup
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

int H, W;
char frame[30][30];
bool cover[26][26];
int outdeg[26];
int ll[26], rr[26], tt[26], bb[26];
char buf[26];

void print_dfs(string& letters, int pos, ofstream& fout) {
    if (pos == letters.size()) {
        for (int i = 0; i < pos; i++) fout << buf[i];
        fout << endl;
        return;
    }
    for (int i = 0; i < letters.size(); i++) {
        int u = letters[i] - 'A';
        if (letters[i] == ' ' || outdeg[u] > 0) continue;
        buf[pos] = letters[i];
        letters[i] = ' ';
        for (int v = 0; v < 26; v++) {
            if (cover[v][u]) outdeg[v]--; 
        }
        print_dfs(letters, pos + 1, fout);
        for (int v = 0; v < 26; v++) {
            if (cover[v][u]) outdeg[v]++; 
        }
        letters[i] = u + 'A';
    }
}

int main() {
    ifstream fin("frameup.in");
    ofstream fout("frameup.out");
    
    fin >> H >> W;
    memset(cover, 0, 26*26*sizeof(bool));
    memset(outdeg, 0, 26*sizeof(int));
    memset(ll, 0x3f, 26*sizeof(int));
    memset(rr, -1, 26*sizeof(int));
    memset(tt, 0x3f, 26*sizeof(int));
    memset(bb, -1, 26*sizeof(int));

    char x;
    for (int r = 0; r < H; r++) {
        for (int c = 0; c < W; c++) {
            fin >> x;
            frame[r][c] = x;
            if (x >= 'A' && x <= 'Z') {
                int i = x - 'A';
                ll[i] = min(ll[i], c); rr[i] = max(rr[i], c);
                tt[i] = min(tt[i], r); bb[i] = max(bb[i], r);
            }
        }
    }

    string letters = "";
    for (char z = 'A'; z <= 'Z'; z++) {
        int i = z - 'A';
        if (rr[i] >= 0) letters += z;
        else continue;
        for (int c = ll[i]; c <= rr[i]; c++) {
            if (frame[tt[i]][c] != z) cover[frame[tt[i]][c] - 'A'][i] = true;
            if (frame[bb[i]][c] != z) cover[frame[bb[i]][c] - 'A'][i] = true;
        }
        for (int r = tt[i]; r <= bb[i]; r++) {
            if (frame[r][ll[i]] != z) cover[frame[r][ll[i]] - 'A'][i] = true;
            if (frame[r][rr[i]] != z) cover[frame[r][rr[i]] - 'A'][i] = true;
        }
    }
    for (int u = 0; u < 26; u++) 
        for (int v = 0; v < 26; v++)
            outdeg[u] += cover[u][v];

    print_dfs(letters, 0, fout);
    
    return 0;
}