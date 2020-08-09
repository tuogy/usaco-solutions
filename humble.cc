/*
USER: guobich1
TASK: humble
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ifstream fin("humble.in");
    ofstream fout("humble.out");
    
    int K, N, p;
    fin >> K >> N;

    vector<int> humbles {1};
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;

    for (int i = 0; i < K; i++) {
        fin >> p;
        pq.push({p, p, 0});
    }
    while (humbles.size() <= N) {
        auto& v = pq.top();
        if (v[0] > humbles.back()) humbles.push_back(v[0]);
        pq.push({v[1] * humbles[v[2] + 1], v[1], v[2] + 1});
        pq.pop();
    }

    fout << humbles.back() << endl;

    return 0;
}