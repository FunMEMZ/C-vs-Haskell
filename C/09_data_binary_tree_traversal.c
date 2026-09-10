/*
 * 任务：树，二叉树及其前中后序遍历。
 * 编译：gcc -std=c11 -O2 -Wall -Wextra 09_09_data_binary_tree_traversal.c
 */

#include <stdio.h>
#include <stdlib.h>


/* ---------- 二叉树与二叉搜索树插入 ---------- */

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

static TreeNode *tree_new(int val) {
    TreeNode *p = malloc(sizeof *p);
    if (!p) { perror("malloc"); exit(1); }
    p->val = val;
    p->left = p->right = NULL;
    return p;
}

static TreeNode *bst_insert(TreeNode *root, int val) {
    if (!root) return tree_new(val);
    if (val < root->val)       root->left  = bst_insert(root->left, val);
    else if (val > root->val)  root->right = bst_insert(root->right, val);
    return root;                 /* 已存在则忽略 */
}

static void tree_free(TreeNode *root) {
    if (!root) return;
    tree_free(root->left);
    tree_free(root->right);
    free(root);
}


/* ---------- 前序、中序、后序遍历 ---------- */

static void preorder(const TreeNode *root) {
    if (!root) return;
    printf("%d ", root->val);
    preorder(root->left);
    preorder(root->right);
}

static void inorder(const TreeNode *root) {
    if (!root) return;
    inorder(root->left);
    printf("%d ", root->val);
    inorder(root->right);
}

static void postorder(const TreeNode *root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->val);
}


int main(void) {
    int values[] = {5, 3, 8, 1, 4, 7, 9, 2, 6};
    TreeNode *root = NULL;
    for (int i = 0; i < (int)(sizeof values / sizeof values[0]); ++i)
        root = bst_insert(root, values[i]);

    printf("preorder:  "); preorder(root);  printf("\n");
    printf("inorder:   "); inorder(root);   printf("\n");
    printf("postorder: "); postorder(root); printf("\n");
    tree_free(root);
    return 0;
}