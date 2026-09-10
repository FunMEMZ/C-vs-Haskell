/*
 * 任务：DFS（洛谷 P1605 迷宫）。
 * 输入格式：
 *   第一行 n m t
 *   第二行 sx sy ex ey
 *   接下来 t 行，每行一个障碍坐标 x y
 * 输出：从起点到终点的路径数。
 *
 * 样例输入：
 *   2 2 1
 *   1 1 2 2
 *   1 2
 * 样例输出：1
 *
 * 编译：gcc -std=c11 -O2 -Wall -Wextra 15_15_classic_luogu_dfs_maze.c
 */

#include <stdio.h>
#include <stdbool.h>

static int n, m, t;
static int sx, sy, ex, ey, answer;
static bool bar[25][25];
static bool vis[25][25];
static const int dx[4] = {-1, 1, 0, 0};
static const int dy[4] = {0, 0, -1, 1};

static void dfs(int x, int y) {
    if (x == ex && y == ey) {
        ++answer;
        return;
    }
    for (int k = 0; k < 4; ++k) {
        int nx = x + dx[k], ny = y + dy[k];
        if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
        if (bar[nx][ny] || vis[nx][ny]) continue;
        vis[nx][ny] = true;
        dfs(nx, ny);
        vis[nx][ny] = false;
    }
}

int main(void) {
    if (scanf("%d%d%d", &n, &m, &t) != 3) return 0;
    scanf("%d%d%d%d", &sx, &sy, &ex, &ey);
    for (int i = 0; i < t; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        bar[x][y] = true;
    }
    vis[sx][sy] = true;
    dfs(sx, sy);
    printf("%d\n", answer);
    return 0;
}