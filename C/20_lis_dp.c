/*
 * 最长上升子序列 -- 方案 2：O(n^2) 动态规划。
 * 输入：n，然后 n 个整数。
 * 输出：最长严格上升子序列长度。
 * 编译：gcc -std=c11 -O2 -Wall -Wextra 20_20_lis_dp.c
 */

#include <stdio.h>

#define MAXN 1005

static int a[MAXN], dp[MAXN];

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);

    int best = 0;
    for (int i = 0; i < n; ++i) {
        dp[i] = 1;
        for (int j = 0; j < i; ++j)
            if (a[j] < a[i] && dp[j] + 1 > dp[i])
                dp[i] = dp[j] + 1;
        if (dp[i] > best) best = dp[i];
    }

    printf("%d\n", best);
    return 0;
}