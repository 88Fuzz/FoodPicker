#ifndef __GLOBALS_H__
#define __GLOBALS_H__
#include "Types.h"
#include "Constants.h"

extern Command commands[COMMAND_COUNT];
extern FoodPlace foodOptions[FOOD_LENGTH];
extern FoodPlace historyNodes[FOOD_LENGTH];
extern FoodPlace *foodList;
extern FoodPlace *historyList;
extern int numOptions;
extern int historyCount;

#endif
