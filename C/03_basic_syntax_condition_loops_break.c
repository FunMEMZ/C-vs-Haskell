/*
 * 任务：基础语法 —— 判断；循环及跳过（continue）和跳出（break）机制。
 * 编译：gcc -std=c11 -O2 -Wall -Wextra 03_03_basic_syntax_condition_loops_break.c
 */

#include <stdio.h>
#include <stdbool.h>


/* ---------- 判断 ---------- */

static const char *classify(int n) {
    if (n < 0)       return "negative";
    else if (n == 0) return "zero";
    else             return "positive";
}

static void condition_demo(void) {
    printf("classify(-3)=%s, classify(0)=%s, classify(8)=%s\n",
           classify(-3), classify(0), classify(8));

    int day = 3;
    switch (day) {
        case 1: case 2: case 3: case 4: case 5:
            printf("day %d: workday\n", day); break;
        case 6: case 7:
            printf("day %d: weekend\n", day); break;
        default:
            printf("day %d: invalid\n", day); break;
    }
}


/* ---------- 循环、跳过、跳出 ---------- */

static void loop_demo(void) {
    printf("for with continue/break: ");
    for (int i = 1; i <= 10; ++i) {
        if (i % 2 == 0) continue;       /* 跳过偶数 */
        if (i > 7) break;               /* 跳出整个循环 */
        printf("%d ", i);
    }
    printf("\n");

    int i = 0, sum = 0;
    while (i < 100) {
        ++i;
        if (i % 3 != 0) continue;       /* 只累加 3 的倍数 */
        sum += i;
        if (sum > 30) break;            /* 提前结束 while */
    }
    printf("while sum of multiples of 3 until >30: %d\n", sum);

    int j = 0;
    do {
        ++j;
    } while (j < 5);
    printf("do-while final j = %d\n", j);
}


int main(void) {
    condition_demo();
    printf("\n");
    loop_demo();
    return 0;
}