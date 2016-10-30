#include <stdio.h>

#include "../queue.c"


#define SIZE 5


void *copyInt(void *);
void delInt(void *);
void printInt(void *);


int main(void) {
    Queue q;
    int i;

    puts("CONSTRUCTOR");
    q = Queue_construct(&copyInt, &delInt);
    q.print = &printInt;
    List_print(q);

    puts("ENQUEUE");
    for (i = 0; i < SIZE; i++)
        q = Queue_enqueue(q, &i);
    List_print(q);

    puts("PRINT");
    Queue_print(q);

    puts("EMPTY");
    q = Queue_empty(q);
    q = Queue_empty(q);
    List_print(q);

    puts("HEAD");
    for (i = 0; i < SIZE; i++) {
        q = Queue_enqueue(q, &i);
        printf("Head: ");
        printInt(Queue_head(q));
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
