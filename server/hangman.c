//
// Created by omar on 08/01/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "semaphore.h"
#include "hangman.h"
#include "server.h"
#include "../common/playerInfo.c"
#include "../common/stream.h"

/**
 * Initialize a concertConfigStruct instance
 * @return the concert configuration
 */
gameConfigStruct initGame()
{
    gameConfigStruct gameConfig = *(gameConfigStruct *)malloc(sizeof(gameConfigStruct)); // allocate the size of a gameConfigStruct
    for (int i = 0; i < PLAYERS_AMOUNT; i++)                                                 // init every player of the array
        gameConfig.players[i] = initInfo();

    return gameConfig;
}


/**
 * Return the index or -1 of the seat that have a specified code
 * @param config the concert configuration
 * @param code the code that is searched
 * @return the index
 */
int16_t getIndexWhenCode(gameConfigStruct *config, char *code)
{
    sem_wait(&semaphore); // block the access to the gameConfig
    for (int i = 0; i < PLAYERS_AMOUNT; i++)
        if (strcmp(config->players[i].code, code) == 0) // if the code match
        {
            sem_post(&semaphore); // free the access to the concertConfig
            return i;             // we return the number of the seat
        }
    sem_post(&semaphore); // free the access to the concertConfig

    return -1; // default return
}
