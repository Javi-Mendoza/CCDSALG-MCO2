/*
 * linkedlist.h
 * A basic singly linked list. This is what backs the graph's vertex
 * list and each vertex's adjacency (edge) list.
 *
 * It only stores generic pointers (void*) and doesn't know how to
 * free whatever those pointers point to -- that's the caller's job
 * (see graphFree in graph.c), so llFree only frees the list's own
 * nodes, nothing else.
 */
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct LLNode {
    void *data;
    struct LLNode *next;
} LLNode;

typedef struct LinkedList {
    LLNode *head;
    LLNode *tail;
    int size;
} LinkedList;

/* Creates an empty linked list. */
LinkedList *llCreate(void);

/* Inserts data at the end of the list. */
void llAppend(LinkedList *list, void *data);

/* Frees every node of the list (not the data each node points to). */
void llFree(LinkedList *list);

#endif /* LINKEDLIST_H */
