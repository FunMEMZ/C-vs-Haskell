/*
 * 最长上升子序列 -- 方案 4：贪心 + 二分（O(n log n)）。
 * tails[k] 表示长度为 k+1 的上升子序列中，最小的末尾元素。
 * 输入：n，然后 n 个整数。
 * 输出：最长严格上升子序列长度。
 * 编译：gcc -std=c11 -O2 -Wall -Wextra 20_20_lis_binary_search.c
 */

#include <stdio.h>

#define MAXN 1005

static int a[MAXN], tails[MAXN];

static int lower_bound(int len, int x) {
    int l = 0, r = len;
    while (l < r) {
        int mid = (l + r) / 2;
        if (tails[mid] >= x) r = mid;
        else                 l = mid + 1;
    }
    return l;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);

    int len = 0;
    for (int i = 0; i < n; ++i) {
        int pos = lower_bound(len, a[i]);
        tails[pos] = a[i];
        if (pos == len) ++len;
    }

    printf("%d\n", len);
    return 0;
}