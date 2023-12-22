#include <stdio.h>
#include <stdlib.h>
#define N 7
#define WHITE 0
#define BLACK 1
#define GRAY 2
#define TRUE 1
#define FALSE 0
#define NONE -1

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

void printAdjlist(struct adjlist A[N]) {
    int i;
    for (i=0;i<N;i++) {
        printf("%d: stime = %d, etime = %d, color = %d\n", A[i].value, A[i].s_time, A[i].e_time, A[i].color);
    }
}

int time = -1;

void dfs_runner(struct adjlist A[N], int u) {
    time++;
    A[u].s_time = time;
    A[u].color = GRAY;
    struct vertex *v = A[u].next;
    while (v) {
        if (A[v->value].color == WHITE) {
            A[v->value].predecessor = A[u].value;
            dfs_runner(A, v->value);
        }
        v = v->next;
    }

    time++;
    A[u].e_time = time;
    A[u].color = BLACK;
}

void dfs(struct adjlist A[N], int start) { //start can be per default 0 --> Matrix[0][0] or any -1 < number < N
    time = -1;
    int i;
    for (i=0;i<N;i++) {
        A[i].color = WHITE;
        A[i].predecessor = NONE;
        A[i].s_time = NONE;
        A[i].e_time = NONE;
    }

    dfs_runner(A, A[start].value);

    for (i=0;i<N;i++) {
        if (A[i].color == WHITE) {
            dfs_runner(A, A[i].value);
        }
    }
}

int isDag = TRUE;

void dag_runner(struct adjlist A[N], int v) {
    A[v].color = GRAY;
    struct vertex *u = A[v].next;
    while (u) {
        if (A[u->value].color == GRAY) {
            isDag = FALSE;
            return;
        }
        if (A[u->value].color == WHITE) {
            dag_runner(A, u->value);
        }
        u = u->next;
    }
    A[v].color = BLACK;
}

int dagCheck(struct adjlist A[N]) {
    int i;
    for (i=0;i<N;i++) {
        A[i].color = WHITE;
    }
    for (i=0;i<N;i++) {
        if (A[i].color == WHITE) {
            dag_runner(A, A[i].value);
        }
        if (isDag == FALSE) {
            printf("Cycle detected!\n");
            return FALSE;
        }
    }
    printf("Graph is DAG!\n");
    return TRUE;
}

void topologicalSort(struct adjlist A[N]) {
    int i, pos;
    dfs(A,0);
    printf("\n");
    printAdjlist(A);

    int Etime[2*N];
    for (i=0;i<2*N;i++) {
        Etime[i] = -1; //initialize array
    }
    for (i=0;i<N;i++) {
        Etime[A[i].e_time] = i;
        printf("%d: time = %d\n", i, A[i].e_time);
    }
    for (i=0;i<2*N;i++) {
        if (Etime[i] != -1) {
            printf("%d ", Etime[i]);
        }
    }
    printf("\n");
}


int main(void) {
    struct adjlist A[N];
    initAdjlist(A);

    edge(0,1,A);
    edge(0,2,A);
    edge(1,3,A);
    edge(1,5,A);
    edge(2,4,A);
    edge(2,6,A);
    edge(3,5,A);
    edge(4,6,A);
    edge(5,6,A);
    edge(6,0,A);

    dfs_runner(A,0);
    dfs_runner(A, 0);
    dfs_runner(A, 0);


    printAdjlist(A);



    //dagCheck(A);

    topologicalSort(A);


}