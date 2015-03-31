#include "FileIO.h"
#include "Constants.h"
#include "FoodPicker.h"
#include "Globals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Reads in filename and populates array foodOptions with contents of file.
 * filename format <location name (string)>:<weight (int)>:<location key (int)>
 */
int getFoodOptions(char *filename, FoodPlace *foodOptions)
{
    FoodPlace *currPlace;
    char line[STRING_LENGTH];
    char *subStr;
    int count = 0;
    int j;
    FILE *fp = fopen(filename, "r");

    if(fp == NULL)
        return -1;

    while(fgets(line, sizeof(line), fp) != NULL)
    {
        line[STRING_LENGTH-1] = '\0';
        currPlace = &foodOptions[count++];

        //Strip newline
        line[strlen(line)-1] = '\0';

        subStr = strtok(line,":");
        strcpy(currPlace->name, subStr);
        subStr = strtok(NULL,":");
        currPlace->rank = atoi(subStr);
        subStr = strtok(NULL,":");
        currPlace->location = atoi(subStr);
        if(count > FOOD_LENGTH)
            break;
    }
    fclose(fp);

    for(j=1; j<count;j++)
    {
        foodOptions[j].next = &foodOptions[j+1];
        foodOptions[j].prev= &foodOptions[j-1];
    }

    foodOptions[0].prev = NULL;
    foodOptions[0].next = &foodOptions[1];
    foodOptions[count-1].next = NULL;
    return count;
}

/*
 * Give string userInput, return command that matches userInput
 */
Command parseUserInput(char *userInput)
{
    int inputLen = strlen(userInput);
    int j;

    if(inputLen == 0)
        return g_commands[COMMAND_COUNT];

    for(j=0; j<COMMAND_COUNT; j++)
    {
        if(strncmp(g_commands[j].longCommand, userInput, inputLen) == 0
           || strncmp(g_commands[j].shortCommand, userInput, inputLen) == 0)
            return g_commands[j];
    }

    return g_commands[COMMAND_COUNT];
}

void printWelcome(int socket)
{
    sendMessage(socket, "   _____           _    _____ _     _\n");
    sendMessage(socket, "  |   __|___ ___ _| |  |  _  |_|___| |_ ___ ___\n"); 
    sendMessage(socket, "  |   __| . | . | . |  |   __| |  _| '_| -_|  _|\n");
    sendMessage(socket, "  |__|  |___|___|___|  |__|  |_|___|_,_|___|_|\n");
    sendMessage(socket, "Welcome to Food Picker!\n");
    sendMessage(socket, "Enter h for a list of commands\n");
}

/*
 * Print all the names of list history
 */
void printHistory(int socket, FoodPlace *history)
{
    FoodPlace *tmp = history;
    char buffer[STRING_LENGTH];
    int count = 1;
    while(tmp != NULL)
    {
        sprintf(buffer, "%d: %s\n", count++, tmp->name);
        sendMessage(socket, buffer);
        tmp = tmp->next;
    }
}

void sendMessage(int socket, char *msg)
{
    write(socket, msg , strlen(msg));
}

void cleanInput(char *str)
{
    int length = strlen(str);
    int j;
    for(j = 0; j <= length; j++)
    {
        if((str[j] < 'A' || str[j] > 'z'))
            str[j] = '\0';
    }
}
