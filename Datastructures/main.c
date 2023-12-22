#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *next;
};

void enqueue(struct node **q, struct node **l, int v) {
    struct node *t = *q;
    struct node *p;
    p = malloc(sizeof(struct node));
    p->value = v;
    p->next = NULL;
    if (!t) {
        *q = *l = p;
        return;
    }
    (*l)->next = p;
    *l = p;
}

void dequeue(struct node **q) {
    struct node *t = *q;
    if (!t) {
        printf("Cannot dequeue empty queue!\n\n");
        return;
    }
    *q = (*q)->next;
    free(t);
}

void show(struct node *q) {
    struct node *t = q;
    if (!t) {
        printf("Cannot print empty queue\n\n");
        return;
    }
    while (t) {
        printf("%d --> ", t->value);
        t = t->next;
    }
    printf("NULL\n\n");
}

int main(void) {
    struct node *queue = NULL;
    struct node *last = queue;
    enqueue(&queue, &last, 9);
    enqueue(&queue, &last, 2);
    show(queue);
    dequeue(&queue);
    show(queue);
    dequeue(&queue);
    show(queue);
    enqueue(&queue, &last, 1);
    show(queue);
}