/*
 * 任务：数据结构 -- 队列及基本操作（循环队列）。
 * 编译：gcc -std=c11 -O2 -Wall -Wextra 07_07_data_queue.c
 */

#include <stdio.h>
#include <stdbool.h>

#define QUEUE_CAP 8


/* ---------- 循环队列定义与基本操作 ---------- */

typedef struct {
    int data[QUEUE_CAP];
    int head;    /* 队头下标 */
    int tail;    /* 下一个入队位置 */
    int size;
} Queue;

static void queue_init(Queue *q) { q->head = q->tail = q->size = 0; }
static bool queue_empty(const Queue *q) { return q->size == 0; }
static bool queue_full(const Queue *q)  { return q->size == QUEUE_CAP; }

static bool enqueue(Queue *q, int x) {
    if (queue_full(q)) return false;
    q->data[q->tail] = x;
    q->tail = (q->tail + 1) % QUEUE_CAP;
    ++q->size;
    return true;
}

static bool dequeue(Queue *q, int *out) {
    if (queue_empty(q)) return false;
    *out = q->data[q->head];
    q->head = (q->head + 1) % QUEUE_CAP;
    --q->size;
    return true;
}

static bool queue_peek(const Queue *q, int *out) {
    if (queue_empty(q)) return false;
    *out = q->data[q->head];
    return true;
}


int main(void) {
    Queue q;
    queue_init(&q);

    for (int i = 1; i <= 5; ++i) enqueue(&q, i * 10);
    int x;
    printf("front = %d\n", queue_peek(&q, &x) ? x : -1);

    printf("dequeue order:");
    while (dequeue(&q, &x)) printf(" %d", x);
    printf("\n");

    printf("empty after dequeues: %s\n", queue_empty(&q) ? "true" : "false");
    return 0;
}