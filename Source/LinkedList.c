#include "LinkedList.h"
#include <stdlib.h>

/*
 * Insert node into the front of list
 */
void insertNodeInFront(FoodPlace **list, FoodPlace *node)
{
    if(node == NULL)
        return;

    node->next = *list;
    node->prev = NULL;

    if(*list != NULL)
        (*list)->prev=node;

    *list = node;
    return;
}

/*
 * Insert node in the back of list
 */
void insertNodeInBack(FoodPlace **list, FoodPlace *node)
{
    FoodPlace *tmp = *list;
    FoodPlace *prev = NULL;
    if(node == NULL)
        return;

    //List is empty
    if(tmp == NULL)
    {
        node->prev = NULL;
        node->next = NULL;
        *list = node;
    }

    while(tmp != NULL)
    {
        prev = tmp;
        tmp=tmp->next;
    }

    if(prev != NULL)
        prev->next = node;

    node->prev = prev;
    node->next = NULL;
}

/*
 * Remove node from head. Note head is double pointer only if node if the first node
 */
void removeNode(FoodPlace **head, FoodPlace *node)
{
    FoodPlace *tmp;

    if(node == NULL)
        return;

    if(*head == node)
    {
        *head = node->next;
        //If node was not both the first and last item in the list (ie. only item), set the head's prev to NULL
        if(*head != NULL)
            (*head)->prev = NULL;
        return;
    }

    tmp = node->prev;
    if(tmp != NULL)
        tmp->next = node->next;

    tmp = node->next;
    if(tmp != NULL)
        tmp->prev = node->prev;
}

/*
 * return FoodPlace that is pos in foodList
 */
FoodPlace *getNodeFromList(FoodPlace **foodList, int pos)
{
    int count=0;
    FoodPlace *node = *foodList;
    while(node != NULL)
    {
        if(count++==pos)
            return node;
        
        node = node->next;
    }

    return NULL;
}

/*
 *
 */
void mergeLists(FoodPlace **destList, FoodPlace *srcList)
{
    FoodPlace *tmp;

    if(srcList == NULL)
        return;

    while(srcList != NULL)
    {
        tmp = srcList;
        srcList = srcList->next;
        tmp->next = NULL;
        tmp->prev = NULL;
        insertNodeInFront(destList, tmp);
    }
}
/*
 * Given list, return the number of nodes in the list
 */
int getSizeOfList(FoodPlace *list)
{
    int count=0;
    while(list != NULL)
    {
        count++;
        list = list->next;
    }

    return count;
}
