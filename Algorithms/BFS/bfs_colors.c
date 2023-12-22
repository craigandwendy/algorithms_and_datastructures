#include <stdlib.h>
#include <stdio.h>
#define N 8
#define GRAY -1
#define WHITE 0
#define BLACK 1

struct node {
    int value;
    struct node *next;
};

struct adjlist {
    int value;
    int color; //-1 = gray, 0 = white, 1 = black
    int distance;
    int predecessor;
    struct node *next;
};

struct queue {
    int size;
    struct node *first;
    struct node *last;
};

void initQueue(struct queue **Q) {
    (*Q) = malloc(sizeof(struct queue));
    (*Q)->size = 0;
    (*Q)->first = (*Q)->last = NULL;
}

void enqueue(struct queue **Q, int val) {
    (*Q)->size += 1;
    struct node *t = (*Q)->last;
    struct node *p = malloc(sizeof(struct node));
    p->value = val;
    p->next = NULL;
    if (!t) {
        (*Q)->last = (*Q)->first = p;
        return;
    }
    (*Q)->last->next = p;
    (*Q)->last = (*Q)->last->next;
}

int dequeue(struct queue **Q) {
    struct node *t = (*Q)->last;
    if (!t) {
        printf("\nCannot delete empty queue!\n");
        return -1;
    }
    if ((*Q)->first->next == NULL) {
        t = (*Q)->first;
        free(*Q);
        initQueue(&(*Q));
        return t->value;
    }
    t = (*Q)->first;
    int v = t->value;
    (*Q)->first = (*Q)->first->next;
    free(t);
    return v;
}

void initAdjlist(struct adjlist A[N]) {
    int i;
    for (i=0;i<N;i++) {
        A[i].value = i;
        A[i].distance = -1; //no distance defined yet or unreachable
        A[i].color = WHITE;
        A[i].predecessor = -1; //no predecessor
        A[i].next = NULL;
    }
}

void edge(int from, int to, struct adjlist A[N]) {
    struct node *p = malloc(sizeof(struct node));
    struct node *t = A[from].next;
    p->value = to;
    p->next = NULL;
    if (A[from].next == NULL) {
        A[from].next = p;
        return;
    }
    p->next = t;
    A[from].next = p;
}

void printAdjlist(struct adjlist A[N]) {
    int i;
    for (i=0;i<N;i++) {
        printf("%d: distance = %d, predecessor = %d, color = %d\n", i, A[i].distance, A[i].predecessor, A[i].color); //at initialization must be: i,-1,-1,WHITE
    }
}

void bfs(struct adjlist A[N], int s) {
    int u;
    A[s].color = GRAY;
    A[s].distance = 0;
    A[s].predecessor = -1;
    struct queue *Q;
    initQueue(&Q);
    enqueue(&Q, A[s].value);
    while (Q->size) {
        u = dequeue(&Q);
        struct node *t = A[u].next;
        while (t) {
            if (A[t->value].color == WHITE) {
                A[t->value].color = GRAY;
                A[t->value].distance = A[u].distance + 1;
                A[t->value].predecessor = u;
                enqueue(&Q, t->value);
                //printf("%d: distance = %d, predecessor = %d\n", t->value, A[t->value].distance, A[t->value].predecessor);
            }
            t = t->next;
        }
        A[u].color = BLACK;
    }
}

void k_hop_neighbors(struct adjlist A[N], int s, int k) {
    bfs(A, s);
    int i;
    for (i=0;i<N;i++) {
        if (A[i].distance == k) {
            printf("%d\n", i);
        }
    }
}

int main(void) {
    struct adjlist A[N];
    initAdjlist(A);
    edge(0,2,A);
    edge(0,6,A);
    edge(0,1,A);
    edge(1,2,A);
    edge(1,5,A);
    edge(2,3,A);
    edge(2,4,A);
    edge(2,6,A);
    edge(4,5,A);
    edge(5,7,A);
    edge(6,7,A);

    //bfs(A,0);
    k_hop_neighbors(A,0,2);

    printAdjlist(A);

}
