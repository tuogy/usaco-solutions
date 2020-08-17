/*
USER: guobich1
TASK: tour
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

const int inf = 0x3f3f3f3f;
int dp[100][100];
bool adj[100][100];

int main() {
    ifstream fin("tour.in");
    ofstream fout("tour.out");
    
    int N, V;
    fin >> N >> V;

    string loc, src, dest;
    unordered_map<string, int> um;
    for (int i = 0; i < N; i++) {
        fin >> loc;
        um[loc] = i;
    }

    memset(adj, 0, N * 100 * sizeof(bool));
    for (int i = 0; i < V; i++) {
        fin >> src >> dest;
        int src_i = um[src], dest_i = um[dest];
        adj[src_i][dest_i] = adj[dest_i][src_i] = true;
    }

    dp[N-1][N-1] = 1;
    for (int i = N - 2; i >= 0; i--) {
        for (int j = N - 1; j >= i; j--) {
            if (i == j && i) dp[i][j] = -inf;
            else {
                int best = -inf - 1;
                for (int k = i + 1; k < N; k++) {
                    if(adj[i][k] && dp[k][j] > best) 
                        best = dp[k][j];
                }
                dp[i][j] = dp[j][i] = 1 + best;
            }
        }
    }

    int ret = dp[0][0] - 1;
    if (ret < 0) ret = 1;
    fout << ret << endl;

    return 0;
}