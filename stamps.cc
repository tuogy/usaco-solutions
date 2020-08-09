/*
USER: guobich1
TASK: stamps
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;
using ii = pair<int, int>;

void merge_int(vector<ii>& a, vector<ii>& b, int add, vector<ii>& ret) {
    vector<ii>().swap(ret);

    int i = 0, j = 0, c = 0, l, r;
    while (i < a.size() || j < b.size()) {
        if (i < a.size() && (
            j == b.size() || a[i].first < b[j].first + add || a[i].first == b[j].first + add && a[i].second == 0
            )) {
            if (a[i].second == 0) {
                if (c == 0) l = a[i].first;
                c++;
            }
            else {
                c--;
                if (c == 0) {
                    ret.push_back({l, 0});
                    ret.push_back({a[i].first, 1});
                }
            }
            i++;
        }
        else {
            if (b[j].second == 0) {
                if (c == 0) l = b[j].first + add;
                c++;
            }
            else {
                c--;
                if (c == 0) {
                    ret.push_back({l, 0});
                    ret.push_back({b[j].first + add, 1});
                }
            }
            j++;
        }
    }
}

int main() {
    ifstream fin("stamps.in");
    ofstream fout("stamps.out");
    
    int N, K;
    fin >> K >> N;
    vector<int> stamps(N);
    for (int i = 0; i < N; i++) fin >> stamps[i];
    sort(stamps.begin(), stamps.end());

    vector<vector<ii>> dp(K + 1, {{0, 0}, {1, 1}});
    vector<ii> prev, cur;
    for (int n = 1; n <= N; n++) {
        prev = {{0, 0}, {1, 1}};
        for (int k = 1; k <= K; k++) {
            merge_int(dp[k], prev, stamps[n - 1], cur);
            dp[k - 1].swap(prev);
            dp[k - 1].shrink_to_fit();
            prev.swap(cur);
        }
        dp[K].swap(prev);
        dp[K].shrink_to_fit();

        // cout << "---" << n << "---" << endl;
        // for (int k = 0; k <= K; k++) {
        //     cout << '#' << k << ':' << dp[k].size() << endl;
        //     for (int i = 0; i < dp[k].size(); i += 2) 
        //         cout << '[' << dp[k][i].first << ',' << dp[k][i + 1].first << ']';
        //     cout << endl;
        // }
    }
    fout << dp[K][1].first - 1 << endl;

    return 0;
}