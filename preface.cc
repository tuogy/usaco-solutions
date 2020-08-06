/*
USER: guobich1
TASK: preface
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int prefix_c[5000][26];
int cur_c[5000][26];

vector<int> letters = {'C', 'D', 'I', 'L', 'M', 'V', 'X'};
int g_v[] = {1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};
string g_s[] = {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};
int tmp[32];

void compute_head(int n) {
    int i = 12;
    memset(tmp, 0, 32*sizeof(int));
    while (n) {
        if (g_v[i] <= n) {
            n -= g_v[i];
            for (auto c : g_s[i]) tmp[c - 'A']++;
        }
        else i--;
    }
    return;
}

int main() {
    ifstream fin("preface.in");
    ofstream fout("preface.out");

    int N;
    fin >> N;

    memset(prefix_c, 0, N*26*sizeof(int));
    memset(cur_c, 0, N*26*sizeof(int));
    for (auto& l : letters) l -= 'A';

    int base = 1, cur = 1;
    while (cur <= N) {
        compute_head(cur);
        for (int i : letters) {
            cur_c[cur][i] = tmp[i];
            prefix_c[cur][i] = prefix_c[cur - 1][i] + tmp[i];
            prefix_c[cur + base - 1][i] = prefix_c[cur][i] + prefix_c[base - 1][i] + tmp[i] * (base - 1);
        }
        cur += base;
        if (cur == base * 10) base = cur;
    }

    int dg = 1;
    for (int n = N; n; n /= 10) dg *= 10;
    dg /= 10;
    memset(tmp, 0, 32*sizeof(int));
    while (N) {
        int cur = dg * (N / dg);
        for (int i : letters) {
            tmp[i] += prefix_c[cur][i];
        }
        N %= dg;
        dg /= 10;
        for (int i : letters) {
            tmp[i] += cur_c[cur][i] * N;
        }
    }
    vector<int> letters_sorted = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
    int j = 6;
    while (tmp[letters_sorted[j] - 'A'] == 0) j--;
    for (int i = 0; i <= j; i++) fout << (char)letters_sorted[i] << " " << tmp[letters_sorted[i] - 'A'] << endl;

    return 0;
}