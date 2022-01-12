//
// Created by omar on 08/01/2022.
//

#ifndef PRJ_HANGMANC_PLAYERINFO_H
#define PRJ_HANGMANC_PLAYERINFO_H

#define NAME_SIZE 100
#define CODE_LENGTH 10
#define PLAYERS_AMOUNT 3

typedef struct
{
    int  wins;
    char code[CODE_LENGTH + 1];
} infoStruct;

infoStruct initInfo();
void generateCode(char *);
int randomInt(int min, int max);
#endif //PRJ_HANGMANC_PLAYERINFO_H
