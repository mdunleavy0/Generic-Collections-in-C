#include <stdio.h>

#include "../linkedList.c"


#define SIZE 5


int compareInt(void *, void *);
void *copyInt(void *);
void delInt(void *);
void printInt(void *);


int main(void) {
    List ls;
    int indices[] = {0, 0, 2, 2, 3};
    int unordereds[] = {1, 0, 4, 2, 3};
    int i;
    int x;
    int z;

    puts("CONSTRUCTOR");
    ls = List_construct(&copyInt, &delInt);
    ls.print = &printInt;
    List_print(ls);

    puts("PREPEND");
    for (i = 0; i < SIZE; i++)
        ls = List_prepend(ls, &i);
    List_print(ls);

    puts("GET");
    printf("Data: {");
    for (i = 0; i < SIZE - 1; i++) {
        printInt(List_get(ls, i));
        printf(", ");
    }
    printInt(List_get(ls, SIZE - 1));
    printf("}\n\n");

    puts("EMPTY");
    ls = List_empty(ls);
    ls = List_empty(ls);
    List_print(ls);

    puts("APPEND");
    for (i = 0; i < SIZE; i++)
        ls = List_append(ls, &i);
    List_print(ls);

    puts("POP HEAD");
    for (i = 0; i < SIZE; i++)
        ls = List_pop(ls);
    List_print(ls);

    puts("INSERT");
    for (i = 0; i < SIZE; i++)
        ls = List_insert(ls, indices[i], &unordereds[i]);
    List_print(ls);

    puts("REMOVE");
    for (i = SIZE - 1; i >= 0; i--)
        ls = List_remove(ls, indices[i]);
    List_print(ls);

    puts("INSERT IN ORDER");
    ls.compare = &compareInt;
    for (i = 0; i < SIZE; i++)
        ls = List_insertInOrder(ls, &unordereds[i]);
    List_print(ls);

    puts("POP TAIL");
    for (i = 0; i < SIZE; i++)
        ls = List_popTail(ls);
    List_print(ls);

    puts("SET");
    z = -1;
    for (i = 0; i < SIZE; i++)
        ls = List_append(ls, &z);
    for (i = 0; i < SIZE; i++)
        ls = List_set(ls, i, &i);
    List_print(ls);

    puts("CONTAINS");
    for (i = -1; i < SIZE + 1; i++) {
        if (List_contains(ls, &i))
            printf("List contains %d\n", i);
        else
            printf("List does not contain %d\n", i);
    }
    putchar('\n');

    puts("FIND");
    for (i = -1; i < SIZE + 1; i++) {
        x = List_find(ls, &i);
        if (x != ls.length)
            printf("%d found at index %d\n", i, x);
        else
            printf("%d not found\n", i);
    }
    putchar('\n');

    puts("SORT");
    ls = List_empty(ls);
    for (i = 0; i < SIZE; i++)
        ls = List_append(ls, &unordereds[i]);
    ls = List_sort(ls);
    List_print(ls);

    puts("TAIL");
    ls = List_empty(ls);
    for (i = 0; i < SIZE; i++) {
        ls = List_append(ls, &i);
        printf("Tail: ");
        printInt(List_tail(ls));
        putchar('\n');
    }
    putchar('\n');

    puts("HEAD");
    for (i = 0; i < SIZE; i++) {
        printf("Tail: ");
        printInt(List_head(ls));
        putchar('\n');
        ls = List_pop(ls);
    }
    putchar('\n');

    puts("DESTRUCTOR");
    ls = List_destruct(ls);
    List_print(ls);

    return 0;
}


int compareInt(void *a, void *b) {
    int a1 = *((int *) a);
    int b1 = *((int *) b);
    return a1 - b1;
}


void *copyInt(void *ptr) {
    int n = *((int *) ptr);
    int *cp = (int *) malloc(sizeof(int));
    *cp = n;
    return (void *) cp;
}


void delInt(void *ptr) {
    free(ptr);
}


void printInt(void *ptr) {
    int n = *((int *) ptr);
    printf("%d", n);
}
