/*
 * 任务：数据结构 -- 栈及基本操作。
 * 编译：gcc -std=c11 -O2 -Wall -Wextra 06_06_data_stack.c
 */

#include <stdio.h>
#include <stdbool.h>

#define STACK_CAP 100


/* ---------- 栈定义与基本操作 ---------- */

typedef struct {
    int data[STACK_CAP];
    int top;                 /* 栈顶下标，空栈为 -1 */
} Stack;

static void stack_init(Stack *s) { s->top = -1; }
static bool stack_empty(const Stack *s) { return s->top < 0; }
static bool stack_full(const Stack *s) { return s->top >= STACK_CAP - 1; }

static bool stack_push(Stack *s, int x) {
    if (stack_full(s)) return false;
    s->data[++s->top] = x;
    return true;
}

static bool stack_pop(Stack *s, int *out) {
    if (stack_empty(s)) return false;
    *out = s->data[s->top--];
    return true;
}

static bool stack_peek(const Stack *s, int *out) {
    if (stack_empty(s)) return false;
    *out = s->data[s->top];
    return true;
}


int main(void) {
    Stack s;
    stack_init(&s);

    for (int i = 1; i <= 5; ++i) stack_push(&s, i * 10);
    printf("after pushes, top element = ");
    int x;
    if (stack_peek(&s, &x)) printf("%d\n", x);

    printf("pop order:");
    while (stack_pop(&s, &x)) printf(" %d", x);
    printf("\n");

    printf("empty after pops: %s\n", stack_empty(&s) ? "true" : "false");
    return 0;
}