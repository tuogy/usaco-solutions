/*
USER: guobich1
TASK: palsquare
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

char int2char[20];

string toBaseB(int n, int B) {
    string ret;
    while (n) {
        ret += int2char[n % B];
        n /= B;
    }
    return ret;
} 

bool isPalin(string& s) {
    for (int i = 0, j = (int)s.size() - 1; i < j; i++, j--) {
        if (s[i] != s[j]) return false;
    }
    return true;
}

int main() {
    ifstream fin("palsquare.in");
    ofstream fout("palsquare.out");
    
    for (int i = 0; i < 10; i++) int2char[i] = '0' + i;
    for (int i = 10; i < 20; i++) int2char[i] = 'A' + i - 10;

    int B;
    fin >> B;
    for (int n = 1; n <= 300; n++) {
        string n2s = toBaseB(n * n, B);
        if (isPalin(n2s)) {
            string ns = toBaseB(n, B);
            reverse(ns.begin(), ns.end());
            reverse(n2s.begin(), n2s.end());
            fout << ns << " " << n2s << endl;
        }
    }

    return 0;
}