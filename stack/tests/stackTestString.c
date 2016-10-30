#include <stdio.h>
#include <string.h>

#include "../stack.c"


#define SIZE 5


void *copyStr(void *);
void delStr(void *);
void printStr(void *);


int main(void) {
    Stack stk;
    char ordereds[][4] = {"abc", "def", "ghi", "jkl", "mno"};
    int i;

    puts("CONSTRUCTOR");
    stk = Stack_construct(&copyStr, &delStr);
    stk.print = &printStr;
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
        printStr(Stack_head(stk));
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


void *copyStr(void *ptr) {
    return strcpy(malloc(strlen(ptr + 1)), ptr);
}


void delStr(void *ptr) {
    free(ptr);
}


void printStr(void *ptr) {
    printf("\"%s\"", ptr);
}
