/*
 * 最长上升子序列 -- 方案 1：暴力枚举所有子集（适合 n <= 20）。
 * 输入：n，然后 n 个整数。
 * 输出：最长严格上升子序列长度。
 * 编译：gcc -std=c11 -O2 -Wall -Wextra 20_20_lis_bruteforce.c
 */

#include <stdio.h>
#include <limits.h>

#define MAXN 25

static int a[MAXN];

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);

    int best = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
        int len = 0, prev = INT_MIN, ok = 1;
        for (int i = 0; i < n; ++i) {
            if (!(mask & (1 << i))) continue;
            if (a[i] <= prev) { ok = 0; break; }
            prev = a[i];
            ++len;
        }
        if (ok && len > best) best = len;
    }

    printf("%d\n", best);
    return 0;
}