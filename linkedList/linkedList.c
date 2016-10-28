#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


/*
    Exit error codes:
    -1  Index out of bounds
    -2  Member function not defined
    -3  Popping from empty list
*/


typedef struct ListNode {
    void *data;
    struct ListNode *next;
} ListNode;


typedef struct List {
    ListNode *head, *tail;
    size_t length;
    int (*compare)(void *, void *);
    void *(*copy)(void *);
    void (*del)(void *);
    void (*print)(void *);
} List;


List List_construct(void *(*)(void *), void (*)(void *));
List List_destruct(List);
List List_append(List, void *);
bool List_contains(List, void *);
List List_empty(List);
size_t List_find(List, void *);
void *List_get(List, size_t);
List List_insert(List, size_t, void *);
List List_insertInOrder(List, void *);
List List_pop(List);
List List_popTail(List);
List List_prepend(List, void *);
void List_print(List);
void List_printData(List);
List List_remove(List, size_t);
List List_set(List, size_t, void *);
List List_sort(List);


List List_construct(void *(*copy)(void *), void (*del)(void *)) {
    List ls = {0};
    ls.copy = copy;
    ls.del = del;
    return ls;
}


List List_destruct(List ls) {
    ls = List_empty(ls);

    ls.compare = NULL;
    ls.copy = NULL;
    ls.del = NULL;
    ls.print = NULL;

    return ls;
}


List List_append(List ls, void *elem) {
    if (ls.length) {
        ListNode *new = (ListNode *) malloc(sizeof(ListNode));
        new->data = (*ls.copy)(elem);
        new->next = NULL;

        ls.tail->next = new;
        ls.tail = new;

        ls.length++;
        return ls;
    }

    else
        return List_prepend(ls, elem);
}


bool List_contains(List ls, void *elem) {
    if (ls.compare) {
        ListNode *cursor;

        for (
            cursor = ls.head;
            cursor != NULL && (*ls.compare)(elem, cursor->data) != 0;
            cursor = cursor->next
        );

        return (bool) cursor;
    }

    else {
        fprintf(
            stderr,
            "Error: Dependent member function not defined: "
            "int (*compare)(void *, void *)"
        );
        exit(-2);
    }
}


List List_empty(List ls) {
    ListNode *cursor, *next;

    for (cursor = ls.head; cursor != NULL; cursor = next) {
        next = cursor->next;
        (*ls.del)(cursor->data);
        free(cursor);
    }

    ls.head = NULL;
    ls.tail = NULL;
    ls.length = 0;

    return ls;
}


size_t List_find(List ls, void *elem) {
    if (ls.compare) {
        ListNode *cursor;
        size_t i;

        for (
            cursor = ls.head, i = 0;
            cursor != NULL && (*ls.compare)(elem, cursor->data) != 0;
            cursor = cursor->next, i++
        );

        return i;
    }

    else {
        fprintf(
            stderr,
            "Error: Dependent member function not defined: "
            "int (*compare)(void *, void *)"
        );
        exit(-2);
    }
}


void *List_get(List ls, size_t idx) {
    if (idx < ls.length) {
        ListNode *cursor;
        size_t i;

        for (
            cursor = ls.head, i = 0;
            i < idx;
            cursor = cursor->next, i++
        );

        return cursor->data;
    }

    else {
        fprintf(
            stderr,
            "Error: Index %zu out of bounds in list of length %zu.\n",
            idx, ls.length
        );
        exit(-1);
    }
}


List List_insert(List ls, size_t idx, void *elem) {
    if (idx == 0)
        return List_prepend(ls, elem);

    else if (idx == ls.length)
        return List_append(ls, elem);

    else if (idx < ls.length) {
        ListNode *prev, *cursor;
        size_t i;

        ListNode *new = (ListNode *) malloc(sizeof(ListNode));
        new->data = (*ls.copy)(elem);

        for (
            i = 1, prev = ls.head, cursor = prev->next;
            i < idx;
            i++, prev = cursor, cursor = cursor->next
        );

        prev->next = new;
        new->next = cursor;
        ls.length++;
        return ls;
    }

    else {
        fprintf(
            stderr,
            "Error: Index %zu out of bounds in list of length %zu.\n",
            idx, ls.length
        );
        exit(-1);
    }
}


List List_insertInOrder(List ls, void *elem) {
    if (ls.compare) {
        if (ls.length == 0 || (*ls.compare)(elem, ls.head->data) < 0)
            return List_prepend(ls, elem);

        else if ((*ls.compare)(elem, ls.tail->data) >= 0)
            return List_append(ls, elem);

        else {
            ListNode *prev, *cursor;

            ListNode *new = (ListNode *) malloc(sizeof(ListNode));
            new->data = (*ls.copy)(elem);

            for (
                prev = ls.head, cursor = prev->next;
                (*ls.compare)(elem, cursor->data) >= 0;
                prev = cursor, cursor = cursor->next
            );

            prev->next = new;
            new->next = cursor;
            ls.length++;
            return ls;
        }
    }

    else {
        fprintf(
            stderr,
            "Error: Dependent member function not defined: "
            "int (*compare)(void *, void *)"
        );
        exit(-2);
    }
}


List List_pop(List ls) {
    if (ls.length) {
        ListNode *next = ls.head->next;

        (*ls.del)(ls.head->data);
        free(ls.head);

        ls.head = next;
        if (ls.length == 1)
            ls.tail = next;

        ls.length--;
        return ls;
    }

    else {
        fprintf(
            stderr,
            "Error: Cannot pop elements from an already empty list."
        );
        exit(-3);
    }
}


List List_popTail(List ls) {
    if (ls.length)
        return List_remove(ls, ls.length - 1);

    else {
        fprintf(
            stderr,
            "Error: Cannot pop elements from an already empty list."
        );
        exit(-3);
    }
}


List List_prepend(List ls, void *elem) {
    ListNode *new = (ListNode *) malloc(sizeof(ListNode));
    new->data = (*ls.copy)(elem);
    new->next = ls.head;

    ls.head = new;
    if (ls.length == 0)
        ls.tail = new;

    ls.length++;
    return ls;
}


void List_print(List ls) {
    printf("Length: %zu,\n", ls.length);

    printf("Methods: {\n");

    printf("  Copy: ");
    (ls.copy) ? printf("Defined") : printf("Undefined");
    printf(",\n");

    printf("  Delete: ");
    (ls.del) ? printf("Defined") : printf("Undefined");
    printf(",\n");

    printf("  Print: ");
    (ls.print) ? printf("Defined") : printf("Undefined");
    printf(",\n");

    printf("  Compare: ");
    (ls.compare) ? printf("Defined") : printf("Undefined");
    printf("\n");

    printf("},\n");

    printf("Head: ");
    if (ls.head) {
        if (ls.print)
            (*ls.print)(ls.head->data);
        else
            printf("Unknown - print method undefined");
    }
    else {
        printf("None");
    }
    printf(",\n");

    printf("Tail: ");
    if (ls.tail) {
        if (ls.print)
            (*ls.print)(ls.tail->data);
        else
            printf("Unknown - print method undefined");
    }
    else {
        printf("None");
    }
    printf(",\n");

    printf("Data: ");
    List_printData(ls);

    printf("\n\n");
}


void List_printData(List ls) {
    if (ls.print) {
        printf("{");

        ListNode *cursor;
        if (ls.head) {
            for (cursor = ls.head; cursor->next != NULL; cursor = cursor->next) {
                (*ls.print)(cursor->data);
                printf(", ");
            }

            (*ls.print)(cursor->data);
        }

        printf("}");
    }
    else {
        printf("Unknown - print method undefined");
    }
}


List List_remove(List ls, size_t idx) {
    if (idx == 0)
        return List_pop(ls);


    else if (idx < ls.length) {
        ListNode *prev, *cursor;
        size_t i;

        for (
            i = 1, prev = ls.head, cursor = prev->next;
            i < idx;
            i++, prev = cursor, cursor = cursor->next
        );

        prev->next = cursor->next;
        if (ls.tail == cursor)
            ls.tail = prev;

        (*ls.del)(cursor->data);
        free(cursor);

        ls.length--;
        return ls;
    }

    else {
        fprintf(
            stderr,
            "Error: Index %zu out of bounds in list of length %zu.\n",
            idx, ls.length
        );
        exit(-1);
    }
}


List List_set(List ls, size_t idx, void *elem) {
    if (idx < ls.length) {
        ListNode *cursor;
        size_t i;

        for (
            i = 0, cursor = ls.head;
            i < idx;
            i++, cursor = cursor->next
        );

        (*ls.del)(cursor->data);
        cursor->data = (*ls.copy)(elem);

        return ls;
    }

    else {
        fprintf(
            stderr,
            "Error: Index %zu out of bounds in list of length %zu.\n",
            idx, ls.length
        );
        exit(-1);
    }
}


List List_sort(List ls) {
    if (ls.compare) {
        ListNode *left, *right;
        ListNode dummyHead;
        size_t i, j, k;

        for (size_t splitSize = 1; splitSize <= ls.length; splitSize *= 2) {
            right = ls.head;

            ls.head = &dummyHead;
            ls.tail = &dummyHead;

            for (i = 0; i < ls.length; i += 2 * splitSize) {

                left = right;
                for (
                    k = 0;
                    right != NULL && k < splitSize;
                    right = right->next, k++
                );

                j = 0;
                k = 0;

                while (
                    left != NULL && j < splitSize &&
                    right != NULL && k < splitSize
                ) {
                    if ((*ls.compare)(left->data, right->data) <= 0) {
                        ls.tail->next = left;
                        ls.tail = left;
                        left = left->next;
                        j++;
                    }
                    else {
                        ls.tail->next = right;
                        ls.tail = right;
                        right = right->next;
                        k++;
                    }
                }

                while (left != NULL && j < splitSize) {
                    ls.tail->next = left;
                    ls.tail = left;
                    left = left->next;
                    j++;
                }

                while (right != NULL && k < splitSize) {
                    ls.tail->next = right;
                    ls.tail = right;
                    right = right->next;
                    k++;
                }
            }

            ls.head = ls.head->next;
            ls.tail->next = NULL;
        }

        return ls;
    }

    else {
        fprintf(
            stderr,
            "Error: Dependent member function not defined: "
            "int (*compare)(void *, void *)"
        );
        exit(-2);
    }
}
