/*
 * 任务：前向星下图的最短路（Dijkstra）。
 * 输入格式：n m s，接下来 m 行 u v w（有向边 u->v，边权非负）。
 * 输出：从 s 到 1..n 的最短距离；不可达输出 -1。
 *
 * 编译：gcc -std=c11 -O2 -Wall -Wextra 12_12_shortest_path_dijkstra_forward_star.c
 */

#include <stdio.h>
#include <stdbool.h>

#define MAXN 1005
#define MAXM 20005
#define INF  (1LL << 60)

static int head[MAXN], to[MAXM], nxt[MAXM], wt[MAXM], ecnt;

static void add_edge(int u, int v, int w) {
    ++ecnt;
    to[ecnt] = v;
    wt[ecnt] = w;
    nxt[ecnt] = head[u];
    head[u] = ecnt;
}

int main(void) {
    int n, m, s;
    if (scanf("%d%d%d", &n, &m, &s) != 3) return 0;

    for (int i = 1; i <= n; ++i) head[i] = 0;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(u, v, w);
    }

    long long dist[MAXN];
    bool vis[MAXN] = { false };
    for (int i = 1; i <= n; ++i) dist[i] = INF;
    dist[s] = 0;

    for (int step = 1; step <= n; ++step) {
        int u = 0;
        for (int v = 1; v <= n; ++v)
            if (!vis[v] && (u == 0 || dist[v] < dist[u])) u = v;

        if (u == 0 || dist[u] == INF) break;
        vis[u] = true;

        for (int e = head[u]; e != 0; e = nxt[e]) {
            int v = to[e];
            if (dist[u] + wt[e] < dist[v])
                dist[v] = dist[u] + wt[e];
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (dist[i] == INF) printf("-1");
        else printf("%lld", dist[i]);
        printf("%c", i == n ? '\n' : ' ');
    }
    return 0;
}