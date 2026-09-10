/*
 * 任务：Fibonacci —— 递归、列表/数组记忆化、通项公式。
 * 编译：gcc -std=c11 -O2 -Wall -Wextra 19_19_fibonacci_recursion_memo_formula.c -lm
 */

#include <stdio.h>
#include <math.h>

#define MEMO_MAX 100


/* ---------- 朴素递归 ---------- */

static unsigned long long fib_rec(int n) {
    if (n < 2) return (unsigned long long)n;
    return fib_rec(n - 1) + fib_rec(n - 2);
}


/* ---------- 数组记忆化 ---------- */

static unsigned long long memo[MEMO_MAX];

static unsigned long long fib_memo(int n) {
    if (n < 2) return (unsigned long long)n;
    if (memo[n] != 0) return memo[n];
    return memo[n] = fib_memo(n - 1) + fib_memo(n - 2);
}


/* ---------- 通项公式（Binet，浮点近似） ---------- */

static unsigned long long fib_formula(int n) {
    const double sqrt5 = sqrt(5.0);
    const double phi = (1.0 + sqrt5) / 2.0;
    const double psi = (1.0 - sqrt5) / 2.0;
    return (unsigned long long)llround((pow(phi, n) - pow(psi, n)) / sqrt5);
}


int main(void) {
    for (int n = 0; n < MEMO_MAX; ++n) memo[n] = 0;

    printf("recursive: ");
    for (int n = 0; n <= 10; ++n) printf("%llu ", fib_rec(n));
    printf("\n");

    printf("memoized:  ");
    for (int n = 0; n <= 20; ++n) printf("%llu ", fib_memo(n));
    printf("\n");

    printf("formula:   ");
    for (int n = 0; n <= 20; ++n) printf("%llu ", fib_formula(n));
    printf("\n");
    return 0;
}