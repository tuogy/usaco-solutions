/*
USER: guobich1
TASK: numtri
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream fin("numtri.in");
    ofstream fout("numtri.out");
    
    int R;
    fin >> R;
    vector<vector<int>> nums(R, vector<int>(R));
    for (int i = 1; i <= R; i++) {
        for (int j = 0; j < i; j++) {
            fin >> nums[i - 1][j];
        }
    }
    for (int i = R - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            nums[i][j] += max(nums[i + 1][j], nums[i + 1][j + 1]);
        }
    }
    fout << nums[0][0] << endl;

    return 0;
}