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
int openFile(const char * path);
char ** readFile(int fileDescriptor, int * wordsTotal);
int randomNumber(int from, int to);
char * getDashedWord(char * word);
void runGame(char * word);
void displayHangman(int length,int fdSocket);
int checkAnswer(char letterTyped, char * word, char * dashedWord);
int16_t getIndexWhenCode(gameConfigStruct *, char *);
#endif //PRJ_HANGMANC_HANGMAN_H
