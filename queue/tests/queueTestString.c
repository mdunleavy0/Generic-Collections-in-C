#include <stdio.h>
#include <string.h>

#include "../queue.c"


#define SIZE 5


void *copyStr(void *);
void delStr(void *);
void printStr(void *);


int main(void) {
    Queue q;
    char ordereds[][4] = {"abc", "def", "ghi", "jkl", "mno"};
    int i;

    puts("CONSTRUCTOR");
    q = Queue_construct(&copyStr, &delStr);
    q.print = &printStr;
    List_print(q);

    puts("ENQUEUE");
    for (i = 0; i < SIZE; i++)
        q = Queue_enqueue(q, &ordereds[i]);
    List_print(q);

    puts("PRINT");
    Queue_print(q);

    puts("EMPTY");
    q = Queue_empty(q);
    q = Queue_empty(q);
    List_print(q);

    puts("HEAD");
    for (i = 0; i < SIZE; i++) {
        q = Queue_enqueue(q, &ordereds[i]);
        printf("Head: ");
        printStr(Queue_head(q));
        putchar('\n');
    }
    putchar('\n');

    puts("DEQUEUE");
    for (i = 0; i < SIZE; i++)
        q = Queue_dequeue(q);
    List_print(q);

    puts("DESTRUCTOR");
    q = Queue_destruct(q);
    List_print(q);

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
