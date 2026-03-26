// #include <iostream>
// #include <vector>

// using namespace std;

// int n;
// int a[35][35];
// bool vis[35][35];
// int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};

// // 存储当前连通块的所有坐标
// struct Point { int x, y; };

// void solve_positive(int n) {
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             // 发现一个没跑过的 0
//             if (a[i][j] == 0 && !vis[i][j]) {
//                 vector<Point> q;     // 这个 vector 既是队列，也是最终的坐标集合
//                 q.push_back({i, j});
//                 vis[i][j] = true;
                
//                 bool is_enclosed = true; 
//                 int head = 0;
                
//                 while(head < q.size()){
//                     Point curr = q[head++]; // 取出当前处理的点
                    
//                     // 核心判断：只要这片区域有一个点在边界上，整片都不是“圈内”
//                     if (curr.x == 0 || curr.x == n-1 || curr.y == 0 || curr.y == n-1) {
//                         is_enclosed = false; 
//                     }
                    
//                     for (int k = 0; k < 4; k++) {
//                         int nx = curr.x + dx[k], ny = curr.y + dy[k];
//                         if (nx >= 0 && nx < n && ny >= 0 && ny < n && !vis[nx][ny] && a[nx][ny] == 0) {
//                             vis[nx][ny] = true;
//                             q.push_back({nx, ny}); // 扩充队列
//                         }
//                     }
//                 }
                
//                 // 如果搜完发现没碰过边界，说明这一坨 0 都在圈里
//                 if (is_enclosed) {
//                     for (Point p : q) a[p.x][p.y] = 2; // 直接遍历 q 进行染色
//                 }
//             }
//         }
//     }
// }

// int main(){
//     int n;
//     cin >> n;
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             cin >> a[i][j];
//         }
//     }
//     solve_positive(n);
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             cout << a[i][j] << (j == n - 1 ? '\n' : ' ');
//         }
//     }
//     return 0;
// }

#include <iostream>
#include <vector>

using namespace std;

const int N = 35;
int n;
int a[N][N];
bool vis[N][N]; // 标记哪些 0 是从边界可以到达的（即圈外的 0）
int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};

// DFS 的目的：标记所有“圈外”的 0
void dfs(int x, int y) {
    vis[x][y] = true; // 只要能搜到，说明它是圈外的

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        // 越界检查 + 未访问检查 + 必须是 0（碰到 1 就停下）
        if (nx >= 0 && nx < n && ny >= 0 && ny < n && !vis[nx][ny] && a[nx][ny] == 0) {
            dfs(nx, ny);
        }
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    // 第一步：从矩阵的四个边界出发，寻找所有的“圈外 0”
    for (int i = 0; i < n; i++) {
        if (a[i][0] == 0 && !vis[i][0]) dfs(i, 0);         // 左边界
        if (a[i][n - 1] == 0 && !vis[i][n - 1]) dfs(i, n - 1); // 右边界
        if (a[0][i] == 0 && !vis[0][i]) dfs(0, i);         // 上边界
        if (a[n - 1][i] == 0 && !vis[n - 1][i]) dfs(n - 1, i); // 下边界
    }

    // 第二步：输出结果
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] == 0 && !vis[i][j]) {
                // 如果是 0，且刚才 DFS 没搜到它，说明它在圈内！
                cout << 2 << " ";
            } else {
                cout << a[i][j] << " ";
            }
        }
        cout << endl;
    }

    return 0;
}