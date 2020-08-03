/*
USER: guobich1
TASK: gift1
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
    ifstream fin("gift1.in");
    ofstream fout("gift1.out");
    
    int NP;
    vector<string> names;
    unordered_map<string, int> balance;

    fin >> NP; fin.ignore();
    for (int i = 0; i < NP; i++) {
        string name;
        getline(fin, name);
        balance[name] = 0;
        names.emplace_back(name);
    }

    string name, recv;
    int amount, n;
    for (int i = 0; i < NP; i++) {
        getline(fin, name);
        fin >> amount >> n; fin.ignore();
        if (n == 0) continue;
        balance[name] -= amount - amount % n;
        for (int j = 0; j < n; j++) {
            getline(fin, recv);
            balance[recv] += amount / n;
        }
    }

    for (auto& name : names) {
        fout << name << " " << balance[name] << endl;
    }

    return 0;
}