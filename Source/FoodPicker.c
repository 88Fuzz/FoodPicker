#include "FoodPicker.h"
#include "LinkedList.h"
#include "Globals.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * Given list of FoodPlaces foodOptions and the length of the list numOptions, return
 * a place to eat (it will be removed from the list)
 */
FoodPlace *calculateWinner(FoodPlace **foodOptions, int numOptions)
{
    FoodPlace *matchup = *foodOptions;
    FoodPlace *winners = NULL;
    FoodPlace *losers = NULL;
    int remainingOptions = numOptions;
    int pos1;
    int pos2;
    FoodPlace *place1;
    FoodPlace *place2;
    int winCount1 = 0;
    int winCount2 = 0;
    int score1 = 0;
    int score2 = 0;

    if(numOptions < 2)
    {
        *foodOptions = NULL;
        return matchup;
    }

    do
    {
        do
        {
            if(remainingOptions == 2)
            {
                pos1 = 0;
                pos2 = 1;
            }
            else
            {
                pos1 = getRandomNumber(remainingOptions);
                do
                {
                    pos2 = getRandomNumber(remainingOptions - 1);
                } while(pos1 == pos2);
            }
            place1 = getNodeFromList(&matchup, pos1);
            place2 = getNodeFromList(&matchup, pos2);

            while(winCount1 < SCORE_LIMIT && winCount2 < SCORE_LIMIT)
            {
                score1 = getRandomNumber(place1->rank);
                score2 = getRandomNumber(place2->rank);
                if(score1 > score2)
                    winCount1++;
                else if(score2 > score1)
                    winCount2++;
            }

            removeNode(&matchup, place1);
            removeNode(&matchup, place2);

            if(winCount1 == SCORE_LIMIT)
            {
                insertNodeInFront(&winners, place1);
                insertNodeInFront(&losers, place2);
            }
            else
            {
                insertNodeInFront(&winners, place2);
                insertNodeInFront(&losers, place1);
            }

            remainingOptions-=2;
            winCount1=0;
            winCount2=0;
        } while(remainingOptions>1);


        //if there is a remaining entry in matchup, move it to the winners list
        if(matchup != NULL)
            insertNodeInFront(&winners, matchup);

        matchup = winners;
        winners = NULL;

        numOptions = roundUpDivision(numOptions, 2);
        remainingOptions = numOptions;
    }while(numOptions > 1);

    *foodOptions = losers;
    return matchup;
}

/*
 * Given a list of FoodPlaces foodOptions and a FoodPlace to match a location, 
 * return a secondary eating location. Returned FoodPlace will not be removed from list
 */
FoodPlace *calculateSecondaryWinner(FoodPlace **foodOptions, FoodPlace *match)
{
    FoodPlace *nonMatchingList = NULL;
    FoodPlace *matchingList = NULL;
    FoodPlace *tmpList = *foodOptions;
    FoodPlace *tmp;
    FoodPlace *winner;
    int numOptions = 0;

    while(tmpList != NULL)
    {
        tmp = tmpList;
        tmpList = tmpList->next;
        if(tmp->location == match->location)
        {
            insertNodeInFront(&matchingList, tmp);
            numOptions++;
        }
        else
            insertNodeInFront(&nonMatchingList, tmp);
    }

    winner = calculateWinner(&matchingList, numOptions);

    //Combine the serparated lists and put them back into foodOptions
    mergeLists(&matchingList, nonMatchingList);
    insertNodeInFront(&matchingList, winner);

    *foodOptions = matchingList;

    return winner;
}

/*
 * Given list of FoodPlaces historyList, array of allocated nodes historyNodes, FoodPlace to be placed in historyList winner,
 * and the length of historyList historyCount. Place winner in historyList. historyCount will be incremented if the length of
 * historyList grows ie. max history nodes not hit
 */
void insertInHistory(FoodPlace **historyList, FoodPlace *historyNodes, FoodPlace *winner, int *historyCount)
{
    FoodPlace *tmp;
    if(*historyCount < FOOD_LENGTH)
    {
        strncpy(historyNodes[*historyCount].name, winner->name, strlen(winner->name) + 1);
        //May need to make historyList a triple pointer?
        //Or make historyList a single pointer?
        insertNodeInBack(historyList, &historyNodes[*historyCount]);
        *historyCount = *historyCount + 1;
    }
    //No more allocated nodes
    else
    {
        tmp = *historyList;
        removeNode(historyList, tmp);
        strncpy(tmp->name, winner->name, strlen(winner->name) + 1);
        insertNodeInBack(historyList, tmp);
    }
}

void helpCommand(int socket, char *args)
{
    char buffer[STRING_LENGTH*2];
    int j;
    Command currCommand;
    sendMessage(socket, "\nCOMMANDS\n");
    for(j=0; j<COMMAND_COUNT; j++)
    {
        currCommand = commands[j];
        sprintf(buffer, "%s | %s\n", currCommand.shortCommand, currCommand.longCommand);
        sendMessage(socket, buffer);
        sprintf(buffer, "   %s\n", currCommand.description);
        sendMessage(socket, buffer);
    }
}

void invalidCommand(int socket, char *args)
{
    char buffer[STRING_LENGTH*2];
    sprintf(buffer, " Unknown command: %s\n", args);
    sendMessage(socket, buffer);
}

/*
 * Given FoodPlace list, increment all coolDown Timers of elements in list
 */
void incrementCoolDownTimer(FoodPlace *list)
{
    while(list!=NULL)
    {
        list->coolDown++;
        list = list->next;
    }
}

/*
 * Give FoodPlace list, return a list of all nodes that are past the COOLDOWN timer
 */
FoodPlace *getReadyFoodPlaces(FoodPlace *list)
{
    FoodPlace *tmp;
    FoodPlace *readyPlaces = NULL;
    while(list != NULL)
    {
        tmp = list;
        list = list->next;
        if(tmp->coolDown > COOLDOWN)
        {
            removeNode(&readyPlaces, tmp);
            insertNodeInFront(&readyPlaces, tmp);
        }
    }
    return readyPlaces;
}
