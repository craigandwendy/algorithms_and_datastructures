#include <stdlib.h>
#include <stdio.h>
#define RED 1
#define BLACK 0

struct node {
    int key;
    int color; //0 = black, 1 = red
    struct node *parent;
    struct node *left;
    struct node *right;
};

void leftRotate(struct node **R, struct node *x) {
    struct node *y = x->right;
    x->right = y->left;
    y->parent = x->parent;
    if (y->left) {
        y->left->parent = x;
    }
    if (!x->parent) {
        *R = y;
    } else {
        if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
    }
    y->left = x;
    x->parent = y;
}

void rightRotate(struct node **R, struct node *x) {
    struct node *y = x->left;
    x->left = y->right;
    y->parent = x->parent;
    if (y->right) {
        y->right->parent = x;
    }
    if (!x->parent) {
        *R = y;
    } else {
        if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
    }
    y->right = x;
    x->parent = y;
}

void insert_fixup(struct node **R, struct node *x) {
    struct node *y;
    while (x->parent->color == RED) {
        if (x->parent == x->parent->parent->left) { //x's parent is a left child
            y = x->parent->parent->right; //y = x's uncle
            if (y->color == RED) { //case 1, x's parent & uncle red?
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {
                if (x == x->parent->right) { //case 2
                    x = x->parent;
                    leftRotate(&*R,x);
                }
                x->parent->color = BLACK; //case 3
                x->parent->parent->color = BLACK;
                rightRotate(&*R,x->parent->parent);
            }
        } else { //x's parent is a right child
            y = x->parent->parent->left; //y = x's uncle
            if (y->color == RED) { //case 1m, x's parent & uncle red?
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {
                if (x == x->parent->left) { //case 2m
                    x = x->parent;
                    rightRotate(&*R,x);
                }
                x->parent->color = BLACK; //case 3m
                x->parent->parent->color = RED;
                leftRotate(&*R,x->parent->parent);
            }
        }
    }
    (*R)->color = BLACK;
}

void insert(struct node **R, int val) {
    struct node *t = *R;
    struct node *p = malloc(sizeof(struct node));
    p->key = val;
    p->color = 1;
    p->parent = p->left = p->right = NULL;
    if (!t) {
        p->color = 0;
        *R = p;
        return;
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
        } else {
            if (t->right) {
                t = t->right;
            } else {
                p->parent = t;
                t->right = p;
                return;
            }
        }
    }
    insert_fixup(&*R,p);
}

void inorder(struct node *R) {
    struct node *t = R;
    if (t) {
        inorder(t->left);
        printf("%d ", t->key);
        inorder(t->right);
    }
}


int main(void) {
    struct node *root = NULL;
    insert(&root, 1);
    insert(&root, 2);
    insert(&root, 3);
}