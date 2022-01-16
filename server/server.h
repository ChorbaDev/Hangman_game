#ifndef PRJ_HANGMANC_SERVER_H
#define PRJ_HANGMANC_SERVER_H
#include <netinet/in.h>
#include <stdbool.h>
#include "../common/Hangman/hangman.c"
#include "../common/Stream/stream.c"

typedef struct
{
    int communicationID;
    struct sockaddr_in connectedAddr;
    gameConfigStruct *gameConfig;
} connectionStruct;

void *connectionThread(void *);
void clientConnected(int, gameConfigStruct *);
int existAt(int id, infoStruct players[PLAYERS_AMOUNT]);

#endif //PRJ_HANGMANC_SERVER_H
