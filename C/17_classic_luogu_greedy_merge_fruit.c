/*
 * 任务：贪心（洛谷 P1090 合并果子）。
 * 输入格式：第一行 n，第二行 n 个正整数。
 * 输出：合并成一堆的最小体力消耗。
 *
 * 样例输入：
 *   3
 *   1 2 9
 * 样例输出：15
 *
 * 编译：gcc -std=c11 -O2 -Wall -Wextra 17_17_classic_luogu_greedy_merge_fruit.c
 */

#include <stdio.h>

#define HEAP_CAP 10005

static int heap[HEAP_CAP];
static int hn;

static void heap_swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }

static void heap_push(int x) {
    int i = hn++;
    heap[i] = x;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p] <= heap[i]) break;
        heap_swap(&heap[p], &heap[i]);
        i = p;
    }
}

static int heap_pop(void) {
    int top = heap[0];
    heap[0] = heap[--hn];
    int i = 0;
    for (;;) {
        int l = 2 * i + 1, r = 2 * i + 2, m = i;
        if (l < hn && heap[l] < heap[m]) m = l;
        if (r < hn && heap[r] < heap[m]) m = r;
        if (m == i) break;
        heap_swap(&heap[i], &heap[m]);
        i = m;
    }
    return top;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        heap_push(x);
    }

    long long total = 0;
    while (hn > 1) {
        int a = heap_pop();
        int b = heap_pop();
        int sum = a + b;
        total += sum;
        heap_push(sum);
    }
    printf("%lld\n", total);
    return 0;
}