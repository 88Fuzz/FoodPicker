#ifndef __LINKED_LIST__
#define __LINKED_LIST__
#include "FoodPicker.h"

FoodPlace *getNodeFromList(FoodPlace **, int);
void removeNode(FoodPlace **, FoodPlace *);
void insertNodeInFront(FoodPlace **, FoodPlace *);
void insertNodeInBack(FoodPlace **, FoodPlace *);
void mergeLists(FoodPlace **, FoodPlace *);

#endif
