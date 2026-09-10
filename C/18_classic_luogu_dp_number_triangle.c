/*
 * 任务：简单 DP（洛谷 P1216 数字三角形）。
 * 输入格式：第一行 n，接下来 n 行每行 1..i 个整数。
 * 输出：从顶部到底部的最大路径和。
 *
 * 样例输入：
 *   5
 *   7
 *   3 8
 *   8 1 0
 *   2 7 4 4
 *   4 5 2 6 5
 * 样例输出：30
 *
 * 编译：gcc -std=c11 -O2 -Wall -Wextra 18_18_classic_luogu_dp_number_triangle.c
 */

#include <stdio.h>

#define MAXN 1005

static int a[MAXN][MAXN];

static int max_int(int x, int y) { return x > y ? x : y; }

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= i; ++j)
            scanf("%d", &a[i][j]);

    for (int i = n - 1; i >= 1; --i)
        for (int j = 1; j <= i; ++j)
            a[i][j] += max_int(a[i + 1][j], a[i + 1][j + 1]);

    printf("%d\n", a[1][1]);
    return 0;
}