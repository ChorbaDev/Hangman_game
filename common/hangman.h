//
// Created by omar on 08/01/2022.
//

#ifndef PRJ_HANGMANC_HANGMAN_H
#define PRJ_HANGMANC_HANGMAN_H

#include "playerInfo.h"
#include "stream.h"

typedef struct
{
    infoStruct players[PLAYERS_AMOUNT];
} gameConfigStruct;

gameConfigStruct initGame();
char * getDashedWord(char * word);
void runGame(char * word);
void displayHangman(int length,int fdSocket);
int checkAnswer(char letterTyped, char * word, char * dashedWord);
#endif //PRJ_HANGMANC_HANGMAN_H
