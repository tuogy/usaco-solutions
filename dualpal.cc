/*
USER: guobich1
TASK: dualpal
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool isPalinBaseB(int n, int B) {
    string s;
    while (n) {
        s += '0' + (n % B);
        n /= B;
    }
    for (int i = 0, j = (int)s.size() - 1; i < j; i++, j--) {
        if (s[i] != s[j]) return false;
    }
    return true;
} 

int main() {
    ifstream fin("dualpal.in");
    ofstream fout("dualpal.out");
    
    int N, S;
    fin >> N >> S;
    for (int i = S + 1, c = 0; c < N; i++) {
        int count = 0;
        for (int b = 2; b <= 10 && count < 2; b++) {
            if (isPalinBaseB(i, b)) count++;
        }
        if (count == 2) {
            c++;
            fout << i << endl;
        }
    }

    return 0;
}