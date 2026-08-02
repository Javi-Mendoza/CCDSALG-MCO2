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

LinkedList *llCreate(void);

void llAppend(LinkedList *list, void *data);

void llFree(LinkedList *list);

#endif /* LINKEDLIST_H */
