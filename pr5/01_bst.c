#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Структура для хранения узла дерева.
// Необходимо хранить ссылки на потомков, предка и некоторое значение
typedef struct node {
    struct node *left;
    struct node *right;
    struct node *parent;
    int value;
} node;


// Структура для хранения дерева.
// Хранит ссылку на корень дерева и количество элементов в дереве
typedef struct tree {
    struct node *root;
    int count;
} tree;


//-------------------------------------------------------------------------------
// функции дерева
// Инициализация дерева
void init(tree *t) {
    t->root = NULL;
    t->count = 0;
}

// Поиск элемента по значению. Вернуть NULL если элемент не найден
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

// Вставка значения в дерево:
// 0 - вставка выполнена успешно
// 1 - элемент существует
// 2 - не удалось выделить память для нового элемента
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

// Удалить элемент из дерева:
// 0 - удаление прошло успешно
// 1 - нет элемента с указанным значением
int remove_node(tree *t, int value) {
    node *b, *temp;
    b = find(t, value);
    if (b == NULL)
        return 1;
    if ((b->left == NULL) && (b->right == NULL)) {
        if (t->root != b)
            if (b->parent->left == b)
                b->parent->left = NULL;
            else
                b->parent->right = NULL;
        else
            t->root = NULL;
    }
    else if (b->right == NULL){
        temp = b->left;
        while (temp->right != NULL)
            temp = temp->right;
        if (temp->parent != b){
            temp->parent->right = temp->left;
            if (temp->left != NULL)
                temp->left->parent = temp->parent;
            temp->left = b->left;
            b->left->parent = temp;
        }
        if (t->root == b){
            temp->parent = NULL;
            t->root = temp;
        }
        else{
            temp->parent = b->parent;
            if (b->parent->left == b)
                b->parent->left = temp;
            else
                b->parent->right = temp;
        }
    }
    else if (b->left == NULL){
        temp = b->right;
        while (temp->left != NULL)
            temp = temp->left;
        if (temp->parent != b){
            temp->parent->left = temp->right;
            if (temp->right != NULL)
                temp->right->parent = temp->parent;
            temp->right = b->right;
            b->right->parent = temp;
        }
        if (t->root == b){
            temp->parent = NULL;
            t->root = temp;
        }
        else{
            temp->parent = b->parent;
            if (b->parent->left == b)
                b->parent->left = temp;
            else
                b->parent->right = temp;
        }
    }
    else{
        temp = b->right;
        while (temp->left != NULL)
            temp = temp->left;
        if (temp->parent != b){
            temp->parent->left = temp->right;
            if (temp->right != NULL)
                temp->right->parent = temp->parent;
            temp->right = b->right;
            b->right->parent = temp;
            b->left->parent = temp;
        }
        temp->left = b->left;
        b->left->parent = temp;
        temp->parent = b->parent;
        if (t->root == b)
            t->root = temp;
        else if (b->parent->right == b)
            b->parent->right = temp;
        else
            b->parent->left = temp;
    }
    t->count--;
    free(b);
    return 0;
}


// Удалить минимальный элемент из поддерева, корнем которого является n
// Вернуть значение удаленного элемента
int remove_min(node *n);

// Выполнить правое вращение поддерева, корнем которого является n:
// 0 - успешно выполненная операция
// 1 - вращение невозможно
int rotate_right(tree *t){
    node *NewRoot, *OldRoot;
    if (t->root != NULL){
        if (t->root->left == NULL)
            return 1;
        while (t->root->left != NULL) {
            OldRoot = t->root;
            NewRoot = OldRoot->left;
            OldRoot->left = NewRoot->right;
            if (NewRoot->right != NULL) {
                NewRoot->right->parent = OldRoot;
            }
            NewRoot->parent = OldRoot->parent;
            if (OldRoot->parent != NULL) {
                if (OldRoot->parent->left == OldRoot) {
                    OldRoot->parent->left = NewRoot;
                } else {
                    OldRoot->parent->right = NewRoot;
                }
            }
            t->root = NewRoot;
            NewRoot->right = OldRoot;
            OldRoot->parent = NewRoot;
        }
        return 0;
    }
    else
        return 1;
}

// Выполнить левое вращение поддерева, корнем которого является n:
// 0 - успешно выполненная операция
// 1 - вращение невозможно
int rotate_left(tree *t){
    node *NewRoot, *OldRoot;
    if (t->root != NULL){
        if (t->root->right == NULL)
            return 1;
        while (t->root->right != NULL) {
            OldRoot = t->root;
            NewRoot = OldRoot->right;
            OldRoot->right = NewRoot->left;
            if (NewRoot->left != NULL) {
                NewRoot->left->parent = OldRoot;
            }
            NewRoot->parent = OldRoot->parent;
            if (OldRoot->parent != NULL) {
                if (OldRoot->parent->right == OldRoot) {
                    OldRoot->parent->right = NewRoot;
                } else {
                    OldRoot->parent->left = NewRoot;
                }
            }
            t->root = NewRoot;
            NewRoot->left = OldRoot;
            OldRoot->parent = NewRoot;
        }
        return 0;
    }
    else
        return 1;
}


void printNode(node *n, int current, int deep, int first) {
    if (current == deep) {
        if (first > 0) {
            printf(" ");
        }
        if (n == NULL) {
            printf("_");
        } else {
            printf("%d", n->value);
        }
    } else if (n != NULL) {
        printNode(n->left, current + 1, deep, first);
        printNode(n->right, current + 1, deep, first + 1);
    } else {
        printNode(n, current + 1, deep, first);
        printNode(n, current + 1, deep, first + 1);
    }
}

int deepness(node *n, int deep) {
    if (n == NULL) {
        return deep;
    }
    int deepleft;
    deepleft = deepness(n->left, deep + 1);
    int deepright;
    deepright = deepness(n->right, deep + 1);
    if (deepleft > deepright)
        return deepleft;
    else
        return deepright;
}

// Вывести все значения из поддерева, корнем которого является n
// по уровням начиная с корня.
// Каждый уровень выводится на своей строке.
// Элементы в строке разделяются пробелом. Если элемента нет, заменить на _.
// Если дерево пусто, вывести -
void print(node *n) {
    if (n == NULL)
        printf("-");
    else {
        int lvl, i;
        lvl = deepness(n, 0);
        for (i = 1; i <= lvl; i++) {
            printNode(n, 1, i, 0);
            printf("\n");
        }
        printf("\n");
    }
}

// Вывести все значения дерева t, аналогично функции print
void print_tree(tree *t) {
    if (t->root == NULL) {
        printf("-");
        printf("\n");
        return;
    } else
        print(t->root);
}

// Удалить все элементы из дерева
void clean(tree *t){
    while (t->root != NULL)
        remove_node(t, t->root->value);
}


int main() {
    tree T;
    int i, input;
    node *b;
    init(&T);
    // Задание 1
    for (i = 0; i < 4; i++) {
        (void) scanf("%d", &input);
        insert(&T, input);
    }
    // Задание 2
    print_tree(&T);
    //Задание 3
    for (i = 0; i < 3; i++) {
        (void) scanf("%d", &input);
        insert(&T, input);
    }
    // Задание 4
    print_tree(&T);
    //Задание 5
    (void) scanf("%d", &input);
    b = find(&T, input);
    if (b == NULL)
        printf("- \n");
    else {
        if (b->parent == NULL)
            printf("_ ");
        else
            printf("%d ", b->parent->value);
        if (b->left == NULL)
            printf("_ ");
        else
            printf("%d ", b->left->value);
        if (b->right == NULL)
            printf("_ \n");
        else
            printf("%d \n", b->right->value);
    }
    printf("\n");
    // Задание 6
    (void) scanf("%d", &input);
    b = find(&T, input);
    if (b == NULL)
        printf("- \n");
    else {
        if (b->parent == NULL)
            printf("_ ");
        else
            printf("%d ", b->parent->value);
        if (b->left == NULL)
            printf("_ ");
        else
            printf("%d ", b->left->value);
        if (b->right == NULL)
            printf("_ \n");
        else
            printf("%d \n", b->right->value);
    }
    printf("\n");
    // Задание 7 и 8
    (void) scanf("%d", &input);
    remove_node(&T, input);
    print_tree(&T);
    printf("\n");
    // Задание 9, 10
    rotate_left(&T);
    print_tree(&T);
    printf("\n");
    // Задание 11, 12
    rotate_right(&T);
    print_tree(&T);
    printf("\n");
    // Задание 13
    printf("%d", T.count);
    printf("\n");
    printf("\n");
    // Задание 14 и 15
    clean(&T);
    print_tree(&T);
    return 0;
}
