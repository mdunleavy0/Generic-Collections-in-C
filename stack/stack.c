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


// stack meta-structure
typedef List Stack;


// Stack "methods"
Stack Stack_construct(void *(*)(void *), void (*)(void *));
Stack Stack_destruct(Stack);
Stack Stack_empty(Stack);
void *Stack_head(Stack);
Stack Stack_pop(Stack);
void Stack_print(Stack);
Stack Stack_push(Stack, void *);


/*
    Constructor function for Stack.
    Initialises Stack meta-attributes.
    Complexity: O(1).
*/
Stack Stack_construct(void *(*copy)(void *), void (*del)(void *)) {
    return List_construct(copy, del);
}


/*
    Destructor function for Stack.
    Frees all nodes and resets meta-attributes.
    Complexity: O(n).
*/
Stack Stack_destruct(Stack stk) {
    return List_destruct(stk);
}


/*
    Remove and free all nodes in the Stack.
    Complexity: O(n).
*/
Stack Stack_empty(Stack stk) {
    return List_empty(stk);
}


/*
    Return the element located at the head of the Stack.
    Complexity: O(1).
*/
void *Stack_head(Stack stk) {
    return List_head(stk);
}


/*
    Remove and free one node from the front of the Stack.
    Complexity: O(1).
*/
Stack Stack_pop(Stack stk) {
    return List_pop(stk);
}


/*
    Print Stack to stdout.
    Prints meta-attributes as well as all elements.
    A print function is required to define how to print individual elements.
    Complexity: O(n).
*/
void Stack_print(Stack stk) {
    printf("Length: %zu,\n", stk.length);

    printf("Methods: {\n");

    printf("  Copy: ");
    (stk.copy) ? printf("Defined") : printf("Undefined");
    printf(",\n");

    printf("  Delete: ");
    (stk.del) ? printf("Defined") : printf("Undefined");
    printf(",\n");

    printf("  Print: ");
    (stk.print) ? printf("Defined") : printf("Undefined");
    printf("\n");

    printf("},\n");

    printf("Head: ");
    if (stk.head) {
        if (stk.print)
            (*stk.print)(stk.head->data);
        else
            printf("Unknown - print method undefined");
    }
    else
        printf("None");
    printf("\n\n");
}


/*
    Prepend one element to the front of the Stack.
    Complexity: O(1).
*/
Stack Stack_push(Stack stk, void *elem) {
    return List_prepend(stk, elem);
}
