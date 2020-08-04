/*
USER: guobich1
TASK: transform
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int N;
char s[10][10], t[10][10], ss[10][10];

void copy(char a[][10], char b[][10]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            b[i][j] = a[i][j];
}

void hflip(char v[][10]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N / 2; j++) 
            swap(v[i][j], v[i][N - 1 - j]);
}

void rotate90(char v[][10]) {
    hflip(v);
    for (int i = 0; i < N; i++) {
        for (int j = 0; i + j < N - 1; j++) {
            swap(v[i][j], v[N - 1 - j][N - 1 - i]);
        }
    }
}

void print(char v[][10]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
}

bool same(char a[][10], char b[][10]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (a[i][j] != b[i][j]) return false;
        }
    }
    return true;
}

int main() {
    ifstream fin("transform.in");
    ofstream fout("transform.out");
    
    fin >> N;
    
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            fin >> s[i][j];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            fin >> t[i][j];
    
    copy(s, ss);
    for (int i = 1; i <= 3; i++) {
        rotate90(ss);
        if (same(ss, t)) {
            fout << i << endl; return 0;
        }
    }
    copy(s, ss);
    hflip(ss);
    if (same(ss, t)) {
        fout << 4 << endl; return 0;
    }
    for (int i = 1; i <= 3; i++) {
        rotate90(ss);
        if (same(ss, t)) {
            fout << 5 << endl; return 0;
        }
    }
    if (same(s, t)) {
        fout << 6 << endl; return 0;
    }
    fout << 7 << endl;
    
    return 0;
}