//
// Created by omar on 08/01/2022.
//

#ifndef PRJ_HANGMANC_HANGMAN_H
#define PRJ_HANGMANC_HANGMAN_H

#include "../common/playerInfo.h"
#include "../common/stream.h"

typedef struct
{
    infoStruct players[PLAYERS_AMOUNT];
} gameConfigStruct;

gameConfigStruct initGame();
int16_t getIndexWhenCode(gameConfigStruct *, char *);
#endif //PRJ_HANGMANC_HANGMAN_H
