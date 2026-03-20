#include<bits/stdc++.h>
using namespace std;

vector<int> w;
vector<vector<int>> tree;
vector<bool> vis;
int f[1001][1001]; 
// f[u][j] 表示以 u 为根的子树，在父节点给出的限制额度为 j 时，能提供的最大产出

void dfs(int u) {
    int cap = w[u];       // 当前设备的加工上限（加工中心能力）
    bool is_leaf = true;  // 标记是否为叶子节点（即原始产出设备）

    // 1. 递归深入：先处理所有子节点
    for (int v : tree[u]) {
        if (!vis[v]) {    // 防止走回头路（回到父节点）
            vis[v] = true;
            is_leaf = false;
            dfs(v);       // 递归处理子节点 v，完成后 f[v] 表已填好

            // 2. 核心：树形背包合并
            // 将子节点 v 看作一个“物品组”，尝试分配不同的额度 k 给它
            for (int j = cap; j >= 0; j--) {        // j: 父节点 u 当前总共能控制的额度
                for (int k = 0; k <= j; k++) {      // k: 尝试分给子节点 v 的额度
                    // 状态转移：保持原样 vs (给 v 分配 k 额度 + 剩下的给之前的子节点)
                    f[u][j] = max(f[u][j], f[u][j - k] + f[v][k]);
                }
            }
        }
    }

    // 3. 结果修正：根据节点类型决定最终产出方案
    if (is_leaf) {
        // 如果是叶子节点：它本身就是产出源
        for (int i = 0; i <= 1000; i++) 
            // 只有当配额 i 大于等于其产出能力 w[u] 时，才能产出 w[u]
            f[u][i] = (i >= w[u] ? w[u] : 0);
    } else {
        // 如果是中间加工中心：对子节点的汇总结果进行“截断”
        for (int i = 0; i <= 1000; i++) 
            // 产出受到三方制约：父节点配额 i、子节点汇总值 f[u][i]、自身加工能力 cap
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