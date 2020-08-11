/*
USER: guobich1
TASK: heritage
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

int main() {
    ifstream fin("heritage.in");
    ofstream fout("heritage.out");
    
    string inorder, preorder;
    getline(fin, inorder);
    getline(fin, preorder);
    int n = inorder.size();
    int pos[26];
    for (int i = 0; i < n; i++) {
        pos[inorder[i] - 'A'] = i;
    }

    stack<vector<int>> stk;
    stk.push({0, n - 1, 0, n - 1});
    while (!stk.empty()) {
        auto& v = stk.top(); 
        int il = v[0], ir = v[1], pl = v[2], pr = v[3];
        stk.pop();
        if (il > ir) continue;
        else if (il == ir) {
            fout << inorder[il];
        }
        else {
            int j = pos[preorder[pl] - 'A'];
            int len_left = j - il, len_right = ir - j;
            stk.push({j, j, pl, pl});
            if (len_right)
                stk.push({j + 1, ir, pr + j - ir + 1, pr});
            if (len_left)
                stk.push({il, j - 1, pl + 1, pl + j - il});
        }
    }
    fout << endl;

    return 0;
}