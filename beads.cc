/*
USER: guobich1
TASK: beads
LANG: C++
*/

#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream fin("beads.in");
    ofstream fout("beads.out");
    
    int N;
    string beads;

    fin >> N; fin.ignore();
    getline(fin, beads);

    int nr = 0, nb = 0, ret = 0;
    for (auto c : beads) {
        nr += c == 'r';
        nb += c == 'b';
    }
    if (nr == 0 || nb == 0) ret = N;
    else {
        int l = 0, r = 0;
        while (beads[l] == 'w') l = (l + 1) % N;
        r = (l + 1) % N;
        while (beads[r] == 'w' || beads[l] == beads[r]) {
            if (beads[l] == beads[r]) l = r;
            r = (r + 1) % N;
        }
        int nl[350] = {0}, nr[350] = {0};
        int dist = (r + N - l) % N;
        nl[r] = dist; nr[l] = dist;
        for (int rr = r, r_next = r + 1, prev = r; r_next != r; rr = r_next) {
            r_next = (rr + 1) % N;
            if (beads[r_next] == 'w') nl[r_next] = nl[rr] + 1;
            else {
                if (beads[r_next] == beads[prev]) nl[r_next] = nl[rr] + 1;
                else nl[r_next] = (r_next + N - prev) % N;
                prev = r_next;
            }
        }
        for (int ll = l, l_next = l - 1, prev = l; l_next != l; ll = l_next) {
            l_next = (ll + N - 1) % N;
            if (beads[l_next] == 'w') nr[l_next] = nr[ll] + 1;
            else {
                if (beads[l_next] == beads[prev]) nr[l_next] = nr[ll] + 1;
                else nr[l_next] = (prev + N - l_next) % N;
                prev = l_next;
            }
        }
        ret = nr[0] + nl[N - 1];
        for (int i = 1; i < N; i++) ret = max(ret, nr[i] + nl[i - 1]);
        // for (int i = 0; i < N; i++) cout << beads[i] << ' ' << nl[i] << ' ' << nr[i] << endl;
    }
    fout << min(ret, N) << endl;

    return 0;
}