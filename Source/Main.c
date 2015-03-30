#include "FoodPicker.h"
#include "FileIO.h"
#include "Utils.h"
#include "LinkedList.h"
#include "Constants.h"
#include "Globals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

void *foodPickerMain(void *);

int main(int argc, char** argv)
{
    int listeningSocket, newSocket, *clientSocket;
    struct sockaddr_in server, client;
    char filename[STRING_LENGTH];
    char userInput[STRING_LENGTH];
    int serverSize;

    if(argc != 2)
    {
        fprintf(stderr, "%s <input file>\n", argv[0]);
        return 1;
    }

    strcpy(filename, argv[1]);
    if((numOptions = getFoodOptions(filename, foodOptions))<=0)
    {
        fprintf(stderr, "Error reading %s\n", filename);
        return 1;
    }
    srand(time(NULL));
    foodList = &foodOptions[0];
    historyCount = 0;
    historyList = NULL;

    //Initialize socket
    if((listeningSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        fprintf(stderr, "Could not initialize socket\n");
        return 1;
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    if(bind(listeningSocket, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        fprintf(stderr, "Could not bind socket\n");
        return 1;
    }

    //Allow for three pending connections at a time
    listen(listeningSocket, 3);

    printf("Listening on port %d\n", PORT);
    serverSize = sizeof(struct sockaddr_in);
    while((newSocket = accept(listeningSocket, (struct sockaddr *)&client, &serverSize)) > 0)
    {
        printf("Connection accepted from %s\n", inet_ntoa(client.sin_addr));
        pthread_t listenerThread;
         
        clientSocket = malloc(sizeof(int));
        *clientSocket = newSocket;
         
        if(pthread_create(&listenerThread, NULL, foodPickerMain, (void*) clientSocket) < 0)
        {
            perror("Could not create thread\n");
            free(clientSocket);
            return 1;
        }
    }

    fprintf(stderr, "Error accepting a connection\n");
    return 0;
}

void *foodPickerMain(void *clientSocket)
{
    int socket = *(int*)clientSocket;
    char userInput[STRING_LENGTH];
    int readSize;
    int processInput = 1;
    //Used to place winners for the COOLDOWN generates cool down period
    FoodPlace *timeoutPlaces = NULL;
    FoodPlace *readyPlaces = NULL;
    FoodPlace *secondaryWinner = NULL;
    FoodPlace *winner = NULL;
    Command userCommand;
    char buffer[STRING_LENGTH];
    int receiveCount = 0;
    int j;

    printWelcome(socket);

    while(processInput)
    {
        sendMessage(socket, ">");
        receiveCount = recv(socket, userInput, STRING_LENGTH, 0);

        if(receiveCount == 0)
            processInput = 0;
        else
        {
            userInput[STRING_LENGTH-1] = '\0';

            //Remove newline
            cleanInput(userInput);
            userCommand = parseUserInput(userInput);
            switch(userCommand.type)
            {
                case GENERATE_CHOICE:
                    winner = calculateWinner(&foodList, numOptions);
                    secondaryWinner = calculateSecondaryWinner(&foodList, winner);
                    winner->coolDown = 0;
                    insertNodeInFront(&timeoutPlaces, winner);
                    incrementCoolDownTimer(timeoutPlaces);
                    readyPlaces = getReadyFoodPlaces(timeoutPlaces);
                    mergeLists(&foodList, readyPlaces);
                    insertInHistory(&historyList, historyNodes, winner, &historyCount);

                    sprintf(buffer, "%s%s\n", "You should eat at ", winner->name);
                    sendMessage(socket, buffer);
                    if(secondaryWinner != NULL)
                    {
                        sprintf(buffer, "%s%s\n", "With a secondary location of ", secondaryWinner->name);
                        sendMessage(socket, buffer);
                    }
                    numOptions--;
                    break;
                case QUIT:
                    sprintf(buffer, "%s\n", "GoodBye");
                    sendMessage(socket, buffer);
                    processInput = 0;
                    break;
                case HISTORY:
                    printHistory(socket, historyList);
                    break;
                default:
                    userCommand.function(socket, userInput);
                    break;
            }
        }
    }
    free(clientSocket);
}
