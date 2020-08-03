/*
USER: guobich1
TASK: ride
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream fin("ride.in");
    ofstream fout("ride.out");
    
    string comet, group;
    getline(fin, comet);
    getline(fin, group);
    
    const int mod = 47;
    int ncomet = 1, ngroup = 1;
    for (auto c : comet) ncomet = ncomet * (c - 'A' + 1) % mod;
    for (auto c : group) ngroup = ngroup * (c - 'A' + 1) % mod;
    if (ncomet == ngroup) fout << "GO" << endl;
    else fout << "STAY" << endl;

    return 0;
}