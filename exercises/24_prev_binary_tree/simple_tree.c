#include "simple_tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

Queue* create_queue() {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue *q, TreeNode *tree_node) {
    QueueNode *node = (QueueNode*)malloc(sizeof(QueueNode));
    if (node == NULL) {
        return;
    }
    node->tree_node = tree_node;
    node->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = node;
        return;
    }

    q->rear->next = node;
    q->rear = node;
}

TreeNode* dequeue(Queue *q) {
    if (q->front == NULL) {
        return NULL;
    }

    QueueNode *node = q->front;
    TreeNode *tree_node = node->tree_node;
    q->front = node->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(node);
    return tree_node;
}

bool is_empty(Queue *q) {
    return q->front == NULL;
}

void free_queue(Queue *q) {
    while (!is_empty(q)) {
        dequeue(q);
    }
    free(q);
}

TreeNode* build_tree_by_level(int *level_order, int size) {
    if (level_order == NULL || size <= 0 || level_order[0] == INT_MIN) {
        return NULL;
    }

    TreeNode *root = (TreeNode*)malloc(sizeof(TreeNode));
    if (root == NULL) {
        return NULL;
    }
    root->val = level_order[0];
    root->left = NULL;
    root->right = NULL;

    Queue *queue = create_queue();
    enqueue(queue, root);

    int index = 1;
    while (!is_empty(queue) && index < size) {
        TreeNode *current = dequeue(queue);

        if (index < size && level_order[index] != INT_MIN) {
            current->left = (TreeNode*)malloc(sizeof(TreeNode));
            current->left->val = level_order[index];
            current->left->left = NULL;
            current->left->right = NULL;
            enqueue(queue, current->left);
        }
        index++;

        if (index < size && level_order[index] != INT_MIN) {
            current->right = (TreeNode*)malloc(sizeof(TreeNode));
            current->right->val = level_order[index];
            current->right->left = NULL;
            current->right->right = NULL;
            enqueue(queue, current->right);
        }
        index++;
    }

    free_queue(queue);
    return root;
}

void preorder_traversal(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->val);
    preorder_traversal(root->left);
    preorder_traversal(root->right);
}

void preorder_traversal_iterative(TreeNode *root) {
    if (root == NULL) {
        return;
    }

    TreeNode *stack[1024];
    int top = 0;
    stack[top++] = root;

    while (top > 0) {
        TreeNode *node = stack[--top];
        printf("%d ", node->val);

        if (node->right != NULL) {
            stack[top++] = node->right;
        }
        if (node->left != NULL) {
            stack[top++] = node->left;
        }
    }
}

void free_tree(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
