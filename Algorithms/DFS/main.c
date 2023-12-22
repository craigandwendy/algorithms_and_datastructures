#include <stdio.h>
#include <stdlib.h>
#define N 8
#define WHITE 0
#define BLACK 1
#define GRAY 2
#define NONE -1

struct vertex {
    int value;
    struct vertex *next;
};

struct adjlist {
    int value;
    int color; //white = not visited, black = visited
    int predecessor; //-1 = no predecessor
    int s_time; //starting time
    int e_time; //end time
    struct vertex *next;
};

void printAdjlist(struct adjlist A[N]) {
    int i;
    for (i=0;i<N;i++) {
        struct vertex *t = A[i].next;
        printf("%d(%d): stime = %d, etime = %d , next: ", A[i].value, A[i].color, A[i].s_time, A[i].e_time);
        while (t) {
            printf("%d ", t->value);
            t = t->next;
        }
        printf("\n");
    }
    printf("\n");
}

void initAdjlist(struct adjlist A[N]) {
    int i;
    for (i=0;i<N;i++) {
        A[i].value = i;
        A[i].color = 0;
        A[i].predecessor = -1;
        A[i].s_time = -1;
        A[i].e_time = -1;
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

void dfs_visit(struct adjlist A[N], int u);

int time = -1;

void dfs(struct adjlist A[N], int start) {
    int i;
    for (i=0;i<N;i++) {
        A[i].color = WHITE;
        A[i].predecessor = NONE;
    }
    dfs_visit(A, A[start].value);

    for (i=0;i<N;i++) {
        if (A[i].color == WHITE) {
            dfs_visit(A, A[i].value);
        }
    }
    printf("end\n");
}

void dfs_visit(struct adjlist A[N], int u) {
    printf("%d -> ", u);
    time++;
    A[u].s_time = time;
    A[u].color = GRAY;
    struct vertex *v = A[u].next;
    while (v) {
        if (A[v->value].color == WHITE) {
            A[v->value].predecessor = u;
            dfs_visit(A, v->value);
        }
        v = v->next;
    }
    time++;
    A[u].e_time = time;
    A[u].color = BLACK;
}


int main(void) {
    struct adjlist A[N];
    initAdjlist(A);
    edge(0,1,A);
    edge(0,2,A);
    edge(0,4,A);
    edge(1,3,A);
    edge(1,4,A);
    edge(2,5,A);
    edge(3,6,A);
    edge(5,7,A);
    edge(6,7,A);

    printAdjlist(A);

    dfs(A, 0);

    printAdjlist(A);
}