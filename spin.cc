/*
USER: guobich1
TASK: spin
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>

using namespace std;

bool contains(int deg, int wedge[2]) {
    if (wedge[0] + wedge[1] >= 360) return deg >= wedge[0] || deg <= (wedge[0] + wedge[1]) % 360;
    else return deg >= wedge[0] && deg <= wedge[0] + wedge[1];
}

int main() {
    ifstream fin("spin.in");
    ofstream fout("spin.out");
    
    int rot[5], nw[5], w[5][5][2];
    for (int i = 0; i < 5; i++) {
        fin >> rot[i] >> nw[i];
        for (int j = 0; j < nw[i]; j++) {
            fin >> w[i][j][0] >> w[i][j][1];
        }
    }

    for (int t = 0; t < 360; t++) {
        for (int deg = 0; deg < 360; deg++) {
            int nw_found = 0;
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < nw[i]; j++)  {
                    if(contains(deg, w[i][j])) {
                        nw_found++; break;
                    }
                }
            }
            if (nw_found == 5) {
                fout << t << endl;
                return 0;
            }
        }
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < nw[i]; j++) {
                w[i][j][0] += rot[i];
                w[i][j][0] %= 360;
            }
        }
    }
    fout << "none" << endl;

    return 0;
}