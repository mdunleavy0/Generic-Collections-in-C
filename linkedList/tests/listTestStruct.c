#include <stdio.h>
#include <string.h>

#include "../linkedList.c"


#define SIZE 5


typedef struct Nato {
    char letter;
    char *phonetic;
} Nato;


int compareNato(void *, void *);
void *copyNato(void *);
void delNato(void *);
void printNato(void *);


int main(void) {
    List ls;
    int indices[] = {0, 0, 2, 2, 3};
    Nato ordereds[] = {
        {'A', "alpha"},
        {'B', "bravo"},
        {'C', "charlie"},
        {'D', "delta"},
        {'E', "echo"}
    };
    Nato unordereds[] = {
        {'B', "bravo"},
        {'A', "alpha"},
        {'E', "echo"},
        {'C', "charlie"},
        {'D', "delta"}
    };
    int i;
    int x;
    Nato z;
    char zPh[20];
    z.phonetic = zPh;

    puts("CONSTRUCTOR");
    ls = List_construct(&copyNato, &delNato);
    ls.print = &printNato;
    List_print(ls);

    puts("PREPEND");
    for (i = 0; i < SIZE; i++)
        ls = List_prepend(ls, &ordereds[i]);
    List_print(ls);

    puts("GET");
    printf("Data: {");
    for (i = 0; i < SIZE - 1; i++) {
        printNato(List_get(ls, i));
        printf(", ");
    }
    printNato(List_get(ls, SIZE - 1));
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
    ls.compare = &compareNato;
    for (i = 0; i < SIZE; i++)
        ls = List_insertInOrder(ls, &unordereds[i]);
    List_print(ls);

    puts("POP TAIL");
    for (i = 0; i < SIZE; i++)
        ls = List_popTail(ls);
    List_print(ls);

    puts("SET");
    z.letter = 'Z';
    strcpy(z.phonetic, "zulu");
    for (i = 0; i < SIZE; i++)
        ls = List_append(ls, &z);
    for (i = 0; i < SIZE; i++)
        ls = List_set(ls, i, &ordereds[i]);
    List_print(ls);

    puts("CONTAINS");
    for (i = 0; i < SIZE; i++) {
        if (List_contains(ls, &ordereds[i]))
            printf(
                "List contains (%c, %s)\n",
                ordereds[i].letter, ordereds[i].phonetic
            );
        else
            printf(
                "List does not contain (%c, %s)\n",
                ordereds[i].letter, ordereds[i].phonetic
            );
    }
    if (List_contains(ls, &z))
        printf("List contains (%c, %s)\n", z.letter, z.phonetic);
    else
        printf("List does not contain (%c, %s)\n", z.letter, z.phonetic);
    putchar('\n');

    puts("FIND");
    for (i = 0; i < SIZE; i++) {
        x = List_find(ls, &ordereds[i]);
        if (x != ls.length)
            printf(
                "(%c, %s) found at index %d\n",
                ordereds[i].letter, ordereds[i].phonetic, x
            );
        else
            printf(
                "(%c, %s) not found\n",
                ordereds[i].letter, ordereds[i].phonetic
            );
    }
    x = List_find(ls, &z);
    if (x != ls.length)
        printf("(%c, %s) found at index %d\n", z.letter, z.phonetic, x);
    else
        printf("(%c, %s) not found\n", z.letter, z.phonetic);
    putchar('\n');

    puts("SORT");
    ls = List_empty(ls);
    z.letter = 'Z';
    for (i = 0; i < SIZE; i++) {
        sprintf(z.phonetic, "zulu%d", i);
        ls = List_append(ls, &z);
        ls = List_append(ls, &unordereds[i]);
    }
    ls = List_sort(ls);
    List_print(ls);

    puts("DESTRUCTOR");
    ls = List_destruct(ls);
    List_print(ls);

    return 0;
}


int compareNato(void *a, void *b) {
    char l1 = ((Nato *) a)->letter;
    char l2 = ((Nato *) b)->letter;
    return l1 - l2;
}


void *copyNato(void *ptr) {
    Nato *orig, *copy;

    orig = (Nato *) ptr;
    copy = (Nato *) malloc(sizeof(Nato));

    copy->letter = orig->letter;
    copy->phonetic = strcpy(malloc(strlen(orig->phonetic + 1)), orig->phonetic);

    return copy;
}


void delNato(void *ptr) {
    Nato *n = (Nato *) ptr;
    free(n->phonetic);
    free(ptr);
}


void printNato(void *ptr) {
    Nato *n = (Nato *) ptr;
    printf("(%c, %s)", n->letter, n->phonetic);
}
