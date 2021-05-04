#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct node {
    int value;          // значение, которое хранит узел
    struct node *next;  // ссылка на следующий элемент списка
    struct node *prev;  // ссылка на предыдущий элемент списка
} node;

typedef struct list {
    struct node *head;  // начало списка
    struct node *tail;  // конец списка
} list;


// инициализация пустого списка
void init(list *l){
    l->head = NULL;
    l->tail = NULL;
}

// удалить все элементы из списка
void clean(list *l){
    node* p1 = l->head;
    node* p2;
    while (p1->next != NULL){
        p2 = p1;
        p1 = p1->next;
        free(p2);
    }
    free(p1);
    init(l);
}

// проверка на пустоту списка
bool is_empty(list *l){
    if (l->head == NULL)
        return 1;
    else
        return 0;
}

// поиск элемента по значению. вернуть NULL если элемент не найден
node *find(list *l, int value){
    node* p = l->head;
    while (p->next != NULL){
        if (p->value == value)
            return p;
        p = p->next;
    }
    if (p->value == value)
        return p;
    return NULL;
}

// вставка значения в конец списка, вернуть 0 если успешно
int push_back(list *l, int value){
    node* Nnode;
    Nnode = (node*)malloc(sizeof(node));
    Nnode->value = value;
    Nnode->next = NULL;
    if (is_empty(l)){
        l->head = Nnode;
        l->tail = Nnode;
        Nnode->prev = NULL;
    }
    else{
        Nnode->prev = l->tail;
        l->tail->next = Nnode;
        l->tail = Nnode;
    }
    return 0;
}

// вставка значения в начало списка, вернуть 0 если успешно
int push_front(list *l, int value){
    node* Nnode;
    Nnode = (node*)malloc(sizeof(node));
    Nnode->value = value;
    Nnode->prev = NULL;
    if (is_empty(l)){
        l->head = Nnode;
        l->tail = Nnode;
        Nnode->next = NULL;
    }
    else{
        Nnode->next = l->head;
        l->head->prev = Nnode;
        l->head = Nnode;
    }
    return 0;
}

node *findNode(list* l, int n){
    int i;
    node* p = l->head;
    for (i = 1; i < n; i++)
        p = p->next;
    return p;

}

// вставка значения после указанного узла, вернуть 0 если успешно
int insert_after(list *l, node *n, int value){
    {
        node* Nnode;
        Nnode = (node*)malloc(sizeof(node));
        Nnode->value = value;
        Nnode->prev = n;
        if (n->next == NULL){
            Nnode->next = NULL;
            n->next = Nnode;
            l->tail = Nnode;
        }
        else{
            Nnode->next = n->next;
            Nnode->next->prev = Nnode;
            n->next = Nnode;
        }
        return 0;
    }
}

// вставка значения перед указанным узлом, вернуть 0 если успешно
int insert_before(list *l, node *n, int value){
    if (n->prev == NULL){
        push_front(l, value);
        return 0;
    }
    node* Nnode;
    Nnode = (node*)malloc(sizeof(node));
    Nnode->next = n;
    Nnode->prev = n->prev;
    Nnode->prev->next = Nnode;
    n->prev = Nnode;
    Nnode->value = value;
    return 0;
}

// удалить первый элемент из списка с указанным значением,
// вернуть 0 если успешно
int remove_first(list *l, int value){
    node* p1 = l->head;
    node* p2;
    while ((p1->value != value)&&(p1->next != NULL)){
        p2 = p1;
        p1 = p1->next;
    }
    if ((p1->next == NULL)&&(p1->value != value))
        return 1;
    else if ((p1->next == NULL)&&(p1->value == value)){
        p2->next = NULL;
        l->tail = p2;
    }
    else if (p1 == l->head) {
        l->head = p1->next;
        p1->next->prev = NULL;
    }
    else{
        p2->next = p1->next;
        p1->next->prev = p2;
    }
    free(p1);
    return 0;
}

// удалить последний элемент из списка с указанным значением,
// вернуть 0 если успешно
int remove_last(list *l, int value) {
    node *p1 = l->tail;
    node *p2;
    while ((p1->value != value) && (p1->prev != NULL)) {
        p2 = p1;
        p1 = p1->prev;
    }
    if ((p1->prev == NULL) && (p1->value != value))
        return 1;
    else if ((p1->prev == NULL) && (p1->value == value)){
        p2->prev = NULL;
        l->head = p2;
    }
    else if (p1 == l->tail){
        l->tail = p1->prev;
        p1->prev->next = NULL;

    }
    else {
        p2->prev = p1->prev;
        p1->prev->next = p2;
    }
    free(p1);
    return 0;
}

// вывести все значения из списка в прямом порядке через пробел,
// после окончания вывода перейти на новую строку
void print(list *l){
    node *p = l->head;
    while (p->next != NULL){
        printf("%d ", p->value);
        p = p->next;
    }
    printf("%d", p->value);
    printf("\n");
}

// вывести все значения из списка в обратном порядке через пробел,
// после окончания вывода перейти на новую строку
void print_invers(list *l){
    node *p = l->tail;
    while (p->prev != NULL){
        printf("%d ", p->value);
        p = p->prev;
    }
    printf("%d", p->value);
    printf("\n");
}


int main() {
    list L;
    node* b;
    int n, i, input, k1, k2, k3;
    init(&L); // задание 1
    (void)scanf("%d", &n);
    for (i = 1; i <= n; i++){ // задание 2
        (void)scanf("%d", &input);
        push_back(&L, input);
    }
    print(&L); // задание 3
    (void)scanf("%d %d %d", &k1, &k2, &k3); // задание 4
    b = find(&L, k1);
    if (b != NULL)
        k1 = 1;
    else
        k1 = 0;
    b = find(&L, k2);
    if (b != NULL)
        k2 = 1;
    else
        k2 = 0;
    b = find(&L, k3);
    if (b != NULL)
        k3 = 1;
    else
        k3 = 0;
    printf("%d %d %d\n", k1, k2, k3);
    (void)scanf("%d", &input); // задание 5
    push_back(&L, input);
    print_invers(&L); // задание 6
    (void)scanf("%d", &input); // задание 7
    push_front(&L, input);
    print(&L); // задание 8
    (void)scanf("%d %d", &n, &input); // задание 9
    b = findNode(&L, n);
    insert_after(&L, b, input);
    print_invers(&L); // задание 10
    (void)scanf("%d %d", &n, &input); // задание 11
    b = findNode(&L, n);
    insert_before(&L, b, input);
    print(&L); // задание 12
    (void)scanf("%d", &input); //задание 13
    remove_first(&L, input);
    print_invers(&L); // задание 14
    (void)scanf("%d", &input); //задание 15
    remove_last(&L, input);
    print(&L); // задание 16
    clean(&L); // задание 17
    return 0;
}