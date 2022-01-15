#ifndef PRJ_HANGMANC_HANGMAN_H
#define PRJ_HANGMANC_HANGMAN_H

#include "playerInfo.h"
#include "stream.h"

typedef struct
{
    infoStruct players[PLAYERS_AMOUNT];
} gameConfigStruct;

gameConfigStruct initGame();
void displayHangman(int length,int fdSocket);

#endif //PRJ_HANGMANC_HANGMAN_H
