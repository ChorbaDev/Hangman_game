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
void wrongGuess(int mistake);
/// PRITING BASIC STRUCTURE OF GALLOWS
void Potence ();

/// PRITING HEAD
void Head ( );

/// PRITING BODY
void Body ( );

/// PRITING RIGHT ARM
void rArm ( );

/// PRITING LEFT ARM
void lArm ( );

/// PRITING RIGHT LEG
void rLeg ( );

/// PRITING LEFT LEG
void lLeg ( );

void perdu();
void potenceGagnant();
#endif //PRJ_HANGMANC_HANGMAN_H
