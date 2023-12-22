#include <stdio.h>
#include <stdlib.h>
#define V 7

struct node {
    int value;
    struct node * next;
};

struct queue{
    int count;
    struct node* first;
    struct node* last;
};

void init_AdjList(struct node* AdjList[]) {
    int i;
    for (i=0;i<V;i++) {
        AdjList[i] = NULL;
    }
}

void init_AdjMatrix(int AdjMatrix[V][V]) {
    int i, j;
    for (i=0;i<V;i++) {
        for (j=0;j<V;j++) {
            AdjMatrix[i][j] = 0;
        }
    }
}

void init_Queue(struct queue **Q) {
    *Q = malloc(sizeof(struct queue));
    (*Q)->count = 0;
    (*Q)->first = (*Q)->last = NULL;
}

int isEmpty(struct queue *Q) {
    if (Q->last == NULL) {
        return 1;
    }
    return 0;
}

void enqueue(struct queue **Q, int val) {
    struct node *p = malloc(sizeof(struct node));
    p->value = val;
    p->next = NULL;
    if ((*Q)->last == NULL) {
        (*Q)->last = (*Q)->first = p;
        return;
    }
    (*Q)->last->next = p;
    (*Q)->last = p;
}

int dequeue(struct queue **Q) {
    if (isEmpty(*Q) == 1) {
        return -1;
    }
    int val;
    struct node *t = (*Q)->first;
    val = (*Q)->first->value;
    if ((*Q)->first->next == NULL) {
        free(t);
        init_Queue(&(*Q));
        return val;
    }
    (*Q)->first = (*Q)->first->next;
    free(t);
    return val;
}

void insert(struct node *AdjList[], int from, int to) { //insert vertices into adjacency list
    struct node *t = AdjList[from];
    struct node *p = malloc(sizeof(struct node));
    p->value = to;
    p->next = NULL;
    if (!t) {
        AdjList[from] = p;
        return;
    }
    AdjList[from] = p;
    AdjList[from]->next = t;
}

void printGraph(struct node *AdjList[]) { //print adjacency list
    printf("\n\n");
    int i;
    for (i=0;i<V;i++) {
        struct node *t = AdjList[i];
        printf("%d: ", i);
        while (t) {
            printf("%d -> ", t->value);
            t = t->next;
        }
        printf("NULL\n");
    }
}

void printAdjMatrix(int AdjMatrix[V][V]) {
    printf("\n\n");
    int i, j;
    for (i=0;i<V;i++) {
        for (j=0;j<V;j++) {
            printf("%d ", AdjMatrix[i][j]);
        }
        printf("\n");
    }
}

void convert_to_adjacency_matrix(struct node* AdjList[], int AdjMatrix[V][V]) {
    int i;
    for (i=0;i<V;i++) {
        struct node *t = AdjList[i];
        while (t) {
            int v = t->value;
            AdjMatrix[i][v] = 1;
            t = t->next;
        }
    }
}


void BFS(struct node *AdjList[], int start) { //might not visit all nodes
    int u, v;
    int visited[V] = {0};
    struct queue *Q;
    init_Queue(&Q);
    int AdjMatrix[V][V] = {};
    init_AdjMatrix(AdjMatrix);
    convert_to_adjacency_matrix(AdjList, AdjMatrix);
    visited[0] = 1;
    printf("%d", start);
    enqueue(&Q, start);
    while (isEmpty(Q) == 0) {
        u = dequeue(&Q);
        for (v=0;v<V;v++) {
            if (AdjMatrix[u][v] == 1 && visited[v] == 0) {
                printf(" -> %d", v);
                visited[v] = 1;
                enqueue(&Q, v);
            }
        }
    }
}



int main() {
    struct node *AdjList[V];
    init_AdjList(AdjList);
    insert(AdjList, 0, 1);
    insert(AdjList, 0, 2);
    insert(AdjList, 0, 3);
    insert(AdjList, 1, 4);
    insert(AdjList, 1, 5);
    insert(AdjList, 2, 3);
    insert(AdjList, 5, 4);
    insert(AdjList, 6, 3);
    insert(AdjList, 6, 5);
    BFS(AdjList, 0);
}
