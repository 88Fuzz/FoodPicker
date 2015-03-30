#ifndef __FILEIO_H__
#define __FILEIO_H__
#include "FoodPicker.h"

int getFoodOptions(char *, FoodPlace *);
Command parseUserInput(char *);
void printWelcome(int );
void sendMessage(int, char *);
void cleanInput(char *);
#endif
