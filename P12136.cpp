#include<bits/stdc++.h>
using namespace std;

vector<int> w;
vector<vector<int>> tree;
vector<bool> vis;
int f[1001][1001];

void dfs(int u) {
    int cap = w[u];
    bool is_leaf = true;

    for (int v : tree[u]) {
        if (!vis[v]) {
            vis[v] = true;
            is_leaf = false;
            dfs(v);
            for (int j = cap; j >= 0; j--) {
                for (int k = 0; k <= j; k++) {
                    f[u][j] = max(f[u][j], f[u][j - k] + f[v][k]);
                }
            }
        }
    }

    if (is_leaf) {
        for (int i = 0; i <= 1000; i++) 
            f[u][i] = (i >= w[u] ? w[u] : 0);
    } else {
        for (int i = 0; i <= 1000; i++) 
            f[u][i] = min({i, f[u][i], cap});
    }
}

int main() {
    int n;
    cin >> n;
    w.resize(n + 1);
    for (int i = 1; i < n + 1; i++){
        cin >> w[i];
    }
    tree.assign(n + 1, vector<int>());
    for (int i = 0; i < n - 1; i++) {
        int u, v; 
        cin >> u >> v;
        tree[u].push_back(v); 
        tree[v].push_back(u);
    }
    vis.assign(n + 1, false);
    vis[1] = true;
    dfs(1);
    cout << f[1][w[1]] << endl;
    return 0;
}