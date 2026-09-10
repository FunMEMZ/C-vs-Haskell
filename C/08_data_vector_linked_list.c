/*
 * 任务：数据结构 -- vector（动态数组）和链表。
 * 编译：gcc -std=c11 -O2 -Wall -Wextra 08_08_data_vector_linked_list.c
 */

#include <stdio.h>
#include <stdlib.h>


/* ---------- vector：动态数组 ---------- */

typedef struct {
    int *data;
    int size;
    int cap;
} Vector;

static int vector_init(Vector *v, int cap) {
    v->data = malloc((size_t)(cap > 0 ? cap : 1) * sizeof *v->data);
    v->size = 0;
    v->cap = cap > 0 ? cap : 1;
    return v->data != NULL;
}

static int vector_reserve(Vector *v, int new_cap) {
    if (new_cap <= v->cap) return 1;
    int *p = realloc(v->data, (size_t)new_cap * sizeof *v->data);
    if (!p) return 0;
    v->data = p;
    v->cap = new_cap;
    return 1;
}

static int vector_push(Vector *v, int x) {
    if (v->size == v->cap && !vector_reserve(v, v->cap * 2)) return 0;
    v->data[v->size++] = x;
    return 1;
}

static int vector_get(const Vector *v, int i) { return v->data[i]; }
static void vector_set(Vector *v, int i, int x) { v->data[i] = x; }
static void vector_free(Vector *v) { free(v->data); v->data = NULL; v->size = v->cap = 0; }

static void vector_demo(void) {
    Vector v;
    vector_init(&v, 2);
    for (int i = 1; i <= 6; ++i) vector_push(&v, i * 10);
    vector_set(&v, 2, 99);

    printf("vector:");
    for (int i = 0; i < v.size; ++i) printf(" %d", vector_get(&v, i));
    printf("  (size=%d, cap=%d)\n", v.size, v.cap);
    vector_free(&v);
}


/* ---------- 链表：单链表 ---------- */

typedef struct Node {
    int val;
    struct Node *next;
} Node;

static Node *list_push_front(Node *head, int x) {
    Node *p = malloc(sizeof *p);
    if (!p) { perror("malloc"); exit(1); }
    p->val = x;
    p->next = head;
    return p;
}

static Node *list_reverse(Node *head) {
    Node *prev = NULL;
    while (head) {
        Node *next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}

static void list_print(const Node *head) {
    for (const Node *p = head; p; p = p->next) printf(" %d", p->val);
}

static void list_free(Node *head) {
    while (head) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

static void list_demo(void) {
    Node *head = NULL;
    for (int i = 1; i <= 5; ++i) head = list_push_front(head, i * 2);
    printf("list (newest first):");
    list_print(head);
    printf("\n");

    head = list_reverse(head);
    printf("list after reverse:");
    list_print(head);
    printf("\n");
    list_free(head);
}


int main(void) {
    vector_demo();
    printf("\n");
    list_demo();
    return 0;
}