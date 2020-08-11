/*
USER: guobich1
TASK: shopping
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int p[5], bct[5];
int code[1000];
int sp_p[100], sp_n[100], sp_ct[100][5], sp_code[100][5];
int pos[8000];

void make_states(vector<vector<int>>& states, vector<int>& state, int b, int cur) {
    if (cur == b) {
        int hash = 0;
        for (auto i : state) hash = hash * 6 + i;
        pos[hash] = states.size();
        states.push_back(state);
        return;
    }
    else {
        for (int i = 0; i <= bct[cur]; i++) {
            state.push_back(i);
            make_states(states, state, b, cur + 1);
            state.pop_back();
        }
    }
}


int main() {
    ifstream fin("shopping.in");
    ofstream fout("shopping.out");
    
    memset(code, -1, 1000*sizeof(int));
    int s, b, c;
    fin >> s;
    for (int i = 0; i < s; i++) {
        fin >> sp_n[i];
        for (int j = 0; j < sp_n[i]; j++) {
            fin >> sp_code[i][j] >> sp_ct[i][j];
        }
        fin >> sp_p[i];
    }
    fin >> b;
    for (int i = 0; i < b; i++) {
        fin >> c >> bct[i] >> p[i];
        code[c] = i;
    }

    vector<vector<int>> states;
    vector<int> state;
    make_states(states, state, b, 0);
    int nstates = states.size();

    vector<int> dp(nstates), dp_next(nstates);
    for (int i = 0; i < nstates; i++) {
        dp[i] = 0;
        for (int j = 0; j < states[i].size(); j++) 
            dp[i] += states[i][j] * p[j];
    }
    for (int k = 0; k < s; k++) {
        for (int i = 0; i < nstates; i++) {
            dp_next[i] = dp[i];
            bool ok = true;
            vector<int> cur = states[i];
            for (int r = 1; ok; r++) {
                for (int j = 0, jj; j < sp_n[k] && ok; j++) {
                    jj = code[sp_code[k][j]];
                    if (jj == -1 || cur[jj] < sp_ct[k][j]) ok = false;
                    else cur[jj] -= sp_ct[k][j];
                }
                if (ok) {
                    int hash = 0;
                    for (auto v : cur)
                        hash = hash * 6 + v;
                    dp_next[i] = min(dp_next[i], dp[pos[hash]] + r * sp_p[k]);
                }
            }
        }
        dp.swap(dp_next);
    }
    int hash = 0;
    for (int i = 0; i < b; i++) hash = hash * 6 + bct[i];
    fout << dp[pos[hash]] << endl;

    return 0;
}