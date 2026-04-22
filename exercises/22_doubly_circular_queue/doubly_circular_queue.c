#include "doubly_circular_queue.h"

#include <stdlib.h>

// 头尾哨兵
static struct node tailsentinel;
static struct node headsentinel = {0, NULL, &tailsentinel};
static struct node tailsentinel = {0, &headsentinel, NULL};

static link head = &headsentinel;
static link tail = &tailsentinel;

link make_node(int data) {
    link node = (link)malloc(sizeof(struct node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

void free_node(link p) {
    free(p);
}

link search(int key) {
    for (link current = head->next; current != tail; current = current->next) {
        if (current->data == key) {
            return current;
        }
    }
    return NULL;
}

void insert(link p) {
    if (p == NULL) {
        return;
    }
    p->next = head->next;
    p->prev = head;
    head->next->prev = p;
    head->next = p;
}

void delete(link p) {
    if (p == NULL || p == head || p == tail) {
        return;
    }
    p->prev->next = p->next;
    p->next->prev = p->prev;
    p->prev = NULL;
    p->next = NULL;
}

void traverse(void (*visit)(link)) {
    for (link current = head->next; current != tail; current = current->next) {
        visit(current);
    }
}

void destroy(void) {
    link current = head->next;
    while (current != tail) {
        link next = current->next;
        free_node(current);
        current = next;
    }
    head->next = tail;
    tail->prev = head;
}
