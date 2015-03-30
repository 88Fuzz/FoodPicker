#ifndef __TYPES_H__
#define __TYPES_H__
#include "Constants.h"

typedef struct Node_1
{
    char name[STRING_LENGTH];
    int location;
    int rank;
    int coolDown;
    struct Node_1 *next;
    struct Node_1 *prev;
} FoodPlace;

typedef enum
{
    GENERATE_CHOICE,
    HELP,
    HISTORY,
    QUIT,
    COMMAND_COUNT
} CommandEnum;

typedef struct Node_2
{
    CommandEnum type;
    char shortCommand[4];
    char longCommand[STRING_LENGTH];
    char description[STRING_LENGTH*5];
    void (*function)(int,char *);
} Command;

#endif
