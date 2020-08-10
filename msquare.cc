/*
USER: guobich1
TASK: msquare
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <queue>
#include <vector>

using namespace std;

int tA(int n) {
    int ret = 0;
    while (n) ret = ret * 10 + n % 10, n /= 10;
    return ret;
}

int tB(int n) {
    int ret = n / 10000 % 10;
    ret = ret * 1000 + n / 100000;
    ret = ret * 1000 + n % 1000;
    ret = ret * 10 + n / 1000 % 10;
    return ret;
}

int tC(int n) {
    vector<int> digits; digits.reserve(8);
    while (n) {
        digits.push_back(n % 10); n /= 10;
    }
    int ret = 0;
    for (int i : {7, 1, 6, 4, 3, 5, 2, 0})
        ret = ret * 10 + digits[i];
    return ret;
}

int main() {
    ifstream fin("msquare.in");
    ofstream fout("msquare.out");
    
    int N = 0, x;
    for (int i = 0; i < 8; i++) {
        fin >> x;
        N = N * 10 + x;
    }

    vector<pair<int, char>> record = {{-1, ' '}};
    queue<pair<int, int>> bfs;
    unordered_set<int> vis;
    bfs.push({12345678, 0});
    vis.insert(12345678);
    int n, recid;
    while (!bfs.empty()) {
        n = bfs.front().first;
        recid = bfs.front().second;
        if (n == N) break;
        else bfs.pop();
        int na = tA(n);
        if (vis.find(na) == vis.end()) {
            vis.insert(na);
            record.push_back({recid, 'A'});
            bfs.push({na, record.size() - 1});
        }
        int nb = tB(n);
        if (vis.find(nb) == vis.end()) {
            vis.insert(nb);
            record.push_back({recid, 'B'});
            bfs.push({nb, record.size() - 1});
        }
        int nc = tC(n);
        if (vis.find(nc) == vis.end()) {
            vis.insert(nc);
            record.push_back({recid, 'C'});
            bfs.push({nc, record.size() - 1});
        }
    }
    string ret = "";
    while (recid != -1) {
        ret += record[recid].second;
        recid = record[recid].first;
    }
    reverse(ret.begin(), ret.end());
    fout << ret.size() - 1 << endl;
    int c = 0;
    stringstream ss;
    for (auto c : ret) ss << c;
    char xx;
    while (ss >> xx) {
        c++, fout << xx;
        if (c == 60) {
            fout << endl; c = 0;
        }
    }
    if (c || ret.size() == 1) fout << endl;

    return 0;
}