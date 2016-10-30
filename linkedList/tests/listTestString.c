#include <stdio.h>
#include <string.h>

#include "../linkedList.c"


#define SIZE 5


int compareStr(void *, void *);
void *copyStr(void *);
void delStr(void *);
void printStr(void *);


int main(void) {
    List ls;
    int indices[] = {0, 0, 2, 2, 3};
    char ordereds[][4] = {"abc", "def", "ghi", "jkl", "mno"};
    char unordereds[][4] = {"def", "abc", "mno", "ghi", "jkl"};
    int i;
    int x;
    char z[] = "zzz";

    puts("CONSTRUCTOR");
    ls = List_construct(&copyStr, &delStr);
    ls.print = &printStr;
    List_print(ls);

    puts("PREPEND");
    for (i = 0; i < SIZE; i++)
        ls = List_prepend(ls, &ordereds[i]);
    List_print(ls);

    puts("GET");
    printf("Data: {");
    for (i = 0; i < SIZE - 1; i++) {
        printStr(List_get(ls, i));
        printf(", ");
    }
    printStr(List_get(ls, SIZE - 1));
    printf("}\n\n");

    puts("EMPTY");
    ls = List_empty(ls);
    ls = List_empty(ls);
    List_print(ls);

    puts("APPEND");
    for (i = 0; i < SIZE; i++)
        ls = List_append(ls, &ordereds[i]);
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
    ls.compare = &compareStr;
    for (i = 0; i < SIZE; i++)
        ls = List_insertInOrder(ls, &unordereds[i]);
    List_print(ls);

    puts("POP TAIL");
    for (i = 0; i < SIZE; i++)
        ls = List_popTail(ls);
    List_print(ls);

    puts("SET");
    for (i = 0; i < SIZE; i++)
        ls = List_append(ls, z);
    for (i = 0; i < SIZE; i++)
        ls = List_set(ls, i, &ordereds[i]);
    List_print(ls);

    puts("CONTAINS");
    for (i = 0; i < SIZE; i++) {
        if (List_contains(ls, &ordereds[i]))
            printf("List contains %s\n", ordereds[i]);
        else
            printf("List does not contain %s\n", ordereds[i]);
    }
    if (List_contains(ls, z))
        printf("List contains %s\n", z);
    else
        printf("List does not contain %s\n", z);
    putchar('\n');

    puts("FIND");
    for (i = 0; i < SIZE; i++) {
        x = List_find(ls, &ordereds[i]);
        if (x != ls.length)
            printf("%s found at index %d\n", ordereds[i], x);
        else
            printf("%s not found\n", ordereds[i]);
    }
    x = List_find(ls, z);
    if (x != ls.length)
        printf("%s found at index %d\n", z, x);
    else
        printf("%s not found\n", z);
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
        ls = List_append(ls, &ordereds[i]);
        printf("Tail: ");
        printStr(List_tail(ls));
        putchar('\n');
    }
    putchar('\n');

    puts("HEAD");
    for (i = 0; i < SIZE; i++) {
        printf("Head: ");
        printStr(List_head(ls));
        putchar('\n');
        ls = List_pop(ls);
    }
    putchar('\n');

    puts("DESTRUCTOR");
    ls = List_destruct(ls);
    List_print(ls);

    return 0;
}


int compareStr(void *a, void *b) {
    return strcmp(a, b);
}


void *copyStr(void *ptr) {
    return strcpy(malloc(strlen(ptr + 1)), ptr);
}


void delStr(void *ptr) {
    free(ptr);
}


void printStr(void *ptr) {
    printf("\"%s\"", ptr);
}
