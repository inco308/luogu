#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

struct Point { int x, y; };

int R, C, N;
char g[55][55];
bool vis[1005][55][55]; // 核心：记录第 i 步时，(x,y) 是否已经作为起始点考虑过

int main() {
    cin >> R >> C;
    int startX, startY;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> g[i][j];
            if (g[i][j] == '*') {
                startX = i; startY = j;
                g[i][j] = '.'; // 起点标记改为平地，方便后续行驶
            }
        }
    }

    cin >> N;
    queue<Point> q;
    q.push({startX, startY});

    for (int step = 1; step <= N; step++) {
        string dir;
        cin >> dir;
        int dx = 0, dy = 0;
        if (dir == "NORTH") dx = -1;
        else if (dir == "SOUTH") dx = 1;
        else if (dir == "WEST") dy = -1;
        else if (dir == "EAST") dy = 1;

        int sz = q.size();
        // 用一个临时的 vis 标记这一步处理出的终点，防止这一步内重复入队
        // 或者直接用三维 vis[step][x][y]
        while (sz--) {
            Point curr = q.front();
            q.pop();

            int nx = curr.x + dx;
            int ny = curr.y + dy;

            // 沿着方向一直走，直到撞墙或出界
            while (nx >= 0 && nx < R && ny >= 0 && ny < C && g[nx][ny] == '.') {
                if (!vis[step][nx][ny]) {
                    vis[step][nx][ny] = true;
                    q.push({nx, ny});
                }
                nx += dx;
                ny += dy;
            }
        }
    }

    // 最后队列里剩下的就是所有可能的终点
    while (!q.empty()) {
        Point p = q.front();
        q.pop();
        g[p.x][p.y] = '*';
    }

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) cout << g[i][j];
        cout << endl;
    }

    return 0;
}