#include "list.h"

/*doubly linked list*/

list_t *init(void)
{
    list_t *list = malloc(sizeof(list_t));
    if (list == NULL)
    {
        printf("Failed to allocate memory to create a collection\n");
        return NULL;
    }
    list->size = 0;
    list->head = list->tail = NULL;

    return list;
}

bool isEmpty(list_t *list)
{
    return getSize(list) == 0;
}

size_t getSize(list_t *list)
{
    return list->size;
}

void push_front(list_t *list, void *data)
{
    list_node_t *node = malloc(sizeof(list_node_t));
    if (!node)
    {
        perror("Error allocating memory for a list node\n");
        return;
    }

    node->data = data;
    node->pPrevious = NULL;

    if (list->head != NULL)
    {
        node->pNext = list->head;
        list->head->pPrevious = node;
        list->head = node;
    }
    else
    {
        list->head = list->tail = node;
    }
    list->size += 1;
}

void push_back(list_t *list, void *data)
{
    if (list->head == NULL)
    {
        push_front(list, data);
        return;
    }

    list_node_t *node = malloc(sizeof(list_node_t));
    if (!node)
    {
        perror("Error allocating memory for a list node\n");
        return;
    }

    node->data = data;
    node->pNext = NULL;
    node->pPrevious = NULL;

    if (list->tail != NULL)
    {
        list->tail->pNext = node;
        node->pPrevious = list->tail;
        list->tail = node;
    }
    else
    {
        list->head = node;
        list->tail = node;
    }
    list->size += 1;
}

void pop_front(list_t *list)
{
    if (list->head == NULL || list->tail == NULL)
    {
        printf("The collection is empty! The first element could not be deleted\n");
        return;
    }

    list_node_t *node = list->head;
    if (node->pNext != NULL)
    {
        list->head = node->pNext;
        list->head->pPrevious = NULL;
    }
    else
    {
        list->head = NULL;
        list->tail = NULL;
    }

    free(node);
    list->size -= 1;
}

void pop_back(list_t *list)
{
    if (list->head == NULL || list->tail == NULL)
    {
        printf("The collection is empty! The last element could not be deleted\n");
        return;
    }
    list_node_t *node = list->tail;
    if (node->pPrevious != NULL)
    {
        list->tail = node->pPrevious;
        list->tail->pNext = NULL;
    }
    else
    { 
        list->head = NULL;
        list->tail = NULL;
    }

    free(node);
    list->size -= 1;
}

void clearList(list_t *list)
{
    while (list->size)
    {
        pop_front(list);
    }
}

void insert(list_t *list, void *data, int index)
{
    if (list->size < index)
    {
        printf("An element with such an index does not exist in the collection!\n");
        return;
    }
    if (index == 0)
    {
        push_front(list, data);
        return;
    }
    //
    list_node_t *newNode = malloc(sizeof(list_node_t));

    if (!newNode)
    {
        perror("Error allocating memory for a list node");
        return;
    }

    list_node_t *previous = list->head;
    for (int i = 0; i < index - 1; ++i)
        previous = previous->pNext;
    //
    newNode->data = data;
    newNode->pNext = previous->pNext;
    newNode->pPrevious = previous;
    previous->pNext->pPrevious = newNode;

    previous->pNext = newNode;

    list->size += 1;
    printf("Added value to the collection: %d\n", *(int *)newNode->data);
}

void *At(list_t *list, int index)
{
    if (!list->size)
    {
        printf("The collection is empty!\n");
        return NULL;
    }

    if (index > list->size)
    {
        printf("The index of the element [%d] cannot exceed the number of elements in the collection!\n", index);
        return NULL;
    }

    list_node_t *prev = list->head;

    int count = 0;
    while (prev)
    {
        if (count == index)
        {
            return prev->data;
        }
        prev = prev->pNext;
        count++;
    }

    return NULL;
}

void *getFromFront(list_t *list)
{
    return isEmpty(list) ? NULL : list->head->data;
}

void *getFromBack(list_t *list)
{
    return isEmpty(list) ? NULL : list->tail->data;
}

void print_list(list_t *list)
{
    if (isEmpty(list))
    {
        printf("The collection is empty!");
        return;
    }
    printf("Contents of the collection: ");
    list_node_t *current = list->head;

    while (current)
    {
        printf("%d ", *(int *)current->data);
        current = current->pNext;
    }
}
int find_data(list_t *list, void *fdata)
{

    if (isEmpty(list))
    {
        perror("The collection is empty! The element was not found. Index not returned!\n");
        return -1;
    }

    list_node_t *current = list->head;
    int ftemp = *(int *)fdata;
    int count = 0;
    int tmp;
    //////
    while (current)
    {

        tmp = *(int *)current->data;  //there is have problem with gcc 11.4.0 in function
        if (tmp == ftemp)
        {
            return count;
        }
        current = current->pNext;
        count++;
    }

    return -1;
}

