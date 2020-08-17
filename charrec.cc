/*
USER: guobich1
TASK: charrec
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

using namespace std;

const int inf = 0x3f3f3f3f;
int fonts[27][20];

int main() {
    ifstream fin("charrec.in");
    ifstream ffont("font.in");
    ofstream fout("charrec.out");
    
    int N;
    ffont >> N;
    for (int i = 0; i < 27; i++) {
        for (int j = 0; j < 20; j++) {
            int val = 0; char c;
            for (int k = 0; k < 20; k++) {
                ffont >> c;
                val = (val << 1) | (c == '1');
            }
            fonts[i][j] = val;
        }
    }

    fin >> N;
    vector<int> data(N), dp(N + 1, inf), dp_next(N + 1, -1), dp_choice(N + 1, -1);
    for (int i = 0; i < N; i++) {
        int val = 0; char c;
        for (int k = 0; k < 20; k++) {
            fin >> c;
            val = (val << 1) | (c == '1');
        }
        data[i] = val;
    }

    dp[N] = 0;
    for (int i = N - 1; i >= 0; i--) {
        unordered_set<int> choice;
        if (i + 20 <= N && dp[i + 20] < inf) {
            for (int j = 0; j < 27; j++) {
                int num_replace = 0;
                for (int k = 0; k < 20; k++) {
                    num_replace += __builtin_popcount(data[i + k] ^ fonts[j][k]);
                }
                if (num_replace <= 120) { 
                    if (dp[i] == num_replace + dp[i + 20])
                        choice.insert(j);
                    else if (dp[i] > num_replace + dp[i + 20]) {
                        dp[i] = num_replace + dp[i + 20];
                        dp_next[i] = i + 20;
                        choice.clear();
                        choice.insert(j);
                    }
                }
            }
        }
        if (i + 19 <= N && dp[i + 19] < inf) {
            for (int j = 0; j < 27; j++) {
                for (int miss = 0; miss < 20; miss++) {
                    int num_replace = 0;
                    for (int k = 0; k < 19; k++) {
                        if (k < miss)
                            num_replace += __builtin_popcount(data[i + k] ^ fonts[j][k]);
                        else
                            num_replace += __builtin_popcount(data[i + k] ^ fonts[j][k + 1]);
                    }
                    if (num_replace <= 120) { 
                        if (dp[i] == num_replace + dp[i + 19])
                            choice.insert(j);
                        else if (dp[i] > num_replace + dp[i + 19]) {
                            dp[i] = num_replace + dp[i + 19];
                            dp_next[i] = i + 19;
                            choice.clear();
                            choice.insert(j);
                        }
                    }
                }
            }
        }
        if (i + 21 <= N && dp[i + 21] < inf) {
            for (int j = 0; j < 27; j++) {
                for (int dup = 0; dup < 20; dup++) {
                    int num_replace = 0;
                    for (int k = 0; k < 20; k++) {
                        if (k < dup)
                            num_replace += __builtin_popcount(data[i + k] ^ fonts[j][k]);
                        else if (k > dup)
                            num_replace += __builtin_popcount(data[i + k + 1] ^ fonts[j][k]);
                        else
                            num_replace += min(__builtin_popcount(data[i + k] ^ fonts[j][k]), 
                                               __builtin_popcount(data[i + k + 1] ^ fonts[j][k]));
                    }
                    if (num_replace <= 120) { 
                        if (dp[i] == num_replace + dp[i + 21])
                            choice.insert(j);
                        else if (dp[i] > num_replace + dp[i + 21]) {
                            dp[i] = num_replace + dp[i + 21];
                            dp_next[i] = i + 21;
                            choice.clear();
                            choice.insert(j);
                        }
                    }
                }
            }
        }
        if (choice.size() == 1) dp_choice[i] = *choice.begin();
        else dp_choice[i] = -1;
    }
    
    string images = " abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i != N; i = dp_next[i]) {
        if (dp_choice[i] == -1) fout << '?';
        else fout << images[dp_choice[i]];
    }
    fout << endl;

    return 0;
}