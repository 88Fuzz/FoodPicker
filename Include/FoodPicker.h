#ifndef __FOODPICKER_H__
#define __FOODPICKER_H__
#include "Constants.h"
#include "Types.h"

FoodPlace *calculateWinner(FoodPlace **, int);
FoodPlace *calculateSecondaryWinner(FoodPlace **, FoodPlace *);
void incrementCoolDownTimer(FoodPlace *);
FoodPlace *getReadyFoodPlaces(FoodPlace *);
void insertInHistory(FoodPlace **, FoodPlace *, FoodPlace *, int*);

//Commands
void helpCommand(int, char *args);
void historyCommand(int, FoodPlace *);
void invalidCommand(int, char *args);

#endif
