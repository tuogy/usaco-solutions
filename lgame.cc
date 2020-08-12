/*
USER: guobich1
TASK: lgame
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int best_val, target;
int char_val[] = {
    2, 5, 4, 4, 1, 6, 5,
    5, 1, 7, 6, 3, 5, 2,
    3, 5, 7, 2, 1, 2,
    4, 6, 6, 7, 5, 7};

class TrieNode {
public:
    TrieNode() : word(false) { memset(ch, 0, 26*sizeof(TrieNode*)); }
    TrieNode* ch[26];
    bool word;
};

vector<vector<string>> results;
TrieNode* root;

void dfs(TrieNode* cur, string& letters, int curval, int prev) {
    if (prev > best_val) best_val = prev;
    int L = letters.size(); char x;
    for (int i = 0; i < L; i++) {
        if (letters[i] == ' ' || i && letters[i] == letters[i - 1]) continue;
        x = letters[i];
        if (cur->ch[x - 'a']) {
            letters[i] = ' ';
            dfs(cur->ch[x - 'a'], letters, curval + char_val[x - 'a'], prev);
            letters[i] = x;
        }
    }
    if (cur->word)
        dfs(root, letters, 0, prev + curval);
}

void dfs_second(TrieNode* cur, string& letters, int curval, int prev, vector<string>& buf, string& curword) {
    if (prev == target) {
        if (buf.size() == 1 || buf[0] <= buf[1])
            results.push_back(buf);
        return;
    }
    int L = letters.size(); char x;
    for (int i = 0; i < L; i++) {
        if (letters[i] == ' ' || i && letters[i] == letters[i - 1]) continue;
        x = letters[i];
        if (cur->ch[x - 'a']) {
            letters[i] = ' ';
            curword += x;
            dfs_second(cur->ch[x - 'a'], letters, curval + char_val[x - 'a'], prev, buf, curword);
            letters[i] = x;
            curword.pop_back();
        }
    }
    if (cur->word) {
        buf.push_back(curword);
        string nextword;
        dfs_second(root, letters, 0, prev + curval, buf, nextword);
        buf.pop_back();
    }
}

int main() {
    ifstream fin("lgame.in");
    ifstream fdict("lgame.dict");
    ofstream fout("lgame.out");
    
    string letters, word;
    getline(fin, letters);
    sort(letters.begin(), letters.end());

    root = new TrieNode();
    while (true) {
        getline(fdict, word);
        if (word[0] == '.') break;
        auto cur = root;
        for (auto c : word) {
            if (!cur->ch[c - 'a']) cur->ch[c - 'a'] = new TrieNode();
            cur = cur->ch[c - 'a'];
        }
        cur->word = true;
    }

    best_val = 0, target = -1;
    string curword;
    vector<string> buf;
    dfs(root, letters, 0, 0);
    fout << best_val << endl;
    target = best_val;
    dfs_second(root, letters, 0, 0, buf, curword);
    sort(results.begin(), results.end(), [](vector<string>& a, vector<string>& b){return a[0] < b[0] || a[0] == b[0] && a[1] < b[1];});
    for (auto& v : results) {
        if (v.size() == 1) fout << v[0] << endl;
        else fout << v[0] << " " << v[1] << endl;
    }

    return 0;
}