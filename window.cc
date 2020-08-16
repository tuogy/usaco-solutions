/*
USER: guobich1
TASK: window
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
using ii = pair<int, int>;

class Window {
public:
    Window(int l=0, int r=0, int t=0, int b=0) : 
    l(l), r(r), t(t), b(b), prev(nullptr), next(nullptr) {}
    int l, r, t, b;
    Window *prev, *next;
};

class coord {
public:
    coord(int l=0, int r=0, int t=0, int b=0) : l(l), r(r), t(t), b(b) {}
    int l, r, t, b;
};

Window* pwins[256], *head, *tail;

coord get_coord(string& line) {
    int i = 4, j = 0, val[4] = {0}, n = line.size();
    while (i < n) {
        if (line[i] >= '0' && line[i] <= '9') val[j] = val[j] * 10 + line[i++] - '0';
        else i++, j++;
    }
    return coord(min(val[0], val[2]), max(val[0], val[2]), max(val[1], val[3]), min(val[1], val[3]));
}

double print_visible(Window *w) {
    if (!w) return 0.;
    vector<int> xs;
    for (auto p = head->next; p != w->next; p = p->next) {
        xs.push_back(p->l); xs.push_back(p->r);
    }
    sort(xs.begin(), xs.end());
    int h_prev = 0, x_prev = 0, xs_size = xs.size();
    int area = 0;
    for (int i = 0; i < xs_size; i++) {
        vector<ii> ys;
        for (auto p = head->next; p != w; p = p->next) {
            if (xs[i] >= p->l && xs[i] < p->r) {
                ys.push_back({p->b, 1});
                ys.push_back({p->t, -1});
            }
        }
        sort(ys.begin(), ys.end());
        int counter = 0, y_prev = -1, h_cur = 0;
        for (auto it = ys.begin(); it != ys.end(); it++) {
            if (it->second == -1) {
                counter--;
                if (counter == 0) {
                    h_cur += max(0, min(w->t, it->first) - max(w->b, y_prev));
                }
            }
            else {
                if (counter == 0) y_prev = it->first;
                counter++;
            }
        }
        area += max(0, min(w->r, xs[i]) - max(w->l, x_prev)) * h_prev;
        h_prev = h_cur;
        x_prev = xs[i];
    }
    double ret = 100. - area * 100. / ((w->t - w->b) * (w->r - w->l));
    // cout << ret << endl;
    return ret;
}

int main() {
    ifstream fin("window.in");
    ofstream fout("window.out");


    memset(pwins, 0, 256 * sizeof(Window*));
    head = new Window();
    tail = new Window();
    head->next = tail; tail->prev = head;

    string input;
    while (getline(fin, input)) {
        char id = input[2];
        Window *w;
        coord c;
        switch (input[0]) {
            case 'w':
                if (pwins[id]) break;
                c = get_coord(input);
                w = new Window(c.l, c.r, c.t, c.b);
                pwins[id] = w;
                head->next->prev = w;
                w->next = head->next;
                w->prev = head;
                head->next = w;
                break;
            case 't':
                if (!pwins[id]) break;
                w = pwins[id];
                w->prev->next = w->next;
                w->next->prev = w->prev;
                head->next->prev = w;
                w->next = head->next;
                w->prev = head;
                head->next = w;
                break;
            case 'b':
                if (!pwins[id]) break;
                w = pwins[id];
                w->prev->next = w->next;
                w->next->prev = w->prev;
                tail->prev->next = w;
                w->prev = tail->prev;
                w->next = tail;
                tail->prev = w;
                break;
            case 'd':
                if (!pwins[id]) break;
                w = pwins[id];
                w->prev->next = w->next;
                w->next->prev = w->prev;
                pwins[id] = nullptr;
                delete w;
                break;
            case 's':
                w = pwins[id];
                fout << fixed << setprecision(3) << print_visible(w) << endl;
        }
    }


    return 0;
}