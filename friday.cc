/*
USER: guobich1
TASK: friday
LANG: C++
*/

#include <iostream>
#include <fstream>
using namespace std;

const int daysinMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool isLeapYear(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int main() {
    ifstream fin("friday.in");
    ofstream fout("friday.out");
    
    int N;
    fin >> N;

    int ret[7] = {0};
    int day[13] = {0, 5};
    for (int m = 2; m <= 12; m++) {
        day[m] = (day[m - 1] + daysinMonth[m - 1]) % 7;
    }
    for (int i = 0; i < N; i++) {
        for (int m = 1; m <= 12; m++) {
            ret[day[m]]++;
            if (m < 3) {
                day[m] = (day[m] + 1 + isLeapYear(1900 + i)) % 7;
            }
            else {
                day[m] = (day[m] + 1 + isLeapYear(1900 + i + 1)) % 7;
            }
        }
    }

    fout << ret[5] << ' ' << ret[6] << ' ';
    for (int i = 0; i < 5; i++)
        fout << ret[i] << ((i == 4) ? '\n' : ' ');

    return 0;
}