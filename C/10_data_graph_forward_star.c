/*
 * 任务：有向图、无向图（强制使用链式前向星）。
 * 编译：gcc -std=c11 -O2 -Wall -Wextra 10_10_data_graph_forward_star.c
 */

#include <stdio.h>

#define MAXN 1005
#define MAXM 20005


/* ---------- 链式前向星 ---------- */

typedef struct {
    int n;
    int head[MAXN];        /* head[u] = 第一条边的编号，-1 表示无边 */
    int to[MAXM];
    int nxt[MAXM];
    int wt[MAXM];
    int ecnt;
} ForwardStar;

static void fs_init(ForwardStar *g, int n) {
    g->n = n;
    g->ecnt = 0;
    for (int i = 0; i <= n; ++i) g->head[i] = -1;
}

static void fs_add_directed(ForwardStar *g, int u, int v, int w) {
    ++g->ecnt;
    g->to[g->ecnt] = v;
    g->wt[g->ecnt] = w;
    g->nxt[g->ecnt] = g->head[u];
    g->head[u] = g->ecnt;
}

static void fs_add_undirected(ForwardStar *g, int u, int v, int w) {
    fs_add_directed(g, u, v, w);
    fs_add_directed(g, v, u, w);
}

static void fs_print(const ForwardStar *g) {
    for (int u = 1; u <= g->n; ++u) {
        printf("%d:", u);
        for (int e = g->head[u]; e != -1; e = g->nxt[e])
            printf(" (to=%d,w=%d)", g->to[e], g->wt[e]);
        printf("\n");
    }
}


int main(void) {
    ForwardStar dg;
    fs_init(&dg, 4);
    fs_add_directed(&dg, 1, 2, 3);
    fs_add_directed(&dg, 1, 3, 4);
    fs_add_directed(&dg, 2, 4, 5);
    fs_add_directed(&dg, 3, 4, 6);
    printf("directed graph:\n");
    fs_print(&dg);

    printf("\n");
    ForwardStar ug;
    fs_init(&ug, 4);
    fs_add_undirected(&ug, 1, 2, 3);
    fs_add_undirected(&ug, 2, 3, 4);
    fs_add_undirected(&ug, 3, 4, 5);
    printf("undirected graph:\n");
    fs_print(&ug);
    return 0;
}