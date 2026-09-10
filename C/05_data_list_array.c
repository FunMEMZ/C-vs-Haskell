/*
 * 任务：数据结构 —— 列表/数组。
 * 编译：gcc -std=c11 -O2 -Wall -Wextra 05_05_data_list_array.c
 */

#include <stdio.h>
#include <stdlib.h>


/* ---------- 静态数组操作 ---------- */

static int array_sum(const int a[], int n) {
    int s = 0;
    for (int i = 0; i < n; ++i) s += a[i];
    return s;
}

static int array_max(const int a[], int n) {
    int m = a[0];
    for (int i = 1; i < n; ++i) if (a[i] > m) m = a[i];
    return m;
}

static void array_reverse(int a[], int n) {
    for (int i = 0, j = n - 1; i < j; ++i, --j) {
        int t = a[i]; a[i] = a[j]; a[j] = t;
    }
}

static void static_array_demo(void) {
    int a[] = {3, 1, 4, 1, 5, 9, 2, 6};
    int n = (int)(sizeof a / sizeof a[0]);
    printf("sum=%d, max=%d\n", array_sum(a, n), array_max(a, n));
    array_reverse(a, n);
    printf("reversed:");
    for (int i = 0; i < n; ++i) printf(" %d", a[i]);
    printf("\n");
}


/* ---------- 动态数组 ---------- */

static void dynamic_array_demo(void) {
    int cap = 2, n = 0;
    int *a = malloc((size_t)cap * sizeof *a);
    if (!a) { perror("malloc"); return; }

    for (int i = 1; i <= 6; ++i) {
        if (n == cap) {
            cap *= 2;
            int *p = realloc(a, (size_t)cap * sizeof *a);
            if (!p) { perror("realloc"); free(a); return; }
            a = p;
        }
        a[n++] = i * i;
    }

    printf("dynamic array:");
    for (int i = 0; i < n; ++i) printf(" %d", a[i]);
    printf("  (size=%d, capacity=%d)\n", n, cap);
    free(a);
}


/* ---------- 二维数组 ---------- */

static void matrix_demo(void) {
    int m[2][3] = {{1, 2, 3}, {4, 5, 6}};
    printf("2D array:\n");
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) printf("%3d", m[i][j]);
        printf("\n");
    }
}


int main(void) {
    static_array_demo();
    printf("\n");
    dynamic_array_demo();
    printf("\n");
    matrix_demo();
    return 0;
}