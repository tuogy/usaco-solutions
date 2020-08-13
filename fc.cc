/*
USER: guobich1
TASK: fc
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

struct coord {
    coord (double _x, double _y) :x(_x), y(_y) {}
    double x, y;
};

double eps = 1e-6;
bool ccw(coord& a, coord& b, coord& c) {
    double x1 = b.x - a.x, y1 = b.y - a.y;
    double x2 = c.x - b.x, y2 = c.y - b.y;
    double cpd = x1 * y2 - x2 * y1;
    return cpd > -eps;
}


int main() {
    ifstream fin("fc.in");
    ofstream fout("fc.out");

    int N;
    fin >> N;
    if (N <= 1) {
        fout << "0.00" << endl;
        return 0;
    }
    vector<coord> pos(N, {0., 0.});
    for (int i = 0; i < N; i++) {
        double x, y;
        fin >> x >> y;
        pos[i] = {x, y};
    }
    coord anchor(2e6, 2e6);
    for (int i = 0; i < N; i++) {
        if (pos[i].y < anchor.y || abs(pos[i].y - anchor.y) < eps && pos[i].x < anchor.x) 
            anchor = pos[i];
    }
    vector<int> pos_idx;
    for (int i = 0; i < N; i++) pos_idx.push_back(i);
    sort(pos_idx.begin(), pos_idx.end(), [&](int i, int j){
        double ang_i = atan2(pos[i].y - anchor.y, pos[i].x - anchor.x);
        double ang_j = atan2(pos[j].y - anchor.y, pos[j].x - anchor.x);
        if (abs(ang_i - ang_j) < eps) {
            double dist_i = pow(pos[i].y - anchor.y, 2.) + pow(pos[i].x - anchor.x, 2.);
            double dist_j = pow(pos[j].y - anchor.y, 2.) + pow(pos[j].x - anchor.x, 2.);
            return dist_i < dist_j;
        }
        else return ang_i < ang_j;
    });
    pos_idx.push_back(pos_idx.front());

    vector<int> hull_idx {{pos_idx[0], pos_idx[1]}};
    int j = 2;
    while (j != pos_idx.size()) {
        int last = hull_idx.back();
        hull_idx.pop_back();
        int prev = hull_idx.back();
        if (ccw(pos[prev], pos[last], pos[pos_idx[j]])) {
            hull_idx.push_back(last);
            hull_idx.push_back(pos_idx[j++]);
        }
    }
    double dist = 0.;
    for (int i = 1; i < hull_idx.size(); i++) {
        coord a = pos[hull_idx[i - 1]];
        coord b = pos[hull_idx[i]];
        dist += sqrt(pow(a.x - b.x, 2.) + pow(a.y - b.y, 2.));
    }
    fout << fixed << setprecision(2) << dist << endl;

    return 0;
}