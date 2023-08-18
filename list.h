#ifndef _LIST_H
#define _LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node
{
    struct node *pNext;
    struct node *pPrevious;
    void *data;

} list_node_t;

typedef struct list
{
    list_node_t *head;
    list_node_t *tail;
    size_t size;
} list_t;

list_t *init(void);
bool isEmpty(list_t *list);
size_t getSize(list_t *list);
void push_front(list_t *list, void *data);
void push_back(list_t *list, void *data);
void pop_front(list_t *list);
void pop_back(list_t *list);
void clearList(list_t *list);
void insert(list_t *list, void *data, int index);
void *At(list_t *list, int index);
void *getFromFront(list_t *list);
void *getFromBack(list_t *list);
void print_list(list_t *list);
int find_data(list_t *list, void *fdata);

#endif