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
void runGame(char * word);
void displayHangman(int length,int fdSocket);
bool existIn(char i, char errors[]);
int randomNumber(int from, int to);
char **readFile(int fileDescriptor, int *wordsTotal);
int openFile(const char *path);
int checkAnswer(char letterTyped, char * word, char * dashedWord);
#endif //PRJ_HANGMANC_HANGMAN_H
