#include <stdlib.h>
#include "linkedlist.h"

LinkedList *llCreate(void)
{
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void llAppend(LinkedList *list, void *data)
{
    LLNode *node = (LLNode *)malloc(sizeof(LLNode));
    node->data = data;
    node->next = NULL;

    if (list->tail == NULL)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        list->tail->next = node;
        list->tail = node;
    }
    list->size++;
}

void llFree(LinkedList *list)
{
    LLNode *cur = list->head;
    while (cur != NULL)
    {
        LLNode *next = cur->next;
        free(cur);
        cur = next;
    }
    free(list);
}
