/*
USER: guobich1
TASK: cowtour
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const float inf = 1e12;
double dist[150][150];
double longest[150];
double longest_group[150];

double compute_dist(pair<int, int>& a, pair<int, int>& b) {
    return sqrt(pow(a.first - b.first, 2.0) + pow(a.second - b.second, 2.0));
}

int main() {
    ifstream fin("cowtour.in");
    ofstream fout("cowtour.out");
    
    int N, x, y;
    char c;
    fin >> N;
    vector<pair<int, int>> pas(N);
    for (int i = 0; i < N; i++) {
        fin >> x >> y;
        pas[i] = {x, y};
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fin >> c;
            if (i == j) dist[i][j] = 0.;
            else if (c == '0') dist[i][j] = inf;
            else dist[i][j] = compute_dist(pas[i], pas[j]);
        }
    }

    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    for (int i = 0; i < N; i++) {
        longest[i] = 0.;
        for (int j = 0; j < N; j++) {
            if (dist[i][j] < inf)
                longest[i] = max(longest[i], dist[i][j]);
        }
    }

    for (int i = 0; i < N; i++) {
        longest_group[i] = 0.;
        for (int j = 0; j < N; j++) {
            if (dist[i][j] < inf)
                longest_group[i] = max(longest_group[i], longest[j]);
        }
    }

    double ret = inf, cur;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (dist[i][j] == inf) {
                cur = max({longest[i] + longest[j] + compute_dist(pas[i], pas[j]), longest_group[i], longest_group[j]});
                if (cur < ret) ret = cur;
            }
        }
    }

    fout << fixed << setprecision(6) << ret << endl;

    return 0;
}