/*
USER: guobich1
TASK: milk2
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ifstream fin("milk2.in");
    ofstream fout("milk2.out");
    
    int N, s, e;
    fin >> N;
    vector<vector<int>> times;
    for (int i = 0; i < N; i++) {
        fin >> s >> e;
        times.push_back({s, e});
    }
    sort(times.begin(), times.end());
    int l = times[0][0], r = times[0][1], alone = r - l, noone = 0;
    for (int j = 1; j < N; j++) {
        if (times[j][0] > r) noone = max(noone, times[j][0] - r), l = times[j][0], r = times[j][1];
        else if (times[j][1] > r) r = times[j][1], alone = max(alone, r - l);
    }
    fout << alone << " " << noone << endl;

    return 0;
}