#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../linkedList/linkedList.c"

/*
    Exit error codes:
    -1  Index out of bounds
    -2  Member function not defined
    -3  Popping from empty list
*/


// queue meta-structure
typedef List Queue;


// Queue "methods"
Queue Queue_construct(void *(*)(void *), void (*)(void *));
Queue Queue_dequeue(Queue);
Queue Queue_destruct(Queue);
Queue Queue_empty(Queue);
Queue Queue_enqueue(Queue, void *);
void *Queue_head(Queue);
void Queue_print(Queue);


/*
    Constructor function for Queue.
    Initialises Queue meta-attributes.
    Complexity: O(1).
*/
Queue Queue_construct(void *(*copy)(void *), void (*del)(void *)) {
    return List_construct(copy, del);
}


/*
    Remove and free one node from the front of the Queue.
    Complexity: O(1).
*/
Queue Queue_dequeue(Queue q) {
    return List_pop(q);
}


/*
    Destructor function for Queue.
    Frees all nodes and resets meta-attributes.
    Complexity: O(n).
*/
Queue Queue_destruct(Queue q) {
    return List_destruct(q);
}


/*
    Remove and free all nodes in the Queue.
    Complexity: O(n).
*/
Queue Queue_empty(Queue q) {
    return List_empty(q);
}


/*
    Append one element to the back of the Queue.
    Complexity: O(1).
*/
Queue Queue_enqueue(Queue q, void *elem) {
    return List_append(q, elem);
}


/*
    Return the element located at the head of the Queue.
    Complexity: O(1).
*/
void *Queue_head(Queue q) {
    return List_head(q);
}


/*
    Print Queue to stdout.
    Prints meta-attributes as well as all elements.
    A print function is required to define how to print individual elements.
    Complexity: O(n).
*/
void Queue_print(Queue q) {
    printf("Length: %zu,\n", q.length);

    printf("Methods: {\n");

    printf("  Copy: ");
    (q.copy) ? printf("Defined") : printf("Undefined");
    printf(",\n");

    printf("  Delete: ");
    (q.del) ? printf("Defined") : printf("Undefined");
    printf(",\n");

    printf("  Print: ");
    (q.print) ? printf("Defined") : printf("Undefined");
    printf("\n");

    printf("},\n");

    printf("Head: ");
    if (q.head) {
        if (q.print)
            (*q.print)(q.head->data);
        else
            printf("Unknown - print method undefined");
    }
    else {
        printf("None");
    }
    printf("\n\n");
}
