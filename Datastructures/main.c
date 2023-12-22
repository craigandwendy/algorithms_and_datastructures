#include <stdio.h>
#include <stdlib.h>

/*
 * use of stacks: to invert array for example
 * deletion and insertion is always O(1)
 * dynamical size
 * LIFO
 *
 * |__9__| --> top = last pushed element = first popped element
 * |__2__|
 * |__1__|
 * |__8__|
 * |__9__| --> bottom = first pushed element = last popped element
 * */

struct node {
    int value;
    struct node *next;
};

void push(struct node **s, int v) { //insertion O(1)
    struct node *t = *s;
    struct node *p;
    p = malloc(sizeof(struct node));
    p->value = v;
    p->next = NULL;
    if (!t) { //if empty, root = first element
        *s = p;
        return;
    }
    *s = p; //if not empty, insert p at root and p->next = root
    p->next = t;
}

void pop(struct node **s) { //deletion O(1)
    struct node *t = *s;
    if (!t) { //check if empty
        printf("Cannot pop empty stack!\n\n");
        return;
    }
    *s = (*s)->next; //if not empty, root = root->next
    free(t); //delete original root
}

void show(struct node *s) {
    struct node *t = s;
    if (!t) { //check if empty
        printf("Empty stack!\n\n");
        return;
    }
    while (t) { //print while t is not NULL
        printf("|__%d__|\n", t->value);
        t = t->next;
    }
    printf("End of stack\n\n");
}

int main(void) {
    struct node *stack = NULL;
    push(&stack, 5);
    push(&stack, 9);
    push(&stack, 3);
    show(stack);
    pop(&stack);
    show(stack);
    push(&stack, 1);
    push(&stack, 6);
    push(&stack, 7);
    show(stack);
    pop(&stack);
    pop(&stack);
    pop(&stack);
    pop(&stack);
    pop(&stack);
    show(stack);
    pop(&stack);
    show(stack);
}