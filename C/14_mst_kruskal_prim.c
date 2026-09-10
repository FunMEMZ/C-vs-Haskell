/*
 * 任务：最小生成树（Kruskal 与 Prim）。
 * 输入格式：n m，接下来 m 行 u v w（无向边）。
 * 输出：Kruskal 和 Prim 各自得到的最小生成树总权值；不连通输出 -1。
 *
 * 编译：gcc -std=c11 -O2 -Wall -Wextra 14_14_mst_kruskal_prim.c
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005
#define MAXM 20005
#define INF  (1LL << 60)

typedef struct { int u, v, w; } Edge;
static Edge edges[MAXM];

static int cmp_edge(const void *a, const void *b) {
    const Edge *x = a, *y = b;
    return (x->w > y->w) - (x->w < y->w);
}


/* ---------- Kruskal + 并查集 ---------- */

static int parent[MAXN], rnk[MAXN];

static void dsu_init(int n) {
    for (int i = 1; i <= n; ++i) { parent[i] = i; rnk[i] = 0; }
}

static int dsu_find(int x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

static int dsu_union(int a, int b) {
    a = dsu_find(a); b = dsu_find(b);
    if (a == b) return 0;
    if (rnk[a] < rnk[b]) { int t = a; a = b; b = t; }
    parent[b] = a;
    if (rnk[a] == rnk[b]) ++rnk[a];
    return 1;
}

static long long kruskal(int n, int m) {
    qsort(edges, (size_t)m, sizeof edges[0], cmp_edge);
    dsu_init(n);

    long long total = 0;
    int used = 0;
    for (int i = 0; i < m && used < n - 1; ++i) {
        if (dsu_union(edges[i].u, edges[i].v)) {
            total += edges[i].w;
            ++used;
        }
    }
    return used == n - 1 ? total : -1;
}


/* ---------- Prim + 邻接矩阵 ---------- */

static long long graph[MAXN][MAXN];
static long long dist_prim[MAXN];
static int used_prim[MAXN];

static long long prim(int n) {
    for (int i = 1; i <= n; ++i) {
        dist_prim[i] = INF;
        used_prim[i] = 0;
    }
    dist_prim[1] = 0;

    long long total = 0;
    for (int step = 0; step < n; ++step) {
        int u = 0;
        for (int v = 1; v <= n; ++v)
            if (!used_prim[v] && (u == 0 || dist_prim[v] < dist_prim[u])) u = v;
        if (u == 0 || dist_prim[u] == INF) return -1;

        used_prim[u] = 1;
        total += dist_prim[u];
        for (int v = 1; v <= n; ++v)
            if (!used_prim[v] && graph[u][v] < dist_prim[v])
                dist_prim[v] = graph[u][v];
    }
    return total;
}


int main(void) {
    int n, m;
    if (scanf("%d%d", &n, &m) != 2) return 0;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            graph[i][j] = (i == j ? 0 : INF);

    for (int i = 0; i < m; ++i) {
        scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w);
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        if (w < graph[u][v]) { graph[u][v] = w; graph[v][u] = w; }
    }

    printf("Kruskal MST weight = %lld\n", kruskal(n, m));
    printf("\n");
    printf("Prim MST weight = %lld\n", prim(n));
    return 0;
}