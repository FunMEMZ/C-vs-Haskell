/*
 * 任务：函数及其递归；文件和控制台 IO；跳转。
 * 编译：gcc -std=c11 -O2 -Wall -Wextra 04_04_functions_recursion_io_jump.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>


/* ---------- 函数及其递归 ---------- */

static unsigned long long factorial(int n) {
    return n <= 1 ? 1ULL : (unsigned long long)n * factorial(n - 1);
}

static int ackermann(int m, int n) {
    if (m == 0) return n + 1;
    if (n == 0) return ackermann(m - 1, 1);
    return ackermann(m - 1, ackermann(m, n - 1));
}

/* 互递归：is_even 与 is_odd 互相调用。 */
static int is_odd(int n);
static int is_even(int n) { return n == 0 ? 1 : is_odd(n - 1); }
static int is_odd(int n)  { return n == 0 ? 0 : is_even(n - 1); }


/* ---------- 文件和控制台 IO ---------- */

static void io_demo(void) {
    const char *path = "04_04_functions_recursion_io_jump_demo.txt";
    FILE *fp = fopen(path, "w");
    if (!fp) { perror("fopen(w)"); return; }
    fprintf(fp, "line one\nline two\n");
    fclose(fp);

    fp = fopen(path, "r");
    if (!fp) { perror("fopen(r)"); return; }
    char buf[100];
    printf("file content: ");
    while (fgets(buf, sizeof buf, fp)) printf("[%s]", buf);
    fclose(fp);

    printf("console input (one line): ");
    fflush(stdout);
    if (fgets(buf, sizeof buf, stdin))
        printf("you typed: %s", buf);
    else
        printf("(EOF)\n");
}


/* ---------- 跳转：goto 与 setjmp/longjmp ---------- */

static jmp_buf jump_env;

static void may_fail(int x) {
    if (x < 0) longjmp(jump_env, 1);   /* 非局部跳转 */
    printf("may_fail: x=%d\n", x);
}

static void jump_demo(void) {
    int i = 0;
    printf("goto loop: ");
again:
    printf("%d ", i);
    ++i;
    if (i < 5) goto again;
    printf("\n");

    if (setjmp(jump_env) == 0) {
        printf("before longjmp\n");
        may_fail(-1);
        printf("never printed\n");
    } else {
        printf("after longjmp: caught in calling function\n");
    }
}


int main(void) {
    printf("factorial(10)=%llu\n", factorial(10));
    printf("ackermann(2,3)=%d\n", ackermann(2, 3));
    printf("is_even(10)=%d, is_odd(10)=%d\n", is_even(10), is_odd(10));
    printf("\n");
    io_demo();
    printf("\n");
    jump_demo();
    return 0;
}