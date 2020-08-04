/*
USER: guobich1
TASK: namenum
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream fin("namenum.in");
    ofstream fout("namenum.out");
    
    int letter2num[26] = {0};
    for (int i = 2, letter = 'A', count = 0; letter != 'Z'; letter++) {
        if (letter == 'Q') continue;
        else if (count == 3) count = 0, i++;
        count++;
        letter2num[letter - 'A'] = i;
    }

    long long N;
    fin >> N;
    ifstream dict("dict.txt");
    
    string name;
    int count = 0;
    while (getline(dict, name)) {
        long long cur = 0;
        for (auto c : name) {
            if (c == 'Q' || c == 'Z' || cur > N) goto fail;
            else cur = cur * 10 + letter2num[c - 'A'];
        }
        if (cur == N) {
            count++;
            fout << name << endl;
        }
        fail:;
    }
    if (!count) fout << "NONE" << endl;
    
    return 0;
}