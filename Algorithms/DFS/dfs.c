#include <stdio.h>
#include <stdlib.h>
#define V 7

struct node {
    int value;
    struct node * next;
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

int visited[V] = {0};
int AdjMatrix[V][V] = {};

void DFS(int start) { //visits all nodes
    if (visited[start] == 0) { //check if start was visited
        visited[start] = 1;
        printf("%d", start);
    }
    int v;
    for (v=0;v<V;v++) { //check all adjacent vertices of start
        if (AdjMatrix[start][v] == 1 && visited[v] == 0) {
            DFS(v);
        }
    }
}

void DFS_runner(int start) { //this works well
    DFS(start); //first call DFS on the starting vertex
    printf("\n");
    int v;
    for (v=0;v<V;v++) {
        if (visited[v] == 0) { //call DFS on all unvisited vertices
            DFS(v);
            printf("\n");
        }
    }
}

void abdul_dfs(int start) { //this one is buggy, it only prints vertices on the path of start, all other vertices that cannot be reached are simply ignored!
    if (visited[start] == 0) {
        printf("%d ", start);
        visited[start] = 1;
        int v;
        for (v = 0; v < V; v++) {
            if (AdjMatrix[start][v] == 1 && visited[v] == 0) {
                DFS(v);
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

    init_AdjMatrix(AdjMatrix);
    convert_to_adjacency_matrix(AdjList, AdjMatrix);

    //DFS_runner(6);
    DFS_runner(1);
}
