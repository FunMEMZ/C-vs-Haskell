/*
 * 最长上升子序列 -- 方案 3：递归 + 记忆化（自顶向下）。
 * 输入：n，然后 n 个整数。
 * 输出：最长严格上升子序列长度。
 * 编译：gcc -std=c11 -O2 -Wall -Wextra 20_20_lis_memo.c
 */

#include <stdio.h>
#include <string.h>

#define MAXN 1005

static int n, a[MAXN], memo[MAXN];

static int dfs(int i) {
    if (memo[i] != -1) return memo[i];
    int best = 1;
    for (int j = i + 1; j < n; ++j)
        if (a[j] > a[i]) {
            int cand = 1 + dfs(j);
            if (cand > best) best = cand;
        }
    return memo[i] = best;
}

int main(void) {
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    memset(memo, -1, sizeof memo);

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int cand = dfs(i);
        if (cand > ans) ans = cand;
    }
    printf("%d\n", ans);
    return 0;
}