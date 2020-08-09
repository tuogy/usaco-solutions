/*
USER: guobich1
TASK: contact
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

char buf[200000];

int main() {
    ifstream fin("contact.in");
    ofstream fout("contact.out");
    
    int A, B, N;
    char x;
    fin >> A >> B >> N;

    int nchar = 0;
    while (fin >> x) {
        buf[nchar++] = x;
    }

    vector<pair<int, string>> freq;
    for (int len = A; len <= B && len <= nchar; len++) {
        vector<pair<int, int>> dp(1 << len);
        for (int i = 0; i < dp.size(); i++) dp[i] = {0, i}; 
        int cur = 0;
        for (int i = 0; i < len; i++) cur = (cur << 1) + (buf[i] == '1');
        dp[cur].first++;
        for (int i = len; i < nchar; i++) {
            cur = (cur << 1) + (buf[i] == '1') - ((buf[i - len] == '1') << len);
            dp[cur].first++;
        }
        sort(dp.begin(), dp.end());
        for (int i = dp.size() - 1; i >= 0; i--) {
            if (dp[i].first == 0) break;
            else {
                string cur(len, ' ');
                for (int d = len - 1; d >= 0; d--)
                    cur[len - 1 - d] = (dp[i].second & (1 << d)) ? '1' : '0';
                freq.push_back({dp[i].first, cur});
            }
        }
    }
    sort(freq.begin(), freq.end(), [](pair<int, string>& a, pair<int, string>& b) {
        return (a.first > b.first) || (a.first == b.first && (a.second.size() < b.second.size() ||
        a.second.size() == b.second.size() && a < b));
    });
    int prev = INT_MAX, nfreq = 0;
    for (int i = 0, count = 0; i < freq.size(); i++) {
        if (freq[i].first != prev) {
            prev = freq[i].first;
            nfreq++;
            if (nfreq > N) break;
            if (nfreq > 1) fout << endl;
            fout << freq[i].first << endl << freq[i].second;
            count = 1;
        }
        else {
            if (count == 6) {
                count = 1;
                fout << endl << freq[i].second;
            }
            else {
                count++;
                fout << " " << freq[i].second;
            }
        }
    }
    fout << endl;

    return 0;
}