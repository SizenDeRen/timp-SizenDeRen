#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    struct node *left;
    struct node *right;
    struct node *parent;
    int value;
} node;


typedef struct tree {
    struct node *root;
    int count;
} tree;

void init(tree *t) {
    t->root = NULL;
    t->count = 0;
}

node *find(tree *t, int value) {
    node *temp;
    temp = t->root;
    if (temp == NULL)
        return NULL;
    while (temp->value != value) {
        if (value > temp->value)
            temp = temp->right;
        else
            temp = temp->left;
        if (temp == NULL)
            return NULL;
    }
    return temp;
}

void straight(tree * t)
{
    node * a[15];
    int a_i = 0;
    node * nmb[15];
    int w_i = 0;
    node * n = t->root;
    while (w_i < t->count)
    {
        while (n != NULL)
        {
            w_i++;
            if (n->right != NULL)
            {
                a_i++;
                a[a_i] = n->right;
            }
            nmb[w_i] = n;
            n = n->left;
        }
        n = a[a_i];
        a_i -= 1;
    }
    int fl = 0;
    for (int i = 1; i <= w_i; i++)
    {
        if (fl > 0) printf(" ");
        else fl++;
        printf("%d", nmb[i]->value);
    }
    printf("\n");
}

int insert(tree *t, int value) {
    node *error;
    error = find(t, value);
    if (error != NULL)
        return 1;
    node *temp;
    node *elem;
    elem = (node *) malloc(sizeof(node));
    elem->value = value;
    elem->left = NULL;
    elem->right = NULL;
    temp = t->root;
    if (temp == NULL) {
        elem->parent = NULL;
        t->root = elem;
        t->count++;
        return 0;
    }
    int i;
    while (true) {
        if (temp->value > value) {
            if (temp->left != NULL)
                temp = temp->left;
            else {
                temp->left = elem;
                elem->parent = temp;
                t->count++;
                return 0;
            }
        } else {
            if (temp->right != NULL)
                temp = temp->right;
            else {
                temp->right = elem;
                elem->parent = temp;
                t->count++;
                return 0;
            }
        }
    }
}

int main() {
    tree T;
    int i, input;
    node *b;
    init(&T);
    // Задание 1
    for (i = 0; i < 7; i++) {
        (void) scanf("%d", &input);
        insert(&T, input);
    }
    straight(&T);
    return 0;
}