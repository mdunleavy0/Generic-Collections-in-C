#include <stdio.h>
#include <string.h>

#include "../stack.c"


#define SIZE 5


typedef struct Nato {
    char letter;
    char *phonetic;
} Nato;


void *copyNato(void *);
void delNato(void *);
void printNato(void *);


int main(void) {
    Stack stk;
    Nato ordereds[] = {
        {'A', "alpha"},
        {'B', "bravo"},
        {'C', "charlie"},
        {'D', "delta"},
        {'E', "echo"}
    };
    int i;

    puts("CONSTRUCTOR");
    stk = Stack_construct(&copyNato, &delNato);
    stk.print = &printNato;
    List_print(stk);

    puts("PUSH");
    for (i = 0; i < SIZE; i++)
        stk = Stack_push(stk, &ordereds[i]);
    List_print(stk);

    puts("PRINT");
    Stack_print(stk);

    puts("EMPTY");
    stk = Stack_empty(stk);
    stk = Stack_empty(stk);
    List_print(stk);

    puts("HEAD");
    for (i = 0; i < SIZE; i++) {
        stk = Stack_push(stk, &ordereds[i]);
        printf("Head: ");
        printNato(Stack_head(stk));
        putchar('\n');
    }
    putchar('\n');

    puts("POP");
    for (i = 0; i < SIZE; i++)
        stk = Stack_pop(stk);
    List_print(stk);

    puts("DESTRUCTOR");
    stk = Stack_destruct(stk);
    List_print(stk);

    return 0;
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
