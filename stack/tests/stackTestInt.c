#include <stdio.h>

#include "../stack.c"


#define SIZE 5


void *copyInt(void *);
void delInt(void *);
void printInt(void *);


int main(void) {
    Stack stk;
    int i;

    puts("CONSTRUCTOR");
    stk = Stack_construct(&copyInt, &delInt);
    stk.print = &printInt;
    List_print(stk);

    puts("PUSH");
    for (i = 0; i < SIZE; i++)
        stk = Stack_push(stk, &i);
    List_print(stk);

    puts("PRINT");
    Stack_print(stk);

    puts("EMPTY");
    stk = Stack_empty(stk);
    stk = Stack_empty(stk);
    List_print(stk);

    puts("HEAD");
    for (i = 0; i < SIZE; i++) {
        stk = Stack_push(stk, &i);
        printf("Head: ");
        printInt(Stack_head(stk));
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
