/*
USER: guobich1
TASK: sort3
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int nums[1000];

int main() {
    ifstream fin("sort3.in");
    ofstream fout("sort3.out");
    
    int N;
    fin >> N;
    int counts[4] = {0};
    int mx[4][4] = {0};
    for (int i = 0; i < N; i++) {
        fin >> nums[i];
        counts[nums[i]]++;
    }
    for (int i = 0; i < N; i++) {
        if (i < counts[1]) mx[1][nums[i]]++;
        else if (i < counts[1] + counts[2]) mx[2][nums[i]]++;
        else mx[3][nums[i]]++;
    }
    int ret = 0;
    int ex12 = min(mx[1][2], mx[2][1]);
    ret += ex12, mx[1][2] -= ex12, mx[2][1] -= ex12;
    int ex23 = min(mx[2][3], mx[3][2]);
    ret += ex23, mx[2][3] -= ex23, mx[3][2] -= ex23;
    int ex31 = min(mx[3][1], mx[1][3]);
    ret += ex31, mx[3][1] -= ex31, mx[1][3] -= ex31;
    ret += 2 * max(mx[1][2], mx[1][3]);
    fout << ret << endl;

    return 0;
}