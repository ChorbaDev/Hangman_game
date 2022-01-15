//
// Created by omar on 08/01/2022.
//

#ifndef PRJ_HANGMANC_PLAYERINFO_H
#define PRJ_HANGMANC_PLAYERINFO_H

#define CODE_LENGTH 10
#define PLAYERS_AMOUNT 10

typedef struct
{
    int  wins;
    int connectionID;
} infoStruct;

infoStruct initInfo();

int existAt(int id, infoStruct players[]);
#endif //PRJ_HANGMANC_PLAYERINFO_H
