#include <stdio.h>
#include <stdlib.h>

struct node {
    int key;
    struct node *parent;
    struct node *left;
    struct node *right;
};

struct node* minimum(struct node *R) {
    struct node *t = R;
    if (!t) {
        return NULL;
    }
    if (t->left) {
        minimum(t->left);
    } else {
        return t;
    }
}

struct node* maximum(struct node *R) {
    struct node *t = R;
    if (!t) {
        return NULL;
    }
    if (t->right) {
        maximum(t->right);
    } else {
        return t;
    }
}

struct node* successor(struct node *x) { //one right, then left
    if (x->right) {
        return minimum(x->right);
    } else {
        struct node *y = x->parent;
        while (y && x == y->right) {
            x = y;
            y = y->parent;
        }
        return y;
    }
}

struct node* predecessor(struct node *x) { //one left, then right
    if (x->left) {
        return maximum(x->left);
    } else {
        struct node *y = x->parent;
        while (y && x == y->left) {
            x = y;
            y = y->parent;
        }
        return y;
    }
}

void insert(struct node **R, int val) {
    struct node *t = *R;
    struct node *p = malloc(sizeof(struct node));
    p->key = val;
    p->parent = p->left = p->right = NULL;
    if (!t) {
        *R = p;
    }
    while (t) {
        if (t->key >= val) {
            if (t->left) {
                t = t->left;
            } else {
                p->parent = t;
                t->left = p;
                return;
            }
        }
        else {
            if (t->right) {
                t = t->right;
            } else {
                p->parent = t;
                t->right = p;
                return;
            }
        }
    }
}

struct node* search(struct node *R, int val) {
    struct node *t = R;
    while (t) {
        if (t->key > val) {
            t = t->left;
        } else if (t->key < val) {
            t = t->right;
        } else {
            return t;
        }
    }
    return NULL;
}

void transplant(struct node **R, struct node *u, struct node *v) {
    if (!u->parent) {
        *R = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v) {
        v->parent = u->parent;
    }
}

int delete(struct node **R, int val) {
    struct node *t = *R;
    if (!t) {
        printf("\ntree is empty\n");
        return -1;
    }
    struct node *x = search(*R, val);

    if (!x) {
        printf("\n%d is not in tree!\n", val);
        return -1;
    }

    if (!x->left) {
        transplant(&*R,x,x->right);
    } else if (!x->right) {
        transplant(&*R,x,x->left);
    } else {
        struct node *y = minimum(x->right);
        if (y != x->right) {
            transplant(&*R,y,y->right);
            y->right = x->right;
            y->right->parent = y;
        }
        transplant(&*R,x,y);
        y->left = x->left;
        y->left->parent = y;
    }
    return val;

}


void inorder(struct node *R) { //inorder traversal
    struct node *t = R;
    if (t) {
        inorder(t->left);
        printf("%d ", t->key);
        inorder(t->right);
    }
}

void postorder(struct node *R) {
    struct node *t = R;
    if (t) {
        postorder(t->left);
        postorder(t->right);
        printf("%d ", t->key);
    }
}

void preorder(struct node *R) {
    struct node *t = R;
    if (t) {
        printf("%d ", t->key);
        preorder(t->left);
        preorder(t->right);
    }
}

int main(void) {
    struct node *Tree = NULL;
    insert(&Tree, 4);
    insert(&Tree, 2);
    insert(&Tree, 1);
    insert(&Tree, 3);
    insert(&Tree, 6);
    insert(&Tree, 5);
    insert(&Tree, 7);
}
