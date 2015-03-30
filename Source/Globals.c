#include "Types.h"
#include "FoodPicker.h"
#include <stdlib.h>

Command commands[COMMAND_COUNT+1] = {
        {GENERATE_CHOICE, "g", "generate", "Generate a place to eat. Will show up in history and add recent location back into availability list.", NULL},
        {HELP, "h", "help", "What you are looking at.", &helpCommand},
        {HISTORY, "hi", "history", "List of all previous restaurants.", NULL},
        {QUIT, "q", "quit", "Quit the program.", NULL},
        {COMMAND_COUNT, "", "", "", &invalidCommand}
};

FoodPlace foodOptions[FOOD_LENGTH];
FoodPlace historyNodes[FOOD_LENGTH];
FoodPlace *foodList;
FoodPlace *historyList;
int numOptions;
int historyCount;

