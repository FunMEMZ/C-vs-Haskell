/*
 * 任务：BFS（洛谷 P1443 马的遍历）。
 * 输入格式：n m x y
 * 输出：n 行，每行 m 个数，表示马到每个格子的最少步数；不可达为 -1。
 *
 * 样例输入：3 3 1 1
 * 样例输出：
 *      0    3    2
 *      3   -1    1
 *      2    1    4
 *
 * 编译：gcc -std=c11 -O2 -Wall -Wextra 16_16_classic_luogu_bfs_horse.c
 */

#include <stdio.h>
#include <string.h>

#define MAXN 405

static int n, m, sx, sy;
static int dist[MAXN][MAXN];
static int qx[MAXN * MAXN], qy[MAXN * MAXN];
static const int hx[8] = {1, 1, -1, -1, 2, 2, -2, -2};
static const int hy[8] = {2, -2, 2, -2, 1, -1, 1, -1};

int main(void) {
    if (scanf("%d%d%d%d", &n, &m, &sx, &sy) != 4) return 0;
    memset(dist, -1, sizeof dist);

    int head = 0, tail = 0;
    qx[tail] = sx; qy[tail] = sy; ++tail;
    dist[sx][sy] = 0;

    while (head < tail) {
        int x = qx[head], y = qy[head];
        ++head;
        for (int k = 0; k < 8; ++k) {
            int nx = x + hx[k], ny = y + hy[k];
            if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
            if (dist[nx][ny] != -1) continue;
            dist[nx][ny] = dist[x][y] + 1;
            qx[tail] = nx; qy[tail] = ny; ++tail;
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) printf("%5d", dist[i][j]);
        printf("\n");
    }
    return 0;
}