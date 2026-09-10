/*
 * 最长上升子序列 -- 方案 5：树状数组（Fenwick）优化 DP，O(n log n)。
 * 输入：n，然后 n 个整数。
 * 输出：最长严格上升子序列长度。
 * 编译：gcc -std=c11 -O2 -Wall -Wextra 20_20_lis_fenwick.c
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005

static int a[MAXN], vals[MAXN], bit[MAXN];

static int cmp_int(const void *x, const void *y) {
    int a = *(const int *)x, b = *(const int *)y;
    return (a > b) - (a < b);
}

static int lower_bound(int m, int x) {
    int l = 0, r = m;
    while (l < r) {
        int mid = (l + r) / 2;
        if (vals[mid] >= x) r = mid;
        else                l = mid + 1;
    }
    return l;
}

static int bit_query(int i) {
    int res = 0;
    for (; i > 0; i -= i & -i)
        if (bit[i] > res) res = bit[i];
    return res;
}

static void bit_update(int i, int v, int m) {
    for (; i <= m; i += i & -i)
        if (v > bit[i]) bit[i] = v;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
        vals[i] = a[i];
    }

    qsort(vals, (size_t)n, sizeof vals[0], cmp_int);
    int m = 0;
    for (int i = 0; i < n; ++i)
        if (i == 0 || vals[i] != vals[i - 1]) vals[m++] = vals[i];

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int rank = lower_bound(m, a[i]) + 1;
        int best = bit_query(rank - 1) + 1;
        bit_update(rank, best, m);
        if (best > ans) ans = best;
    }

    printf("%d\n", ans);
    return 0;
}