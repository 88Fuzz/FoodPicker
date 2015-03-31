#include "Types.h"
#include "FoodPicker.h"
#include <stdlib.h>

Command g_commands[COMMAND_COUNT+1] = {
        {GENERATE_CHOICE, "g", "generate", "Generate a place to eat. Will show up in history and add recent location back into availability list.", NULL},
        {HELP, "h", "help", "What you are looking at.", &helpCommand},
        {HISTORY, "hi", "history", "List of all previous restaurants.", NULL},
        {QUIT, "q", "quit", "Quit the program.", NULL},
        {COMMAND_COUNT, "", "", "", &invalidCommand}
};

FoodPlace g_foodOptions[FOOD_LENGTH];
FoodPlace g_historyNodes[FOOD_LENGTH];
FoodPlace *g_foodList;
FoodPlace *g_historyList;
int g_numOptions;
int g_historyCount;
pthread_mutex_t g_lock;

