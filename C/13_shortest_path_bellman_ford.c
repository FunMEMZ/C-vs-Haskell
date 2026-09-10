/*
 * 任务：Bellman-Ford 最短路。
 * 输入格式：n m s，接下来 m 行 u v w（有向边）。
 * 输出：最短距离；若存在从 s 可达的负环则输出 NEGATIVE CYCLE。
 *
 * 编译：gcc -std=c11 -O2 -Wall -Wextra 13_13_shortest_path_bellman_ford.c
 */

#include <stdio.h>
#include <stdbool.h>

#define MAXN 1005
#define MAXM 20005
#define INF  (1LL << 60)

static int eu[MAXM], ev[MAXM], ew[MAXM];

int main(void) {
    int n, m, s;
    if (scanf("%d%d%d", &n, &m, &s) != 3) return 0;
    for (int i = 0; i < m; ++i)
        scanf("%d%d%d", &eu[i], &ev[i], &ew[i]);

    long long dist[MAXN];
    for (int i = 1; i <= n; ++i) dist[i] = INF;
    dist[s] = 0;

    for (int step = 1; step <= n - 1; ++step) {
        bool changed = false;
        for (int i = 0; i < m; ++i) {
            int u = eu[i], v = ev[i], w = ew[i];
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                changed = true;
            }
        }
        if (!changed) break;
    }

    bool neg_cycle = false;
    for (int i = 0; i < m; ++i) {
        int u = eu[i], v = ev[i], w = ew[i];
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            neg_cycle = true;
            break;
        }
    }

    if (neg_cycle) {
        printf("NEGATIVE CYCLE\n");
    } else {
        for (int i = 1; i <= n; ++i) {
            if (dist[i] == INF) printf("INF");
            else printf("%lld", dist[i]);
            printf("%c", i == n ? '\n' : ' ');
        }
    }
    return 0;
}