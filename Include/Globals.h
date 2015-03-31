#ifndef __GLOBALS_H__
#define __GLOBALS_H__
#include "Types.h"
#include "Constants.h"
#include <pthread.h>

extern Command g_commands[COMMAND_COUNT];
extern FoodPlace g_foodOptions[FOOD_LENGTH];
extern FoodPlace g_historyNodes[FOOD_LENGTH];
extern FoodPlace *g_foodList;
extern FoodPlace *g_historyList;
extern int g_numOptions;
extern int g_historyCount;
extern pthread_mutex_t g_lock;

#endif
