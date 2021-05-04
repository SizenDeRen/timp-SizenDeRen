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


typedef struct queue {
    int value;
    struct queue *next;
} queue;

typedef struct list {
    struct queue *head;
} list;


void  init_list(list *l){
    l->head = NULL;
}

void init(tree *t) {
    t->root = NULL;
    t->count = 0;
}

bool is_empty(list *l){
    if (l->head == NULL)
        return 1;
    else
        return 0;
}

int push_back(list *l, int value){
    queue* Nnode;
    Nnode = (queue*)malloc(sizeof(queue));
    Nnode->value = value;
    Nnode->next = NULL;
    if (is_empty(l))
        l->head = Nnode;
    else{
        queue* p = l->head;
        while (p->next != NULL){
            p = p->next;
        }
        p->next = Nnode;
    }
    return 0;
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

int remove_first(tree *t, list *l, int value){
    queue* p1 = l->head;
    node* b;
    b = find(t, value);
    if (b->left != NULL)
        push_back(l, b->left->value);
    if (b->right != NULL)
        push_back(l, b->right->value);
    l->head = p1->next;
    free(p1);
    return 0;
}

void print_head(list *l, tree* t){
    while (l->head != NULL){
        printf("%d ", l->head->value);
        remove_first(t, l, l->head->value);
    }
}

int main() {
    tree T;
    list L;
    init_list(&L);
    int i, input;
    node *b;
    init(&T);
    // Задание 1
    for (i = 0; i < 7; i++) {
        (void) scanf("%d", &input);
        insert(&T, input);
    }
    push_back(&L, T.root->value);
    print_head(&L, &T);
    return 0;
}
