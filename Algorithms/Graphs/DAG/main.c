#include <stdlib.h>
#include <stdio.h>
#define N 7
#define BLACK 1
#define WHITE 0
#define GRAY -1
#define NONE -2
#define TRUE 1
#define FALSE 0

struct vertex {
    int value;
    struct vertex *next;
};

struct adjlist {
    int value;
    int color;
    int predecessor;
    int s_time;
    int e_time;
    struct vertex *next;
};

void printAdjlist(struct adjlist A[N]) {
    int i;
    for (i=0;i<N;i++) {
        struct vertex *t = A[i].next;
        printf("value = %d, next: ", A[i].value);
        while (t) {
            printf("%d, ", t->value);
            t = t->next;
        }
        printf("\n");
    }
}

void initAdjlist(struct adjlist A[N]) {
    int i;
    for (i=0;i<N;i++) {
        A[i].value = i;
        A[i].color = WHITE;
        A[i].predecessor = NONE;
        A[i].s_time = NONE;
        A[i].e_time = NONE;
        A[i].next = NULL;
    }
}

void edge(int from, int to, struct adjlist A[N]) {
    struct vertex *t = A[from].next;
    struct vertex *p = malloc(sizeof(struct vertex));
    p->value = to;
    p->next = NULL;
    if (!t) {
        A[from].next = p;
        return;
    }
    p->next = t;
    A[from].next = p;
}

int isDag = TRUE;

void DAGcheckRunner(struct adjlist A[N], int v) {
    struct vertex *u = A[v].next;
    A[v].color = GRAY;
    while (u) {
        if (A[u->value].color == GRAY) {
            isDag = FALSE;
            return;
        }
        if (A[u->value].color == WHITE) {
            DAGcheckRunner(A,u->value);
        }
        u = u->next;
    }
    A[v].color = BLACK;
}

void DAGcheck(struct adjlist A[N]) {
    //initAdjlist(A);
    int i;
    for (i=0;i<N;i++) {
        A[i].color = WHITE;
    }
    isDag = TRUE;
    for (i=0;i<N;i++) {
        struct vertex *u = A[i].next;
        if (isDag == FALSE) {
            printf("cycle detected!\n");
            return;
        }
        while (u) {
            if (A[u->value].color == WHITE) {
                DAGcheckRunner(A,u->value);
            }
            u = u->next;
        }
    }
    printf("Graph is DAG\n");
}



int main(void) {
    struct adjlist A[N];
    initAdjlist(A);
    edge(0,1,A);
    edge(1,2,A);
    edge(2,3,A);
    edge(2,6,A);
    edge(3,4,A);
    edge(4,5,A);
    edge(5,6,A);
    edge(6,3,A);

    DAGcheck(A);

}