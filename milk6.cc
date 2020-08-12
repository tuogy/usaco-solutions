/*
USER: guobich1
TASK: milk6
LANG: C++
*/

#ifndef __clang__
    #include <bits/stdc++.h>
#endif
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;
using ll = long long;

const ll BigIntBase = 1LL << 32;
class BigInt {
vector<ll> digits;
public:
    BigInt(ll n) {
        while (n) digits.push_back(n % BigIntBase), n /= BigIntBase;
        if (digits.empty()) digits.push_back(0);
    }

    bool isPositive() {
        return digits.size() > 1 || digits[0] != 0;
    }

    BigInt& operator+=(const BigInt& val) {
        ll carry = 0;
        int max_size = max(digits.size(), val.digits.size());
        int digit_size = digits.size();
        for (int i = 0; i < max_size; i++) {
            ll left = i < digit_size ? digits[i] : 0;
            ll right = i < val.digits.size() ? val.digits[i] : 0;
            ll sum = left + right + carry;
            carry = sum / BigIntBase;
            sum %= BigIntBase;
            if (i < digit_size) digits[i] = sum;
            else digits.push_back(sum);
        }
        while (carry > 0) {
            digits.push_back(carry % BigIntBase);
            carry /= BigIntBase;
        }
        return *this;
    }

    BigInt& operator-=(const BigInt& val) {
        ll borrow = 0;
        for (int i = 0; i < digits.size(); i++) {
            ll left = digits[i];
            ll right = i < val.digits.size() ? val.digits[i] : 0;
            ll diff = 0; 
            if (left < right + borrow) diff = BigIntBase - right + left - borrow, borrow = 1;
            else diff = left - right - borrow, borrow = 0;
            digits[i] = diff;
        }
        while (digits.size() > 1 && digits.back() == 0) digits.pop_back();
        return *this;
    }

    BigInt& operator*=(ll val) {
        ll carry = 0;
        for (int i = 0; i < digits.size(); i++) {
            ll left = digits[i];
            ll prod = left * val + carry;
            carry = prod / BigIntBase;
            digits[i] = prod % BigIntBase;
        }
        while (carry > 0) {
            digits.push_back(carry % BigIntBase);
            carry /= BigIntBase;
        }
        return *this;
    }

    bool operator<(const BigInt& val) {
        if (digits.size() < val.digits.size()) return true;
        else if (digits.size() > val.digits.size()) return false;
        for (int i = (int)digits.size() - 1; i >= 0; i--) {
            if (digits[i] < val.digits[i]) return true;
            else if (digits[i] > val.digits[i]) return false;
        }
        return false;
    }
};

int V, E, s, t;
vector<int> adj[32];
vector<int> cap[32][32];
vector<BigInt> rG[32][32];
vector<int> edge_id[32][32];
bool vis[32];
int parent[32];
int parent_edge[32];

bool bfs() {
    memset(vis, 0, V * sizeof(bool));
    queue<int> q;
    q.push(s), vis[s] = true;
    while (!q.empty() && !vis[t]) {
        int u = q.front(); q.pop();
        for (auto v : adj[u]) {
            if (vis[v]) continue;
            for (int i = 0; i < rG[u][v].size(); i++) {
                if (rG[u][v][i].isPositive()) {
                    q.push(v), vis[v] = true;
                    parent[v] = u, parent_edge[v] = i;
                    break;
                }
            }
        }
    }
    return vis[t];
}

int main() {
    ifstream fin("milk6.in");
    ofstream fout("milk6.out");
    
    fin >> V >> E;
    s = 0, t = V - 1;
    for (int i = 0; i < V; i++) {
        adj[i].clear();
        for (int j = 0; j < V; j++) {
            cap[i][j].clear();
            rG[i][j].clear();
            edge_id[i][j].clear();
        }
    }
    vector<BigInt> power_of_two, w_edge;
    power_of_two.push_back(1);
    for (int i = 1; i <= E + 10; i++) {
        power_of_two.push_back(power_of_two[i - 1]);
        power_of_two[i] *= 2;
    }
    for (int i = 0; i < E; i++) {
        w_edge.push_back(power_of_two[E - 1]);
        w_edge[i] -= power_of_two[E - 1 - i];
    }
    BigInt lambda = power_of_two[E + 10];

    vector<vector<bool>> adj_mat(V, vector<bool>(V, false));
    for (int i = 0; i < E; i++) {
        int u, v, w;
        fin >> u >> v >> w;
        u--, v--;
        adj_mat[u][v] = adj_mat[v][u] = true;
        cap[u][v].push_back(w), cap[v][u].push_back(0);
        BigInt w_rG = lambda;
        w_rG *= 2LL * E * w + 1;
        w_rG += w_edge[i];
        rG[u][v].push_back(w_rG), rG[v][u].push_back(0);
        edge_id[u][v].push_back(i), edge_id[v][u].push_back(i);
    }

    for (int i = 0; i < V; i++) {
        for (int j = i; j < V; j++) {
            if (adj_mat[i][j]) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }

    while (bfs()) {
        BigInt f = rG[parent[t]][t][parent_edge[t]];
        for (int v = parent[t]; v != s; v = parent[v]) {
            if (rG[parent[v]][v][parent_edge[v]] < f)
                f = rG[parent[v]][v][parent_edge[v]];
        }
        for (int v = t; v != s; v = parent[v])
            rG[parent[v]][v][parent_edge[v]] -= f, rG[v][parent[v]][parent_edge[v]] += f;
    }

    vector<int> ret;
    int min_cut = 0;
    for (int u = 0; u < V; u++) {
        if (!vis[u]) continue;
        for (int v = 0; v < V; v++) {
            if (vis[v]) continue;
            for (int i = 0; i < rG[u][v].size(); i++) {
                if (cap[u][v][i] > 0 && !rG[u][v][i].isPositive())
                    min_cut += cap[u][v][i], ret.push_back(edge_id[u][v][i] + 1);
            }
        }
    }
    
    fout << min_cut << " " << ret.size() << endl;
    sort(ret.begin(), ret.end());
    for (int i = 0; i < ret.size(); i++) fout << ret[i] << endl;

    return 0;
}