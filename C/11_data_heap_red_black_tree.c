/*
 * 任务：堆、红黑树。
 * 编译：gcc -std=c11 -O2 -Wall -Wextra 11_11_data_heap_red_black_tree.c
 */

#include <stdio.h>
#include <stdlib.h>


/* ---------- 二叉堆（数组实现，小根堆） ---------- */

#define HEAP_CAP 100

typedef struct {
    int data[HEAP_CAP];
    int n;
} MinHeap;

static void heap_init(MinHeap *h) { h->n = 0; }

static void heap_swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }

static int heap_push(MinHeap *h, int x) {
    if (h->n >= HEAP_CAP) return 0;
    int i = h->n++;
    h->data[i] = x;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h->data[p] <= h->data[i]) break;
        heap_swap(&h->data[p], &h->data[i]);
        i = p;
    }
    return 1;
}

static int heap_pop(MinHeap *h, int *out) {
    if (h->n == 0) return 0;
    *out = h->data[0];
    h->data[0] = h->data[--h->n];
    int i = 0;
    for (;;) {
        int l = 2 * i + 1, r = 2 * i + 2, m = i;
        if (l < h->n && h->data[l] < h->data[m]) m = l;
        if (r < h->n && h->data[r] < h->data[m]) m = r;
        if (m == i) break;
        heap_swap(&h->data[i], &h->data[m]);
        i = m;
    }
    return 1;
}

static void heap_demo(void) {
    MinHeap h;
    int x;
    int vals[] = {5, 3, 8, 1, 9, 2, 7};
    heap_init(&h);
    for (int i = 0; i < (int)(sizeof vals / sizeof vals[0]); ++i) heap_push(&h, vals[i]);

    printf("heap pop order:");
    while (heap_pop(&h, &x)) printf(" %d", x);
    printf("\n");
}


/* ---------- 红黑树（左倾红黑树 LLRB） ---------- */

typedef enum { RED, BLACK } Color;

typedef struct RBNode {
    int key;
    Color color;
    struct RBNode *left, *right;
} RBNode;

static int is_red(const RBNode *h) { return h != NULL && h->color == RED; }

static RBNode *rb_new(int key, Color color) {
    RBNode *p = malloc(sizeof *p);
    if (!p) { perror("malloc"); exit(1); }
    p->key = key;
    p->color = color;
    p->left = p->right = NULL;
    return p;
}

static RBNode *rotate_left(RBNode *h) {
    RBNode *x = h->right;
    h->right = x->left;
    x->left = h;
    x->color = h->color;
    h->color = RED;
    return x;
}

static RBNode *rotate_right(RBNode *h) {
    RBNode *x = h->left;
    h->left = x->right;
    x->right = h;
    x->color = h->color;
    h->color = RED;
    return x;
}

static void flip_colors(RBNode *h) {
    h->color = RED;
    h->left->color = BLACK;
    h->right->color = BLACK;
}

static RBNode *rb_insert(RBNode *h, int key) {
    if (!h) return rb_new(key, RED);

    if (key < h->key)       h->left  = rb_insert(h->left, key);
    else if (key > h->key)  h->right = rb_insert(h->right, key);
    else                    return h;

    if (is_red(h->right) && !is_red(h->left))          h = rotate_left(h);
    if (is_red(h->left) && is_red(h->left->left))      h = rotate_right(h);
    if (is_red(h->left) && is_red(h->right))           flip_colors(h);
    return h;
}

static void rb_inorder(const RBNode *h) {
    if (!h) return;
    rb_inorder(h->left);
    printf("%d ", h->key);
    rb_inorder(h->right);
}

static void rb_free(RBNode *h) {
    if (!h) return;
    rb_free(h->left);
    rb_free(h->right);
    free(h);
}

static void rb_demo(void) {
    int vals[] = {7, 3, 18, 10, 22, 8, 11, 26, 2, 6, 13};
    RBNode *root = NULL;
    for (int i = 0; i < (int)(sizeof vals / sizeof vals[0]); ++i)
        root = rb_insert(root, vals[i]);
    root->color = BLACK;

    printf("red-black tree inorder:");
    rb_inorder(root);
    printf("\n");
    rb_free(root);
}


int main(void) {
    heap_demo();
    printf("\n");
    rb_demo();
    return 0;
}