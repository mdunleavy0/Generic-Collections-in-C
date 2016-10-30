#include <stdio.h>
#include <string.h>

#include "../queue.c"


#define SIZE 5


typedef struct Nato {
    char letter;
    char *phonetic;
} Nato;


void *copyNato(void *);
void delNato(void *);
void printNato(void *);


int main(void) {
    Queue q;
    Nato ordereds[] = {
        {'A', "alpha"},
        {'B', "bravo"},
        {'C', "charlie"},
        {'D', "delta"},
        {'E', "echo"}
    };
    int i;

    puts("CONSTRUCTOR");
    q = Queue_construct(&copyNato, &delNato);
    q.print = &printNato;
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
        printNato(Queue_head(q));
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
